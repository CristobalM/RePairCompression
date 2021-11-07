//
// Created by cristobal on 31-10-21.
//
#include <RePairCompression.hpp>
#include <gtest/gtest.h>
#include <random>

std::string randomStringGenerator(std::size_t length, int seed = 12345) {
  static const std::string characters =
      "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

  std::mt19937 generator(seed);
  std::uniform_int_distribution<> distribution(0, characters.size() - 1);
  std::stringstream ss;

  for (std::size_t i = 0; i < length; ++i) {
    ss << characters[distribution(generator)];
  }

  return ss.str();
}

TEST(CompressionTestSuite, CanCompressAndDecompressString) {
  std::string inputString("Hello, this is some string to be compressed");
  auto repairDs = RePairCompression::compress(inputString);
  auto decompressedString = repairDs->decompress();
  ASSERT_EQ(decompressedString, inputString);
}

TEST(CompressionTestSuite, CanCompressAndDecompressString2) {
  auto inputString = randomStringGenerator(886);
  auto repairDs = RePairCompression::compress(inputString);
  auto decompressedString = repairDs->decompress();
  ASSERT_EQ(decompressedString, inputString);
}

TEST(CompressionTestSuite, CanCompressAndDecompressString3) {
  auto inputString = "AAAAAAAAAAAAEEEEEEEEAAAAAAAAAAAAAAA";
  auto repairDs = RePairCompression::compress(inputString);
  auto decompressedString = repairDs->decompress();
  ASSERT_EQ(decompressedString, inputString);
}

TEST(CompressionTestSuite, CanCompressAndDecompressString4) {
  auto inputString = "aa";
  auto repairDs = RePairCompression::compress(inputString);
  auto decompressedString = repairDs->decompress();
  ASSERT_EQ(decompressedString, inputString);
}
TEST(CompressionTestSuite, CanCompressAndDecompressString5) {
  auto inputString = "aaa";
  auto repairDs = RePairCompression::compress(inputString);
  auto decompressedString = repairDs->decompress();
  ASSERT_EQ(decompressedString, inputString);
}

TEST(CompressionTestSuite, CanCompressAndDecompressString6) {
  auto inputString = "aaaa";
  auto repairDs = RePairCompression::compress(inputString);
  auto decompressedString = repairDs->decompress();
  ASSERT_EQ(decompressedString, inputString);
}
TEST(CompressionTestSuite, CanCompressAndDecompressString7) {
  auto inputString = "abbabb";
  auto repairDs = RePairCompression::compress(inputString);
  auto decompressedString = repairDs->decompress();
  ASSERT_EQ(decompressedString, inputString);
}
TEST(CompressionTestSuite, CanCompressAndDecompressString8) {
  auto inputString = "aabbbbaaaa";
  auto repairDs = RePairCompression::compress(inputString);
  auto decompressedString = repairDs->decompress();
  ASSERT_EQ(decompressedString, inputString);
}
TEST(CompressionTestSuite, CanCompressAndDecompressString9) {
  auto inputString = "aaaaaaaaaabbbbbaaaa";
  auto repairDs = RePairCompression::compress(inputString);
  auto decompressedString = repairDs->decompress();
  ASSERT_EQ(decompressedString, inputString);
}
TEST(CompressionTestSuite, CanCompressAndDecompressString10) {
  auto inputString = "AAAAAAAAAAAEEEEEEEEAAAAAAAAAAAAAAA";
  auto repairDs = RePairCompression::compress(inputString);
  auto decompressedString = repairDs->decompress();
  ASSERT_EQ(decompressedString, inputString);
}
TEST(CompressionTestSuite, CanCompressAndDecompressString11) {
  auto inputString = "aaaaaaaaaaaa";
  auto repairDs = RePairCompression::compress(inputString);
  auto decompressedString = repairDs->decompress();
  ASSERT_EQ(decompressedString, inputString);
}

