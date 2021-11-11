//
// Created by cristobal on 07-11-21.
//

#include <RePairCompression.hpp>
#include <chrono>
#include <cstddef>
#include <iostream>
#include <vector>
int main(int, char **) {
  const int dataSize = 10'000'000;

  std::vector<int> data;
  data.reserve(dataSize);
  for (size_t i = 0; i < dataSize; i++) {
    data.push_back(1);
  }

  auto start = std::chrono::high_resolution_clock::now();
  auto repairDs = RePairCompression::compressIntegerSequence(data);
  auto end = std::chrono::high_resolution_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);

  std::cout << "Compression Elapsed microseconds " << duration.count()
            << std::endl;

  start = std::chrono::high_resolution_clock::now();
  repairDs->decompressIntegerSequence();
  end = std::chrono::high_resolution_clock::now();

  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

  std::cout << "Decompression Elapsed microseconds " << duration.count()
            << std::endl;

  return 0;
}