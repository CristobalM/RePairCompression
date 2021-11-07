# RePair Compression

This is a C++ implementation of the RePair compression
(N. J. Larsson and A. Moffat, "Off-line dictionary-based compression," in Proceedings of the IEEE, vol. 88, no. 11, pp. 1722-1732, Nov. 2000, doi: 10.1109/5.892708).

# Build

```
mkdir build
cd build
cmake ..
make
```

# Usage

```
./build/CompressFile inputfile.txt outputfile.bin
./build/DecompressFile outputfile.bin decompressed.txt
```

# Library

* Include the src directory
* Link the static library libRePairCompression.a

# API Usage

```c++
auto rePairDs = RePairCompression::compress(inputString);
std::stringstream ss;
rePairDs->dump(ss);  // can be any std::ostream

auto deserialized = RePairCompression::load(ss); // can be any std::istream
auto decompressedString = deserialized->decompress();

// now decompressedString == inputString
```


