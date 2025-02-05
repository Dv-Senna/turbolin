#pragma once

#include <x86intrin.h>

#include "turbolin/simd.hpp"
#include "turbolin/vector.hpp"
#include "turbolin/default/vector.inl"


namespace tl::sse2::vector {
	template <typename T>
	struct Reg {
		using Type = __m128i;
	};

	template <>
	struct Reg<float> {
		using Type = __m128;
	};

	template <typename T>
	using Reg_t = typename Reg<T>::Type;


	template <tl::IsSSE2 T, tl::IsSSE2 T2, std::size_t D>
	inline auto loadReg(const tl::Vector<T2, D> &vector) noexcept -> Reg_t<T> {
		if constexpr (std::is_same_v<T, float>) {
			if constexpr (std::is_same_v<T2, float>)
				return _mm_load_ps(reinterpret_cast<const float*> (&vector));
			return _mm_cvtepi32_ps(_mm_load_si128(reinterpret_cast<const __m128i*> (&vector)));
		}
		else {
			if constexpr (std::is_same_v<T2, float>)
				return _mm_load_si128(reinterpret_cast<const __m128i*> (&vector));
			return _mm_cvtps_epi32(_mm_load_ps(reinterpret_cast<const float*> (&vector)));
		}
	}

	template <tl::IsSSE2 T, std::size_t D>
	inline auto storeReg(tl::Vector<T, D> &vector, Reg_t<T> reg) noexcept -> void {
		if constexpr (std::is_same_v<T, float>)
			_mm_store_ps(reinterpret_cast<float*> (&vector), reg);
		else
			_mm_store_si128(reinterpret_cast<__m128i*> (&vector), reg);
	}



	template <tl::Arithmetic T, std::size_t D, tl::Arithmetic ...Args>
	constexpr auto construct(tl::Vector<T, D> &self, Args ...args) noexcept -> void {
		if constexpr (!tl::IsSSE2<T> || sizeof...(Args) != 0)
			return tl::default_::vector::construct(self, args...);
		else {
			if constexpr (std::is_same_v<T, float>) {
				__m128 zero {_mm_setzero_ps()};
				storeReg(self, zero);
			}
			else if constexpr (std::is_same_v<T, std::int32_t>) {
				__m128i zero {_mm_setzero_si128()};
				storeReg(self, zero);
			}
		}
	}


	template <tl::Arithmetic T, std::size_t D, tl::Arithmetic T2, std::size_t D2, tl::Arithmetic ...Args>
	constexpr auto copy(tl::Vector<T, D> &self, const tl::Vector<T2, D2> &vector, Args ...args) noexcept -> void {
		if constexpr (!tl::IsSSE2<T> || !tl::IsSSE2<T2> || D != D2 || sizeof...(Args) != 0)
			return tl::default_::vector::copy(self, vector, args...);
		else {
			if constexpr (std::is_same_v<T, float>) {
				__m128 r1 {loadReg<float> (vector)};
				storeReg(self, r1);
			}
			else if constexpr (std::is_same_v<T, std::int32_t>) {
				__m128i r1 {loadReg<std::int32_t> (vector)};
				storeReg(self, r1);
			}
		}
	}


	template <tl::Arithmetic T, std::size_t D, tl::Arithmetic T2>
	constexpr auto add(tl::Vector<T, D> &self, const tl::Vector<T2, D> &vector) noexcept -> void {
		if constexpr (!tl::IsSSE2<T> || !tl::IsSSE2<T2>)
			return tl::default_::vector::add(self, vector);
		else {
			if constexpr (std::is_same_v<T, float>) {
				__m128 r1 {loadReg<float> (self)};
				__m128 r2 {loadReg<float> (vector)};
				r1 = _mm_add_ps(r1, r2);
				storeReg(self, r1);
			}
			else if constexpr (std::is_same_v<T, std::int32_t>) {
				__m128i r1 {loadReg<std::int32_t> (self)};
				__m128i r2 {loadReg<std::int32_t> (vector)};
				r1 = _mm_add_epi32(r1, r2);
				storeReg(self, r1);
			}
		}
	}

} // namespace tl::sse2::vector
