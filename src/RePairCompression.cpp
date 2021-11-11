#include <algorithm>
#include <iostream>

#include "CommonDefinitions.hpp"
#include "HashTable.hpp"
#include "PriorityQueue.hpp"
#include "RePairCompression.hpp"
#include "RePairDataStructureConcrete.hpp"
#include "RepairCoder.hpp"
#include "Serialization.hpp"
#include "TranslateTable.hpp"

namespace RePairCompression {

static std::unique_ptr<RePairDataStructure>
createCompressedWrapper(std::vector<int> &&flatCompressed,
                        TranslateTable &&translateTable) {
  return std::make_unique<RePairDataStructureConcrete>(
      std::move(flatCompressed), std::move(translateTable));
}

template <typename T> static int castToInt(T value) {
  if constexpr (std::is_same<T, char>::value) {
    return (int)(unsigned char)value;
  } else {
    return (int)value;
  }
}

template <typename TSequence>
static std::unique_ptr<RePairDataStructure>
compressSequence(TSequence &&sequence) {
  std::reverse(sequence.begin(), sequence.end()); // inplace reverse
  EntriesList entriesList;
  entriesList.reserve(sequence.size());
  auto initialSize = sequence.size();
  for (size_t i = 0; i < initialSize; i++) {
    auto value = castToInt(sequence.back());
    sequence.pop_back();
    entriesList.emplace_back(-1, -1, value);
  }
  HashTable hashTable;
  auto priorityQueue = PriorityQueue(entriesList, hashTable);
  auto rePairCoder = RepairCoder(entriesList, hashTable, priorityQueue);
  while (!rePairCoder.done()) {
    rePairCoder.step();
  }
  std::cout << "total iterations: " << rePairCoder.getDebugTotalSteps()
            << std::endl;
  std::cout << "total inc freq: " << rePairCoder.totalIncFreq << std::endl;
  auto compressedFlat = rePairCoder.getFlattenedCompressed();
  return createCompressedWrapper(std::move(compressedFlat),
                                 rePairCoder.getTranslateTable());
}

std::unique_ptr<RePairDataStructure>
compressIntegerSequence(std::vector<int> &&integerSequence) {
  return compressSequence(std::move(integerSequence));
}

std::unique_ptr<RePairDataStructure> compress(std::string &&inputString) {
  return compressSequence(std::move(inputString));
}

std::unique_ptr<RePairDataStructure> compress(const std::string &inputString) {
  std::vector<int> integerSequence;
  integerSequence.reserve(inputString.size());
  std::transform(inputString.begin(), inputString.end(),
                 std::back_inserter(integerSequence),
                 [](char c) -> int { return c; });
  return compressIntegerSequence(integerSequence);
}

std::unique_ptr<RePairDataStructure>
compressIntegerSequence(const std::vector<int> &integerSequence) {
  EntriesList entriesList;
  entriesList.reserve(integerSequence.size());
  std::transform(integerSequence.begin(), integerSequence.end(),
                 std::back_inserter(entriesList),
                 [](int value) { return Entry(-1, -1, value); });
  HashTable hashTable;
  auto priorityQueue = PriorityQueue(entriesList, hashTable);
  auto rePairCoder = RepairCoder(entriesList, hashTable, priorityQueue);
  while (!rePairCoder.done()) {
    rePairCoder.step();
  }
  auto compressedFlat = rePairCoder.getFlattenedCompressed();
  return createCompressedWrapper(std::move(compressedFlat),
                                 rePairCoder.getTranslateTable());
}

std::unique_ptr<RePairDataStructure> load(std::istream &is) {
  auto translateTable = TranslateTable::load(is);
  std::vector<int> compressedData;
  auto compressedSize = read_u32(is);
  compressedData.reserve(compressedSize);
  for (unsigned int i = 0; i < compressedSize; i++) {
    auto value = read_u32(is);
    compressedData.push_back(value);
  }
  return std::make_unique<RePairDataStructureConcrete>(
      std::move(compressedData), std::move(translateTable));
}

} // namespace RePairCompression