TEST(CompressionTestSuite, CanCompressAndDecompressString12) {
  auto inputString =
      "HOHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
  auto repairDs = RePairCompression::compress(inputString);
  auto decompressedString = repairDs->decompress();
  ASSERT_EQ(decompressedString, inputString);
}

TEST(CompressionTestSuite, CanCompressAndDecompressString13) {
  auto inputString =
      "vtJ8B2CpZWaxxSevkNe9ktx10I6OIoecousYxqi3dnivSMKgR8jpzJfjnaAM1nnhuo1tUpWu"
      "ay3etoj6oEVNoh5UDPGdTlSYhgBuW1AplNvIb09RUjNNqUu0NFJLZnBw76gjnyZhyxdvtPUK"
      "LliKV5DtFmniURukweXMFNieM3U4E5Lne4JDl9mgq7wF6Ru6KJpLtl26CvIKcQ5G8mVSg5r4"
      "eKaBipF3tYRZ1SxweLVsgQUzvnVw4NZPcHwRPlGZ6NUcSj1uhWiWj6P70duRm4A9J4bsMA9v"
      "A0rnHIaFSlPhssguHD3QCAvDqqxu3gZPTD1pNmPjbrfyqPmbOjnGtlGvzsq7jxMIsbrAxr0j"
      "14JWza9SAalJ4oh5TA0DmTnu9z1blvDMG0SeFAZUqnNoQMp7NC21YdRTiDNGqBTtYie4SFcv"
      "DCjSNlCXGYFE9Hl1FQ72f3PJfReAIICRDT7h2h2aEyEfcstPmni8JGMECXwhYFoCLmnP6Qic"
      "ugnQKIFzUCPYQT45bJkbn3NMn7T1ijBGQipgpoBn1bhVLQQ6lUxOta8RnEgdWErFky5RK5P7"
      "0SbmgOMcOnTUa28izgVJUpB2Idn1IjhOGWuSIftqwJAJMAggvo8B62PVym2cBwbE5mJPbhCF"
      "gVFHgDUvGmHGuEHnqACIKowRVqPw1CcvLOHT3DKi4d0u2ULE5gWeDlzcGhgfWTRuf18umR8X"
      "d1Dr1dcUdNd0rjKFPyb5wS9dBN99iTvXQxXgJS9ShBjzxzMeiozK63l89Co2YhaCwFQqUefn"
      "dJ8oLsdgun5s4JPqDnWZY6TkDhEBDqepquvrnDgKC2jEh7NHqRWrtKozExoh8fT29mRWffmQ"
      "f2ietZ8h9hKE1zg7lCLxcv";
  auto repairDs = RePairCompression::compress(inputString);
  auto decompressedString = repairDs->decompress();
  ASSERT_EQ(decompressedString, inputString);
}

TEST(CompressionTestSuite, CanCompressAndDecompressString14) {
  auto inputString =
      "Zi4ktKvMgXXUBucCN3vWecfWvjfbEWFLDO5cBSi7zM8aDBHYkAyVmbhxwP4sDffOnzdK2jHz"
      "5oscxRjg1bkEtIGovaPUPLCXz0JkBb0XnKVQTTmHHf6isWw8bZdeU3jcxyW3n8Uolma2TkUB"
      "TbQCmF7f8KLH7zhUa5HKX3oFaK58RjBLjtxgZmfbM6FUAf6PeuUB6c0EWJV8dzKDuuVaG5P3"
      "7G0Cup0LDOU5iq5EraIQYZd53tZbuE4tIDeNEIPMinCWaemnzYj3qNqlkiaryiPOt1OSbHlS"
      "hUB";
  auto repairDs = RePairCompression::compress(inputString);
  auto decompressedString = repairDs->decompress();
  ASSERT_EQ(decompressedString, inputString);
}

TEST(CompressionTestSuite, CanCompressAndDecompressString15) {
  auto inputString =
      "AAABAABAAAABAAEEEEEEEEEEEEEEEEAAABAABAAAABAAEEEEEEEEEEEEEEEE";
  auto repairDs = RePairCompression::compress(inputString);
  auto decompressedString = repairDs->decompress();
  ASSERT_EQ(decompressedString, inputString);
}

