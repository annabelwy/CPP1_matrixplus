#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

void InitMatrix(S21Matrix *matrix, double number) {
  for (int i = 0; i < matrix->GetRows(); i++) {
    for (int j = 0; j < matrix->GetCols(); j++) {
      (*matrix)(i, j) = number;
    }
  }
}

void InitMatrix2(S21Matrix *matrix, double x) {
  for (int i = 0; i < matrix->GetRows(); i++) {
    for (int j = 0; j < matrix->GetCols(); j++) {
      (*matrix)(i, j) = x;
      x++;
    }
  }
}

void InitMatrix3(S21Matrix *matrix) {
  double x = 1;
  for (int i = 0; i < matrix->GetRows(); i++) {
    for (int j = 0; j < matrix->GetCols(); j++) {
      if (i == 0 && j > 0)
        (*matrix)(i, j) = 3;
      else
        (*matrix)(i, j) = x;
      x++;
    }
  }
}

TEST(Operation, eqMatrix) {
  S21Matrix matrix1 = S21Matrix(3, 3);
  S21Matrix matrix2 = S21Matrix(3, 3);
  InitMatrix(&matrix1, 48.4);
  InitMatrix(&matrix2, 48.4);
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}
TEST(Operation, eqMatrix2) {
  S21Matrix matrix1 = S21Matrix(3, 3);
  S21Matrix matrix2 = S21Matrix(3, 3);
  InitMatrix(&matrix1, 48.5);
  InitMatrix(&matrix2, 48.4);
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}
TEST(Operation, eqMatrix3) {
  S21Matrix matrix1 = S21Matrix(3, 4);
  S21Matrix matrix2 = S21Matrix(3, 3);
  InitMatrix(&matrix1, 48.5);
  InitMatrix(&matrix2, 48.5);
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(Operation, sumMatrix) {
  S21Matrix matrix1 = S21Matrix(5, 5);
  S21Matrix matrix2 = S21Matrix(5, 5);
  S21Matrix sum = S21Matrix(5, 5);
  InitMatrix(&matrix1, 18.4);
  InitMatrix(&matrix2, 15.0);
  InitMatrix(&sum, 33.4);
  matrix1.SumMatrix(matrix2);
  EXPECT_TRUE(matrix1.EqMatrix(sum));
}

TEST(Operation, sumMatrix2) {
  S21Matrix matrix1 = S21Matrix(5, 5);
  S21Matrix matrix2 = S21Matrix(5, 5);
  S21Matrix sum = S21Matrix(5, 5);
  InitMatrix(&matrix1, 25.7);
  InitMatrix(&matrix2, 15.0);
  InitMatrix(&sum, 33.4);
  matrix1.SubMatrix(matrix2);
  EXPECT_FALSE(matrix1.EqMatrix(sum));
}

TEST(Operation, subMatrix) {
  S21Matrix matrix1 = S21Matrix(5, 5);
  S21Matrix matrix2 = S21Matrix(5, 5);
  S21Matrix sub = S21Matrix(5, 5);
  InitMatrix(&matrix1, 50.67);
  InitMatrix(&matrix2, 15.0);
  InitMatrix(&sub, 35.67);
  matrix1.SubMatrix(matrix2);
  EXPECT_TRUE(matrix1.EqMatrix(sub));
}

TEST(Operation, subMatrix2) {
  S21Matrix matrix1 = S21Matrix(5, 5);
  S21Matrix matrix2 = S21Matrix(5, 5);
  S21Matrix sub = S21Matrix(5, 5);
  InitMatrix(&matrix1, 50.67);
  InitMatrix(&matrix2, 15.0);
  InitMatrix(&sub, 11.5);
  matrix1.SubMatrix(matrix2);
  EXPECT_FALSE(matrix1.EqMatrix(sub));
}

TEST(Operation, mulMatrix) {
  S21Matrix matrix1 = S21Matrix(5, 4);
  S21Matrix matrix2 = S21Matrix(4, 6);
  S21Matrix mul = S21Matrix(5, 6);
  InitMatrix(&matrix1, -1);
  InitMatrix(&matrix2, 4);
  InitMatrix(&mul, -16);
  matrix1.MulMatrix(matrix2);
  EXPECT_TRUE(matrix1.EqMatrix(mul));
}

TEST(Operation, mulNumber) {
  S21Matrix matrix1 = S21Matrix(5, 4);
  S21Matrix mul = S21Matrix(5, 4);
  InitMatrix(&matrix1, -1);
  InitMatrix(&mul, -16);
  matrix1.MulNumber(16);
  EXPECT_TRUE(matrix1.EqMatrix(mul));
}

TEST(Operation, transpose) {
  S21Matrix matrix = S21Matrix(7, 3);
  S21Matrix res = S21Matrix(3, 7);
  InitMatrix(&matrix, -1);
  InitMatrix(&res, -1);
  S21Matrix transpose = matrix.Transpose();
  EXPECT_TRUE(transpose.EqMatrix(res));
}

TEST(Operation, calcComplements) {
  S21Matrix matrix = S21Matrix(3, 3);
  S21Matrix dop = S21Matrix(3, 3);
  InitMatrix2(&matrix, 1);
  matrix(0, 0) = -3.0;
  matrix(0, 1) = 6.0;
  matrix(0, 2) = -3.0;
  matrix(1, 0) = 6.0;
  matrix(1, 1) = -12;
  matrix(1, 2) = 6;
  matrix(2, 0) = -3;
  matrix(2, 1) = 6;
  matrix(2, 2) = -3;
  S21Matrix res = matrix.CalcComplements();
  EXPECT_TRUE(res.EqMatrix(dop));
}

TEST(Operation, inverseMatrix) {
  S21Matrix matrix = S21Matrix(3, 3);
  InitMatrix3(&matrix);
  S21Matrix dop = S21Matrix(3, 3);
  dop(0, 0) = -1.0 / 2.0;
  dop(0, 1) = -1.0 / 2.0;
  dop(0, 2) = 1.0 / 2.0;
  dop(1, 0) = 1.0;
  dop(1, 1) = -2.0;
  dop(1, 2) = 1.0;
  dop(2, 0) = -1.0 / 2.0;
  dop(2, 1) = 13.0 / 6.0;
  dop(2, 2) = -7.0 / 6.0;
  S21Matrix res = matrix.InverseMatrix();
  EXPECT_TRUE(res.EqMatrix(dop));
}

TEST(Operation, operatorSum) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  S21Matrix dop(2, 2);
  InitMatrix2(&matrix1, 1);
  InitMatrix2(&matrix2, 0);
  dop(0, 0) = 1;
  dop(0, 1) = 3;
  dop(1, 0) = 5;
  dop(1, 1) = 7;
  S21Matrix sum = matrix1 + matrix2;
  EXPECT_TRUE(sum == dop);
}

