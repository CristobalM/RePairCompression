#include <algorithm>

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