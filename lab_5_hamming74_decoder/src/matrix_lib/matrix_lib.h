#pragma once

#include <vector>
#include <iostream>
#include <initializer_list>
#include <assert.h>
#include <cmath>	//fmod

template <class T>
class Matrix
{
private:
	size_t m_rows, m_cols;
	std::vector<T> m_matrix;
public:
	Matrix() :m_rows(0), m_cols(0), m_matrix(0) {};
	Matrix(const size_t rows, const size_t cols);
	Matrix(const size_t rows, const size_t cols, T* mtx);
	Matrix(const std::initializer_list<T> &list);

	Matrix(const Matrix& mtx);
	Matrix& operator=(const Matrix kRightMtx);
	Matrix& operator=(const std::initializer_list<T> &list);
	Matrix& operator=(const T*);


	T& at(size_t cell) { assert(cell < m_rows*m_cols);  return m_matrix.at(cell); };
	T& at(size_t row, size_t col) { return m_matrix.at(row*m_cols + col); };

	T at(size_t cell) const { assert(cell < m_rows*m_cols); return m_matrix.at(cell); };
	T at(size_t row, size_t col) const { return m_matrix.at( row*m_cols + col); };

	std::vector<T> getVector() const;
	Matrix getRow (const size_t row) const;
	Matrix getCol (const size_t col) const;


	size_t getSize() const { return m_rows * m_cols; }
	size_t getNumRows() const { return m_rows; }
	size_t getNumCols() const { return m_cols; }

	template <class Tf>
	friend Matrix<Tf> operator+ (const Matrix<Tf>& kLeftMtx, const Matrix<Tf>& kRightMtx);

	template <class Tf>
	friend Matrix<Tf> operator+ (const Matrix<Tf>& kLeftMtx, Tf num);

	template <class Tf>
	friend Matrix<Tf> operator+ (Tf num, const Matrix<Tf>& kRightMtx);

	template <class Tf>
	friend Matrix<Tf> operator- (const Matrix<Tf>& kLeftMtx, const Matrix<Tf>& kRightMtx);

	template <class Tf>
	friend Matrix<Tf> operator- (const Matrix<Tf>& kLeftMtx, Tf num);

	template <class Tf>
	friend Matrix<Tf> operator* (const Matrix<Tf>& kLeftMtx, const Matrix<Tf>& kRightMtx);

	friend Matrix<bool> operator* (const Matrix<bool>& kLeftMtx, const Matrix<bool>& kRightMtx);

	template <class Tf>
	friend Matrix<Tf> operator* (const Matrix<Tf>& kLeftMtx, const Tf& num);

	template <class Tf>
	friend Matrix<Tf> operator* (const Tf &num, const Matrix<Tf>& kRightMtx);

	template <class Tf>
	friend Matrix<Tf> operator! (const Matrix<Tf>& kRightMtx);  //Transpose

	template <class Tf>
	friend std::ostream& operator<<(std::ostream& out, const Matrix<Tf>& kRightMtx);

	template <class Tf>
	friend Tf SumElements(const Matrix<Tf>& kMatrix);
};


template <class T>
Matrix<T>::Matrix(const size_t rows, const size_t cols) : m_rows(rows), m_cols(cols)
{
    for (int it(0); it < rows*cols; ++it) m_matrix.push_back(0);
}

template <class T>
Matrix<T>::Matrix(const size_t rows, const size_t cols, T* mtx) : m_rows(rows), m_cols(cols)
{
	assert(num_list.size() < rows*cols);
	for (int it = 0; it < m_rows*m_cols){
		m_matrix.push_back(*(mtx + it));
	}
}

template <class T>
Matrix<T>::Matrix(const std::initializer_list<T> &list)
{
	m_cols = static_cast<size_t>(list.size());
	m_rows = 1;
	for (auto &num : list) { m_matrix.push_back(num); }
}