TEST(Operation, operatorSum2) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  S21Matrix dop(2, 2);
  InitMatrix2(&matrix1, 1);
  InitMatrix2(&matrix2, 0);
  dop(0, 0) = 1;
  dop(0, 1) = 3;
  dop(1, 0) = 5;
  dop(1, 1) = 7;
  matrix1 += matrix2;
  EXPECT_TRUE(matrix1.EqMatrix(dop));
}

TEST(Operation, operatorSub) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  S21Matrix dop(2, 2);
  InitMatrix2(&matrix1, 1);
  InitMatrix2(&matrix2, 0);
  dop(0, 0) = 1;
  dop(0, 1) = 1;
  dop(1, 0) = 1;
  dop(1, 1) = 1;
  S21Matrix sum = matrix1 - matrix2;
  EXPECT_TRUE(sum == dop);
}

TEST(Operation, operatorSub2) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  S21Matrix dop(2, 2);
  InitMatrix2(&matrix1, 1);
  InitMatrix2(&matrix2, 0);
  dop(0, 0) = 1;
  dop(0, 1) = 1;
  dop(1, 0) = 1;
  dop(1, 1) = 1;
  matrix1 -= matrix2;
  EXPECT_TRUE(matrix1 == dop);
}

TEST(Operation, operatorMulMatrix) {
  S21Matrix matrix1(5, 4);
  S21Matrix matrix2(4, 6);
  S21Matrix dop(5, 6);
  InitMatrix(&matrix1, -1);
  InitMatrix(&matrix2, 4);
  InitMatrix(&dop, -16);
  S21Matrix mul = matrix1 * matrix2;
  EXPECT_TRUE(mul == dop);
}

TEST(Operation, operatorMulMatrix2) {
  S21Matrix matrix1(5, 4);
  S21Matrix matrix2(4, 6);
  S21Matrix dop(5, 6);
  InitMatrix(&matrix1, -1);
  InitMatrix(&matrix2, 4);
  InitMatrix(&dop, -16);
  matrix1 *= matrix2;
  EXPECT_TRUE(matrix1 == dop);
}

TEST(Operation, operatorMulNumber) {
  S21Matrix matrix(2, 2);
  S21Matrix dop(2, 2);
  InitMatrix(&matrix, 1);
  InitMatrix(&dop, 4);
  S21Matrix mul = matrix * 4;
  EXPECT_TRUE(mul == dop);
}

TEST(Operation, operatorMulNumber2) {
  S21Matrix matrix(2, 2);
  S21Matrix dop(2, 2);
  InitMatrix(&matrix, 1);
  InitMatrix(&dop, 4);
  matrix *= 4;
  EXPECT_TRUE(matrix == dop);
}

TEST(GetAndSet, setSize) {
  S21Matrix matrix1(3, 6);
  S21Matrix matrix2(5, 4);
  matrix2.SetRows(3);
  matrix2.SetCols(6);
  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(GetAndSet, getRows) {
  S21Matrix matrix(4, 7);
  int rows = matrix.GetRows();
  EXPECT_TRUE(rows == 4);
}

TEST(GetAndSet, getCols) {
  S21Matrix matrix(4, 7);
  int cols = matrix.GetCols();
  EXPECT_TRUE(cols == 7);
}

TEST(Construct, moveMatrix) {
  S21Matrix matrix(4, 5);
  InitMatrix2(&matrix, 1);
  S21Matrix dop(matrix);
  S21Matrix result(std::move(matrix));
  EXPECT_TRUE(result == dop);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
