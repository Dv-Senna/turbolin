#pragma once

#include "turbolin/vector.hpp"

#include <cstring>

#include "turbolin/assert.hpp"


namespace tl {
	template <tl::Arithmetic T, std::size_t D>
	template <tl::Arithmetic ...Args>
	requires (sizeof...(Args) <= D)
	constexpr Vector<T, D>::Vector(Args ...args) noexcept {
		std::tuple tuple {args...};

		if constexpr (sizeof...(Args) >= 1)
			this->x = std::get<0> (tuple);
		else
			this->x = static_cast<T> (0);

		if constexpr (sizeof...(Args) >= 2)
			this->y = std::get<1> (tuple);
		else
			this->y = static_cast<T> (0);

		if constexpr (sizeof...(Args) >= 3)
			this->z = std::get<2> (tuple);
		else if constexpr (D >= 3)
			this->z = static_cast<T> (0);
		else if constexpr (tl::IsSimd<T>)
			this->__padding[0] = static_cast<T> (0);

		if constexpr (sizeof...(Args) >= 4)
			this->w = std::get<3> (tuple);
		else if constexpr (D >= 4)
			this->w = static_cast<T> (0);
		else if constexpr (tl::IsSimd<T> && D == 3)
			this->__padding[1] = static_cast<T> (0);
		else if constexpr (tl::IsSimd<T>)
			this->__padding[0] = static_cast<T> (0);
	}


	template <tl::Arithmetic T, std::size_t D>
	template <tl::Arithmetic T2, std::size_t D2, tl::Arithmetic ...Args>
	requires (sizeof...(Args) <= D - D2)
	constexpr Vector<T, D>::Vector(const Vector<T2, D2> &vector, Args ...args) noexcept {
		this->x = static_cast<T> (vector.x);
		this->y = static_cast<T> (vector.y);
		
		std::tuple tuple {args...};

		if constexpr (D2 == 2) {
			if constexpr (sizeof...(Args) >= 1)
				this->z = std::get<0> (tuple);
			if constexpr (sizeof...(Args) >= 2)
				this->w = std::get<1> (tuple);
		}
		else if constexpr (D2 == 3) {
			this->z = static_cast<T> (vector.z);
			if constexpr (sizeof...(Args) == 1)
				this->w = std::get<0> (tuple);
		}
		else {
			this->z = static_cast<T> (vector.z);
			this->w = static_cast<T> (vector.w);
		}
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
