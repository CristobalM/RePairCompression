//
// Created by cristobal on 31-10-21.
//

#ifndef REPAIRCOMPRESSION_REPAIRCODER_HPP
#define REPAIRCOMPRESSION_REPAIRCODER_HPP
#include "EntryPair.hpp"
#include "HashTable.hpp"
#include "PriorityQueue.hpp"
#include "TranslateTable.hpp"
namespace RePairCompression {
class RepairCoder {
  EntriesList &entriesList;
  HashTable &hashTable;
  PriorityQueue &priorityQueue;
  TranslateTable translateTable;

  int nextSymbol;

public:
  RepairCoder(const RepairCoder &other) = delete;
  RepairCoder &operator=(const RepairCoder &other) = delete;

  RepairCoder(EntriesList &entriesList, HashTable &hashTable,
              PriorityQueue &priorityQueue);
  bool done();
  void step();
  TranslateTable getTranslateTable();

  std::vector<int> getFlattenedCompressed();

  //  int getDebugTotalSteps();

private:
  void initStructures();
  void insertToPriorityQueue(int leftValue, int rightValue);
  int getLeft(int entryPosition);
  int getRight(int entryPosition);
  void decreaseFrequency(int leftEntryPosition, int rightEntryPosition);
  void replacePair(int leftEntryPosition, int rightEntryPosition,
                   int newSymbol);
  void increaseFrequency(int leftEntryPosition, int rightEntryPosition);
  bool matchingPair(int leftFirstPos, int leftSecondPos, int replacingLeft,
                    int replacingRight);
  inline int getValue(int position);
  inline void setValue(int position, int value);
};
} // namespace RePairCompression

#endif // REPAIRCOMPRESSION_REPAIRCODER_HPP