TEST(CompressionTestSuite, CanCompressAndDecompressString16) {
  auto inputString = "AAABAABAAAABAAEEEAAABAABAAAABAAEEE";
  auto repairDs = RePairCompression::compress(inputString);
  auto decompressedString = repairDs->decompress();
  ASSERT_EQ(decompressedString, inputString);
}

TEST(CompressionTestSuite, CanCompressAndDecompressString17) {
  auto inputString = "BAABAAAABAABAABAAAABAA";
  auto repairDs = RePairCompression::compress(inputString);
  auto decompressedString = repairDs->decompress();
  ASSERT_EQ(decompressedString, inputString);
}

TEST(CompressionTestSuite, CanCompressAndDecompressString18) {
  auto inputString = "BABABABA";
  auto repairDs = RePairCompression::compress(inputString);
  auto decompressedString = repairDs->decompress();
  ASSERT_EQ(decompressedString, inputString);
}

TEST(CompressionTestSuite, CanCompressAndDecompressString19) {
  auto inputString = "HOlaHolaHolaAHOHOla";
  auto repairDs = RePairCompression::compress(inputString);
  auto decompressedString = repairDs->decompress();
  ASSERT_EQ(decompressedString, inputString);
}

TEST(CompressionTestSuite, CanCompressAndDecompressString20) {
  auto inputString = "HOlalaHOHOla";
  auto repairDs = RePairCompression::compress(inputString);
  auto decompressedString = repairDs->decompress();
  ASSERT_EQ(decompressedString, inputString);
}

TEST(CompressionTestSuite, CanCompressAndDecompressString21) {
  auto inputString = "HOlalaHOHOla";
  auto repairDs = RePairCompression::compress(inputString);
  auto decompressedString = repairDs->decompress();
  ASSERT_EQ(decompressedString, inputString);
}

TEST(CompressionTestSuite, CanCompressAndDecompressString22) {
  auto inputString = "AAAAAAAAAAAA";
  auto repairDs = RePairCompression::compress(inputString);
  auto decompressedString = repairDs->decompress();
  ASSERT_EQ(decompressedString, inputString);
}

TEST(CompressionTestSuite, CanCompressAndDecompressString23) {
  auto inputString = "AAAAAA";
  auto repairDs = RePairCompression::compress(inputString);
  auto decompressedString = repairDs->decompress();
  ASSERT_EQ(decompressedString, inputString);
}

TEST(CompressionTestSuite, CanCompressAndDecompressString24) {
  auto inputString =
      "HOHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
  auto repairDs = RePairCompression::compress(inputString);
  auto decompressedString = repairDs->decompress();
  ASSERT_EQ(decompressedString, inputString);
}

TEST(CompressionTestSuite, CanCompressAndDecompressString25) {
  auto inputString =
      "HOHOlaHolaHolaAHOlaHolaHolaAAAA"
      "HOHOlaHolaHolaOlaHolaHolaAAAA"
      "VHOlaHolaHola"
      "AAHOlaHolaHolaHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAHOlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAlaHolaHolaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
  auto repairDs = RePairCompression::compress(inputString);
  auto decompressedString = repairDs->decompress();
  ASSERT_EQ(decompressedString, inputString);
}

TEST(CompressionTestSuite, CanCompressAndDecompressString26) {
  auto inputString =
      "ZRZZZZZRZZZZZRZZZZZRZZZZZRZZZZZRZZZZZRZZZZZRZZZZZRZZZZZRZZZZZRZZZZZRZZZZ"
      "ZRZZZZZRZZZZZRZZZZZRZZZZZRZZZZZRZZZZZRZZZZZRZZZZ";
  auto repairDs = RePairCompression::compress(inputString);
  auto decompressedString = repairDs->decompress();
  ASSERT_EQ(decompressedString, inputString);
}