template <class T>
Matrix<T>::Matrix(const Matrix& mtx)
{
	m_rows = mtx.m_rows;
	m_cols = mtx.m_cols;

	m_matrix.clear();
    m_matrix = mtx.m_matrix;
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix kRightMtx)
 {
	this->m_cols = kRightMtx.m_cols;
	this->m_rows = kRightMtx.m_rows;
	this->m_matrix.clear();
	this->m_matrix = kRightMtx.m_matrix;
	return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const std::initializer_list<T> &list)
{
	assert(list.size() == static_cast<size_t>(m_rows*m_cols));
	m_matrix.clear();
	for (auto &num : list){
		m_matrix.push_back(num);
	}
	return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const T* input_arr)
{
	m_matrix.clear();
	for (int it = 0; it < this->getSize(); ++it) {
		m_matrix.push_back(*(input_arr + it));
	}
	return *this;
}


template <class T>
Matrix<T> Matrix<T>::getRow(const size_t kRow) const
{
	assert(kRow < m_rows);
	Matrix<T> row_vector(1,m_cols);
	for (int col = 0; col < m_cols; ++col) {
		row_vector.at(col) = (this->at(kRow, col));
	}
	return row_vector;
}

template <class T>
Matrix<T> Matrix<T>::getCol(const size_t kCol) const
{
	assert(kCol < m_cols);
	Matrix<T> col_vector(m_rows, 1);
	for (int row = 0; row < m_rows; ++row) {
		col_vector.at(row) = (this->at(row, kCol));
	}
	return col_vector;
}

template <class T>
std::vector<T> Matrix<T>::getVector() const
{
	return m_matrix;
}


template <class T>
Matrix<T> operator+(const Matrix<T>& kLeftMtx, const Matrix<T>& kRightMtx)
{
	Matrix<T> mtx_sum(kLeftMtx);
	assert(kLeftMtx.m_cols == kRightMtx.m_cols);
	assert(kLeftMtx.m_rows == kRightMtx.m_rows);

	for (int it(0); it < kLeftMtx.getSize(); ++it) {
		mtx_sum.at(it) = kLeftMtx.at(it) + kRightMtx.at(it);
	}
	return mtx_sum;
}


template<class Tf>
Matrix<Tf> operator+(const Matrix<Tf>& kLeftMtx, Tf num)
{
	Matrix<Tf> mtx_sum(kLeftMtx);
	for (int it(0); it < kLeftMtx.getSize(); ++it) {
		mtx_sum.at(it) = kLeftMtx.at(it) + num;
	}
	return mtx_sum;
}

template <class Tf>
Matrix<Tf> operator+ (Tf num, const Matrix<Tf>& kRightMtx) { return (kRightMtx + num); }

template<class Tf>
Matrix<Tf> operator-(const Matrix<Tf>& kLeftMtx, Tf num)
{
	Matrix<Tf> mtx_diff(kLeftMtx);
	for (int it(0); it < kLeftMtx.getSize(); ++it) {
		mtx_diff.at(it) = kLeftMtx.at(it) - num;
	}
	return mtx_diff;
}


template<class Tf>
Matrix<Tf> operator-(const Matrix<Tf>& kLeftMtx, const Matrix<Tf>& kRightMtx)
{
	Matrix<Tf> mtx_diff(kLeftMtx);
	assert(kLeftMtx.m_cols == kRightMtx.m_cols);
	assert(kLeftMtx.m_rows == kRightMtx.m_rows);

	for (int it(0); it < kLeftMtx.getSize(); ++it) {
		mtx_diff.at(it) = kLeftMtx.at(it) - kRightMtx.at(it);
	}
	return mtx_diff;
}


