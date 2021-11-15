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
  Record *increaseFrequency(int leftEntryPosition, const ValuePair &valuePair);
  Record *getRecord(const ValuePair &valuePair);
  void deleteRecord(const ValuePair &valuePair);
  Record *createRecordIfNotExists(int position, const ValuePair &valuePair,
                                  bool &created);
  LPRecordHTable &getHTable();
};
} // namespace RePairCompression
#endif // REPAIRCOMPRESSION_HASHTABLE_HPP
