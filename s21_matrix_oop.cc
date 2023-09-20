#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : S21Matrix(1, 1) {}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 1 || cols < 1) {
    throw std::out_of_range("Wrong count of rows or columns");
  }
  rows_ = rows;
  cols_ = cols;
  matrix_ = AllocateMatrix(rows, cols);
}

S21Matrix::S21Matrix(const S21Matrix& other) { this->CopyMatrix(other); }

S21Matrix::S21Matrix(S21Matrix&& other) noexcept {
  this->MoveMatrix((S21Matrix &&) other);
}

S21Matrix::~S21Matrix() { FreeMatrix(); }

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Wrong matrix size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Wrong matrix size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool flag = false;
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    flag = true;
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
          flag = false;
        }
      }
    }
  }
  return flag;
}

void S21Matrix::MultNumber(const double number) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= number;
    }
  }
}

void S21Matrix::MultMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "First matrix columns is not equil second matrix rows");
  }
  double** temp = AllocateMatrix(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int t = 0; t < cols_; t++) {
        temp[i][j] += matrix_[i][t] * other.matrix_[t][j];
      }
    }
  }
  FreeMatrix();
  matrix_ = temp;
  cols_ = other.cols_;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix new_matrix(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      new_matrix.matrix_[j][i] = matrix_[i][j];
    }
  }
  return new_matrix;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Rows and columns are not equil");
  }
  double d = 0;
  if (rows_ == 1) {
    d = matrix_[0][0];
  } else {
    for (int j = 0; j < cols_; j++) {
      double temp = 0;
      S21Matrix buffer(rows_ - 1, cols_ - 1);
      S21Matrix::Minor(0, j, buffer);
      temp = buffer.Determinant();
      d += matrix_[0][j] * pow(-1, (1 + (j + 1))) * temp;
      buffer.FreeMatrix();
    }
  }
  return d;
}

void S21Matrix::Minor(int l, int k, S21Matrix& other) {
  int r = 0;
  for (int i = 0; i < rows_; i++) {
    if (l != i) {
      int t = 0;
      for (int j = 0; j < cols_; j++) {
        if (k != j) {
          other.matrix_[r][t] = matrix_[i][j];
          t++;
        }
      }
      r++;
    }
  }
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_ || rows_ < 2) {
    throw std::invalid_argument(
        "Rows and columns are not equil or side less then 2");
  }
  S21Matrix new_matrix(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      double d = 0;
      S21Matrix minor(rows_ - 1, cols_ - 1);
      S21Matrix::Minor(i, j, minor);
      d = minor.Determinant();
      new_matrix.matrix_[i][j] = pow(-1, i + j) * d;
      minor.FreeMatrix();
    }
  }
  return new_matrix;
}

S21Matrix S21Matrix::InverseMatrix() {
  double d = Determinant();
  if (fabs(d) < 1e-7) {
    throw std::invalid_argument("Matrix determinant equil zero");
  }
  S21Matrix new_matrix(rows_, cols_);
  if (rows_ == cols_ && rows_ == 1) {
    new_matrix.matrix_[0][0] = 1 / matrix_[0][0];
  } else {
    new_matrix = CalcComplements();
    new_matrix.Transpose();
    new_matrix.MultNumber(1 / d);
  }
  return new_matrix;
}
