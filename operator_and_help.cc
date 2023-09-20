#include "s21_matrix_oop.h"

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix new_matrix(*this);
  new_matrix.SumMatrix(other);
  return new_matrix;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix new_matrix(*this);
  new_matrix.SubMatrix(other);
  return new_matrix;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix new_matrix(*this);
  new_matrix.MultMatrix(other);
  return new_matrix;
}

S21Matrix operator*(const S21Matrix& other, const double number) {
  S21Matrix new_matrix(other);
  new_matrix.MultNumber(number);
  return new_matrix;
}

S21Matrix operator*(const double number, const S21Matrix& other) {
  S21Matrix new_matrix(other);
  new_matrix.MultNumber(number);
  return new_matrix;
}

bool S21Matrix::operator==(const S21Matrix& other) {
  return this->EqMatrix(other);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  this->CopyMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  this->MoveMatrix((S21Matrix &&) other);
  return *this;
}

void S21Matrix::operator+=(const S21Matrix& other) { this->SumMatrix(other); }

void S21Matrix::operator-=(const S21Matrix& other) { this->SubMatrix(other); }

void S21Matrix::operator*=(const S21Matrix& other) { this->MultMatrix(other); }

void S21Matrix::operator*=(const double number) { this->MultNumber(number); }

double& S21Matrix::operator()(int rows, int cols) const {
  if (rows >= rows_ || cols >= cols_ || rows < 0 || cols < 0) {
    throw std::logic_error("Wrong matrix index");
  }
  return matrix_[rows][cols];
}

void S21Matrix::FreeMatrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

double** S21Matrix::AllocateMatrix(int rows, int cols) {
  double** temp = new double*[rows];
  for (int i = 0; i < rows; i++) {
    temp[i] = new double[cols];
    for (int j = 0; j < cols; j++) {
      temp[i][j] = 0;
    }
  }
  return temp;
}

void S21Matrix::CopyMatrix(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = AllocateMatrix(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::MoveMatrix(S21Matrix&& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

void S21Matrix::SetRows(int rows) {
  if (rows < 1) {
    throw std::invalid_argument("Rows cannot be less then 1");
  }
  double** new_matrix = AllocateMatrix(rows, cols_);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols_; j++) {
      if (i >= rows_) {
        new_matrix[i][j] = 0.0;
      } else {
        new_matrix[i][j] = matrix_[i][j];
      }
    }
  }
  FreeMatrix();
  rows_ = rows;
  matrix_ = new_matrix;
}

void S21Matrix::SetCols(int cols) {
  if (cols < 1) {
    throw std::invalid_argument("Rows cannot be less then 1");
  }
  double** new_matrix = AllocateMatrix(rows_, cols);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols; j++) {
      if (j >= cols_) {
        new_matrix[i][j] = 0.0;
      } else {
        new_matrix[i][j] = matrix_[i][j];
      }
    }
  }
  FreeMatrix();
  cols_ = cols;
  matrix_ = new_matrix;
}