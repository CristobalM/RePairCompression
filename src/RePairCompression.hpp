#ifndef REPAIRCOMPRESSION_REPAIRCOMPRESSION_HPP
#define REPAIRCOMPRESSION_REPAIRCOMPRESSION_HPP

#include "RePairDataStructure.hpp"
#include <memory>
#include <string>
namespace RePairCompression {
/**
 * Function to compress an inputString and returning a handler
 * which allows decompression and other functionalities over
 * the compressed string
 *
 * @param inputString string to compress
 * @return handler for the compressed string
 */
std::unique_ptr<RePairDataStructure> compress(const std::string &inputString);

/**
 * Function to compress an integerSequence and returning a handler
 * which allows decompression and other functionalities over
 * the compressed sequence
 * @param integerSequence integer sequence to compress
 * @return handler for the compressed integer sequence
 */
std::unique_ptr<RePairDataStructure>
compressIntegerSequence(const std::vector<int> &integerSequence);

std::unique_ptr<RePairDataStructure> load(std::istream &is);

} // namespace RePairCompression

#endif // REPAIRCOMPRESSION_REPAIRCOMPRESSION_HPP
