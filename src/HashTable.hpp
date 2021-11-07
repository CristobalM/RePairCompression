//
// Created by cristobal on 31-10-21.
//

#ifndef REPAIRCOMPRESSION_HASHTABLE_HPP
#define REPAIRCOMPRESSION_HASHTABLE_HPP
#include "CommonDefinitions.hpp"
#include "Record.hpp"
#include "ValuePair.hpp"
#include <memory>
#include <unordered_map>
namespace RePairCompression {

class HashTable {
  std::unordered_map<ValuePair, std::unique_ptr<Record>,
                     ValuePair::HashFunction>
      hashTable;

public:
  HashTable();
  Record *increaseFrequency(int leftEntryPosition, ValuePair valuePair);
  Record *getRecord(ValuePair valuePair);
  void deleteRecord(ValuePair valuePair);
  Record *createRecordIfNotExists(int position, ValuePair valuePair,
                                  bool &created);
};
} // namespace RePairCompression
#endif // REPAIRCOMPRESSION_HASHTABLE_HPP
