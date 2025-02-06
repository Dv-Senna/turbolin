#pragma once

#include <x86intrin.h>
#include <cmath>

#include "turbolin/simd.hpp"
#include "turbolin/vector.hpp"
#include "turbolin/default/vector.inl"


namespace tl::sse42::vector {
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


	template <tl::IsSSE42 T, tl::IsSSE42 T2, std::size_t D>
	[[gnu::target("sse4.2")]]
	inline auto loadReg(const tl::Vector<T2, D> &vector) noexcept -> Reg_t<T> {
		if constexpr (std::is_same_v<T, float>) {
			if constexpr (std::is_same_v<T2, float>)
				return _mm_load_ps(reinterpret_cast<const float*> (&vector));
			return _mm_cvtepi32_ps(_mm_load_si128(reinterpret_cast<const __m128i*> (&vector)));
		}
		else {
			if constexpr (std::is_same_v<T2, float>)
				return _mm_cvtps_epi32(_mm_load_ps(reinterpret_cast<const float*> (&vector)));
			return _mm_load_si128(reinterpret_cast<const __m128i*> (&vector));
		}
	}

	template <tl::IsSSE42 T, std::size_t D>
	[[gnu::target("sse4.2")]]
	inline auto storeReg(tl::Vector<T, D> &vector, Reg_t<T> reg) noexcept -> void {
		if constexpr (std::is_same_v<T, float>)
			_mm_store_ps(reinterpret_cast<float*> (&vector), reg);
		else
			_mm_store_si128(reinterpret_cast<__m128i*> (&vector), reg);
	}