TEST(CompressionTestSuite, CanCompressAndDecompressString27) {
  auto inputString = "10001000001000001000";
  auto repairDs = RePairCompression::compress(inputString);
  auto decompressedString = repairDs->decompress();

  ASSERT_EQ(decompressedString, inputString);
}

TEST(CompressionTestSuite, CanCompressAndDecompressInteger1) {
  std::vector<int> inputIntegers = {
      1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  };
  auto repairDs = RePairCompression::compressIntegerSequence(inputIntegers);
  auto decompressed = repairDs->decompressIntegerSequence();
  ASSERT_EQ(decompressed, inputIntegers);
}

TEST(CompressionTestSuite, CanCompressAndDecompressInteger2) {
  std::vector<int> inputIntegers = {
      1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
  };
  auto repairDs = RePairCompression::compressIntegerSequence(inputIntegers);
  auto decompressed = repairDs->decompressIntegerSequence();
  ASSERT_EQ(decompressed, inputIntegers);
}

TEST(CompressionTestSuite, CanCompressAndDecompressInteger3) {

  std::vector<int> inputIntegers = {
      1, 0, 0, 0, 1, 1, 0, 0, 0,
  };
  auto repairDs = RePairCompression::compressIntegerSequence(inputIntegers);
  auto decompressed = repairDs->decompressIntegerSequence();
  ASSERT_EQ(decompressed, inputIntegers);
}

TEST(CompressionTestSuite, CanCompressAndDecompressStringSingleCharSeveral) {
  int range = 3;
  int start = 100000;
  for (int i = start; i < start + range; i++) {
    std::stringstream ss;
    for (int j = 0; j < i; j++) {
      ss << "Z";
    }
    auto inputString = ss.str();
    auto repairDs = RePairCompression::compress(inputString);
    auto decompressedString = repairDs->decompress();
    ASSERT_EQ(decompressedString, inputString);
  }
}

TEST(CompressionTestSuite, CanCompressAndDecompressStringSingleCharSeveral2) {
  int range = 200;
  int start = 1;
  for (int i = start; i < start + range; i++) {
    std::stringstream ss;
    for (int j = 0; j < i; j++) {
      ss << "Z";
      if (j % 5 == 0) {
        ss << "R";
      }
    }
    auto inputString = ss.str();
    auto repairDs = RePairCompression::compress(inputString);
    auto decompressedString = repairDs->decompress();
    ASSERT_EQ(decompressedString, inputString);
  }
}

TEST(CompressionTestSuite, CanCompressAndDecompressStringSeveralRandom) {
  for (size_t stringSize = 1; stringSize < 100; stringSize++) {
    for (int seed = 0; seed < 100; seed++) {
      auto inputString = randomStringGenerator(stringSize, seed);
      auto repairDs = RePairCompression::compress(inputString);
      auto decompressedString = repairDs->decompress();
      ASSERT_EQ(decompressedString, inputString);
    }
  }
}
TEST(CompressionTestSuite, CanCompressAndDecompressStringSeveralRandom2) {
  for (size_t stringSize = 500; stringSize < 1000; stringSize++) {
    for (int seed = 0; seed < 10; seed++) {
      auto inputString = randomStringGenerator(stringSize, seed);
      auto repairDs = RePairCompression::compress(inputString);
      auto decompressedString = repairDs->decompress();
      ASSERT_EQ(decompressedString, inputString)
          << "failed at stringSize=" << stringSize << " seed=" << seed;
    }
  }
}

TEST(CompressionTestSuite, CanCompressIntegerSequenceAndDecompressIt) {
  std::vector<int> integerSequence = {3, 4,   5,   9,     8,   7,    5,     3,
                                      2, 123, 321, 91919, 231, 1923, 939393};
  auto repairDs = RePairCompression::compressIntegerSequence(integerSequence);
  auto decompressedSequence = repairDs->decompressIntegerSequence();
  ASSERT_EQ(decompressedSequence, integerSequence);
}

