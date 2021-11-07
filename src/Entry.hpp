//
// Created by cristobal on 31-10-21.
//

#ifndef REPAIRCOMPRESSION_ENTRY_HPP
#define REPAIRCOMPRESSION_ENTRY_HPP

namespace RePairCompression {
struct Entry {
  int left;
  int right;
  int value;
  Entry(int left, int right, int value)
      : left(left), right(right), value(value) {}
};

} // namespace RePairCompression

#endif // REPAIRCOMPRESSION_ENTRY_HPP
