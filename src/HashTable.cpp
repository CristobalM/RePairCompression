//
// Created by cristobal on 31-10-21.
//
#include "HashTable.hpp"
#include <functional>
#include <stdexcept>
namespace RePairCompression {

Record *HashTable::increaseFrequency(int leftEntryPosition,
                                     ValuePair valuePair) {
  auto it = hashTable.find(valuePair);
  if (it == hashTable.end()) {
    auto record = std::make_unique<Record>(valuePair, leftEntryPosition, 1);
    auto *record_ptr = record.get();
    hashTable[valuePair] = std::move(record);
    return record_ptr;
  }
  it->second->frequency++;
  return it->second.get();
}

HashTable::HashTable() {
  hashTable.reserve((int)((float)(256 * 256) * ((float)1.25)));
}

Record *HashTable::getRecord(ValuePair valuePair) {
  auto it = hashTable.find(valuePair);
  if (it == hashTable.end()) {
    return nullptr;
  }
  return it->second.get();
}

void HashTable::deleteRecord(ValuePair valuePair) {
  auto it = hashTable.find(valuePair);
  if (it == hashTable.end())
    return;
  hashTable.erase(it);
}
Record *HashTable::createRecordIfNotExists(int position, ValuePair valuePair,
                                           bool &created) {
  auto it = hashTable.find(valuePair);
  if (it != hashTable.end()) {
    auto *record = it->second.get();
    created = false;
    return record;
  }
  created = true;
  auto record = std::make_unique<Record>(valuePair, position, 0);
  auto *record_ptr = record.get();
  hashTable[valuePair] = std::move(record);
  return record_ptr;
}

} // namespace RePairCompression
