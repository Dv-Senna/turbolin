#pragma once

#include "turbolin/vector.hpp"

#include <cstring>
#include <iostream>

#include "turbolin/assert.hpp"

#include "turbolin/default/vector.inl"
#include "turbolin/sse2/vector.inl"


namespace tl {
	template <tl::Arithmetic T, std::size_t D>
	template <tl::Arithmetic ...Args>
	requires (sizeof...(Args) <= D)
	constexpr Vector<T, D>::Vector(Args ...args) noexcept {
		tl::simdRuntimeDispatcher<
			void(*)(Vector<T, D>&, Args...),
			tl::default_::vector::construct<T, D, Args...>,
			tl::sse2::vector::construct<T, D, Args...>
		> (*this, args...);
	}


	template <tl::Arithmetic T, std::size_t D>
	template <tl::Arithmetic T2, std::size_t D2, tl::Arithmetic ...Args>
	requires (sizeof...(Args) <= D - D2)
	constexpr Vector<T, D>::Vector(const Vector<T2, D2> &vector, Args ...args) noexcept {
		tl::simdRuntimeDispatcher<
			void(*)(Vector<T, D>&, const Vector<T2, D2>&, Args...),
			tl::default_::vector::copy<T, D, T2, D2, Args...>,
			tl::sse2::vector::copy<T, D, T2, D2, Args...>
		> (*this, vector, args...);
	}


	template <tl::Arithmetic T, std::size_t D>
	template <tl::Arithmetic T2>
	constexpr auto Vector<T, D>::operator=(const Vector<T2, D> &vector) noexcept -> Vector<T, D>& {
		new (this) Vector<T, D> (vector);
		return this;
	}


	template <tl::Arithmetic T, std::size_t D>
	constexpr auto Vector<T, D>::get(std::size_t index) noexcept -> T& {
		TL_ASSERT(index < D, "Out of bound vector component access");

		if (index == 0)
			return this->x;
		if (index == 1)
			return this->y;

		if constexpr (D >= 3) {
			if (index == 2)
				return this->z;
		}
		if constexpr (D >= 4) {
			if (index == 3)
				return this->w;
		}
	}


	template <tl::Arithmetic T, std::size_t D>
	constexpr auto Vector<T, D>::get(std::size_t index) const noexcept -> const T& {
		TL_ASSERT(index < D, "Out of bound vector component access");

		if (index == 0)
			return this->x;
		if (index == 1)
			return this->y;

		if constexpr (D >= 3) {
			if (index == 2)
				return this->z;
		}
		if constexpr (D >= 4) {
			if (index == 3)
				return this->w;
		}
	}


	template <tl::Arithmetic T, std::size_t D>
	template <tl::Arithmetic T2>
	constexpr auto Vector<T, D>::operator+=(const Vector<T2, D> &vector) noexcept -> Vector<T, D>& {
		tl::simdRuntimeDispatcher<
			void(*)(Vector<T, D>&, const Vector<T2, D>&),
			tl::default_::vector::add<T, D, T2>,
			tl::sse2::vector::add<T, D, T2>
		> (*this, vector);
		return *this;
	}


	template <tl::Arithmetic T, std::size_t D>
	template <tl::Arithmetic T2>
	constexpr auto Vector<T, D>::operator-=(const Vector<T2, D> &vector) noexcept -> Vector<T, D>& {
		tl::simdRuntimeDispatcher<
			void(*)(Vector<T, D>&, const Vector<T2, D>&),
			tl::default_::vector::sub<T, D, T2>,
			tl::sse2::vector::sub<T, D, T2>
		> (*this, vector);
		return *this;
	}


	template <tl::Arithmetic T, std::size_t D>
	template <tl::Arithmetic T2>
	constexpr auto Vector<T, D>::operator*=(const Vector<T2, D> &vector) noexcept -> Vector<T, D>& {
		tl::simdRuntimeDispatcher<
			void(*)(Vector<T, D>&, const Vector<T2, D>&),
			tl::default_::vector::mul<T, D, T2>,
			tl::sse2::vector::mul<T, D, T2>
		> (*this, vector);
		return *this;
	}


	template <tl::Arithmetic T, std::size_t D>
	template <tl::Arithmetic T2>
	constexpr auto Vector<T, D>::operator*=(T2 scalar) noexcept -> Vector<T, D>& {
		tl::simdRuntimeDispatcher<
			void(*)(Vector<T, D>&, T2),
			tl::default_::vector::scalarMul<T, D, T2>,
			tl::sse2::vector::scalarMul<T, D, T2>
		> (*this, vector);
		return *this;
	}


	template <tl::Arithmetic T, std::size_t D>
	auto operator<<(std::ostream &stream, const Vector<T, D> &vector) noexcept -> std::ostream& {
		if constexpr (D == 2)
			stream << "(" << vector.x << ", " << vector.y << ")";
		else if constexpr (D == 3)
			stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
		else
			stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
		return stream;
	}

} // namespace tl
