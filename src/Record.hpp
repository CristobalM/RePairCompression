//
// Created by cristobal on 31-10-21.
//

#ifndef REPAIRCOMPRESSION_RECORD_HPP
#define REPAIRCOMPRESSION_RECORD_HPP

#include "Entry.hpp"
#include "ValuePair.hpp"

namespace RePairCompression {
struct Record {
  int leftValue;
  int rightValue;

  int firstEntryPosition;
  int frequency;
  Record *prev;
  Record *next;

  Record() = default;

  Record(int leftValue, int rightValue, int firstEntryPosition, int frequency)
      : leftValue(leftValue), rightValue(rightValue),
        firstEntryPosition(firstEntryPosition), frequency(frequency),
        prev(nullptr), next(nullptr) {}
};
} // namespace RePairCompression
#endif // REPAIRCOMPRESSION_RECORD_HPP
