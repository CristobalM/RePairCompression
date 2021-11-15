//
// Created by cristobal on 02-11-21.
//

#ifndef REPAIRCOMPRESSION_ENTRYPAIR_HPP
#define REPAIRCOMPRESSION_ENTRYPAIR_HPP
#include "Entry.hpp"
namespace RePairCompression {
struct EntryPair {
  int firstPosition;
  int secondPosition;
  EntryPair(int firstPosition, int secondPosition);
};
} // namespace RePairCompression
#endif // REPAIRCOMPRESSION_ENTRYPAIR_HPP
