#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix {
public:
	Matrix() {
		rows = 0;
		cols = 0;
		vals.clear();
	}
	Matrix(const int& num_rows, const int& num_cols) {
		if (num_rows < 0 || num_cols < 0) {
			throw out_of_range("Negative dimension is not supported.");
		}
		if (num_rows == 0 || num_cols == 0) {
			rows = 0;
			cols = 0;
			vals.clear();
		} else {
			vector<int> row(num_cols, 0);
			vals.assign(num_rows, row);
			rows = num_rows;
			cols = num_cols;
		}
		/*
		vals(num_rows);
		for (int i = 0; i < num_rows; ++i) {
			vals[i].assign(num_cols, 0);
		}
		*/
	}
	void Reset(const int& num_rows, const int& num_cols) {
		if (num_rows < 0 || num_cols < 0) {
			throw out_of_range("Negative dimension is not supported.");
		}
		if (num_rows == 0 || num_cols == 0) {
			rows = 0;
			cols = 0;
			vals.clear();
		} else {
			vector<int> row(num_cols, 0);
			vals.assign(num_rows, row);
			rows = num_rows;
			cols = num_cols;
		}
	}
	int At(const int& row, const int& col) const {
		if (row >= rows || col >= cols || row < 0 || col < 0) {
			throw out_of_range("Dimension is bigger than it should be.");
		}
		return vals[row][col];
	}
	int& At(const int& row, const int& col) {
		if (row >= rows || col >= cols || row < 0 || col < 0) {
			throw out_of_range("Dimension is bigger than it should be.");
		}
		return vals[row][col];
	}
	int GetNumRows() const {
		return rows;
	}
	int GetNumColumns() const {
		return cols;
	}

private:
	vector<vector<int>> vals;
	int rows;
	int cols;
};

istream& operator >> (istream& stream, Matrix& m) {
	int r = 0;
	int c = 0;
	stream >> r >> c;
	m.Reset(r, c);
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			stream >> m.At(i, j);
		}
	}
	return stream;
}

ostream& operator << (ostream& stream, const Matrix& m) {
	stream << m.GetNumRows() << " " << m.GetNumColumns() << endl;
	for (int i = 0; i < m.GetNumRows(); ++i) {
		for (int j = 0; j < m.GetNumColumns(); ++j) {
			stream << m.At(i, j) << " ";
		}
		stream << endl;
	}
	return stream;
}

bool operator == (const Matrix& lhs, const Matrix& rhs) {
	if (lhs.GetNumRows() != rhs.GetNumRows() || lhs.GetNumColumns() != rhs.GetNumColumns()) {
		return false;
	} else {
		for (int i = 0; i < lhs.GetNumRows(); ++i) {
			for (int j = 0; j < lhs.GetNumColumns(); ++j) {
				if (lhs.At(i, j) != rhs.At(i, j)) {
					return false;
				}
			}
		}
	}
	return true;
}

Matrix operator + (const Matrix& lhs, const Matrix& rhs) {
	if (lhs.GetNumRows() != rhs.GetNumRows() || lhs.GetNumColumns() != rhs.GetNumColumns()) {
		throw invalid_argument("Matrices have different dimensions.");
	}
	Matrix result(lhs.GetNumRows(), lhs.GetNumColumns());
	for (int i = 0; i < lhs.GetNumRows(); ++i) {
		for (int j = 0; j < lhs.GetNumColumns(); ++j) {
			result.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
		}
	}
	return result;
}

int main() {
  try {
	  Matrix one;
	  Matrix two;

	  cin >> one >> two;
	  cout << one + two << endl;


  } catch (const exception& ex) {
	  cout << ex.what() << endl;
	  return 1;
  }

  return 0;
}

/* #include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix {
private:
  int num_rows_;
  int num_columns_;

  vector<vector<int>> elements_;

public:
  Matrix() {
    num_rows_ = 0;
    num_columns_ = 0;
  }

  Matrix(int num_rows, int num_columns) {
    Reset(num_rows, num_columns);
  }

  void Reset(int num_rows, int num_columns) {
    if (num_rows < 0) {
      throw out_of_range("num_rows must be >= 0");
    }
    if (num_columns < 0) {
      throw out_of_range("num_columns must be >= 0");
    }
    if (num_rows == 0 || num_columns == 0) {
      num_rows = num_columns = 0;
    }

    num_rows_ = num_rows;
    num_columns_ = num_columns;
    elements_.assign(num_rows, vector<int>(num_columns));
  }

  int& At(int row, int column) {
    return elements_.at(row).at(column);
  }

  int At(int row, int column) const {
    return elements_.at(row).at(column);
  }

  int GetNumRows() const {
    return num_rows_;
  }

  int GetNumColumns() const {
    return num_columns_;
  }
};

bool operator==(const Matrix& one, const Matrix& two) {
  if (one.GetNumRows() != two.GetNumRows()) {
    return false;
  }

  if (one.GetNumColumns() != two.GetNumColumns()) {
    return false;
  }

  for (int row = 0; row < one.GetNumRows(); ++row) {
    for (int column = 0; column < one.GetNumColumns(); ++column) {
      if (one.At(row, column) != two.At(row, column)) {
        return false;
      }
    }
  }

  return true;
}

Matrix operator+(const Matrix& one, const Matrix& two) {
  if (one.GetNumRows() != two.GetNumRows()) {
    throw invalid_argument("Mismatched number of rows");
  }

  if (one.GetNumColumns() != two.GetNumColumns()) {
    throw invalid_argument("Mismatched number of columns");
  }

  Matrix result(one.GetNumRows(), one.GetNumColumns());
  for (int row = 0; row < result.GetNumRows(); ++row) {
    for (int column = 0; column < result.GetNumColumns(); ++column) {
      result.At(row, column) = one.At(row, column) + two.At(row, column);
    }
  }

  return result;
}

istream& operator>>(istream& in, Matrix& matrix) {
  int num_rows, num_columns;
  in >> num_rows >> num_columns;

  matrix.Reset(num_rows, num_columns);
  for (int row = 0; row < num_rows; ++row) {
    for (int column = 0; column < num_columns; ++column) {
      in >> matrix.At(row, column);
    }
  }

  return in;
}

ostream& operator<<(ostream& out, const Matrix& matrix) {
  out << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;
  for (int row = 0; row < matrix.GetNumRows(); ++row) {
    for (int column = 0; column < matrix.GetNumColumns(); ++column) {
      if (column > 0) {
        out << " ";
      }
      out << matrix.At(row, column);
    }
    out << endl;
  }

  return out;
}

int main() {
  Matrix one;
  Matrix two;

  cin >> one >> two;
  cout << one + two << endl;
  return 0;
} */
