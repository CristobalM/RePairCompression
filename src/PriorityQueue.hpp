//
// Created by cristobal on 31-10-21.
//

#ifndef REPAIRCOMPRESSION_PRIORITYQUEUE_HPP
#define REPAIRCOMPRESSION_PRIORITYQUEUE_HPP

#include "HashTable.hpp"
#include <unordered_set>
namespace RePairCompression {

class PriorityQueue {
  HashTable &hashTable;

  int sqrtSize;
  std::vector<Record *> recordLinkedLists;
  int activePosition;

public:
  PriorityQueue(EntriesList &linkedList, HashTable &hashTable);
  void insertRecord(Record *record);
  void insertInSmallerFrequencies(Record *record);
  void insertInBiggerFrequencies(Record *record);

  Record *pop();
  void decreaseFrequency(Record *record);
  void decreaseSmallerFrequency(Record *record);
  void decreaseBiggerFrequency(Record *record);
  void disconnectFromList(int position, Record *record);
  void increaseFrequency(Record *record);
  int getActivePosition() const;
};

} // namespace RePairCompression

#endif // REPAIRCOMPRESSION_PRIORITYQUEUE_HPP
