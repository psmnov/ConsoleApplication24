#include <vector>
#include <iostream>

template <typename T>
class Matrix {
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


	Matrix(const std::vector<std::vector<T>>& m) : matrix(m) {
		createMatrix();
	}
	Matrix(size_t rows, size_t columns) {
		matrix.resize(rows);
		for (auto& row : matrix) {
			row.resize(columns);
		}
	}

	// Получение количества строк

	size_t GetRows() const {
		return matrix.size();
	}

	// Получение количества столбцов
	size_t GetColumns() const {
		if (matrix.empty()) {
			return 0;
		}
		return matrix[0].size();
	}
	// Перегрузка оператора [] для доступа к элементам (константная версия)
	const std::vector<T>& operator[](size_t i) const {
		return matrix[i];
	}

	// Перегрузка оператора [] для доступа к элементам (неконстантная версия)
	std::vector<T>& operator[](size_t i) {
		return matrix[i];
	}

	

	// Перегрузка оператора += для сложения матриц
	Matrix<T>& operator+=(const Matrix<T>& other) {
		if (GetRows() != other.GetRows() || GetColumns() != other.GetColumns()) {
			throw std::invalid_argument("Matrices have different size!");
		}
		for (size_t i = 0; i < GetRows(); ++i) {
			for (size_t j = 0; j < GetColumns(); ++j) {
				matrix[i][j] += other[i][j];
			}
		}
		return *this;
	}

	// Перегрузка оператора + для сложения матриц
	Matrix<T> operator+(const Matrix<T>& other) const {
		Matrix<T> result = *this; // Создаем копию *this
		result += other; // Используем operator+= для сложения
		return result;
	}

	// Умножение матрицы на число
	Matrix<T>& scale(const T& t) {
		for (size_t i = 0; i < GetRows(); ++i) {
			for (size_t j = 0; j < GetColumns(); ++j) {
				matrix[i][j] *= t;
			}
		}
		return *this;
	}


	Matrix<T>& operator-=(const Matrix<T>& other) {
		if (GetRows() != other.GetRows() || GetColumns() != other.GetColumns()) {
			throw std::invalid_argument("Matrices have different size!");
		}
		for (size_t i = 0; i < GetRows(); ++i) {
			for (size_t j = 0; j < GetColumns(); ++j) {
				matrix[i][j] -= other[i][j];
			}
		}
		return *this;
	}


	Matrix<T> operator-(const Matrix<T>& other) const {
		Matrix<T> result = *this; // Создаем копию *this
		result -= other; // Используем operator-= для вычитания
		return result;
	}

	Matrix<T> operator*(const Matrix<T>& other) const {
		const size_t lhsRows = GetRows();
		const size_t lhsCols = GetColumns();
		const size_t rhsRows = other.GetRows();
		const size_t rhsCols = other.GetColumns();

		if (lhsCols != rhsRows) {
			throw std::invalid_argument("Incompatible matrix dimensions for multiplication!");
		}

		Matrix<T> result(lhsRows, rhsCols);

		for (size_t i = 0; i < lhsRows; ++i) {
			for (size_t j = 0; j < rhsCols; ++j) {
				for (size_t k = 0; k < lhsCols; ++k) {
					result[i][j] += matrix[i][k] * other[k][j];
				}
			}
		}

		return result;
	}


	Matrix<T> operator*(const T& scalar) const {
		Matrix<T> result = *this;
		result.scale(scalar);
		return result;
	}
};
template <typename T>
// Перегрузка оператора << для вывода матрицы в поток
std::ostream& operator<<(std::ostream& out, const Matrix<T>& mat) {
	for (size_t i = 0; i < mat.GetRows(); ++i) {
		for (size_t j = 0; j < mat.GetColumns(); ++j) {
			if (j > 0) {
				out << "\t";
			}
			out << mat[i][j];
		}
		out << "\n";
	}
	return out;
}
template <typename T>
// Перегрузка оператора >> для ввода матрицы из потока
std::istream& operator>>(std::istream& in, Matrix<T>& mat) {
	for (size_t i = 0; i < mat.GetRows(); ++i) {
		for (size_t j = 0; j < mat.GetColumns(); ++j) {
			in >> mat[i][j];
		}
	}
	return in;
}
