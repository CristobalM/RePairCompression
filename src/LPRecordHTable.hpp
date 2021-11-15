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

  // static constexpr int DEFAULT_CAPACITY = (int)((float)(100003));
  static constexpr int DEFAULT_CAPACITY = (int)((float)(256 * 256));
  static constexpr int EMPTY_KEY = -1;
  static constexpr int DELETED_KEY = -2;
  static constexpr int NOT_FOUND = -3;
  //
  //  static constexpr double DEFAULT_MAX_FILLED_RATIO = 0.75;
  //  static constexpr double GROW_RATIO = 0.50;

  // using ArrayT = std::array<RecordWrapper, RECORDS_MAX_SIZE>;
  // ArrayT data;
  int currentSize;
  std::vector<int> keys;
  std::vector<int> left;
  std::vector<int> right;
  std::vector<Record> data;

  int usedSlots;

  double maxFilledRatio;

public:
  struct KV {
    int key;
    Record *record;
  };

  class KVIterator {
    LPRecordHTable *hTable;
    int currentPos;
    int validCounted;

  public:
    explicit KVIterator(LPRecordHTable &hTable);
    KVIterator(const KVIterator &) = default;
    KVIterator(KVIterator &&) noexcept = default;
    KVIterator &operator=(const KVIterator &) = default;
    KVIterator &operator=(KVIterator &&) noexcept = default;
    bool hasNext() const;
    KV next();
  };

  LPRecordHTable();
  LPRecordHTable(int capacity, double maxFilledRatio);

  Record *addRecord(int leftValue, int rightValue, int firstEntryPosition,
                    int frequency);
  Record *findRecord(int leftValue, int rightValue);
  void deleteRecord(int leftValue, int rightValue);

  int getSize() const;

  KVIterator startIteration();

private:
  inline int hashFun(int leftValue, int rightValue) const;
  static inline int hashFunSize(int leftValue, int rightValue, int tableSize);

  int findRecordPosition(int leftValue, int rightValue);
  void growIfNeeded() const;

  Record *arbitraryInsert(std::vector<int> &targetKeys,
                          std::vector<int> &targetLeft,
                          std::vector<int> &targetRight,
                          std::vector<Record> &targetRecords, int leftValue,
                          int rightValue, int firstEntryPosition, int frequency,
                          int tableSize);
  static int calcCapacity(int capacity);
};
} // namespace RePairCompression

#endif // REPAIRCOMPRESSION_LPRECORDHTABLE_HPP
