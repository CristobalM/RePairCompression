//
// Created by cristobal on 07-11-21.
//

#ifndef REPAIRCOMPRESSION_LPRECORDHTABLE_HPP
#define REPAIRCOMPRESSION_LPRECORDHTABLE_HPP

#include "Record.hpp"
#include <array>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <vector>

namespace RePairCompression {
struct ReachedMaximumSizeError : public std::runtime_error {
  ReachedMaximumSizeError();

  static const char *msgError();
};
// Linear probing hash table
class LPRecordHTable {

  static constexpr int DEFAULT_CAPACITY = (int)((float)(100003));
  static constexpr int EMPTY_KEY = -1;
  static constexpr int DELETED_KEY = -2;
  static constexpr int NOT_FOUND = -3;
  //
  //  static constexpr double DEFAULT_MAX_FILLED_RATIO = 0.75;
  //  static constexpr double GROW_RATIO = 0.50;

  // using ArrayT = std::array<RecordWrapper, RECORDS_MAX_SIZE>;
  // ArrayT data;

  std::vector<int> keys;
  std::vector<Record> data;

  int currentSize;

  int usedSlots;

  double maxFilledRatio;

public:
  LPRecordHTable();
  LPRecordHTable(int capacity, double maxFilledRatio);

  Record *addRecord(const ValuePair &valuePair, int firstEntryPosition,
                    int frequency);
  Record *findRecord(const ValuePair &valuePair);
  void deleteRecord(const ValuePair &valuePair);

  int getSize() const;

private:
  int hashFun(const ValuePair &valuePair) const;
  static int hashFunSize(const ValuePair &valuePair, int tableSize);

  int findRecordPosition(const ValuePair &valuePair);
  void growIfNeeded() const;

  Record *arbitraryInsert(std::vector<int> &targetKeys,
                          std::vector<Record> &targetRecords,
                          const ValuePair &valuePair, int firstEntryPosition,
                          int frequency, int tableSize);
};
} // namespace RePairCompression

#endif // REPAIRCOMPRESSION_LPRECORDHTABLE_HPP
