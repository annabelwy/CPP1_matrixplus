#include "s21_matrix_oop.h"

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetRows(int rows)
{
  if (rows <= 0)
  {
    throw std::logic_error("rows<0");
  }
  S21Matrix copyMatrix(rows, cols_);
  for (int i = 0; i < rows && i < rows_; i++)
  {
    for (int j = 0; j < cols_; j++)
    {
      copyMatrix.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = copyMatrix;
}

void S21Matrix::SetCols(int cols)
{
  if (cols <= 0)
  {
    throw std::logic_error("cols<0");
  }
  S21Matrix copyMatrix(rows_, cols);
  for (int i = 0; i < rows_; i++)
  {
    for (int j = 0; j < cols && j < cols_; j++)
    {
      copyMatrix.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = copyMatrix;
}

void S21Matrix::CreateMatrix()
{
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++)
  {
    matrix_[i] = new double[cols_]();
  }
}

S21Matrix::S21Matrix(int rows, int cols)
{
  if (rows <= 0 || cols <= 0)
  {
    throw std::logic_error("incorrect parameters");
  }
  rows_ = rows;
  cols_ = cols;
  CreateMatrix();
}

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(const S21Matrix &other)
    : S21Matrix(other.rows_, other.cols_)
{
  for (int i = 0; i < other.rows_; i++)
  {
    for (int j = 0; j < other.cols_; j++)
    {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}
S21Matrix::S21Matrix(S21Matrix &&other) noexcept
{
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

void S21Matrix::FreeMatrix()
{
  if (matrix_ != nullptr)
  {
    for (int i = 0; i < rows_; i++)
    {
      if (matrix_[i] != nullptr)
      {
        delete[] matrix_[i];
      }
    }
    delete[] matrix_;
    rows_ = 0;
    cols_ = 0;
    matrix_ = nullptr;
  }
}

S21Matrix::~S21Matrix() { FreeMatrix(); }

S21Matrix S21Matrix::Transpose()
{
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < result.rows_; i++)
  {
    for (int j = 0; j < result.cols_; j++)
    {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }
  return result;
}
double S21Matrix::Determinant()
{
  if (rows_ < 1 || cols_ < 1)
  {
    throw std::logic_error("matrix size is not correct");
  }
  else if (rows_ != cols_)
  {
    throw std::logic_error("matrix is ​​not square");
  }

  double result = 0;
  if (rows_ == 1)
  {
    result = matrix_[0][0];
  }
  else if (rows_ == 2)
  {
    result = matrix_[0][0] * matrix_[1][1] - (matrix_[0][1] * matrix_[1][0]);
  }
  else if (rows_ > 2)
  {
    for (int i = 0; i < rows_; i++)
    {
      S21Matrix res = MatrWithout(i, 0);
      result = result + pow(-1, i + 2) * matrix_[i][0] * res.Determinant();
    }
  }
  return result;
}

S21Matrix S21Matrix::MatrWithout(int i, int j)
{
  S21Matrix result(rows_ - 1, cols_ - 1);
  int for_rows = 0, for_columns = 0;
  for (int row = 0; row < rows_; row++)
  {
    if (row != i)
    {
      for (int col = 0; col < cols_; col++)
      {
        if (col != j)
        {
          result.matrix_[for_rows][for_columns] = matrix_[row][col];
          for_columns++;
        }
      }
      for_columns = 0;
      for_rows++;
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements()
{
  if (rows_ != cols_)
  {
    throw std::logic_error("matrix is ​​not square");
  }
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++)
  {
    for (int j = 0; j < cols_; j++)
    {
      S21Matrix res = MatrWithout(i, j);
      result.matrix_[i][j] = res.Determinant() * pow(-1, j + i);
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix()
{
  if (fabs(Determinant()) < acc)
  {
    throw std::logic_error("deteminant=0");
  }
  S21Matrix res = CalcComplements().Transpose();
  res.MulNumber(1.0 / Determinant());
  return res;
}