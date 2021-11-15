//
// Created by cristobal on 31-10-21.
//

#ifndef REPAIRCOMPRESSION_HASHTABLE_HPP
#define REPAIRCOMPRESSION_HASHTABLE_HPP
#include "CommonDefinitions.hpp"
#include "LPRecordHTable.hpp"
#include "Record.hpp"
#include "ValuePair.hpp"
#include <memory>
namespace RePairCompression {

class HashTable {
  LPRecordHTable hashTable;

public:
  HashTable();
  Record *increaseFrequency(int leftEntryPosition, int leftValue,
                            int rightValue);
  Record *getRecord(int leftValue, int rightValue);
  void deleteRecord(int leftValue, int rightValue);
  Record *createRecordIfNotExists(int position, int leftValue, int rightValue,
                                  bool &created);
  LPRecordHTable &getHTable();
};
} // namespace RePairCompression
#endif // REPAIRCOMPRESSION_HASHTABLE_HPP
