//
// Created by cristobal on 31-10-21.
//
#include "HashTable.hpp"
#include <functional>
namespace RePairCompression {

Record *HashTable::increaseFrequency(int leftEntryPosition, int leftValue,
                                     int rightValue) {
  auto *record = hashTable.findRecord(leftValue, rightValue);
  if (!record) {
    return hashTable.addRecord(leftValue, rightValue, leftEntryPosition, 1);
  }
  record->frequency++;
  return record;
}

HashTable::HashTable() = default;

Record *HashTable::getRecord(int leftValue, int rightValue) {
  return hashTable.findRecord(leftValue, rightValue);
}

void HashTable::deleteRecord(int leftValue, int rightValue) {
  hashTable.deleteRecord(leftValue, rightValue);
}
Record *HashTable::createRecordIfNotExists(int position, int leftValue,
                                           int rightValue, bool &created) {
  auto *record = hashTable.findRecord(leftValue, rightValue);
  if (record) {
    created = false;
    return record;
  }
  created = true;
  return hashTable.addRecord(leftValue, rightValue, position, 0);
}
LPRecordHTable &HashTable::getHTable() { return hashTable; }

} // namespace RePairCompression
