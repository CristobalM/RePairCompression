//
// Created by cristobal on 01-11-21.
//

#ifndef REPAIRCOMPRESSION_COMMONDEFINITIONS_HPP
#define REPAIRCOMPRESSION_COMMONDEFINITIONS_HPP
#include "Entry.hpp"
#include <vector>
namespace RePairCompression {
// using EntriesList = std::vector<Entry>;

struct EntryPairConnector {
  int left;
  int right;
};

struct EntriesList {
  std::vector<int> values;
  std::vector<EntryPairConnector> connectors;

  explicit EntriesList(int capacity)
      : values(capacity, -1), connectors(capacity, {-1, -1}) {}

  explicit EntriesList(std::vector<int> &&integerSequence)
      : values(std::move(integerSequence)),
        connectors(this->values.size(), {-1, -1}) {}

  explicit EntriesList(const std::vector<int> &integerSequence)
      : values(integerSequence.begin(), integerSequence.end()),
        connectors(this->values.size(), {-1, -1}) {}

  EntriesList(EntriesList &&) noexcept = default;
  EntriesList(const EntriesList &) = default;
  EntriesList &operator=(EntriesList &&) noexcept = default;
  EntriesList &operator=(const EntriesList &) = default;
};
} // namespace RePairCompression
#endif // REPAIRCOMPRESSION_COMMONDEFINITIONS_HPP
