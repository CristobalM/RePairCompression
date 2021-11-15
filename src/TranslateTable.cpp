//
// Created by cristobal on 31-10-21.
//

#include "TranslateTable.hpp"
#include "Serialization.hpp"
namespace RePairCompression {

void TranslateTable::addTranslation(int leftValue, int rightValue, int symbol) {
  translateMap[symbol] = ValuePair(leftValue, rightValue);
}
ValuePair TranslateTable::getPair(int symbol) { return translateMap[symbol]; }
void TranslateTable::setFirstSymbol(int symbol) { this->firstSymbol = symbol; }
int TranslateTable::getFirstSymbol() const { return firstSymbol; }
void TranslateTable::dump(std::ostream &ostream) {
  write_u32(ostream, firstSymbol);
  write_u32(ostream, (unsigned int)translateMap.size());
  for (const auto &p : translateMap) {
    write_u32(ostream, p.first);
    write_u32(ostream, p.second.leftValue);
    write_u32(ostream, p.second.rightValue);
  }
}
TranslateTable TranslateTable::load(std::istream &istream) {
  TranslateTable translateTable;
  auto firstSymbol = (int)read_u32(istream);
  translateTable.setFirstSymbol(firstSymbol);
  auto size = read_u32(istream);
  for (unsigned int i = 0; i < size; i++) {
    auto symbol = (int)read_u32(istream);
    auto leftValue = (int)read_u32(istream);
    auto rightValue = (int)read_u32(istream);
    translateTable.addTranslation(leftValue, rightValue, symbol);
  }

  return translateTable;
}
size_t TranslateTable::size() const { return translateMap.size(); }
} // namespace RePairCompression
