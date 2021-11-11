//
// Created by cristobal on 07-11-21.
//

#include "LPRecordHTable.hpp"
#include <stdexcept>

namespace RePairCompression {
Record *LPRecordHTable::addRecord(const ValuePair &valuePair,
                                  int firstEntryPosition, int frequency) {
  growIfNeeded();
  return arbitraryInsert(keys, data, valuePair, firstEntryPosition, frequency,
                         currentSize);
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
  int baseHValue = hashFun(valuePair);
  for (int i = 0; i < currentSize; i++) {
    int j = (baseHValue + i) % currentSize;
    auto key = keys[j];
    if (key == EMPTY_KEY)
      return NOT_FOUND;
    if (key == DELETED_KEY || data[j].valuePair != valuePair) {
      continue;
    }
    // then recordWrapper.record.valuePair == valuePair
    return j;
  }
  return NOT_FOUND;
}
LPRecordHTable::LPRecordHTable(int capacity, double maxFilledRatio)
    : keys(capacity, EMPTY_KEY), data(capacity), currentSize(capacity),
      usedSlots(0), maxFilledRatio(maxFilledRatio) {}
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
  static constexpr unsigned long primeNumber = 767865341467865341UL;
  unsigned long mergedValue = ((unsigned long)valuePair.leftValue << 32UL) |
                              (unsigned long)valuePair.rightValue;
  return (int)(((mergedValue * primeNumber) >> 32UL) &
               (unsigned long)tableSize);
}

Record *LPRecordHTable::arbitraryInsert(std::vector<int> &targetKeys,
                                        std::vector<Record> &targetRecords,
                                        const ValuePair &valuePair,
                                        int firstEntryPosition, int frequency,
                                        int tableSize) {
  int baseHValue = hashFun(valuePair);
  for (int i = 0; i < tableSize; i++) {
    int j = (baseHValue + i) % tableSize;
    auto &key = targetKeys[j];
    auto &record = targetRecords[j];
    if (key < 0) {
      record = Record(valuePair, firstEntryPosition, frequency);
      key = j;
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

ReachedMaximumSizeError::ReachedMaximumSizeError()
    : std::runtime_error(msgError()) {}
const char *ReachedMaximumSizeError::msgError() {
  return "Hash table reached maximum size";
}

} // namespace RePairCompression
