//
// Created by cristobal on 01-11-21.
//

#include <RePairCompression.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cout << "Expected: CompressFile <input_text_file> <output_binary_file>"
              << std::endl;
    return 1;
  }

  fs::path inputFilePath(argv[1]);
  fs::path outputFilePath(argv[2]);

  std::cout << "input file: " << inputFilePath << std::endl;
  std::cout << "output file: " << outputFilePath << std::endl;

  if (!fs::exists(inputFilePath)) {
    std::cout << "input filename " << inputFilePath << " does not exist"
              << std::endl;
    return 1;
  }

  std::stringstream ss;
  std::ifstream ifs(inputFilePath);
  ss << ifs.rdbuf();

  auto str = ss.str();
  std::cout << "compressing string of size: '" << str.size() << "'"
            << std::endl;
  auto rePairDs = RePairCompression::compress(std::move(str));
  std::cout << "compressed size: "
            << rePairDs->getCompressedIntegerSequence().size()
            << ", table size: " << rePairDs->getTable().size() << std::endl;

  std::ofstream ofs(outputFilePath, std::ios::out | std::ios::binary);
  rePairDs->dump(ofs);

  return 0;
}