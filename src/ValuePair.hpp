//
// Created by cristobal on 31-10-21.
//

#ifndef REPAIRCOMPRESSION_VALUEPAIR_HPP
#define REPAIRCOMPRESSION_VALUEPAIR_HPP
#include <cstddef>
namespace RePairCompression {
struct ValuePair {
  ValuePair(const ValuePair &pair);
  ValuePair &operator=(const ValuePair &pair);
  int leftValue;
  int rightValue;
  ValuePair(int leftValue, int rightValue);
  ValuePair() = default;
  bool operator==(const ValuePair &other) const;
  bool operator!=(const ValuePair &other) const;

  struct HashFunction {
    std::size_t operator()(const ValuePair &valuePair) const;
  };
};

} // namespace RePairCompression
#endif // REPAIRCOMPRESSION_VALUEPAIR_HPP
