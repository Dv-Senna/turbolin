#pragma once

#include "turbolin/vector.hpp"

#include <array>
#include <cstring>
#include <immintrin.h>

#include <cstdio>



namespace turbolin {
	template <turbolin::VectorType T, std::size_t D>
	template <turbolin::VectorType ...Args>
	Vector<T, D>::Vector(Args&& ...args) noexcept {
		static_assert(sizeof...(Args) <= D, "Can't initialize a D-vector with more than D values");

		if constexpr (sizeof...(Args) == 0) {
			if constexpr (std::is_same_v<T, float>) {
				__m128 r1 {_mm_setzero_ps()};
				_mm_store_ps(reinterpret_cast<float*> (this), r1);
			}
			else {
				__m128i r1 {_mm_setzero_si128()};
				_mm_store_si128(reinterpret_cast<__m128i*> (this), r1);
			}
		}

		else {
			std::array<T, 4> content {static_cast<T> (args)...};
			std::memmove(this, content.data(), sizeof(T) * 4);
		}
	}


	template <turbolin::VectorType T, std::size_t D>
	template <turbolin::VectorType T2, std::size_t D2, turbolin::VectorType ...Args>
	Vector<T, D>::Vector(const turbolin::Vector<T2, D2> &vector, Args&& ...args) noexcept : Vector<T, D> () {
		static_assert(D2 + sizeof...(Args) <= D, "Can't initialize a D-vector with more than D values");

		if constexpr (std::is_same_v<T, T2>) {
			std::memcpy(this, &vector, sizeof(T) * D2);
		}
		else {
			if constexpr (std::is_same_v<T2, float>) {
				__m128 r1 {_mm_load_ps(reinterpret_cast<const float*> (&vector))};
				__m128i r2 {_mm_cvtps_epi32(r1)};
				_mm_store_si128(reinterpret_cast<__m128i*> (this), r2);
			}
			else {
				__m128i r1 {_mm_load_si128(reinterpret_cast<const __m128i*> (&vector))};
				__m128 r2 {_mm_cvtepi32_ps(r1)};
				_mm_store_ps(reinterpret_cast<float*> (this), r2);
			}
		}

		std::size_t i {D2};
		([&](){
			reinterpret_cast<T*> (this)[i] = static_cast<T> (args);
			i++;
		}(), ...);
	}


	template <turbolin::VectorType T, std::size_t D>
	template <turbolin::VectorType T2>
	const turbolin::Vector<T, D> &Vector<T, D>::operator=(const turbolin::Vector<T2, D> &vector) noexcept {
		if constexpr (std::is_same_v<T, T2>) {
			std::memcpy(this, &vector, sizeof(T) * D);
		}
		else {
			if constexpr (std::is_same_v<T2, float>) {
				__m128 r1 {_mm_load_ps(reinterpret_cast<const float*> (&vector))};
				__m128i r2 {_mm_cvtps_epi32(r1)};
				_mm_store_si128(reinterpret_cast<__m128i*> (this), r2);
			}
			else {
				__m128i r1 {_mm_load_si128(reinterpret_cast<const __m128i*> (&vector))};
				__m128 r2 {_mm_cvtepi32_ps(r1)};
				_mm_store_ps(reinterpret_cast<float*> (this), r2);
			}
		}

		return *this;
	}


	template <turbolin::VectorType T, std::size_t D>
	template <turbolin::VectorType T2>
	bool Vector<T, D>::operator==(const turbolin::Vector<T2, D> &vector) const noexcept {
		if constexpr (std::is_same_v<T, T2>) {
			if constexpr (std::is_same_v<T, float>) {
				__m128 r1 {_mm_load_ps(reinterpret_cast<const float*> (this))};
				__m128 r2 {_mm_load_ps(reinterpret_cast<const float*> (&vector))};
				r1 = _mm_cmpeq_ps(r1, r2);
				return _mm_movemask_ps(r1) == 0xf;
			}
			else {
				__m128i r1 {_mm_load_si128(reinterpret_cast<const __m128i*> (this))};
				__m128i r2 {_mm_load_si128(reinterpret_cast<const __m128i*> (&vector))};
				r1 = _mm_cmpeq_epi32(r1, r2);
				return _mm_movemask_epi8(r1) == 0xffff;
			}
		}
		else {
			if constexpr (std::is_same_v<T2, float>) {
				__m128i r1 {_mm_load_si128(reinterpret_cast<const __m128i*> (this))};
				__m128 r3 {_mm_load_ps(reinterpret_cast<const float*> (&vector))};
				__m128i r2 {_mm_cvtps_epi32(r3)};
				r1 = _mm_cmpeq_epi32(r1, r1);
				return _mm_movemask_epi8(r1) == 0xffff;
			}
			else {
				__m128 r1 {_mm_load_ps(reinterpret_cast<const float*> (this))};
				__m128i r3 {_mm_load_si128(reinterpret_cast<const __m128i*> (&vector))};
				__m128 r2 {_mm_cvtepi32_ps(r3)};
				r1 = _mm_cmpeq_ps(r1, r1);
				return _mm_movemask_ps(r1) == 0xf;
			}
		}
	}


