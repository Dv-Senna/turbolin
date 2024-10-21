#pragma once

#include "turbolin/matrix.hpp"

#include <iostream>

#include <array>
#include <cstring>
#include <immintrin.h>
#include <type_traits>



namespace turbolin {
	template <turbolin::MatrixType T, std::size_t D>
	template <turbolin::MatrixType ...Args>
	Matrix<T, D>::Matrix(Args&& ...args) {
		if constexpr (std::is_same_v<T, float>) {
			__m256 r1 {_mm256_setzero_ps()};
			_mm256_store_ps(reinterpret_cast<float*> (this), r1);
			if constexpr (D >= 3) {
				__m256 r2 {_mm256_setzero_ps()};
				_mm256_store_ps(reinterpret_cast<float*> (this) + 8, r2);
			}
		}
		else {
			__m256i r1 {(_mm256_setzero_si256())};
			_mm256_store_si256(reinterpret_cast<__m256i*> (this), r1);
			if constexpr (D >= 3) {
				__m256i r2 {_mm256_setzero_si256()};
				_mm256_store_si256(reinterpret_cast<__m256i*> (reinterpret_cast<int*> (this) + 8), r2);
			}
		}

		if constexpr (sizeof...(Args) != 0) {
			std::size_t i {0};
			([&] () {
				std::size_t row {i % D};
				std::size_t column {i / D};
				std::size_t position {column * 4 + row};
				reinterpret_cast<T*> (this)[position] = args;
				++i;
			}(), ...);
		}
	}


	template <turbolin::MatrixType T, std::size_t D>
	template <turbolin::MatrixType T2>
	Matrix<T, D>::Matrix(const turbolin::Matrix<T2, D> &matrix) {
		*this = matrix;
	}


	template <turbolin::MatrixType T, std::size_t D>
	template <turbolin::MatrixType T2>
	const turbolin::Matrix<T, D> &Matrix<T, D>::operator=(const turbolin::Matrix<T2, D> &matrix) {
		if constexpr (std::is_same_v<T, T2>) {
			std::memcpy(reinterpret_cast<T*> (this), reinterpret_cast<T*> (&matrix), sizeof(T) * (D >= 3 ? 16 : 8));
		}
		else if constexpr (std::is_same_v<T, float>) {
			__m256i r1 {_mm256_load_epi32(reinterpret_cast<int*> (&matrix))};
			__m256 r2 {_mm256_cvtepi32_ps(r1)};
			_mm256_store_ps(reinterpret_cast<float*> (this), r2);
			if constexpr (D >= 3) {
				__m256i r1 {_mm256_load_epi32(reinterpret_cast<int*> (&matrix) + 8)};
				__m256 r2 {_mm256_cvtepi32_ps(r1)};
				_mm256_store_ps(reinterpret_cast<float*> (this) + 8, r2);
			}
		}
		else {
			__m256 r1 {_mm256_load_ps(reinterpret_cast<float*> (&matrix))};
			__m256i r2 {_mm256_cvtps_epi32(r1)};
			_mm256_store_si256(reinterpret_cast<__m256i*> (this), r2);
			if constexpr (D >= 3) {
				__m256 r1 {_mm256_load_ps(reinterpret_cast<float*> (&matrix) + 8)};
				__m256i r2 {_mm256_cvtps_epi32(r1)};
				_mm256_store_si256(reinterpret_cast<__m256i*> (reinterpret_cast<int*> (this) + 8), r2);
			}
		}

		return this;
	}


	template <turbolin::MatrixType T, std::size_t D>
	template <turbolin::MatrixType T2>
	bool Matrix<T, D>::operator==(const turbolin::Matrix<T2, D> &matrix) const noexcept {
		if constexpr (std::is_same_v<T, T2>) {
			if constexpr (std::is_same_v<T, float>) {
				__m256 r1 {_mm256_load_ps(reinterpret_cast<const float*> (this))};
				__m256 r2 {_mm256_load_ps(reinterpret_cast<const float*> (&matrix))};
				r1 = _mm256_cmp_ps(r1, r2, _CMP_EQ_OQ);
				bool result {_mm256_movemask_ps(r1) == 0xff};
				if constexpr (D >= 3) {
					r1 = _mm256_load_ps(reinterpret_cast<const float*> (this) + 8);
					r2 = _mm256_load_ps(reinterpret_cast<const float*> (&matrix) + 8);
					r1 = _mm256_cmp_ps(r1, r2, _CMP_EQ_OQ);
					result = result && _mm256_movemask_ps(r1) == 0xff;
				}
				return result;
			}
			else {
				__m256i r1 {_mm256_load_si256(reinterpret_cast<const __m256i*> (this))};
				__m256i r2 {_mm256_load_si256(reinterpret_cast<const __m256i*> (&matrix))};
				r1 = _mm256_cmpeq_epi32(r1, r2);
				bool result {_mm256_movemask_epi8(r1) == 0xffffffff};
				if constexpr (D >= 3) {
					r1 = _mm256_load_si256(reinterpret_cast<const __m256i*> (reinterpret_cast<const int*> (this) + 8));
					r2 = _mm256_load_si256(reinterpret_cast<const __m256i*> (reinterpret_cast<const int*> (&matrix) + 8));
					r1 = _mm256_cmpeq_epi32(r1, r2);
					result = result && _mm256_movemask_epi8(r1) == 0xffffffff;
				}
				return result;
			}
		}
		else {
			if constexpr (std::is_same_v<T, float>) {
				__m256 r1 {_mm256_load_ps(reinterpret_cast<const float*> (this))};
				__m256i r3 {_mm256_load_si256(reinterpret_cast<const __m256i*> (&matrix))};
				__m256 r2 {_mm256_cvtepi32_ps(r3)};
				r1 = _mm256_cmp_ps(r1, r2, _CMP_EQ_OQ);
				bool result {_mm256_movemask_ps(r1) == 0xff};
				if constexpr (D >= 3) {
					r1 = _mm256_load_ps(reinterpret_cast<const float*> (this) + 8);
					r3 = _mm256_load_si256(reinterpret_cast<const __m256i*> (reinterpret_cast<const int*> (&matrix + 8)));
					r2 = _mm256_cvtepi32_ps(r3);
					r1 = _mm256_cmp_ps(r1, r2, _CMP_EQ_OQ);
					result = result && _mm256_movemask_ps(r1) == 0xff;
				}
				return result;
			}
			else {
				__m256i r1 {_mm256_load_si256(reinterpret_cast<const __m256i*> (this))};
				__m256 r3 {_mm256_load_ps(reinterpret_cast<const float*> (&matrix))};
				__m256i r2 {_mm256_cvtps_epi32(r3)};
				r1 = _mm256_cmpeq_epi32(r1, r2);
				bool result {_mm256_movemask_epi8(r1) == 0xffffffff};
				if constexpr (D >= 3) {
					r1 = _mm256_load_si256(reinterpret_cast<const __m256i*> (reinterpret_cast<const int*> (this) + 8));
					r3 = _mm256_load_ps(reinterpret_cast<const float*> (&matrix) + 8);
					r2 = _mm256_cvtps_epi32(r3);
					r1 = _mm256_cmpeq_epi32(r1, r2);
					result = result && _mm256_movemask_epi8(r1) == 0xffffffff;
				}
				return result;
			}
		}
	}


} // namespace turbolin

