#pragma once

#include "turbolin/vector.hpp"

#include <array>
#include <cstring>
#include <immintrin.h>



namespace turbolin {
	template <turbolin::IsVectorType T, std::size_t D>
	template <turbolin::IsVectorType ...Args>
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


	template <turbolin::IsVectorType T, std::size_t D>
	template <turbolin::IsVectorType T2, std::size_t D2, turbolin::IsVectorType ...Args>
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


	template <turbolin::IsVectorType T, std::size_t D>
	template <turbolin::IsVectorType T2>
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


	template <turbolin::IsVectorType T, std::size_t D>
	template <turbolin::IsVectorType T2>
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


	template <turbolin::IsVectorType T, std::size_t D>
	template <turbolin::IsVectorType T2>
	const turbolin::Vector<T, D> Vector<T, D>::operator+=(const turbolin::Vector<T2, D> &vector) noexcept {
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


	template <turbolin::IsVectorType T, std::size_t D>
	template <turbolin::IsVectorType T2>
	const turbolin::Vector<T, D> Vector<T, D>::operator-=(const turbolin::Vector<T2, D> &vector) noexcept {
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


	template <turbolin::IsVectorType T, std::size_t D>
	template <turbolin::IsVectorType T2>
	const turbolin::Vector<T, D> Vector<T, D>::operator*=(const turbolin::Vector<T2, D> &vector) noexcept {
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

			r1 = _mm_mul_epi32(r1, r2);
			_mm_store_si128(reinterpret_cast<__m128i*> (this), r1);
		}

		return *this;
	}


} // namespace turbolin
