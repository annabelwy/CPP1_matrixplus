#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <stdexcept>
constexpr double acc = 1e-07;
class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other) noexcept;
  ~S21Matrix();
  int GetRows() const;
  int GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);

  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  bool EqMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  double Determinant();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();

  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(const double num);
  S21Matrix &operator=(S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other) noexcept;
  bool operator==(const S21Matrix &other);
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(const double num);
  double &operator()(int i, int j);
  const double &operator()(int i, int j) const;

 private:
  int rows_, cols_;
  double **matrix_;
  void FreeMatrix();
  S21Matrix MatrWithout(int i, int j);
  void CreateMatrix();
};
#endif  // SRC_S21_MATRIX_OOP_H_