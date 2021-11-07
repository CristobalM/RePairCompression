//
// Created by cristobal on 31-10-21.
//

#ifndef REPAIRCOMPRESSION_TRANSLATETABLE_HPP
#define REPAIRCOMPRESSION_TRANSLATETABLE_HPP
#include "ValuePair.hpp"
#include <iosfwd>
#include <unordered_map>
namespace RePairCompression {
class TranslateTable {
  std::unordered_map<int, ValuePair> translateMap;
  int firstSymbol;

public:
  void setFirstSymbol(int firstSymbol);
  int getFirstSymbol() const;
  void addTranslation(ValuePair valuePair, int symbol);
  ValuePair getPair(int symbol);
  void dump(std::ostream &ostream);
  size_t size() const;
  static TranslateTable load(std::istream &istream);
};
} // namespace RePairCompression
#endif // REPAIRCOMPRESSION_TRANSLATETABLE_HPP
