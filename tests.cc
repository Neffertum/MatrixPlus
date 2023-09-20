#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

void make_matrix(S21Matrix& a) {
  int t = 0;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      t++;
      a(i, j) = t;
    }
  }
}

TEST(Constructor, Default) {
  S21Matrix a;
  EXPECT_EQ(a.GetRows(), 1);
  EXPECT_EQ(a.GetCols(), 1);
}

TEST(Constructor, RowsCols) {
  S21Matrix a(3, 3);
  EXPECT_EQ(a.GetRows(), 3);
  EXPECT_EQ(a.GetCols(), 3);
}

TEST(Constructor, WrongRowsCols) {
  int rows = 2;
  int cols = 0;
  EXPECT_THROW(S21Matrix a(rows, cols), std::out_of_range);
}

TEST(Constructor, Copy) {
  S21Matrix a(3, 3);
  S21Matrix b(a);
  EXPECT_EQ(b.GetRows(), 3);
  EXPECT_EQ(b.GetCols(), 3);
}

TEST(Constructor, Move) {
  S21Matrix a(3, 3);
  S21Matrix b((S21Matrix &&) a);
  EXPECT_EQ(b.GetRows(), 3);
  EXPECT_EQ(b.GetCols(), 3);
}

TEST(Constructor, Free) {
  S21Matrix a(1, 1);
  a(0, 0) = 8;
  a.FreeMatrix();
  EXPECT_EQ(a.GetMatrix(), nullptr);
}

TEST(Operations, Sum_1) {
  S21Matrix a(4, 4);
  S21Matrix b(4, 4);
  make_matrix(a);
  make_matrix(b);
  a += b;
  S21Matrix check(4, 4);
  check(0, 0) = 2;
  check(1, 1) = 12;
  check(2, 2) = 22;
  check(3, 3) = 32;
  for (int i = 0; i < check.GetRows(); i++) {
    EXPECT_EQ(a(i, i), check(i, i));
  }
}

TEST(Operations, Sum_2) {
  S21Matrix a(4, 4);
  S21Matrix b(4, 4);
  make_matrix(a);
  make_matrix(b);
  S21Matrix c = a + b;
  S21Matrix check(4, 4);
  check(0, 0) = 2;
  check(1, 1) = 12;
  check(2, 2) = 22;
  check(3, 3) = 32;
  for (int i = 0; i < check.GetRows(); i++) {
    EXPECT_EQ(c(i, i), check(i, i));
  }
}

TEST(Operations, Sub_1) {
  S21Matrix a(4, 4);
  S21Matrix b(4, 4);
  make_matrix(a);
  make_matrix(b);
  a -= b;
  S21Matrix check(4, 4);
  check(0, 0) = 0;
  check(1, 1) = 0;
  check(2, 2) = 0;
  check(3, 3) = 0;
  for (int i = 0; i < check.GetRows(); i++) {
    EXPECT_EQ(a(i, i), check(i, i));
  }
}

TEST(Operations, Sub_2) {
  S21Matrix a(4, 4);
  S21Matrix b(4, 4);
  make_matrix(a);
  make_matrix(b);
  S21Matrix c = a - b;
  S21Matrix check(4, 4);
  check(0, 0) = 0;
  check(1, 1) = 0;
  check(2, 2) = 0;
  check(3, 3) = 0;
  for (int i = 0; i < check.GetRows(); i++) {
    EXPECT_EQ(c(i, i), check(i, i));
  }
}

TEST(Operations, Eq_1) {
  S21Matrix a(4, 4);
  S21Matrix b(4, 4);
  make_matrix(a);
  make_matrix(b);
  EXPECT_EQ(a == b, true);
}

TEST(Operations, Eq_2) {
  S21Matrix a(4, 4);
  S21Matrix b(4, 4);
  make_matrix(a);
  make_matrix(b);
  b(0, 0) = 40;
  EXPECT_EQ(a == b, false);
}

TEST(Operations, MultMatrix_1) {
  S21Matrix a(4, 4);
  S21Matrix b(4, 4);
  make_matrix(a);
  make_matrix(b);
  a *= b;
  S21Matrix check(4, 4);
  check(0, 0) = 90;
  check(1, 1) = 228;
  check(2, 2) = 398;
  check(3, 3) = 600;
  for (int i = 0; i < check.GetRows(); i++) {
    EXPECT_EQ(a(i, i), check(i, i));
  }
}

