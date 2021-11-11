//
// Created by cristobal on 31-10-21.
//

#include "PriorityQueue.hpp"
#include <cmath>
namespace RePairCompression {

PriorityQueue::PriorityQueue(EntriesList &entriesList, HashTable &hashTable)
    : hashTable(hashTable),
      sqrtSize((int)std::ceil(std::sqrt(entriesList.size()))),
      recordLinkedLists(sqrtSize, nullptr), activePosition(-1) {}
void PriorityQueue::insertRecord(Record *record) {
  if (record->frequency - 1 < sqrtSize - 1) {
    insertInSmallerFrequencies(record);
  } else {
    insertInBiggerFrequencies(record);
  }
}
void PriorityQueue::insertInSmallerFrequencies(Record *record) {
  int position = record->frequency - 1;
  if (position > activePosition) {
    activePosition = position;
  }

  auto *firstRecord = recordLinkedLists[position];
  if (firstRecord == nullptr) {
    recordLinkedLists[position] = record;
    return;
  }

  record->next = firstRecord;
  firstRecord->prev = record;
  recordLinkedLists[position] = record;
}
void PriorityQueue::insertInBiggerFrequencies(Record *record) {
  int position = sqrtSize - 1;
  if (position > activePosition) {
    activePosition = position;
  }
  auto *recordInList = recordLinkedLists[position];
  auto *lastRecord = recordInList;
  while (recordInList && recordInList->frequency > record->frequency) {
    lastRecord = recordInList;
    recordInList = recordInList->next;
  }
  if (!lastRecord) { // then there were no other records
    recordLinkedLists[position] = record;
    return;
  }

  if (lastRecord == recordInList) { // then it is the first record
    lastRecord->prev = record;
    record->next = lastRecord;
    recordLinkedLists[position] = record;
    return;
  }

  record->next = recordInList;
  if (recordInList) {
    recordInList->prev = record;
  }

  lastRecord->next = record;
  record->prev = lastRecord;
}
bool PriorityQueue::empty() const { return activePosition <= -1; }
Record *PriorityQueue::pop() {
  auto *record = recordLinkedLists[activePosition];
  auto *nextRecord = record->next;
  recordLinkedLists[activePosition] = nextRecord;
  record->next = nullptr;
  if (nextRecord) {
    nextRecord->prev = nullptr;
  } else {
    for (; activePosition >= 0; activePosition--) {
      if (recordLinkedLists[activePosition])
        break;
    }
  }
  return record;
}
void PriorityQueue::decreaseFrequency(const ValuePair &valuePair) {
  auto *record = hashTable.getRecord(valuePair);
  if (!record)
    return;

  if (record->frequency - 1 < sqrtSize - 1) {
    decreaseSmallerFrequency(record);
  } else {
    decreaseBiggerFrequency(record);
  }
  for (; activePosition >= 0; activePosition--) {
    if (recordLinkedLists[activePosition])
      break;
  }
}
void PriorityQueue::decreaseSmallerFrequency(Record *record) {
  int position = record->frequency - 1;
  disconnectFromList(position, record);
  record->prev = nullptr;
  record->next = nullptr;
  record->frequency--;
  if (record->frequency >= 1) {
    insertInSmallerFrequencies(record);
  } else {
    hashTable.deleteRecord(record->valuePair);
  }
}

void PriorityQueue::decreaseBiggerFrequency(Record *record) {
  int position = sqrtSize - 1;
  int nextFrequency = record->frequency - 1;
  record->frequency = nextFrequency;

  if (nextFrequency - 1 < sqrtSize - 1) {
    disconnectFromList(position, record);
    insertInSmallerFrequencies(record);
    return;
  }

  if (!record->next || record->next->frequency <= nextFrequency) {
    // it is already well positioned, do nothing.
    return;
  }

  auto *lastRecord = record->next;
  auto *currentRecord = record->next;
  disconnectFromList(position, record);

  // there is at least another element with higher frequency next, because of
  // the previous check
  while (currentRecord && currentRecord->frequency > nextFrequency) {
    lastRecord = currentRecord;
    currentRecord = currentRecord->next;
  }
  record->next = currentRecord;
  if (currentRecord) {
    currentRecord->prev = record;
  }
  lastRecord->next = record;
  record->prev = lastRecord;
}

void PriorityQueue::disconnectFromList(int position, Record *record) {
  auto *prevRecord = record->prev;
  auto *nextRecord = record->next;
  record->next = nullptr;
  record->prev = nullptr;
  if (nextRecord) {
    nextRecord->prev = prevRecord;
  }
  if (!prevRecord) { // it's root node
    recordLinkedLists[position] = nextRecord;
  } else {
    prevRecord->next = nextRecord;
  }
}

void PriorityQueue::increaseFrequency(const ValuePair &valuePair) {
  auto *record = hashTable.getRecord(valuePair);
  auto currentFrequency = record->frequency;
  auto nextFrequency = currentFrequency + 1;
  record->frequency = nextFrequency;
  if (currentFrequency - 1 < sqrtSize - 1) {
    int position = currentFrequency - 1;
    disconnectFromList(position, record);
    if (nextFrequency - 1 < sqrtSize - 1) {
      insertInSmallerFrequencies(record);
    } else {
      insertInBiggerFrequencies(record);
    }
    return;
  }

  // then it exists on bigger frequencies and must adapted there

  // should move?

  auto *prevRecord = record->prev;
  if (!prevRecord || prevRecord->frequency >= nextFrequency) {
    // nothing to do
    return;
  }

  int position = sqrtSize - 1;
  auto *currentRecord = record->prev;
  auto *lastRecord = record->prev;
  disconnectFromList(position, record);

  while (currentRecord && currentRecord->frequency < nextFrequency) {
    lastRecord = currentRecord;
    currentRecord = currentRecord->prev;
  }

  if (!currentRecord) {
    recordLinkedLists[position] = record;
    record->next = lastRecord;
    lastRecord->prev = record;
    return;
  }

  currentRecord->next = record;
  record->prev = currentRecord;
  lastRecord->prev = record;
  record->next = lastRecord;
}
int PriorityQueue::getActivePosition() { return activePosition; }

} // namespace RePairCompression