#pragma once

#include <cstddef>
#include <format>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>

#include "turbolin/simd.hpp"


namespace tl {
	namespace __internals {
		struct Empty {};

		template <tl::Arithmetic T, std::size_t D>
		requires (D > 1 && D <= 4)
		struct VectorLayout;

		template <tl::Arithmetic T>
		struct VectorLayout<T, 2> {
			union {T x, u, w;};
			union {T y, v, h;};
			[[no_unique_address]]
			std::conditional_t<tl::IsSimd<T>, T[2], Empty> __padding;
		};

		template <tl::Arithmetic T>
		struct VectorLayout<T, 3> {
			union {T x, r;};
			union {T y, g;};
			union {T z, b;};
			[[no_unique_address]]
			std::conditional_t<tl::IsSimd<T>, T[1], Empty> __padding;
		};

		template <tl::Arithmetic T>
		struct VectorLayout<T, 4> {
			union {T x, r;};
			union {T y, g;};
			union {T z, b;};
			union {T w, a;};
		};


		template <tl::Arithmetic T>
		struct VectorAlignment {
			static constexpr std::size_t value {tl::SimdAlignment<tl::SimdExtension::eSSE42, T>::value};
		};

	} // namespace __internals


	template <tl::Arithmetic T, std::size_t D>
	class alignas(__internals::VectorAlignment<T>::value) Vector : public __internals::VectorLayout<T, D> {
		public:
			template <tl::Arithmetic ...Args>
			requires (sizeof...(Args) <= D)
			constexpr Vector(Args ...args) noexcept;

			template <tl::Arithmetic T2, std::size_t D2, tl::Arithmetic ...Args>
			requires (sizeof...(Args) <= D - D2)
			constexpr Vector(const Vector<T2, D2> &vector, Args ...args) noexcept;
			template <tl::Arithmetic T2>
			constexpr auto operator=(const Vector<T2, D> &vector) noexcept -> Vector<T, D>&;

			constexpr auto get(std::size_t index) noexcept -> T&;
			constexpr auto get(std::size_t index) const noexcept -> const T&;

			template <tl::Arithmetic T2>
			constexpr auto operator+=(const Vector<T2, D> &vector) noexcept -> Vector<T, D>&;
			template <tl::Arithmetic T2>
			constexpr auto operator-=(const Vector<T2, D> &vector) noexcept -> Vector<T, D>&;
			template <tl::Arithmetic T2>
			constexpr auto operator*=(const Vector<T2, D> &vector) noexcept -> Vector<T, D>&;
			template <tl::Arithmetic T2>
			constexpr auto operator*=(T2 scalar) noexcept -> Vector<T, D>&;
			template <tl::Arithmetic T2>
			constexpr auto operator/=(T2 scalar) noexcept -> Vector<T, D>& {return *this *= static_cast<T2> (1) / scalar;}

			template <tl::Arithmetic T2>
			constexpr auto operator+(const Vector<T2, D> &vector) const noexcept {auto tmp {*this}; return tmp += vector;}
			template <tl::Arithmetic T2>
			constexpr auto operator-(const Vector<T2, D> &vector) const noexcept {auto tmp {*this}; return tmp -= vector;}
			template <tl::Arithmetic T2>
			constexpr auto operator*(const Vector<T2, D> &vector) const noexcept {auto tmp {*this}; return tmp *= vector;}
			template <tl::Arithmetic T2>
			constexpr auto operator*(T2 scalar) noexcept {auto tmp {*this}; return tmp *= scalar;};
			template <tl::Arithmetic T2>
			constexpr auto operator/(T2 scalar) noexcept {auto tmp {*this}; return tmp /= scalar;};

			template <tl::Arithmetic T2>
			friend constexpr auto operator*(T2 scalar, Vector<T, D> vector) noexcept {return vector *= scalar;}
	};

	template <tl::Arithmetic ...Args>
	Vector(Args ...args) noexcept -> Vector<std::tuple_element_t<0, std::tuple<Args...>>, sizeof...(Args)>;


	template <tl::Arithmetic T, std::size_t D, tl::Arithmetic T2>
	constexpr auto dot(const Vector<T, D> &lhs, const Vector<T2, D> &rhs) noexcept -> T;


	template <tl::Arithmetic T, std::size_t D>
	auto operator<<(std::ostream &stream, const Vector<T, D> &vector) noexcept -> std::ostream&;

	// non-simd type
	static_assert(alignof(Vector<char, 2>) == alignof(char));
	static_assert(alignof(Vector<char, 3>) == alignof(char));
	static_assert(alignof(Vector<char, 4>) == alignof(char));

	static_assert(sizeof(Vector<char, 2>) == 2*sizeof(char));
	static_assert(sizeof(Vector<char, 3>) == 3*sizeof(char));
	static_assert(sizeof(Vector<char, 4>) == 4*sizeof(char));

	// simd type
	static_assert(alignof(Vector<float, 2>) == tl::SimdAlignment<tl::SimdExtension::eSSE42, float>::value);
	static_assert(alignof(Vector<float, 3>) == tl::SimdAlignment<tl::SimdExtension::eSSE42, float>::value);
	static_assert(alignof(Vector<float, 4>) == tl::SimdAlignment<tl::SimdExtension::eSSE42, float>::value);

	static_assert((tl::IsSimd<float> && sizeof(Vector<float, 2>) == tl::SimdSize<tl::SimdExtension::eSSE42, float>::value) || sizeof(Vector<float, 2>) == 2*sizeof(float));
	static_assert((tl::IsSimd<float> && sizeof(Vector<float, 3>) == tl::SimdSize<tl::SimdExtension::eSSE42, float>::value) || sizeof(Vector<float, 3>) == 3*sizeof(float));
	static_assert((tl::IsSimd<float> && sizeof(Vector<float, 4>) == tl::SimdSize<tl::SimdExtension::eSSE42, float>::value) || sizeof(Vector<float, 4>) == 4*sizeof(float));

} // namespace tl 


template <tl::Arithmetic T, std::size_t D>
struct std::formatter<tl::Vector<T, D>> : std::formatter<std::string> {
	template <typename FormatContext>
	inline auto format(const tl::Vector<T, D> &vector, FormatContext &ctx) const noexcept -> typename FormatContext::iterator {
		std::ostringstream stream {};
		stream << vector;
		return std::formatter<std::string>::format(stream.str(), ctx);
	}
};

#include "turbolin/vector.inl"
