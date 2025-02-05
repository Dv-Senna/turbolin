#pragma once

#include "turbolin/simd.hpp"
#include "turbolin/vector.hpp"


namespace tl::default_::vector {
	template <tl::Arithmetic T, std::size_t D, tl::Arithmetic ...Args>
	constexpr auto construct(tl::Vector<T, D> &self, Args ...args) noexcept -> void {
		std::tuple tuple {args...};

		if constexpr (sizeof...(Args) >= 1)
			self.x = std::get<0> (tuple);
		else
			self.x = static_cast<T> (0);

		if constexpr (sizeof...(Args) >= 2)
			self.y = std::get<1> (tuple);
		else
			self.y = static_cast<T> (0);

		if constexpr (sizeof...(Args) >= 3)
			self.z = std::get<2> (tuple);
		else if constexpr (D >= 3)
			self.z = static_cast<T> (0);
		else if constexpr (tl::IsSimd<T>)
			self.__padding[0] = static_cast<T> (0);

		if constexpr (sizeof...(Args) >= 4)
			self.w = std::get<3> (tuple);
		else if constexpr (D >= 4)
			self.w = static_cast<T> (0);
		else if constexpr (tl::IsSimd<T> && D == 3)
			self.__padding[0] = static_cast<T> (0);
		else if constexpr (tl::IsSimd<T>)
			self.__padding[1] = static_cast<T> (0);
	}


	template <tl::Arithmetic T, std::size_t D, tl::Arithmetic T2, std::size_t D2, tl::Arithmetic ...Args>
	constexpr auto copy(tl::Vector<T, D> &self, const tl::Vector<T2, D2> &vector, Args ...args) noexcept -> void {
		self.x = static_cast<T> (vector.x);
		self.y = static_cast<T> (vector.y);
		
		std::tuple tuple {args...};

		if constexpr (D2 == 2) {
			if constexpr (sizeof...(Args) >= 1)
				self.z = std::get<0> (tuple);
			if constexpr (sizeof...(Args) >= 2)
				self.w = std::get<1> (tuple);
		}
		else if constexpr (D2 == 3) {
			self.z = static_cast<T> (vector.z);
			if constexpr (sizeof...(Args) == 1)
				self.w = std::get<0> (tuple);
		}
		else {
			self.z = static_cast<T> (vector.z);
			self.w = static_cast<T> (vector.w);
		}
	}


	template <tl::Arithmetic T, std::size_t D, tl::Arithmetic T2>
	constexpr auto equal(const tl::Vector<T, D> &lhs, const tl::Vector<T2, D> &rhs) noexcept -> bool {
		if (lhs.x != rhs.x || lhs.y != rhs.y)
			return false;
		if constexpr (D >= 3) {
			if (lhs.z != rhs.z)
				return false;
		}
		else {
			if (lhs.w != rhs.w)
				return false;
		}
		return true;
	}


	template <tl::Arithmetic T, std::size_t D, tl::Arithmetic T2>
	constexpr auto add(tl::Vector<T, D> &self, const tl::Vector<T2, D> &vector) noexcept -> void {
		self.x += vector.x;
		self.y += vector.y;
		if constexpr (D >= 3)
			self.z += vector.z;
		if constexpr (D >= 4)
			self.w += vector.w;
	}


	template <tl::Arithmetic T, std::size_t D, tl::Arithmetic T2>
	constexpr auto sub(tl::Vector<T, D> &self, const tl::Vector<T2, D> &vector) noexcept -> void {
		self.x -= vector.x;
		self.y -= vector.y;
		if constexpr (D >= 3)
			self.z -= vector.z;
		if constexpr (D >= 4)
			self.w -= vector.w;
	}


	template <tl::Arithmetic T, std::size_t D, tl::Arithmetic T2>
	constexpr auto mul(tl::Vector<T, D> &self, const tl::Vector<T2, D> &vector) noexcept -> void {
		self.x *= vector.x;
		self.y *= vector.y;
		if constexpr (D >= 3)
			self.z *= vector.z;
		if constexpr (D >= 4)
			self.w *= vector.w;
	}


	template <tl::Arithmetic T, std::size_t D, tl::Arithmetic T2>
	constexpr auto scalarMul(tl::Vector<T, D> &self, T2 scalar) noexcept -> void {
		self.x *= scalar;
		self.y *= scalar;
		if constexpr (D >= 3)
			self.z *= scalar;
		if constexpr (D >= 4)
			self.w *= scalar;
	}


	template <tl::Arithmetic T, std::size_t D, tl::Arithmetic T2>
	constexpr auto dot(const tl::Vector<T, D> &lhs, const tl::Vector<T2, D> &rhs) noexcept -> T {
		T result {lhs.x * static_cast<T> (rhs.x) + lhs.y * static_cast<T> (rhs.y)};
		if constexpr (D >= 3)
			result += lhs.z * static_cast<T> (rhs.z);
		if constexpr (D >= 4)
			result += lhs.w * static_cast<T> (rhs.w);
		return result;
	}


	template <tl::Arithmetic T, tl::Arithmetic T2>
	constexpr auto cross(const tl::Vector<T, 3> &lhs, const tl::Vector<T2, 3> &rhs) noexcept -> tl::Vector<T, 3> {
		tl::Vector<T, 3> result {
			lhs.y * static_cast<T> (rhs.z) - lhs.z * static_cast<T> (rhs.y),
			lhs.z * static_cast<T> (rhs.x) - lhs.x * static_cast<T> (rhs.z),
			lhs.x * static_cast<T> (rhs.y) - lhs.y * static_cast<T> (rhs.x)
		};
		return result;
	}

} // namespace tl::default_::vector
