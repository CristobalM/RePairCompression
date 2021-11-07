//
// Created by cristobal on 31-10-21.
//

#ifndef REPAIRCOMPRESSION_REPAIRDATASTRUCTURECONCRETE_HPP
#define REPAIRCOMPRESSION_REPAIRDATASTRUCTURECONCRETE_HPP
#include "RePairDataStructure.hpp"
#include "TranslateTable.hpp"
#include <list>
#include <vector>
namespace RePairCompression {
class RePairDataStructureConcrete : public RePairDataStructure {

  std::vector<int> compressedData;
  TranslateTable translateTable;
  int firstSymbol;

public:
  RePairDataStructureConcrete(std::vector<int> &&compressedData,
                              TranslateTable &&translateTable);
  std::string decompress() override;
  std::vector<int> decompressIntegerSequence() override;
  void decompressSymbol(int symbol, std::list<int> &outList);
  void dump(std::ostream &ostream) override;
  const std::vector<int> &getCompressedIntegerSequence() override;
  TranslateTable &getTable() override;
  std::vector<int>
  decompressIntegerSequenceFromOffsetToTerminator(int offset,
                                                  int terminator) override;
};
} // namespace RePairCompression

#endif // REPAIRCOMPRESSION_REPAIRDATASTRUCTURECONCRETE_HPP
