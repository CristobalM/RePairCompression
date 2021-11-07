//
// Created by cristobal on 01-11-21.
//

#ifndef REPAIRCOMPRESSION_SERIALIZATION_HPP
#define REPAIRCOMPRESSION_SERIALIZATION_HPP

#include <cstddef>
#include <istream>
#include <ostream>
namespace RePairCompression {
void write_u32(std::ostream &output_stream, uint32_t value);
uint32_t read_u32(std::istream &input_stream);
} // namespace RePairCompression

#endif // REPAIRCOMPRESSION_SERIALIZATION_HPP