TEST(CompressionTestSuite, CanSerializeAndDeserialize) {
  std::vector<int> integerSequence = {3, 4,   5,   9,     8,   7,    5,     3,
                                      2, 123, 321, 91919, 231, 1923, 939393};
  auto repairDs = RePairCompression::compressIntegerSequence(integerSequence);
  std::stringstream ss;
  repairDs->dump(ss);
  auto deserialized = RePairCompression::load(ss);
  auto decompressed = deserialized->decompressIntegerSequence();
  ASSERT_EQ(decompressed, integerSequence);
}

TEST(CompressionTestSuite, CompressedUsesLessSpace) {
  std::vector<int> integerSequence = {
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
  };
  auto repairDs = RePairCompression::compressIntegerSequence(integerSequence);
  const auto &compressedIntegerSequence =
      repairDs->getCompressedIntegerSequence();
  ASSERT_LT(compressedIntegerSequence.size(), integerSequence.size());
}

template <typename TList, typename T>
static int getPos(T value, const TList &where) {
  auto itPos = std::find(where.begin(), where.end(), value);
  if (itPos == where.end())
    throw std::runtime_error("getPos: not found");
  return (int)(itPos - where.begin());
}

TEST(CompressionTestSuite, CanDecompressFromOffsetUntilGivenTerminator) {
  std::vector<int> inputSequence = {
      0, 0, 0,   0, 0, 0, 100, 1, 1, 1,   1, 1, 1, 101, 2, 2, 2,   3,
      3, 3, 102, 4, 4, 4, 1,   1, 1, 103, 1, 4, 0, 0,   1, 1, 104,
  };

  auto pos0 = getPos(100, inputSequence);
  auto pos1 = getPos(101, inputSequence);
  auto pos2 = getPos(102, inputSequence);
  auto pos3 = getPos(103, inputSequence);
  auto pos4 = getPos(104, inputSequence);

  auto part1 =
      std::vector<int>(inputSequence.begin(), inputSequence.begin() + pos0);
  auto part2 = std::vector<int>(inputSequence.begin() + pos0,
                                inputSequence.begin() + pos1);
  auto part3 = std::vector<int>(inputSequence.begin() + pos1,
                                inputSequence.begin() + pos2);
  auto part4 = std::vector<int>(inputSequence.begin() + pos2,
                                inputSequence.begin() + pos3);
  auto part5 = std::vector<int>(inputSequence.begin() + pos3,
                                inputSequence.begin() + pos4);

  auto repairDs = RePairCompression::compressIntegerSequence(inputSequence);
  const auto &compressedIntegerSequence =
      repairDs->getCompressedIntegerSequence();

  auto cPos0 = getPos(100, compressedIntegerSequence);
  auto cPos1 = getPos(101, compressedIntegerSequence);
  auto cPos2 = getPos(102, compressedIntegerSequence);
  auto cPos3 = getPos(103, compressedIntegerSequence);

  auto decompressedPortion =
      repairDs->decompressIntegerSequenceFromOffsetToTerminator(0, 100);
  ASSERT_EQ(decompressedPortion, part1);
  auto decompressedPortion2 =
      repairDs->decompressIntegerSequenceFromOffsetToTerminator(cPos0, 101);
  ASSERT_EQ(decompressedPortion2, part2);
  auto decompressedPortion3 =
      repairDs->decompressIntegerSequenceFromOffsetToTerminator(cPos1, 102);
  ASSERT_EQ(decompressedPortion3, part3);
  auto decompressedPortion4 =
      repairDs->decompressIntegerSequenceFromOffsetToTerminator(cPos2, 103);
  ASSERT_EQ(decompressedPortion4, part4);
  auto decompressedPortion5 =
      repairDs->decompressIntegerSequenceFromOffsetToTerminator(cPos3, 104);
  ASSERT_EQ(decompressedPortion5, decompressedPortion5);
}