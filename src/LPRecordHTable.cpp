//
// Created by cristobal on 07-11-21.
//

#include "LPRecordHTable.hpp"
#include <stdexcept>

namespace RePairCompression {
Record *LPRecordHTable::addRecord(const ValuePair &valuePair,
                                  int firstEntryPosition, int frequency) {
  growIfNeeded();
  return arbitraryInsert(keys, left, right, data, valuePair, firstEntryPosition,
                         frequency, currentSize);
}

Record *LPRecordHTable::findRecord(const ValuePair &valuePair) {
  auto recordPos = findRecordPosition(valuePair);
  if (recordPos == NOT_FOUND)
    return nullptr;
  return &(data[recordPos]);
}

void LPRecordHTable::deleteRecord(const ValuePair &valuePair) {
  int recordPosition = findRecordPosition(valuePair);
  if (recordPosition < 0)
    return;
  keys[recordPosition] = DELETED_KEY;
  usedSlots--;
}

LPRecordHTable::LPRecordHTable() : LPRecordHTable(DEFAULT_CAPACITY, 1) {}

int LPRecordHTable::hashFun(const ValuePair &valuePair) const {
  return hashFunSize(valuePair, currentSize);
}
int LPRecordHTable::findRecordPosition(const ValuePair &valuePair) {
  int base = hashFun(valuePair);

  for (int i = 0; i < currentSize; i++) {
    auto k = (base + i) & currentSize;
    if (keys[k] == EMPTY_KEY)
      break;
    if (keys[k] >= 0 &&
        (left[k] == valuePair.leftValue && right[k] == valuePair.rightValue))
      return k;
  }
  return NOT_FOUND;
  //  int baseHValue = hashFun(valuePair);
  //  for (int i = 0; i < currentSize; i++) {
  //    int j = (baseHValue + i) % currentSize;
  //    auto key = keys[j];
  //    if (key == EMPTY_KEY)
  //      return NOT_FOUND;
  //    if (key == DELETED_KEY || data[j].valuePair != valuePair) {
  //      continue;
  //    }
  //    // then recordWrapper.record.valuePair == valuePair
  //    return j;
  //  }
  //  return NOT_FOUND;
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
  //  double nextSizeDouble = std::ceil(((double)currentSize * (1.0 +
  //  GROW_RATIO))); int nextSize = (int)nextSizeDouble; if (nextSize <
  //  currentSize || nextSizeDouble >= (1UL << 31UL)) {
  //    throw std::runtime_error("Overflowed integer max size 2^31");
  //  }
  //  auto newData = std::make_unique<RecordWrapper[]>(nextSize);
  //  for (int i = 0; i < currentSize; i++) {
  //    auto &recordWrapper = data[i];
  //    auto record = recordWrapper.record;
  //    if (recordWrapper.key >= 0) {
  //      arbitraryInsert(newData.get(), record.valuePair,
  //                      record.firstEntryPosition, record.frequency,
  //                      nextSize);
  //    }
  //  }
  //  data = std::move(newData);
  //  currentSize = nextSize;
}
int LPRecordHTable::hashFunSize(const ValuePair &valuePair, int tableSize) {
  //  static constexpr unsigned long primeNumber = 767865341467865341UL;
  //  unsigned long mergedValue = ((unsigned long)valuePair.leftValue << 32UL) |
  //                              (unsigned long)valuePair.rightValue;
  //  return (int)(((mergedValue * primeNumber) >> 32UL) &
  //               (unsigned long)tableSize);
  return (int)((std::hash<int>()(valuePair.leftValue) ^
                std::hash<int>()(valuePair.rightValue)) &
               (unsigned long)tableSize);
}

Record *LPRecordHTable::arbitraryInsert(std::vector<int> &targetKeys,
                                        std::vector<int> &targetLeft,
                                        std::vector<int> &targetRight,
                                        std::vector<Record> &targetRecords,
                                        const ValuePair &valuePair,
                                        int firstEntryPosition, int frequency,
                                        int tableSize) {
  int baseHValue = hashFun(valuePair);
  for (int i = 0; i < tableSize; i++) {
    int j = (baseHValue + i) & tableSize;
    auto &key = targetKeys[j];
    auto &leftValue = targetLeft[j];
    auto &rightValue = targetRight[j];
    auto &record = targetRecords[j];
    if (key < 0) {
      record = Record(valuePair, firstEntryPosition, frequency);
      key = j;
      leftValue = valuePair.leftValue;
      rightValue = valuePair.rightValue;
      usedSlots++;
      return &record;
    }
    if (record.valuePair == valuePair) {
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