	template <turbolin::VectorType T, std::size_t D>
	template <turbolin::VectorType T2>
	const turbolin::Vector<T, D> &Vector<T, D>::operator+=(const turbolin::Vector<T2, D> &vector) noexcept {
		if constexpr (std::is_same_v<T, float>) {
			__m128 r1 {};
			__m128 r2 {};

			if constexpr (std::is_same_v<T, T2>) {
				r1 = _mm_load_ps(reinterpret_cast<const float*> (this));
				r2 = _mm_load_ps(reinterpret_cast<const float*> (&vector));
			}
			else {
				r1 = _mm_load_ps(reinterpret_cast<const float*> (this));
				__m128i r3 {_mm_load_si128(reinterpret_cast<const __m128i*> (&vector))};
				r2 = _mm_cvtepi32_ps(r3);
			}

			r1 = _mm_add_ps(r1, r2);
			_mm_store_ps(reinterpret_cast<float*> (this), r1);
		}
		else {
			__m128i r1 {};
			__m128i r2 {};

			if constexpr (std::is_same_v<T, T2>) {
				r1 = _mm_load_si128(reinterpret_cast<const __m128i*> (this));
				r2 = _mm_load_si128(reinterpret_cast<const __m128i*> (&vector));
			}
			else {
				r1 = _mm_load_si128(reinterpret_cast<const __m128i*> (this));
				__m128 r3 {_mm_load_ps(reinterpret_cast<const float*> (&vector))};
				r2 = _mm_cvtps_epi32(r3);
			}

			r1 = _mm_add_epi32(r1, r2);
			_mm_store_si128(reinterpret_cast<__m128i*> (this), r1);
		}

		return *this;
	}


	template <turbolin::VectorType T, std::size_t D>
	template <turbolin::VectorType T2>
	const turbolin::Vector<T, D> &Vector<T, D>::operator-=(const turbolin::Vector<T2, D> &vector) noexcept {
		if constexpr (std::is_same_v<T, float>) {
			__m128 r1 {};
			__m128 r2 {};

			if constexpr (std::is_same_v<T, T2>) {
				r1 = _mm_load_ps(reinterpret_cast<const float*> (this));
				r2 = _mm_load_ps(reinterpret_cast<const float*> (&vector));
			}
			else {
				r1 = _mm_load_ps(reinterpret_cast<const float*> (this));
				__m128i r3 {_mm_load_si128(reinterpret_cast<const __m128i*> (&vector))};
				r2 = _mm_cvtepi32_ps(r3);
			}

			r1 = _mm_sub_ps(r1, r2);
			_mm_store_ps(reinterpret_cast<float*> (this), r1);
		}
		else {
			__m128i r1 {};
			__m128i r2 {};

			if constexpr (std::is_same_v<T, T2>) {
				r1 = _mm_load_si128(reinterpret_cast<const __m128i*> (this));
				r2 = _mm_load_si128(reinterpret_cast<const __m128i*> (&vector));
			}
			else {
				r1 = _mm_load_si128(reinterpret_cast<const __m128i*> (this));
				__m128 r3 {_mm_load_ps(reinterpret_cast<const float*> (&vector))};
				r2 = _mm_cvtps_epi32(r3);
			}

			r1 = _mm_sub_epi32(r1, r2);
			_mm_store_si128(reinterpret_cast<__m128i*> (this), r1);
		}

		return *this;
	}


