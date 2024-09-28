#include <vector>
template <typename T>
class Matrix
{
	std::vector<std::vector<T>> matrix;
	void createMatrix() {
		size_t mxSize = 0;
		for (const auto& row : matrix) {
			if (row.size() > mxSize) {
				mxSize = row.size();
			}
		}
		for (auto& row : matrix) {
			row.resize(mxSize);
		}
	}
	
public:
	//const если функци€ не измен€ет объект, а только читает
	size_t getNumOfRows() const {
		return matrix.size();
	};
	size_t getNumOfColumns() const {
		if (matrix.empty()) return 0;
		return matrix[0].size();
	};
	//& - передача ссылки,а не указател€, объект не копируетс€. ћы передаем ровно сам массив, не копируем и не указываем
	Matrix(const std::vector<std::vector<T>>& m) : matrix(m) {
		createMatrix();
	}
	//дл€ инициализации матрицы из нулей
	Matrix(size_t rows, size_t columns) {
		matrix.resize(rows);
		for (auto& row : matrix) {
			row.resize(columns);
		}
	}
	//перегрузка на два случа€
	//если получаем константную матрицу, то и измен€ть ее размеры не можем
	const std::vector<T>& operator [] (size_t i) const {
		return matrix[i];
	}
	//дл€ работы с неконстантными матрицами
	std::vector<T>& operator [] (size_t i) {
		return matrix[i];
	}
	template <typename T>
	std::ostream& operator << (std::ostream& out, const Matrix<T>& matrix) {
		const size_t rows = matrix.GetRows();
		const size_t columns = matrix.GetColumns();
		for (size_t i = 0; i != rows; ++i) {
			for (size_t j = 0; j != columns; ++j) {
				if (j > 0) {
					out << "\t";
				}
				out << matrix[i][j];
			}
			out << "\n";
		}
		return out;
	}

	template <typename T>
	std::istream& operator >> (std::istream& in, Matrix<T>& matrix) {
		const size_t rows = matrix.GetRows();
		const size_t columns = matrix.GetColumns();
		for (size_t i = 0; i != rows; ++i) {
			for (size_t j = 0; j != columns; ++j) {
				in >> matrix(i, j);
			}
		}
		return in;
	}
	Matrix<T>& operator += (const Matrix<T>& other) {
		const size_t rows = GetRows();
		const size_t columns = GetColumns();
		if (rows != other.GetRows() || columns != other.GetColumns()) {
			throw std::invalid_argument("Matrices have different size!");
		}
		for (size_t i = 0; i != rows; ++i) {
			for (size_t j = 0; j != columns; ++j) {
				data[i][j] += other.data[i][j];
			}
		}
		return *this;
	}
	template <typename T>
	Matrix<T> operator + (const Matrix<T>& m1, const Matrix<T>& m2) {
		auto tmp = m1;
		tmp += m2;
		return tmp;
	}
	template <typename T>
	Matrix<T>& scale(const T& t) {
		const size_t rows = GetRows();
		const size_t columns = GetColumns();
		for (size_t i = 0; i != rows; ++i) {
			for (size_t j = 0; j != columns; ++j) {
				matrix[i][j] *= t;
			}
		}
		return *this;
	}
	template <typename T>
	Matrix<T>& operator -= (const Matrix<T>& other) {
		Matrix<T> temp = other;
		temp.scale(-1);
		*this += temp;

		return *this;
	}
	template <typename T>
	Matrix<T>& operator - (const Matrix<T>& other) {
		auto tmp = m1;
		tmp -= m2;
		return tmp;
	}
	template <typename T>
	Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs) {
		const size_t lhsRows = lhs.GetRows();
		const size_t lhsCols = lhs.GetColumns();
		const size_t rhsRows = rhs.GetRows();
		const size_t rhsCols = rhs.GetColumns();

		if (lhsCols != rhsRows) {
			throw std::invalid_argument("Incompatible matrix dimensions for multiplication!");
		}

		Matrix<T> result(lhsRows, rhsCols);

		for (size_t i = 0; i < lhsRows; ++i) {
			for (size_t j = 0; j < rhsCols; ++j) {
				for (size_t k = 0; k < lhsCols; ++k) {
					result[i][j] += lhs[i][k] * rhs[k][j];
				}
			}
		}

		return result;
	}
};


