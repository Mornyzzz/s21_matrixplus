#include "s21_matrix_oop.h"

using namespace std;

S21Matrix S21Matrix::operator+(const S21Matrix& o) {
  S21Matrix res(*this);
  res.SumMatrix(o);
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& o) {
  S21Matrix res(*this);
  res.SubMatrix(o);
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix& o) {
  S21Matrix res(*this);
  res.MulMatrix(o);
  return res;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix res(*this);
  res.MulNumber(num);
  return res;
}

bool S21Matrix::operator==(const S21Matrix& o) { return EqMatrix(o); }

void S21Matrix::operator=(const S21Matrix& o) {
  setRows(o.rows_);
  setCols(o.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; i < cols_; j++) {
      matrix_[i][j] = o.matrix_[i][j];
    }
  }
}

void S21Matrix::operator+=(const S21Matrix& o) { SumMatrix(o); }

void S21Matrix::operator-=(const S21Matrix& o) { SubMatrix(o); }

void S21Matrix::operator*=(const S21Matrix& o) { MulMatrix(o); }

void S21Matrix::operator*=(const double num) { MulNumber(num); }

double& S21Matrix::operator()(int row, int col) {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::out_of_range("Indexes outside the matrix");
  }
  return matrix_[row][col];
}