	template <turbolin::VectorType T, std::size_t D>
	template <turbolin::VectorType T2>
	const turbolin::Vector<T, D> &Vector<T, D>::operator*=(const turbolin::Vector<T2, D> &vector) noexcept {
		if constexpr (std::is_same_v<T, float>) {
			__m128 r1 {};
			__m128 r2 {};

			if constexpr (std::is_same_v<T, T2>) {
				r1 = _mm_load_ps(reinterpret_cast<const float*> (this));
				r2 = _mm_load_ps(reinterpret_cast<const float*> (&vector));
			}
			else {
				r1 = _mm_load_ps(reinterpret_cast<const float*> (this));
				__m128i r3 {_mm_load_si128(reinterpret_cast<const __m128i*> (&vector))};
				r2 = _mm_cvtepi32_ps(r3);
			}

			r1 = _mm_mul_ps(r1, r2);
			_mm_store_ps(reinterpret_cast<float*> (this), r1);
		}
		else {
			__m128i r1 {};
			__m128i r2 {};

			if constexpr (std::is_same_v<T, T2>) {
				r1 = _mm_load_si128(reinterpret_cast<const __m128i*> (this));
				r2 = _mm_load_si128(reinterpret_cast<const __m128i*> (&vector));
			}
			else {
				r1 = _mm_load_si128(reinterpret_cast<const __m128i*> (this));
				__m128 r3 {_mm_load_ps(reinterpret_cast<const float*> (&vector))};
				r2 = _mm_cvtps_epi32(r3);
			}

			r1 = _mm_mullo_epi32(r1, r2);
			_mm_store_si128(reinterpret_cast<__m128i*> (this), r1);
		}

		return *this;
	}


	template <turbolin::VectorType T2>
	const turbolin::Vector<T, D> &Vector<T, D>::operator*=(T2 scalar) noexcept {
		if constexpr (std::is_same_v<T, float>) {
			__m128 r1 {_mm_load_ps(reinterpret_cast<const float*> (this))};
			__m128 r2 {_mm_set1_ps(static_cast<float> (scalar))};

			r1 = _mm_mul_ps(r1, r2);
			_mm_store_ps(reinterpret_cast<float*> (this), r1);
		}
		else {
			__m128i r1 {_mm_load_si128(reinterpret_cast<const __m128i*> (this))};
			__m128i r2 {_mm_set1_epi32(static_cast<std::int32_t> (scalar))};

			r1 = _mm_mullo_epi32(r1, r2);
			_mm_store_si128(reinterpret_cast<__m128i*> (this), r1);
		}

		return *this;
	}


	template <turbolin::VectorType T, turbolin::VectorType T2, std::size_t D>
	T dot(const turbolin::Vector<T, D> &lhs, const turbolin::Vector<T2, D> &rhs) {
		if constexpr (std::is_same_v<T, float>) {
			__m128 r1 {};
			__m128 r2 {};

			if constexpr (std::is_same_v<T, T2>) {
				r1 = _mm_load_ps(reinterpret_cast<const float*> (&lhs));
				r2 = _mm_load_ps(reinterpret_cast<const float*> (&rhs));
			}
			else {
				r1 = _mm_load_ps(reinterpret_cast<const float*> (&lhs));
				__m128i r3 {_mm_load_si128(reinterpret_cast<const __m128i*> (&rhs))};
				r2 = _mm_cvtepi32_ps(r3);
			}

			r1 = _mm_mul_ps(r1, r2);
			__m128 shuf {_mm_movehdup_ps(r1)};
			__m128 sums {_mm_add_ps(r1, shuf)};
			shuf = _mm_movehl_ps(shuf, sums);
			sums = _mm_add_ss(sums, shuf);
			return _mm_cvtss_f32(sums);
		}
		else {
			__m128i r1 {};
			__m128i r2 {};

			if constexpr (std::is_same_v<T, T2>) {
				r1 = _mm_load_si128(reinterpret_cast<const __m128i*> (&lhs));
				r2 = _mm_load_si128(reinterpret_cast<const __m128i*> (&rhs));
			}
			else {
				r1 = _mm_load_si128(reinterpret_cast<const __m128i*> (&lhs));
				__m128 r3 {_mm_load_ps(reinterpret_cast<const float*> (&rhs))};
				r2 = _mm_cvtps_epi32(r3);
			}

			r1 = _mm_mullo_epi32(r1, r2);
			__m128i shuf {_mm_shuffle_epi32(r1, _MM_SHUFFLE(1, 0, 3, 2))};
			__m128i sums {_mm_add_epi32(r1, shuf)};
			shuf = _mm_shuffle_epi32(sums, _MM_SHUFFLE(3, 2, 1, 1));
			sums = _mm_add_epi32(sums, shuf);
			return _mm_extract_epi32(sums, 0);
		}
	}


