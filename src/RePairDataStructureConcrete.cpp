//
// Created by cristobal on 31-10-21.
//

#include <netinet/in.h>
#include <sstream>

#include "RePairDataStructureConcrete.hpp"
#include "Serialization.hpp"
namespace RePairCompression {
RePairDataStructureConcrete::RePairDataStructureConcrete(
    std::vector<int> &&compressedData,
    RePairCompression::TranslateTable &&translateTable)
    : compressedData(std::move(compressedData)),
      translateTable(std::move(translateTable)) {
  firstSymbol = this->translateTable.getFirstSymbol();
}
std::string RePairDataStructureConcrete::decompress() {
  auto integerSequence = decompressIntegerSequence();
  std::stringstream ss;
  for (auto i : integerSequence) {
    ss << (char)i;
  }
  return ss.str();
}

std::vector<int> RePairDataStructureConcrete::decompressIntegerSequence() {
  std::list<int> buildList;
  for (auto v : compressedData) {
    decompressSymbol(v, buildList);
  }
  return {buildList.begin(), buildList.end()};
}
void RePairDataStructureConcrete::decompressSymbol(int symbol,
                                                   std::list<int> &outList) {

  if (symbol < firstSymbol) {
    outList.push_back(symbol);
    return;
  }
  auto valuePair = translateTable.getPair(symbol);
  decompressSymbol(valuePair.leftValue, outList);
  decompressSymbol(valuePair.rightValue, outList);
}

void RePairDataStructureConcrete::dump(std::ostream &ostream) {
  translateTable.dump(ostream);
  write_u32(ostream, compressedData.size());
  for (auto v : compressedData) {
    write_u32(ostream, v);
  }
}
const std::vector<int> &
RePairDataStructureConcrete::getCompressedIntegerSequence() {
  return compressedData;
}
TranslateTable &RePairDataStructureConcrete::getTable() {
  return translateTable;
}

std::vector<int>
RePairDataStructureConcrete::decompressIntegerSequenceFromOffsetToTerminator(
    int offset, int terminator) {
  if (terminator >= firstSymbol)
    throw std::runtime_error(
        "Invalid terminator, value is not in original sequence: " +
        std::to_string(terminator));
  std::list<int> buildList;
  for (size_t i = offset; i < compressedData.size(); i++) {
    if (compressedData[i] == terminator)
      break;
    decompressSymbol(compressedData[i], buildList);
  }
  return {buildList.begin(), buildList.end()};
}

} // namespace RePairCompression