TEST(Operations, MultMatrix_2) {
  S21Matrix a(4, 4);
  S21Matrix b(4, 4);
  make_matrix(a);
  make_matrix(b);
  S21Matrix c = a * b;
  S21Matrix check(4, 4);
  check(0, 0) = 90;
  check(1, 1) = 228;
  check(2, 2) = 398;
  check(3, 3) = 600;
  for (int i = 0; i < check.GetRows(); i++) {
    EXPECT_EQ(c(i, i), check(i, i));
  }
}

TEST(Operations, MultNumber_1) {
  S21Matrix a(4, 4);
  make_matrix(a);
  a *= 3;
  S21Matrix check(4, 4);
  check(0, 0) = 3;
  check(1, 1) = 18;
  check(2, 2) = 33;
  check(3, 3) = 48;
  for (int i = 0; i < check.GetRows(); i++) {
    EXPECT_EQ(a(i, i), check(i, i));
  }
}

TEST(Operations, MultNumber_2) {
  S21Matrix a(4, 4);
  make_matrix(a);
  S21Matrix c = a * 3;
  S21Matrix check(4, 4);
  check(0, 0) = 3;
  check(1, 1) = 18;
  check(2, 2) = 33;
  check(3, 3) = 48;
  for (int i = 0; i < check.GetRows(); i++) {
    EXPECT_EQ(c(i, i), check(i, i));
  }
}

TEST(Operations, MultNumber_3) {
  S21Matrix a(4, 4);
  make_matrix(a);
  S21Matrix c = 3 * a;
  S21Matrix check(4, 4);
  check(0, 0) = 3;
  check(1, 1) = 18;
  check(2, 2) = 33;
  check(3, 3) = 48;
  for (int i = 0; i < check.GetRows(); i++) {
    EXPECT_EQ(c(i, i), check(i, i));
  }
}

TEST(Operations, Transpose) {
  S21Matrix a(4, 4);
  make_matrix(a);
  S21Matrix c = a.Transpose();
  S21Matrix check(4, 4);
  check(0, 2) = 9;
  check(1, 2) = 10;
  check(2, 2) = 11;
  check(3, 2) = 12;
  for (int i = 0; i < check.GetRows(); i++) {
    EXPECT_EQ(c(i, 2), check(i, 2));
  }
}

TEST(Operations, Determinant) {
  S21Matrix a(4, 4);
  make_matrix(a);
  a(0, 0) = -805;
  a(1, 1) = 506;
  double c = a.Determinant();
  double check = 1612000;
  EXPECT_EQ(c, check);
}

TEST(Operations, CalComplements) {
  S21Matrix a(4, 4);
  make_matrix(a);
  a(0, 0) = -805;
  a(1, 1) = 506;
  S21Matrix c = a.CalcComplements();
  S21Matrix check(4, 4);
  check(0, 0) = -2000;
  check(1, 1) = 3224;
  check(2, 2) = -6453104;
  check(3, 3) = -4437776;
  for (int i = 0; i < check.GetRows(); i++) {
    EXPECT_EQ(c(i, i), check(i, i));
  }
}

TEST(Operations, Invesre) {
  S21Matrix a(4, 4);
  make_matrix(a);
  a(0, 0) = -805;
  a(1, 1) = 506;
  S21Matrix c = a.InverseMatrix();
  S21Matrix check(4, 4);
  check(0, 0) = -1.0 / 806.0;
  check(1, 1) = 0.002;
  check(2, 2) = -403319.0 / 100750.0;
  check(3, 3) = -277361.0 / 100750.0;
  for (int i = 0; i < check.GetRows(); i++) {
    EXPECT_EQ(c(i, i), check(i, i));
  }
}

TEST(Help, Set) {
  S21Matrix a(4, 4);
  a.SetRows(3);
  a.SetCols(5);
  EXPECT_EQ(a.GetRows(), 3);
  EXPECT_EQ(a.GetCols(), 5);
}

TEST(Help, GetMatrix) {
  S21Matrix a(4, 4);
  make_matrix(a);
  for (int i = 0; i < a.GetRows(); i++) {
    EXPECT_EQ(a.GetMatrix()[i][i], a(i, i));
  }
}

TEST(Help, EqCopy) {
  S21Matrix a(4, 4);
  make_matrix(a);
  S21Matrix check;
  check = a;
  for (int i = 0; i < a.GetRows(); i++) {
    EXPECT_EQ(check(i, i), a(i, i));
  }
}

TEST(Help, EqMove) {
  S21Matrix a(4, 4);
  make_matrix(a);
  S21Matrix check;
  check = (S21Matrix &&) a;
  EXPECT_EQ(a.GetMatrix(), nullptr);
  EXPECT_EQ(check(1, 1), 6);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}