	template <turbolin::VectorType T, turbolin::VectorType T2>
	turbolin::Vector<T, 3> cross(const turbolin::Vector<T, 3> &lhs, const turbolin::Vector<T2, 3> &rhs) {
		turbolin::Vector<T, 3> output {};

		if constexpr (std::is_same_v<T, float>) {
			__m128 r1 {};
			__m128 r2 {};

			if constexpr (std::is_same_v<T, T2>) {
				r1 = _mm_load_ps(reinterpret_cast<const float*> (&lhs));
				r2 = _mm_load_ps(reinterpret_cast<const float*> (&rhs));
			}
			else {
				r1 = _mm_load_ps(reinterpret_cast<const float*> (&lhs));
				__m128i r3 {_mm_load_si128(reinterpret_cast<const __m128i*> (&rhs))};
				r2 = _mm_cvtepi32_ps(r3);
			}

			__m128 shuf1_pos {_mm_shuffle_ps(r1, r1, _MM_SHUFFLE(3, 0, 2, 1))};
			__m128 shuf1_neg {_mm_shuffle_ps(r1, r1, _MM_SHUFFLE(3, 1, 0, 2))};
			__m128 shuf2_pos {_mm_shuffle_ps(r2, r2, _MM_SHUFFLE(3, 1, 0, 2))};
			__m128 shuf2_neg {_mm_shuffle_ps(r2, r2, _MM_SHUFFLE(3, 0, 2, 1))};

			__m128 mul_pos {_mm_mul_ps(shuf1_pos, shuf2_pos)};
			__m128 mul_neg {_mm_mul_ps(shuf1_neg, shuf2_neg)};

			__m128 res {_mm_sub_ps(mul_pos, mul_neg)};
			_mm_store_ps(reinterpret_cast<float*> (&output), res);
			return output;
		}
		else {
			__m128i r1 {};
			__m128i r2 {};

			if constexpr (std::is_same_v<T, T2>) {
				r1 = _mm_load_si128(reinterpret_cast<const __m128i*> (&lhs));
				r2 = _mm_load_si128(reinterpret_cast<const __m128i*> (&rhs));
			}
			else {
				r1 = _mm_load_si128(reinterpret_cast<const __m128i*> (&lhs));
				__m128 r3 {_mm_load_ps(reinterpret_cast<const float*> (&rhs))};
				r2 = _mm_cvtps_epi32(r3);
			}

			__m128i shuf1_pos {_mm_shuffle_epi32(r1, _MM_SHUFFLE(3, 0, 2, 1))};
			__m128i shuf1_neg {_mm_shuffle_epi32(r1, _MM_SHUFFLE(3, 1, 0, 2))};
			__m128i shuf2_pos {_mm_shuffle_epi32(r2, _MM_SHUFFLE(3, 1, 0, 2))};
			__m128i shuf2_neg {_mm_shuffle_epi32(r2, _MM_SHUFFLE(3, 0, 2, 1))};

			__m128i mul_pos {_mm_mullo_epi32(shuf1_pos, shuf2_pos)};
			__m128i mul_neg {_mm_mullo_epi32(shuf1_neg, shuf2_neg)};

			__m128i res {_mm_sub_epi32(mul_pos, mul_neg)};
			_mm_store_si128(reinterpret_cast<__m128i*> (&output), res);
			return output;
		}
	}


	template <turbolin::VectorType T, std::size_t D>
	std::ostream &operator<<(std::ostream &stream, const turbolin::Vector<T, D> &vector) {
		if constexpr (D == 2) {
			stream << "(" << vector.x << ", " << vector.y << ")";
		}
		else if constexpr (D == 3) {
			stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
		}
		else if constexpr (D == 4) {
			stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
		}

		return stream;
	}


} // namespace turbolin
