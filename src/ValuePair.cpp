//
// Created by cristobal on 31-10-21.
//

#include "ValuePair.hpp"
#include <functional>
namespace RePairCompression {
ValuePair::ValuePair(int leftValue, int rightValue)
    : leftValue(leftValue), rightValue(rightValue) {}
bool ValuePair::operator==(const ValuePair &other) const {
  return leftValue == other.leftValue && rightValue == other.rightValue;
}
ValuePair::ValuePair(const ValuePair &pair) {
  leftValue = pair.leftValue;
  rightValue = pair.rightValue;
}
bool ValuePair::operator!=(const ValuePair &other) const {
  return !operator==(other);
}
ValuePair &ValuePair::operator=(const ValuePair &pair) = default;
std::size_t
ValuePair::HashFunction::operator()(const ValuePair &valuePair) const {
  return std::hash<int>()(valuePair.leftValue) ^
         std::hash<int>()(valuePair.rightValue);
}
} // namespace RePairCompression
