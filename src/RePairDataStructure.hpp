//
// Created by cristobal on 31-10-21.
//

#ifndef REPAIRCOMPRESSION_REPAIRDATASTRUCTURE_HPP
#define REPAIRCOMPRESSION_REPAIRDATASTRUCTURE_HPP

#include "TranslateTable.hpp"
#include <memory>
#include <string>
#include <vector>
namespace RePairCompression {
/*
 * Interface for RePair implementations
 */
class RePairDataStructure {
public:
  virtual std::string decompress() = 0;
  virtual std::vector<int> decompressIntegerSequence() = 0;
  virtual void dump(std::ostream &ostream) = 0;
  virtual const std::vector<int> &getCompressedIntegerSequence() = 0;
  virtual TranslateTable &getTable() = 0;
  virtual ~RePairDataStructure() = default;
};

} // namespace RePairCompression

#endif // REPAIRCOMPRESSION_REPAIRDATASTRUCTURE_HPP
