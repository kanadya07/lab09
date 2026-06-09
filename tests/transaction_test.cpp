#include "Account.h"
#include "Transaction.h"

#include <gtest/gtest.h>

TEST(Transaction, ThrowsOnSameAccount) {
  Transaction transaction;
  Account account(1, 1000);
  EXPECT_THROW(transaction.Make(account, account, 100), std::logic_error);
}

TEST(Transaction, ThrowsOnNegativeSum) {
  Transaction transaction;
  Account from(1, 1000);
  Account to(2, 1000);
  EXPECT_THROW(transaction.Make(from, to, -100), std::invalid_argument);
}

TEST(Transaction, ThrowsOnSmallSum) {
  Transaction transaction;
  Account from(1, 1000);
  Account to(2, 1000);
  EXPECT_THROW(transaction.Make(from, to, 50), std::logic_error);
}

TEST(Transaction, ReturnsFalseWhenFeeIsTooLarge) {
  Transaction transaction;
  Account from(1, 1000);
  Account to(2, 1000);
  transaction.set_fee(60);
  EXPECT_FALSE(transaction.Make(from, to, 100));
}

TEST(Transaction, ReturnsFalseWhenSourceBalanceIsNotEnough) {
  Transaction transaction;
  Account from(1, 100);
  Account to(2, 500);

  EXPECT_FALSE(transaction.Make(from, to, 200));
  EXPECT_EQ(from.GetBalance(), 100);
  EXPECT_EQ(to.GetBalance(), 500);
}

TEST(Transaction, TransfersMoneyAndSavesToDatabase) {
  Transaction transaction;
  Account from(1, 1000);
  Account to(2, 500);
  transaction.set_fee(50);

  EXPECT_TRUE(transaction.Make(from, to, 200));
  EXPECT_EQ(from.GetBalance(), 750);
  EXPECT_EQ(to.GetBalance(), 700);
}
