#include "s21_matrix_oop.h"

using namespace std;

S21Matrix::S21Matrix() {
  rows_ = 5;
  cols_ = 5;
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = 0;
    }
  }
}

S21Matrix::S21Matrix(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = 0;
    }
  }
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;

  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
      matrix_[i] = nullptr;
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}

int S21Matrix::getRows() { return this->rows_; }

void S21Matrix::setRows(int rows) {
  // init new matrix
  double** temp_ = new double*[rows];
  for (int i = 0; i < rows; i++) {
    temp_[i] = new double[cols_];
  }

  // fill
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols_; j++) {
      if (i < rows_)
        temp_[i][j] = matrix_[i][j];
      else
        temp_[i][j] = 0;
    }
  }

  // transfer
  if (matrix_) {
    for (int i = 0; i < rows_; i++) delete[] matrix_[i];
    delete[] matrix_;
  }
  matrix_ = temp_;

  // set
  rows_ = rows;
}

int S21Matrix::getCols() { return this->cols_; }

void S21Matrix::setCols(int cols) {
  // init new matrix
  double** temp_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    temp_[i] = new double[cols];
  }

  // fill
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols; j++) {
      if (j < cols_)
        temp_[i][j] = matrix_[i][j];
      else
        temp_[i][j] = 0;
    }
  }

  // transfer
  if (matrix_) {
    for (int i = 0; i < rows_; i++) delete[] matrix_[i];
    delete[] matrix_;
  }
  matrix_ = temp_;
  //    for (int i = 0; i < rows_; i ++)
  //        delete[] temp_[i];
  //    delete[] temp_;

  // set
  cols_ = cols;
}

// void S21Matrix::printMatrix() {
//     cout << "\n";
//     for (int i = 0; i < rows_; i ++) {
//         for (int j = 0; j < cols_; j ++) {
//             cout << matrix_[i][j] << " ";
//         }
//         cout << "\n";
//     }
// }
//
// void S21Matrix::fillMatrix() {
//     for (int i = 0; i < rows_; i ++) {
//         for (int j = 0; j < cols_; j ++) {
//             matrix_[i][j] = i * cols_ + j;
//         }
//     }
// }

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) >= 1e-7) {
        return false;
      }
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw out_of_range("Incorrect input, matrices should have the same size");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (matrix_[i][j] + other.matrix_[i][j] > DBL_MAX ||
          matrix_[i][j] + other.matrix_[i][j] < -DBL_MAX)
        throw overflow_error("The sum of the elements exceeds DBL_MAX");
    }
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw out_of_range("Incorrect input, matrices should have the same size");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (matrix_[i][j] - other.matrix_[i][j] > DBL_MAX ||
          matrix_[i][j] - other.matrix_[i][j] < -DBL_MAX)
        throw overflow_error("The sub of the elements exceeds DBL_MAX");
    }
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (matrix_[i][j] * num > DBL_MAX || matrix_[i][j] * num < -DBL_MAX)
        throw overflow_error("The mult by a number exceeds DBL_MAX");
    }
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw out_of_range("Incorrect input, need cols_1 == rows_2");
  }

  double temp[rows_][other.cols_];
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      temp[i][j] = 0;
      for (int k = 0; k < cols_; k++) {
        if (temp[i][j] + matrix_[i][k] * other.matrix_[k][j] < -DBL_MAX ||
            temp[i][j] + matrix_[i][k] * other.matrix_[k][j] > DBL_MAX)
          throw overflow_error("The mult of the elements exceeds DBL_MAX");
        else
          temp[i][j] = temp[i][j] + matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  setCols(other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      matrix_[i][j] = temp[i][j];
    }
  }
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  S21Matrix result(rows_, cols_);
  if (rows_ != cols_) {
    throw out_of_range("Incorrect input, need rows_ == cols_");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] = Minor(i, j) * pow(-1, i + j);
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw out_of_range("Incorrect input, need rows_ == cols_");
  }
  double result = 0;
  int n = rows_;
  if (n == 1) {
    result = matrix_[0][0];
  } else if (n == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    for (int j = 0; j < cols_; j++) {
      result += matrix_[0][j] * Minor(0, j) * pow(-1, j);
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw out_of_range("Incorrect input, need rows_ == cols_");
  }
  double det = Determinant();
  if (det == 0) {
    throw invalid_argument("Incorrect input, need det != 0");
  }

  if (rows_ == 1) {
    S21Matrix result = *this;
    result.MulNumber(1.0 / (det * matrix_[0][0]));
    return result;
  } else {
    S21Matrix complem = CalcComplements();
    S21Matrix transp = complem.Transpose();
    transp.MulNumber(1.0 / det);
    return transp;
  }
}

double S21Matrix::Minor(int index_i, int index_j) {
  S21Matrix temp(rows_ - 1, cols_ - 1);
  int count = 0;
  double result;

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (i != index_i && j != index_j) {
        temp.matrix_[count / temp.cols_][count % temp.cols_] = matrix_[i][j];
        count++;
      }
    }
  }
  result = temp.Determinant();
  return result;
}

// int main(int argc, char* argv[]) {
//
//     S21Matrix test_mat(3, 4);
//     test_mat.s21_matrix_oppx_opp();
//
// }