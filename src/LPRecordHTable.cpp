//
// Created by cristobal on 07-11-21.
//

#include "LPRecordHTable.hpp"
#include <stdexcept>

namespace RePairCompression {
Record *LPRecordHTable::addRecord(int leftValue, int rightValue,
                                  int firstEntryPosition, int frequency) {
  growIfNeeded();
  return arbitraryInsert(keys, left, right, data, leftValue, rightValue,
                         firstEntryPosition, frequency, currentSize);
}

Record *LPRecordHTable::findRecord(int leftValue, int rightValue) {
  auto recordPos = findRecordPosition(leftValue, rightValue);
  if (recordPos == NOT_FOUND)
    return nullptr;
  return &(data[recordPos]);
}

void LPRecordHTable::deleteRecord(int leftValue, int rightValue) {
  int recordPosition = findRecordPosition(leftValue, rightValue);
  if (recordPosition < 0)
    return;
  keys[recordPosition] = DELETED_KEY;
  usedSlots--;
}

LPRecordHTable::LPRecordHTable() : LPRecordHTable(DEFAULT_CAPACITY, 1) {}

int LPRecordHTable::hashFun(int leftValue, int rightValue) const {
  return hashFunSize(leftValue, rightValue, currentSize);
}
int LPRecordHTable::findRecordPosition(int leftValue, int rightValue) {
  int base = hashFun(leftValue, rightValue);

  for (int i = 0; i < currentSize; i++) {
    auto k = (base + i) & currentSize;
    if (keys[k] == EMPTY_KEY)
      break;
    if (keys[k] >= 0 && (left[k] == leftValue && right[k] == rightValue))
      return k;
  }
  return NOT_FOUND;
}
LPRecordHTable::LPRecordHTable(int capacity, double maxFilledRatio)
    : currentSize(calcCapacity(capacity)), keys(currentSize, EMPTY_KEY),
      left(currentSize), right(currentSize), data(currentSize), usedSlots(0),
      maxFilledRatio(maxFilledRatio) {}
void LPRecordHTable::growIfNeeded() const {
  double nextFilledRatio = (double)(usedSlots + 1) / (double)currentSize;
  if (nextFilledRatio < maxFilledRatio)
    return;
  throw ReachedMaximumSizeError();
}
int LPRecordHTable::hashFunSize(int leftValue, int rightValue, int tableSize) {
  //  static constexpr unsigned long primeNumber = 767865341467865341UL;
  //  unsigned long mergedValue = ((unsigned long)valuePair.leftValue << 32UL) |
  //                              (unsigned long)valuePair.rightValue;
  //  return (int)(((mergedValue * primeNumber) >> 32UL) &
  //               (unsigned long)tableSize);
  return (int)((std::hash<int>()(leftValue) ^ std::hash<int>()(rightValue)) &
               (unsigned long)tableSize);
}

Record *LPRecordHTable::arbitraryInsert(std::vector<int> &targetKeys,
                                        std::vector<int> &targetLeft,
                                        std::vector<int> &targetRight,
                                        std::vector<Record> &targetRecords,
                                        int leftValue, int rightValue,
                                        int firstEntryPosition, int frequency,
                                        int tableSize) {
  int baseHValue = hashFun(leftValue, rightValue);
  for (int i = 0; i < tableSize; i++) {
    int j = (baseHValue + i) & tableSize;
    auto &key = targetKeys[j];
    auto &record = targetRecords[j];
    if (key < 0) {
      record = Record(leftValue, rightValue, firstEntryPosition, frequency);
      key = j;
      targetLeft[j] = leftValue;
      targetRight[j] = rightValue;
      usedSlots++;
      return &record;
    }
    if (record.leftValue == leftValue && record.rightValue == rightValue) {
      // already inserted
      return &record;
    }
  }
  return nullptr;
}

int LPRecordHTable::getSize() const { return usedSlots; }
int LPRecordHTable::calcCapacity(int capacity) {
  while (capacity & (capacity - 1))
    capacity &= capacity - 1;
  capacity = (capacity - 1) << 1 | 1;
  return capacity;
}
LPRecordHTable::KVIterator LPRecordHTable::startIteration() {
  return KVIterator(*this);
}

ReachedMaximumSizeError::ReachedMaximumSizeError()
    : std::runtime_error(msgError()) {}
const char *ReachedMaximumSizeError::msgError() {
  return "Hash table reached maximum size";
}

LPRecordHTable::KVIterator::KVIterator(LPRecordHTable &hTable)
    : hTable(&hTable), currentPos(0), validCounted(0) {}
bool LPRecordHTable::KVIterator::hasNext() const {
  return validCounted < hTable->usedSlots;
}
LPRecordHTable::KV LPRecordHTable::KVIterator::next() {
  while (validCounted < hTable->usedSlots) {
    int pos = currentPos++;
    int key = hTable->keys[pos];
    if (key >= 0) {
      validCounted++;
      return {key, &(hTable->data[pos])};
    }
  }
  throw std::runtime_error("No more elements in hash table");
}
} // namespace RePairCompression
