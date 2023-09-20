#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <cmath>
#include <iostream>

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix() noexcept;

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MultNumber(const double number);
  void MultMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  friend S21Matrix operator*(const S21Matrix& other, const double number);
  friend S21Matrix operator*(const double number, const S21Matrix& other);
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other);
  void operator+=(const S21Matrix& other);
  void operator-=(const S21Matrix& other);
  void operator*=(const S21Matrix& other);
  void operator*=(const double number);
  double& operator()(const int rows, const int cols) const;

  void FreeMatrix();
  double** AllocateMatrix(int rows, int cols);
  void CopyMatrix(const S21Matrix& other);
  void MoveMatrix(S21Matrix&& other);
  int GetRows() const { return rows_; }
  int GetCols() const { return cols_; }
  double** GetMatrix() const { return matrix_; }
  void SetRows(int rows);
  void SetCols(int cols);
  void Minor(int l, int k, S21Matrix& other);

 private:
  double** matrix_;
  int rows_, cols_;
};

S21Matrix operator*(const S21Matrix& other, const double number);
S21Matrix operator*(const double number, const S21Matrix& other);

#endif  //  SRC_S21_MATRIX_H_