	template <tl::Arithmetic T, std::size_t D, tl::Arithmetic ...Args>
	[[gnu::target("sse4.2")]]
	constexpr auto construct(tl::Vector<T, D> &self, Args ...args) noexcept -> void {
		if constexpr (!tl::IsSSE42<T> || sizeof...(Args) != 0)
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
	[[gnu::target("sse4.2")]]
	constexpr auto copy(tl::Vector<T, D> &self, const tl::Vector<T2, D2> &vector, Args ...args) noexcept -> void {
		if constexpr (!tl::IsSSE42<T> || !tl::IsSSE42<T2> || D != D2 || sizeof...(Args) != 0)
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
	[[gnu::target("sse4.2")]]
	constexpr auto equal(const tl::Vector<T, D> &lhs, const tl::Vector<T2, D> &rhs) noexcept -> bool {
		if constexpr (!tl::IsSSE42<T> || !tl::IsSSE42<T2>)
			return tl::default_::vector::equal(lhs, rhs);
		else {
			if constexpr (std::is_same_v<T, float>) {
				__m128 r1 {loadReg<float> (lhs)};
				__m128 r2 {loadReg<float> (rhs)};

				r1 = _mm_sub_ps(r1, r2);
				__m128 absMask {_mm_set1_ps(-0.f)};
				r1 = _mm_andnot_ps(absMask, r1);
				__m128 epsilon {_mm_set1_ps(std::numeric_limits<float>::epsilon())};
				r1 = _mm_cmple_ps(r1, epsilon);
				return _mm_movemask_ps(r1) == 0xf;
			}
			else {
				__m128i r1 {loadReg<std::int32_t> (lhs)};
				__m128i r2 {loadReg<std::int32_t> (rhs)};
				r1 = _mm_cmpeq_epi32(r1, r2);
				return _mm_movemask_epi8(r1) == 0xffff;
			}
		}
	}


	template <tl::Arithmetic T, std::size_t D, tl::Arithmetic T2>
	[[gnu::target("sse4.2")]]
	constexpr auto add(tl::Vector<T, D> &self, const tl::Vector<T2, D> &vector) noexcept -> void {
		if constexpr (!tl::IsSSE42<T> || !tl::IsSSE42<T2>)
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


	template <tl::Arithmetic T, std::size_t D, tl::Arithmetic T2>
	[[gnu::target("sse4.2")]]
	constexpr auto sub(tl::Vector<T, D> &self, const tl::Vector<T2, D> &vector) noexcept -> void {
		if constexpr (!tl::IsSSE42<T> || !tl::IsSSE42<T2>)
			return tl::default_::vector::sub(self, vector);
		else {
			if constexpr (std::is_same_v<T, float>) {
				__m128 r1 {loadReg<float> (self)};
				__m128 r2 {loadReg<float> (vector)};
				r1 = _mm_sub_ps(r1, r2);
				storeReg(self, r1);
			}
			else if constexpr (std::is_same_v<T, std::int32_t>) {
				__m128i r1 {loadReg<std::int32_t> (self)};
				__m128i r2 {loadReg<std::int32_t> (vector)};
				r1 = _mm_sub_epi32(r1, r2);
				storeReg(self, r1);
			}
		}
	}


	template <tl::Arithmetic T, std::size_t D, tl::Arithmetic T2>
	[[gnu::target("sse4.2")]]
	constexpr auto mul(tl::Vector<T, D> &self, const tl::Vector<T2, D> &vector) noexcept -> void {
		if constexpr (!tl::IsSSE42<T> || !tl::IsSSE42<T2>)
			return tl::default_::vector::mul(self, vector);
		else {
			if constexpr (std::is_same_v<T, float>) {
				__m128 r1 {loadReg<float> (self)};
				__m128 r2 {loadReg<float> (vector)};
				r1 = _mm_mul_ps(r1, r2);
				storeReg(self, r1);
			}
			else if constexpr (std::is_same_v<T, std::int32_t>) {
				__m128i r1 {loadReg<std::int32_t> (self)};
				__m128i r2 {loadReg<std::int32_t> (vector)};
				r1 = _mm_mullo_epi32(r1, r2);
				storeReg(self, r1);
			}
		}
	}


	template <tl::Arithmetic T, std::size_t D, tl::Arithmetic T2>
	[[gnu::target("sse4.2")]]
	constexpr auto scalarMul(tl::Vector<T, D> &self, T2 scalar) noexcept -> void {
		if constexpr (!tl::IsSSE42<T> || !tl::IsSSE42<T2>)
			return tl::default_::vector::scalarMul(self, scalar);
		else {
			if constexpr (std::is_same_v<T, float>) {
				__m128 r1 {loadReg<float> (self)};
				__m128 r2 {_mm_set1_ps(static_cast<float> (scalar))};
				r1 = _mm_mul_ps(r1, r2);
				storeReg(self, r1);
			}
			else if constexpr (std::is_same_v<T, std::int32_t>) {
				__m128i r1 {loadReg<std::int32_t> (self)};
				__m128i r2 {_mm_set1_epi32(static_cast<std::int32_t> (scalar))};
				r1 = _mm_mullo_epi32(r1, r2);
				storeReg(self, r1);
			}
		}
	}


	template <tl::Arithmetic T, std::size_t D, tl::Arithmetic T2>
	[[gnu::target("sse4.2")]]
	constexpr auto dot(const tl::Vector<T, D> &lhs, const tl::Vector<T2, D> &rhs) noexcept -> T {
		if constexpr (!tl::IsSSE42<T> || !tl::IsSSE42<T2>)
			return tl::default_::vector::dot(lhs, rhs);
		else {
			if constexpr (std::is_same_v<T, float>) {
				__m128 r1 {loadReg<float> (lhs)};
				__m128 r2 {loadReg<float> (rhs)};

				r1 = _mm_mul_ps(r1, r2);
				__m128 shuf {_mm_movehdup_ps(r1)};
				__m128 sums {_mm_add_ps(r1, shuf)};
				shuf = _mm_movehl_ps(shuf, sums);
				sums = _mm_add_ss(sums, shuf);
				return _mm_cvtss_f32(sums);
			}
			else if constexpr (std::is_same_v<T, std::int32_t>) {
				__m128i r1 {loadReg<std::int32_t> (lhs)};
				__m128i r2 {loadReg<std::int32_t> (rhs)};

				r1 = _mm_mullo_epi32(r1, r2);
				__m128i shuf {_mm_shuffle_epi32(r1, _MM_SHUFFLE(1, 0, 3, 2))};
				__m128i sums {_mm_add_epi32(r1, shuf)};
				shuf = _mm_shuffle_epi32(sums, _MM_SHUFFLE(3, 2, 1, 1));
				sums = _mm_add_epi32(sums, shuf);
				return _mm_extract_epi32(sums, 0);
			}
		}
	}


	template <tl::Arithmetic T, tl::Arithmetic T2>
	[[gnu::target("sse4.2")]]
	constexpr auto cross(const tl::Vector<T, 3> &lhs, const tl::Vector<T2, 3> &rhs) noexcept -> tl::Vector<T, 3> {
		if constexpr (!tl::IsSSE42<T> || !tl::IsSSE42<T2>)
			return tl::default_::vector::cross(lhs, rhs);
		else {
			if constexpr (std::is_same_v<T, float>) {
				tl::Vector<float, 3> result {};
				__m128 r1 {loadReg<float> (lhs)};
				__m128 r2 {loadReg<float> (rhs)};

				__m128 shuf1_pos {_mm_shuffle_ps(r1, r1, _MM_SHUFFLE(3, 0, 2, 1))};
				__m128 shuf1_neg {_mm_shuffle_ps(r1, r1, _MM_SHUFFLE(3, 1, 0, 2))};
				__m128 shuf2_pos {_mm_shuffle_ps(r2, r2, _MM_SHUFFLE(3, 1, 0, 2))};
				__m128 shuf2_neg {_mm_shuffle_ps(r2, r2, _MM_SHUFFLE(3, 0, 2, 1))};

				__m128 mul_pos {_mm_mul_ps(shuf1_pos, shuf2_pos)};
				__m128 mul_neg {_mm_mul_ps(shuf1_neg, shuf2_neg)};

				__m128 res {_mm_sub_ps(mul_pos, mul_neg)};
				storeReg(result, res);
				return result;
			}
			else if constexpr (std::is_same_v<T, std::int32_t>) {
				tl::Vector<std::int32_t, 3> result {};
				__m128i r1 {loadReg<std::int32_t> (lhs)};
				__m128i r2 {loadReg<std::int32_t> (rhs)};

				__m128i shuf1_pos {_mm_shuffle_epi32(r1, _MM_SHUFFLE(3, 0, 2, 1))};
				__m128i shuf1_neg {_mm_shuffle_epi32(r1, _MM_SHUFFLE(3, 1, 0, 2))};
				__m128i shuf2_pos {_mm_shuffle_epi32(r2, _MM_SHUFFLE(3, 1, 0, 2))};
				__m128i shuf2_neg {_mm_shuffle_epi32(r2, _MM_SHUFFLE(3, 0, 2, 1))};

				__m128i mul_pos {_mm_mullo_epi32(shuf1_pos, shuf2_pos)};
				__m128i mul_neg {_mm_mullo_epi32(shuf1_neg, shuf2_neg)};

				__m128i res {_mm_sub_epi32(mul_pos, mul_neg)};
				storeReg(result, res);
				return result;
			}
		}
	}


	template <tl::Arithmetic T, std::size_t D>
	[[gnu::target("sse4.2")]]
	constexpr auto length(const tl::Vector<T, D> &vector) noexcept -> T {
		if constexpr (!tl::IsSSE42<T>)
			return tl::default_::vector::length(vector);
		else {
			if constexpr (std::is_same_v<T, float>) {
				__m128 r1 {loadReg<float> (vector)};
				r1 = _mm_mul_ps(r1, r1);
				__m128 shuf {_mm_movehdup_ps(r1)};
				__m128 sums {_mm_add_ps(r1, shuf)};
				shuf = _mm_movehl_ps(shuf, sums);
				sums = _mm_add_ss(sums, shuf);
				return std::sqrt(_mm_cvtss_f32(sums));
			}
			else if constexpr (std::is_same_v<T, std::int32_t>) {
				__m128i r1 {loadReg<std::int32_t> (vector)};
				r1 = _mm_mullo_epi32(r1, r1);
				__m128i shuf {_mm_shuffle_epi32(r1, _MM_SHUFFLE(1, 0, 3, 2))};
				__m128i sums {_mm_add_epi32(r1, shuf)};
				shuf = _mm_shuffle_epi32(sums, _MM_SHUFFLE(3, 2, 1, 1));
				sums = _mm_add_epi32(sums, shuf);
				return std::sqrt(_mm_extract_epi32(sums, 0));
			}
		}
	}


	template <tl::Arithmetic T, std::size_t D>
	[[gnu::target("sse4.2")]]
	constexpr auto length2(const tl::Vector<T, D> &vector) noexcept -> T {
		if constexpr (!tl::IsSSE42<T>)
			return tl::default_::vector::length(vector);
		else {
			if constexpr (std::is_same_v<T, float>) {
				__m128 r1 {loadReg<float> (vector)};
				r1 = _mm_mul_ps(r1, r1);
				__m128 shuf {_mm_movehdup_ps(r1)};
				__m128 sums {_mm_add_ps(r1, shuf)};
				shuf = _mm_movehl_ps(shuf, sums);
				sums = _mm_add_ss(sums, shuf);
				return _mm_cvtss_f32(sums);
			}
			else if constexpr (std::is_same_v<T, std::int32_t>) {
				__m128i r1 {loadReg<std::int32_t> (vector)};
				r1 = _mm_mullo_epi32(r1, r1);
				__m128i shuf {_mm_shuffle_epi32(r1, _MM_SHUFFLE(1, 0, 3, 2))};
				__m128i sums {_mm_add_epi32(r1, shuf)};
				shuf = _mm_shuffle_epi32(sums, _MM_SHUFFLE(3, 2, 1, 1));
				sums = _mm_add_epi32(sums, shuf);
				return _mm_extract_epi32(sums, 0);
			}
		}
	}


	template <tl::Arithmetic T, std::size_t D>
	[[gnu::target("sse4.2")]]
	constexpr auto normalize(const tl::Vector<T, D> &vector) noexcept -> tl::Vector<T, D> {
		if constexpr (!tl::IsSSE42<T>)
			return tl::default_::vector::normalize(vector);
		else {
			if constexpr (std::is_same_v<T, float>) {
				__m128 r1 {loadReg<float> (vector)};
				__m128 r2 = _mm_mul_ps(r1, r1);
				__m128 shuf {_mm_movehdup_ps(r2)};
				__m128 sums {_mm_add_ps(r2, shuf)};
				shuf = _mm_movehl_ps(shuf, sums);
				sums = _mm_add_ss(sums, shuf);

				__m128 rsqrt {_mm_set1_ps(_mm_cvtss_f32(sums))};
				rsqrt = _mm_rsqrt_ps(rsqrt);
				r1 = _mm_mul_ps(r1, rsqrt);
				tl::Vector<T, D> result {};
				storeReg(result, r1);
				return result;
			}
			else if constexpr (std::is_same_v<T, std::int32_t>) {
				__m128i r1 {loadReg<std::int32_t> (vector)};
				__m128i r2 = _mm_mullo_epi32(r1, r1);
				__m128i shuf {_mm_shuffle_epi32(r2, _MM_SHUFFLE(1, 0, 3, 2))};
				__m128i sums {_mm_add_epi32(r2, shuf)};
				shuf = _mm_shuffle_epi32(sums, _MM_SHUFFLE(3, 2, 1, 1));
				sums = _mm_add_epi32(sums, shuf);
				return vector / std::sqrt(_mm_extract_epi32(sums, 0));
			}
		}
	}

} // namespace tl::sse42::vector
