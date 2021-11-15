//
// Created by cristobal on 31-10-21.
//
#include "HashTable.hpp"
#include <functional>
#include <stdexcept>
namespace RePairCompression {

Record *HashTable::increaseFrequency(int leftEntryPosition,
                                     const ValuePair &valuePair) {
  auto *record = hashTable.findRecord(valuePair);
  if (!record) {
    return hashTable.addRecord(valuePair, leftEntryPosition, 1);
  }
  record->frequency++;
  return record;
}

HashTable::HashTable() = default;

Record *HashTable::getRecord(const ValuePair &valuePair) {
  return hashTable.findRecord(valuePair);
}

void HashTable::deleteRecord(const ValuePair &valuePair) {
  hashTable.deleteRecord(valuePair);
}
Record *HashTable::createRecordIfNotExists(int position,
                                           const ValuePair &valuePair,
                                           bool &created) {
  auto *record = hashTable.findRecord(valuePair);
  if (record) {
    created = false;
    return record;
  }
  created = true;
  return hashTable.addRecord(valuePair, position, 0);
}
LPRecordHTable &HashTable::getHTable() { return hashTable; }

} // namespace RePairCompression
