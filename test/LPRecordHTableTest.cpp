//
// Created by cristobal on 09-11-21.
//
#include <LPRecordHTable.hpp>
#include <gtest/gtest.h>

using namespace RePairCompression;

TEST(LPRecordHTableTestSuite, CanInsertAndFailOnReachingMaximumSize) {
  LPRecordHTable hTable(5, 0.75);
  for (int i = 0; i < 3; i++) {
    hTable.addRecord(ValuePair(i, i), 0, 1);
  }

  EXPECT_THROW(
      {
        try {
          hTable.addRecord(ValuePair(3, 3), 0, 1);
        } catch (const ReachedMaximumSizeError &e) {
          EXPECT_STREQ(e.what(), e.msgError());
          throw;
        }
      },
      ReachedMaximumSizeError);
}

TEST(LPRecordHTableTestSuite, CanInsertAndFindRecord1) {
  LPRecordHTable hTable;
  auto *recordInserted = hTable.addRecord(ValuePair(1, 1), 0, 1);
  auto *recordFound = hTable.findRecord(ValuePair(1, 1));
  ASSERT_EQ(recordInserted, recordFound);
}
TEST(LPRecordHTableTestSuite, CanInsertAndFindRecord2) {
  LPRecordHTable hTable;
  for (int i = 0; i < 100; i++) {
    auto *recordInserted = hTable.addRecord(ValuePair(i, i), 0, 1);
    auto *recordFound = hTable.findRecord(ValuePair(i, i));
    ASSERT_EQ(recordInserted, recordFound);
    ASSERT_EQ(hTable.getSize(), i + 1);
  }
}
TEST(LPRecordHTableTestSuite, CanInsertAndDeleteRecord1) {
  LPRecordHTable hTable;
  hTable.addRecord(ValuePair(1, 1), 0, 1);
  ASSERT_EQ(hTable.getSize(), 1);
  hTable.deleteRecord(ValuePair(1, 1));
  auto *recordFound = hTable.findRecord(ValuePair(1, 1));
  ASSERT_EQ(recordFound, nullptr);
  ASSERT_EQ(hTable.getSize(), 0);
}

TEST(LPRecordHTableTestSuite, CanInsertAndDeleteRecord2) {
  LPRecordHTable hTable(5, 0.75);
  for (int i = 0; i < 1'000'000; i++) {
    hTable.addRecord(ValuePair(i, i), 0, 1);
    ASSERT_EQ(hTable.getSize(), 1);
    hTable.deleteRecord(ValuePair(i, i));
    auto *recordFound = hTable.findRecord(ValuePair(i, i));
    ASSERT_EQ(recordFound, nullptr);
    ASSERT_EQ(hTable.getSize(), 0);
  }
}

TEST(LPRecordHTableTestSuite, CanInsertAndFindRecordWithSameKeySeveralTimes) {
  LPRecordHTable hTable;
  for (int i = 0; i < 100; i++) {
    auto *recordInserted = hTable.addRecord(ValuePair(1, 1), 0, 1);
    auto *recordFound = hTable.findRecord(ValuePair(1, 1));
    ASSERT_EQ(recordInserted, recordFound);
  }
}