template <class Tf>
Matrix<Tf> operator* (const Matrix<Tf>& kLeftMtx, const Matrix<Tf>& kRightMtx)
{
	assert(kLeftMtx.m_cols == kRightMtx.m_rows);
	Matrix<Tf> mtx_prod(kLeftMtx.m_rows, kRightMtx.m_cols);

	for (int row = 0; row < kLeftMtx.m_rows; ++row) {
		for (int col = 0; col < kRightMtx.m_cols; ++col) {
			std::vector<Tf> a_row = kLeftMtx.getRow(row).m_matrix;
			std::vector<Tf> b_col = kRightMtx.getCol(col).m_matrix;

			std::vector<Tf> product_elements;
			for (int it = 0; it < a_row.size(); ++it) {
				product_elements.push_back(a_row.at(it)*b_col.at(it));
			}

			Tf product_cell = 0;
			for (auto &num : product_elements) { product_cell += num; }

			mtx_prod.at(row, col) = product_cell;
		}
	}
	return mtx_prod;
}

template <class Tf>
Matrix<Tf> operator* (const Matrix<Tf>& kLeftMtx, const Tf& num)
{
	Matrix<Tf> product_mtx(kLeftMtx);
	for (int it = 0; it < kLeftMtx.getSize(); ++it) {
		product_mtx.at(it) = kLeftMtx.at(it)*num;
	}
	return product_mtx;
}

template <class Tf>
Matrix<Tf> operator* (const Tf &num, const Matrix<Tf>& kRightMtx) { return (kRightMtx * num); }


template <class Tf>
Matrix<Tf> operator% (const Matrix<Tf>& kLeftMtx, const Tf& num)
{
	Matrix<Tf> result_mtx(kLeftMtx);
	for (int it = 0; it < kLeftMtx.getSize(); ++it) {
		result_mtx.at(it) = (kLeftMtx.at(it) % num);
	}
	return result_mtx;
}

template<>
inline Matrix<double> operator% (const Matrix<double>& kLeftMtx, const double& num)
{
	Matrix<double> result_mtx(kLeftMtx);
	for (int it = 0; it < kLeftMtx.getSize(); ++it) {
		result_mtx.at(it) = fmod(kLeftMtx.at(it), num);
	}
	return result_mtx;
}

template<>
inline Matrix<float> operator% (const Matrix<float>& kLeftMtx, const float& num)
{
	Matrix<float> result_mtx(kLeftMtx);
	for (int it = 0; it < kLeftMtx.getSize(); ++it) {
		result_mtx.at(it) = fmod(kLeftMtx.at(it), num);
	}
	return result_mtx;
}

template <class Tf>
Matrix<Tf> operator! (const Matrix<Tf>& kRightMtx)
{
	Matrix<Tf> transope_mtx(kRightMtx.m_cols, kRightMtx.m_rows);
	for (int row = 0; row < kRightMtx.m_rows; ++row) {
		for (int col = 0; col < kRightMtx.m_cols; ++col) {
			transope_mtx.at(col, row) = kRightMtx.at(row, col);
		}
	}
	return transope_mtx;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& kRightMtx)
{

	for (int row(0); row < kRightMtx.getNumRows(); ++row) {
		for (int col(0); col < kRightMtx.getNumCols(); ++col) {
			out << (kRightMtx.at(row, col)>=0 ? " " : "") << kRightMtx.at(row, col) << "\t";
		}
		out << std::endl;
	}
	return out;
}

template<>
inline std::ostream& operator<<(std::ostream& out, const Matrix<uint8_t>& kRightMtx)
{
	for (int row(0); row < kRightMtx.getNumRows(); ++row) {
		for (int col(0); col < kRightMtx.getNumCols(); ++col) {
			out << (kRightMtx.at(row, col) >= 0 ? " " : "") << static_cast<unsigned int>(kRightMtx.at(row, col)) << "\t";
		}
		out << std::endl;
	}
	return out;
}


template <class Tf>
Tf SumElements(const Matrix<Tf>& kMatrix)
{
	Tf accumulator(0);
	for (int element = 0; element < kMatrix.getSize(); ++element) {
		accumulator += kMatrix.at(element);
	}
	return accumulator;
}

#include "matrix_lib.cpp"