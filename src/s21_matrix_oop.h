#ifndef CPP1_S21_MATRIXPLUS_11_MATRIX_PLUS_H
#define CPP1_S21_MATRIXPLUS_11_MATRIX_PLUS_H

#include <math.h>

#include <cstring>
#include <iostream>

#include "cfloat"

class S21Matrix {
 private:
  int rows_, cols_;  // Rows and columns
  double** matrix_;  // Pointer to the memory where the matrix is allocated

 public:
  S21Matrix();  // Default constructor
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();  // Destructor

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  double Minor(int index_i, int index_j);

  S21Matrix operator+(const S21Matrix& o);
  S21Matrix operator-(const S21Matrix& o);
  S21Matrix operator*(const S21Matrix& o);
  S21Matrix operator*(const double num);
  bool operator==(const S21Matrix& o);
  void operator=(const S21Matrix& o);
  void operator+=(const S21Matrix& o);
  void operator-=(const S21Matrix& o);
  void operator*=(const S21Matrix& o);
  void operator*=(const double num);
  double& operator()(int row, int col);

  int getRows();
  void setRows(int rows);
  int getCols();
  void setCols(int cols);

  //    void printMatrix();
  //    void fillMatrix();
};

#endif
