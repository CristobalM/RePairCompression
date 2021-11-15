//
// Created by cristobal on 31-10-21.
//

#include "RepairCoder.hpp"
#include "TranslateTable.hpp"
#include <iostream>
#include <unordered_set>

namespace RePairCompression {
bool RepairCoder::done() { return priorityQueue.getActivePosition() <= 0; }
void RepairCoder::step() {
  auto *record = priorityQueue.pop();
  Record recordTmp = *record;
  hashTable.deleteRecord(record->leftValue, record->rightValue);
  record = &recordTmp;

  int recordLeftValue = record->leftValue;
  int recordRightValue = record->rightValue;

  int entryPosition = record->firstEntryPosition;

  int firstPosition = record->firstEntryPosition;
  int prevPosition = firstPosition;
  int replacingSymbol = nextSymbol++;
  translateTable.addTranslation(recordLeftValue, recordRightValue,
                                replacingSymbol);
  while (entryPosition >= 0) {
    //    debugTotalSteps++;
    auto &entryConnectorPair = entriesList.connectors[entryPosition];
    auto nextPosition = entryConnectorPair.right;

    auto otherEntryPosition = getRight(entryPosition);
    auto &otherEntryConnectorPair = entriesList.connectors[otherEntryPosition];

    if (nextPosition == otherEntryPosition) {
      nextPosition = otherEntryConnectorPair.right;
    }

    auto leftPosition = getLeft(entryPosition);
    auto rightPosition = getRight(otherEntryPosition);
    //
    //    EntryPair leftEntryPair(leftPosition, entryPosition);
    //    EntryPair rightEntryPair(otherEntryPosition, rightPosition);
    //    EntryPair replacingEntryPair(entryPosition, otherEntryPosition);

    if (!matchingPair(leftPosition, entryPosition, recordLeftValue,
                      recordRightValue))
      decreaseFrequency(leftPosition, entryPosition);
    if (!matchingPair(otherEntryPosition, rightPosition, recordLeftValue,
                      recordRightValue))
      decreaseFrequency(otherEntryPosition, rightPosition);

    replacePair(entryPosition, otherEntryPosition, replacingSymbol);

    leftPosition = getLeft(entryPosition);
    otherEntryPosition = getRight(entryPosition);
    //
    //    EntryPair newLeftEntryPair(leftPosition, entryPosition);
    //    EntryPair newRightEntryPair(entryPosition, otherEntryPosition);

    increaseFrequency(leftPosition, entryPosition);
    increaseFrequency(entryPosition, otherEntryPosition);

    //    debugPrintCurrentSequence();

    if (nextPosition <= prevPosition || nextPosition < 0)
      break;
    entryPosition = nextPosition;
    prevPosition = nextPosition;
  }

  //  debugCurrentStep++;
}

void RepairCoder::replacePair(int leftEntryPosition, int rightEntryPosition,
                              int newSymbol) {
  auto &leftEntryConnectorPair = entriesList.connectors[leftEntryPosition];
  auto &rightEntryConnectorPair = entriesList.connectors[rightEntryPosition];

  setValue(leftEntryPosition, newSymbol);
  // thread right entry
  {
    auto rightPos = leftEntryConnectorPair.right;
    if (rightPos == rightEntryPosition) {
      rightPos = rightEntryConnectorPair.right;
    }

    auto leftPos = leftEntryConnectorPair.left;
    if (leftPos == rightEntryPosition) {
      leftPos = leftEntryPosition;
    }

    if (rightPos >= 0) {
      auto &toRightEntryConnectorPair = entriesList.connectors[rightPos];
      toRightEntryConnectorPair.left = leftPos;
    }

    if (leftPos >= 0) {
      auto &toLeftEntryConnectorPair = entriesList.connectors[leftPos];
      toLeftEntryConnectorPair.right = rightPos;
    }
  }

  // thread nulls
  {
    auto rightAdjacentEntryPosition = getRight(rightEntryPosition);
    setValue(rightEntryPosition, -1);
    rightEntryConnectorPair.left = rightAdjacentEntryPosition;
    rightEntryConnectorPair.right = leftEntryPosition;

    if (rightAdjacentEntryPosition >= 0) {
      auto adjacentLeftTRPos = rightAdjacentEntryPosition - 1;
      auto &adjacentLeftTREntryConnectorPair =
          entriesList.connectors[adjacentLeftTRPos];
      auto adjacentLeftTREntryValue = getValue(adjacentLeftTRPos);
      if (adjacentLeftTREntryValue == -1 &&
          adjacentLeftTRPos != rightEntryPosition) {
        adjacentLeftTREntryConnectorPair.right = leftEntryPosition;
      }
    }

    auto leftAdjacentEntryPosition = getLeft(rightEntryPosition);
    if (leftAdjacentEntryPosition >= 0) {
      auto adjacentRightTLPos = leftAdjacentEntryPosition + 1;
      auto adjacentRightTLEntryValue =
          adjacentRightTLPos < (int)entriesList.values.size()
              ? getValue(adjacentRightTLPos)
              : -1;
      if (adjacentRightTLEntryValue == -1) {
        auto &adjacentRightTLEntryConnectorPair =
            entriesList.connectors[adjacentRightTLPos];
        adjacentRightTLEntryConnectorPair.left = rightEntryConnectorPair.left;
      }
    }
  }
  // end thread nulls
}

void RepairCoder::decreaseFrequency(int leftEntryPosition,
                                    int rightEntryPosition) {
  if (leftEntryPosition < 0 || rightEntryPosition < 0)
    return;
  auto leftValue = getValue(leftEntryPosition);
  auto rightValue = getValue(rightEntryPosition);
  if (leftValue == -1 || rightValue == -1 ||
      leftEntryPosition >= rightEntryPosition)
    return;

  auto *record = hashTable.getRecord(leftValue, rightValue);

  auto &leftEntryConnectorPair = entriesList.connectors[leftEntryPosition];
  if (leftEntryPosition == record->firstEntryPosition) {
    auto nextEntryPosition = leftEntryConnectorPair.right;
    if (nextEntryPosition != -1 && nextEntryPosition != leftEntryPosition) {
      auto nextEntryValue = getValue(nextEntryPosition);
      if (nextEntryValue != -1) {
        record->firstEntryPosition = nextEntryPosition;
      }
    }
  }

  auto toLeftPosition = leftEntryConnectorPair.left;
  auto toRightPosition = leftEntryConnectorPair.right;

  if (toLeftPosition != -1) {
    auto &toLeftCP = entriesList.connectors[toLeftPosition];
    toLeftCP.right = toRightPosition;
  }

  if (toRightPosition != -1) {
    auto &toRightCP = entriesList.connectors[toRightPosition];
    toRightCP.left = toLeftPosition;
  }

  priorityQueue.decreaseFrequency(record);
}

int RepairCoder::getLeft(int entryPosition) {
  if (entryPosition == 0)
    return -1;
  auto leftPosition = entryPosition - 1;
  auto leftEntryValue = getValue(leftPosition);
  auto &leftEntryConnectorPair = entriesList.connectors[leftPosition];
  if (leftEntryValue ==
      -1) { // was replaced by repair, find leftEntry extreme threaded
    int leftExtremePos = leftEntryConnectorPair.right;
    if (leftExtremePos == -1 || leftExtremePos >= leftPosition)
      return -1;
    return leftExtremePos;
  }
  return leftPosition;
}
int RepairCoder::getRight(int entryPosition) {
  if (entryPosition < 0)
    return -1;
  if (entryPosition == (int)entriesList.values.size() - 1)
    return -1;
  int rightEntryPosition = entryPosition + 1;
  int rightEntryValue = getValue(rightEntryPosition);
  auto &rightEntryConnectorPair = entriesList.connectors[rightEntryPosition];
  if (rightEntryValue ==
      -1) { // was replaced by repair, find rightEntry extreme threaded
    int rightExtremePos = rightEntryConnectorPair.left;
    if (rightExtremePos == -1 || rightExtremePos <= rightEntryPosition)
      return -1;
    return rightExtremePos;
  }
  return rightEntryPosition;
}

TranslateTable RepairCoder::getTranslateTable() { return translateTable; }
RepairCoder::RepairCoder(EntriesList &entriesList, HashTable &hashTable,
                         PriorityQueue &priorityQueue)
    : entriesList(entriesList), hashTable(hashTable),
      priorityQueue(priorityQueue), nextSymbol(256) {
  initStructures();
}
void RepairCoder::initStructures() {
  int maxSymbol = 0;
  for (int i = 0; i < (int)entriesList.values.size() - 1; i++) {
    int currentEntryPosition = i;
    int nextEntryPosition = i + 1;
    int currentEntryValue = getValue(currentEntryPosition);
    int nextEntryValue = getValue(nextEntryPosition);
    auto &currentEntryPairConnector =
        entriesList.connectors[currentEntryPosition];

    auto *record = hashTable.increaseFrequency(
        currentEntryPosition, currentEntryValue, nextEntryValue);
    maxSymbol = std::max(maxSymbol, currentEntryValue);
    int firstEntryPosition = record->firstEntryPosition;

    auto &firstEntryPairConnector = entriesList.connectors[firstEntryPosition];
    int lastEntryPosition;
    if (firstEntryPairConnector.left >= 0) {
      lastEntryPosition = firstEntryPairConnector.left;
    } else {
      lastEntryPosition = currentEntryPosition;
    }
    auto &lastEntryPairConnector = entriesList.connectors[lastEntryPosition];
    lastEntryPairConnector.right = currentEntryPosition;
    firstEntryPairConnector.left = currentEntryPosition;
    currentEntryPairConnector.left = lastEntryPosition;
    currentEntryPairConnector.right = record->firstEntryPosition;
  }

  maxSymbol = std::max(maxSymbol, getValue((int)entriesList.values.size() - 1));
  nextSymbol = maxSymbol + 1;
  translateTable.setFirstSymbol(nextSymbol);
  auto kvIterator = hashTable.getHTable().startIteration();
  while (kvIterator.hasNext()) {
    auto kv = kvIterator.next();

    insertToPriorityQueue(kv.record->leftValue, kv.record->rightValue);
  }
}

void RepairCoder::insertToPriorityQueue(int leftValue, int rightValue) {
  auto *record = hashTable.getRecord(leftValue, rightValue);
  priorityQueue.insertRecord(record);
}
void RepairCoder::increaseFrequency(int leftEntryPosition,
                                    int rightEntryPosition) {
  // totalIncFreq++;

  if (leftEntryPosition < 0 || rightEntryPosition < 0)
    return;

  int leftEntryValue = getValue(leftEntryPosition);
  int rightEntryValue = getValue(rightEntryPosition);

  if (leftEntryValue == -1 || rightEntryValue == -1 ||
      leftEntryPosition >= rightEntryPosition)
    return;

  auto &leftEntryConnectorPair = entriesList.connectors[leftEntryPosition];

  // does not increase frequency
  bool created = false;
  auto *record = hashTable.createRecordIfNotExists(
      leftEntryPosition, leftEntryValue, rightEntryValue, created);

  if (!created) {
    // record existed before
    priorityQueue.increaseFrequency(record);
  } else {
    record->frequency++;
    priorityQueue.insertRecord(record);
  }

  int firstEntryPosition = record->firstEntryPosition;
  auto &firstEntryConnectorPair = entriesList.connectors[firstEntryPosition];
  // we just created it
  if (created) {
    firstEntryConnectorPair.left = firstEntryPosition;
    firstEntryConnectorPair.right = firstEntryPosition;
    // thread with itself, and nothing more to be done
    return;
  }

  int lastEntryPosition = firstEntryConnectorPair.left;
  auto &lastEntryConnectorPair = entriesList.connectors[lastEntryPosition];

  lastEntryConnectorPair.right = leftEntryPosition;
  leftEntryConnectorPair.left = lastEntryPosition;
  leftEntryConnectorPair.right = firstEntryPosition;
  firstEntryConnectorPair.left = leftEntryPosition;
}

bool RepairCoder::matchingPair(int leftFirstPos, int leftSecondPos,
                               int replacingLeft, int replacingRight) {
  if (leftFirstPos < 0 || leftSecondPos < 0)
    return true;
  auto leftF = getValue(leftFirstPos);
  if (leftF == -1)
    return true;
  auto leftS = getValue(leftSecondPos);
  if (leftS == -1)
    return true;
  return leftF == replacingLeft && leftS == replacingRight;
}

std::vector<int> RepairCoder::getFlattenedCompressed() {
  int entryPosition = 0;
  auto entryValue = getValue(entryPosition);
  if (entryValue == -1)
    throw std::runtime_error("Badly compressed entries array");
  std::vector<int> result;
  while (entryPosition >= 0 && entryPosition < (int)entriesList.values.size()) {
    entryValue = getValue(entryPosition);
    result.push_back(entryValue);
    auto nextEntryPosition = getRight(entryPosition);

    if (nextEntryPosition <= entryPosition)
      break;

    entryPosition = nextEntryPosition;
  }
  return result;
}
// int RepairCoder::getDebugTotalSteps() { return debugTotalSteps; }
int RepairCoder::getValue(int position) {
  //  if (position < 0 || position >= (int)entriesList.values.size()) {
  //    throw std::runtime_error("out of range access");
  //  }
  return entriesList.values[position];
}
void RepairCoder::setValue(int position, int value) {
  //  if (position < 0 || position >= (int)entriesList.values.size()) {
  //    throw std::runtime_error("out of range access");
  //  }
  entriesList.values[position] = value;
}

} // namespace RePairCompression
