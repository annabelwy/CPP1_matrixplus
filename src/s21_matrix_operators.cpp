#include "s21_matrix_oop.h"
S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (this->cols_ != other.cols_ || this->rows_ != other.rows_) {
    throw std::logic_error("different sizes");
  }
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = this->matrix_[i][j] + other.matrix_[i][j];
    }
  }
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (this != &other) {
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    this->matrix_ = other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &other) {
  if (this == &other) return *this;
  this->FreeMatrix();
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->CreateMatrix();
  this->SumMatrix(other);
  return *this;
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (this->cols_ != other.cols_ || this->rows_ != other.rows_) {
    throw std::logic_error("different sizes");
  }
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  this->SubMatrix(other);
  return *this;
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (this->cols_ != other.rows_) {
    throw std::logic_error("cols A !=rows B");
  }
  S21Matrix res(this->rows_, other.cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      double mult = 0;
      for (int kol = 0; kol < other.rows_; kol++) {
        mult += this->matrix_[i][kol] * other.matrix_[kol][j];
      }
      res.matrix_[i][j] = mult;
    }
  }
  *this = res;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  this->MulMatrix(other);
  return *this;
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = this->matrix_[i][j] * num;
    }
  }
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix res(*this);
  res.MulNumber(num);
  return res;
}

S21Matrix &S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}
bool S21Matrix::EqMatrix(const S21Matrix &other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) return false;

  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      double accuracy = fabs(this->matrix_[i][j] - other.matrix_[i][j]);
      if (accuracy > acc) return false;
    }
  }
  return true;
}

bool S21Matrix::operator==(const S21Matrix &other) {
  return this->EqMatrix(other);
}

const double &S21Matrix::operator()(int i, int j) const {
  if (i >= this->rows_ || j >= this->cols_ || i < 0 || j < 0) {
    throw std::logic_error("index outside matrix");
  }
  return this->matrix_[i][j];
}

double &S21Matrix::operator()(int i, int j) {
  if (i >= this->rows_ || j >= this->cols_ || i < 0 || j < 0) {
    throw std::logic_error("index outside matrix");
  }
  return this->matrix_[i][j];
}
