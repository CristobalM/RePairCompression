//
// Created by cristobal on 31-10-21.
//

#include "RepairCoder.hpp"
#include "EntryPair.hpp"
#include "TranslateTable.hpp"
#include "ValuePair.hpp"
#include <cstddef>
#include <iostream>
#include <unordered_set>

namespace RePairCompression {
bool RepairCoder::done() { return priorityQueue.getActivePosition() <= 0; }
void RepairCoder::step() {
  auto *record = priorityQueue.pop();
  auto replacingPair = record->valuePair;

  auto *entry = &entriesList[record->firstEntryPosition];
  int firstPosition = record->firstEntryPosition;
  int prevPosition = firstPosition;
  int replacingSymbol = nextSymbol++;
  translateTable.addTranslation(replacingPair, replacingSymbol);
  while (entry) {
    auto nextPosition = entry->right;

    auto *otherEntry = getRight(entry);
    auto otherEntryPosition = getPosition(otherEntry);

    if (nextPosition == otherEntryPosition) {
      nextPosition = otherEntry->right;
    }

    auto *leftEntry = getLeft(entry);
    auto *rightEntry = getRight(otherEntry);

    EntryPair leftEntryPair(leftEntry, entry);
    EntryPair rightEntryPair(otherEntry, rightEntry);
    EntryPair replacingEntryPair(entry, otherEntry);

    if (!matchingPair(leftEntryPair, replacingEntryPair))
      decreaseFrequency(leftEntryPair);
    if (!matchingPair(rightEntryPair, replacingEntryPair))
      decreaseFrequency(rightEntryPair);

    replacePair(replacingEntryPair, replacingSymbol);

    leftEntry = getLeft(entry);
    otherEntry = getRight(entry);

    EntryPair newLeftEntryPair(leftEntry, entry);
    EntryPair newRightEntryPair(entry, otherEntry);

    increaseFrequency(newLeftEntryPair);
    increaseFrequency(newRightEntryPair);

    debugPrintCurrentSequence();

    if (nextPosition <= prevPosition || nextPosition < 0)
      break;
    entry = &entriesList[nextPosition];
    prevPosition = nextPosition;
  }

  debugCurrentStep++;
}

void RepairCoder::replacePair(EntryPair replacingEntryPair, int newSymbol) {
  Entry *leftEntry = replacingEntryPair.first;
  Entry *rightEntry = replacingEntryPair.second;
  if (false) {
    std::cout << "Replacing pair ("
              << (leftEntry ? std::to_string(leftEntry->value) : "NULL") << ", "
              << (rightEntry ? std::to_string(rightEntry->value) : "NULL")
              << ") for " << newSymbol << " at position "
              << getPosition(leftEntry) << std::endl;
  }

  int currentPos = getPosition(leftEntry);
  leftEntry->value = newSymbol;

  // thread right entry
  {
    auto rightPos = leftEntry->right;
    if (rightPos == getPosition(rightEntry)) {
      rightPos = rightEntry->right;
    }

    auto leftPos = leftEntry->left;
    if (leftPos == getPosition(rightEntry)) {
      leftPos = currentPos;
    }

    auto *toRightEntry = rightPos != -1 ? &entriesList[rightPos] : nullptr;
    auto *toLeftEntry = leftPos != -1 ? &entriesList[leftPos] : nullptr;

    if (toRightEntry) {
      toRightEntry->left = leftPos;
    }

    if (toLeftEntry) {
      toLeftEntry->right = rightPos;
    }
  }

  // thread nulls
  {
    auto *rightAdjacentEntry = getRight(rightEntry);
    rightEntry->value = -1;
    rightEntry->left =
        rightAdjacentEntry ? getPosition(rightAdjacentEntry) : -1;
    rightEntry->right = currentPos;

    if (rightAdjacentEntry) {
      auto rightAdjacentEntryPosition = getPosition(rightAdjacentEntry);
      auto adjacentLeftTRPos = rightAdjacentEntryPosition - 1;
      auto *adjacentLeftTREntry = &entriesList[adjacentLeftTRPos];
      if (adjacentLeftTREntry->value == -1 &&
          adjacentLeftTREntry != rightEntry) {
        adjacentLeftTREntry->right = currentPos;
      }
    }

    auto *leftAdjacentEntry = getLeft(rightEntry);
    if (leftAdjacentEntry) {
      auto leftAdjacentEntryPosition = getPosition(leftAdjacentEntry);
      auto adjacentRightTLPos = leftAdjacentEntryPosition + 1;
      auto *adjacentRightTLEntry = &entriesList[adjacentRightTLPos];
      if (adjacentRightTLEntry->value == -1) {
        adjacentRightTLEntry->left = rightEntry->left;
      }
    }
  }
  // end thread nulls
}

void RepairCoder::decreaseFrequency(EntryPair entryPair) {
  Entry *leftEntry = entryPair.first;
  Entry *rightEntry = entryPair.second;
  if (!leftEntry || !rightEntry || leftEntry->value == -1 ||
      rightEntry->value == -1 ||
      getPosition(leftEntry) >= getPosition(rightEntry))
    return;
  auto valuePair = ValuePair(leftEntry->value, rightEntry->value);

  auto *record = hashTable.getRecord(valuePair);
  //
  //  if (!record)
  //    throw std::runtime_error("record can't not exist");
  if (!record)
    return;

  auto leftPosition = getPosition(leftEntry);

  if (leftPosition == record->firstEntryPosition) {
    auto nextEntryPosition = leftEntry->right;
    if (nextEntryPosition != -1 && nextEntryPosition != leftPosition) {
      auto *nextEntry = &entriesList[nextEntryPosition];
      if (nextEntry->value != -1) {
        record->firstEntryPosition = nextEntryPosition;
      }
    }
  }

  auto toLeftPosition = leftEntry->left;
  auto toRightPosition = leftEntry->right;
  Entry *toLeft = nullptr;
  Entry *toRight = nullptr;
  if (toLeftPosition != -1) {
    toLeft = &entriesList[toLeftPosition];
  }
  if (toRightPosition != -1) {
    toRight = &entriesList[toRightPosition];
  }
  if (toLeft)
    toLeft->right = toRight ? getPosition(toRight) : -1;
  if (toRight)
    toRight->left = toLeft ? getPosition(toLeft) : -1;

  priorityQueue.decreaseFrequency(valuePair);
}

int RepairCoder::getPosition(Entry *entry) {
  return (int)(entry - &entriesList[0]);
}

Entry *RepairCoder::getLeft(Entry *entry) {
  int currentPosition = getPosition(entry);
  if (currentPosition == 0)
    return nullptr;
  auto *leftEntry = &entriesList[currentPosition - 1];
  if (leftEntry->value ==
      -1) { // was replaced by repair, find leftEntry extreme threaded
    int leftExtremePos = leftEntry->right;
    if (leftExtremePos == -1 || leftExtremePos >= currentPosition - 1)
      return nullptr;
    return &entriesList[leftExtremePos];
  }
  return leftEntry;
}
Entry *RepairCoder::getRight(Entry *entry) {
  if (!entry)
    return nullptr;
  int currentPosition = getPosition(entry);
  if (currentPosition == (int)entriesList.size() - 1)
    return nullptr;
  auto *rightEntry = &entriesList[currentPosition + 1];
  if (rightEntry->value ==
      -1) { // was replaced by repair, find rightEntry extreme threaded
    int rightExtremePos = rightEntry->left;
    if (rightExtremePos == -1 || rightExtremePos <= currentPosition + 1)
      return nullptr;
    return &entriesList[rightExtremePos];
  }
  return rightEntry;
}

TranslateTable RepairCoder::getTranslateTable() { return translateTable; }
RepairCoder::RepairCoder(EntriesList &entriesList, HashTable &hashTable,
                         PriorityQueue &priorityQueue)
    : entriesList(entriesList), hashTable(hashTable),
      priorityQueue(priorityQueue), debugCurrentStep(0) {
  initStructures();
  debugPrintCurrentSequence();
}
void RepairCoder::initStructures() {
  int maxSymbol = 0;
  for (int i = 0; i < (int)entriesList.size() - 1; i++) {
    auto *entry = &entriesList[i];
    auto *nextEntry = &entriesList[i + 1];
    increasePairFrequencyInit((int)i, entry, nextEntry);
    maxSymbol = std::max(maxSymbol, entry->value);

    ValuePair valuePair(entry->value, nextEntry->value);
    auto *record = hashTable.getRecord(valuePair);
    auto *firstEntry = &entriesList[record->firstEntryPosition];
    int lastEntryPosition;
    if (firstEntry->left >= 0) {
      lastEntryPosition = firstEntry->left;
    } else {
      lastEntryPosition = i;
    }
    auto *lastEntry = &entriesList[lastEntryPosition];
    lastEntry->right = i;
    firstEntry->left = i;
    entry->left = lastEntryPosition;
    entry->right = record->firstEntryPosition;
  }
  maxSymbol = std::max(maxSymbol, entriesList[entriesList.size() - 1].value);
  nextSymbol = maxSymbol + 1;
  translateTable.setFirstSymbol(nextSymbol);
  std::unordered_set<ValuePair, ValuePair::HashFunction> inQueue;
  for (size_t i = 0; i < entriesList.size() - 1; i++) {
    auto *entry = &entriesList[i];
    auto *nextEntry = &entriesList[i + 1];
    ValuePair valuePair(entry->value, nextEntry->value);
    if (inQueue.find(valuePair) == inQueue.end()) {
      insertToPriorityQueue(entry, nextEntry);
      inQueue.insert(valuePair);
    }
  }
}

void RepairCoder::increasePairFrequencyInit(int leftEntryPosition,
                                            Entry *leftEntry,
                                            Entry *rightEntry) {
  ValuePair valuePair(leftEntry->value, rightEntry->value);
  hashTable.increaseFrequency(leftEntryPosition, valuePair);
}
void RepairCoder::insertToPriorityQueue(Entry *leftEntry, Entry *rightEntry) {
  auto *record =
      hashTable.getRecord(ValuePair(leftEntry->value, rightEntry->value));
  priorityQueue.insertRecord(record);
}
void RepairCoder::increaseFrequency(EntryPair entryPair) {
  Entry *leftEntry = entryPair.first;
  Entry *rightEntry = entryPair.second;

  if ((!rightEntry || rightEntry->value == -1) && leftEntry &&
      leftEntry->value != -1) {
    leftEntry->right = -1;
    leftEntry->left = -1;
    return;
  }

  if (!leftEntry || !rightEntry || leftEntry->value == -1 ||
      rightEntry->value == -1 ||
      getPosition(leftEntry) >= getPosition(rightEntry))
    return;

  int position = getPosition(leftEntry);
  ValuePair valuePair(leftEntry->value, rightEntry->value);

  // does not increase frequency
  bool created = false;
  auto *record =
      hashTable.createRecordIfNotExists(position, valuePair, created);

  if (!created) {
    // record existed before
    priorityQueue.increaseFrequency(valuePair);
  } else {
    record->frequency++;
    priorityQueue.insertRecord(record);
  }

  int firstEntryPosition = record->firstEntryPosition;
  auto *firstEntry = &entriesList[firstEntryPosition];
  // we just created it
  if (created) {
    firstEntry->left = firstEntryPosition;
    firstEntry->right = firstEntryPosition;
    // thread with itself, and nothing more to be done
    return;
  }

  int lastEntryPosition = firstEntry->left;
  auto *lastEntry = &entriesList[lastEntryPosition];

  int currentPosition = getPosition(leftEntry);

  lastEntry->right = currentPosition;
  leftEntry->left = lastEntryPosition;
  leftEntry->right = firstEntryPosition;
  firstEntry->left = currentPosition;
}
bool RepairCoder::notSamePair(Entry *p1a, Entry *p1b, Entry *p2a, Entry *p2b) {
  if (!p1a || !p1b || !p2a || !p2b)
    return false;
  return !(p1a->value == p2a->value && p1b->value == p2b->value);
}
void RepairCoder::debugPrintCurrentSequence() {
  return;
  for (size_t i = 0; i < entriesList.size(); i++) {
    auto value = entriesList[i].value;
    std::cout << "(" << value << ", " << entriesList[i].left << ", "
              << entriesList[i].right << "); ";
  }
  std::cout << std::endl;
}
bool RepairCoder::matchingPair(EntryPair left, EntryPair right) {
  return (!left.first || !left.second || !right.first || !right.second ||
          left.first->value == -1 || left.second->value == -1 ||
          right.first->value == -1 || right.second->value == -1) ||
         (left.first->value == right.first->value &&
          left.second->value == right.second->value);
}

std::vector<int> RepairCoder::getFlattenedCompressed() {
  auto *entry = &entriesList[0];
  if (entry->value == -1)
    throw std::runtime_error("Badly compressed entries array");
  std::vector<int> result;
  while (entry) {
    result.push_back(entry->value);
    auto *nextEntry = getRight(entry);
    if (getPosition(nextEntry) < getPosition(entry))
      break;
    entry = nextEntry;
  }
  return result;
}

} // namespace RePairCompression
