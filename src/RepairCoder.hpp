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
  int debugCurrentStep;
  int debugTotalSteps;

public:
  int totalIncFreq;
  RepairCoder(const RepairCoder &other) = delete;
  RepairCoder &operator=(const RepairCoder &other) = delete;

  RepairCoder(EntriesList &entriesList, HashTable &hashTable,
              PriorityQueue &priorityQueue);
  bool done();
  void step();
  TranslateTable getTranslateTable();

  std::vector<int> getFlattenedCompressed();

  int getDebugTotalSteps();

private:
  void initStructures();
  void insertToPriorityQueue(const ValuePair &valuePair);
  int getLeft(int entryPosition);
  int getRight(int entryPosition);
  void decreaseFrequency(EntryPair entryPair);
  void replacePair(EntryPair replacingEntryPair, int newSymbol);
  void increaseFrequency(EntryPair entryPair);
  void debugPrintCurrentSequence();
  bool matchingPair(const EntryPair &targetEntryPair,
                    const ValuePair &replacingPair);
  int getValue(int position);
  void setValue(int position, int value);
};
} // namespace RePairCompression

#endif // REPAIRCOMPRESSION_REPAIRCODER_HPP
