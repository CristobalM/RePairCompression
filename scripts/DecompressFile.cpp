//
// Created by cristobal on 01-11-21.
//

#include <RePairCompression.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cout << "Expected: DecompressFile <input_compressed_file> "
                 "<output_decompressed_file>"
              << std::endl;
    return 1;
  }

  fs::path inputFilePath(argv[1]);
  fs::path outputFilePath(argv[2]);

  std::cout << "input compressed file: " << inputFilePath << std::endl;
  std::cout << "output decompressed file: " << outputFilePath << std::endl;

  if (!fs::exists(inputFilePath)) {
    std::cout << "input filename " << inputFilePath << " does not exist"
              << std::endl;
    return 1;
  }

  std::stringstream ss;
  std::ifstream ifs(inputFilePath, std::ios::in | std::ios::binary);

  auto rePairDs = RePairCompression::load(ifs);
  auto decompressed = rePairDs->decompress();

  std::ofstream ofs(outputFilePath, std::ios::out);
  ofs << decompressed;

  return 0;
}