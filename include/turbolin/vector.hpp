#pragma once

#include <cstddef>
#include <type_traits>

#include "turbolin/simd.hpp"


namespace tl {
	namespace __internals {
		struct Empty {};

		template <tl::Arithmetic T, std::size_t D>
		struct VectorLayout;

		template <tl::Arithmetic T>
		struct VectorLayout<T, 2> {
			union {T x, u, w;};
			union {T y, v, h;};
			private:
				[[no_unique_address]]
				std::conditional_t<tl::IsSimd<T>, T[2], Empty> __padding;
		};

		template <tl::Arithmetic T>
		struct VectorLayout<T, 3> {
			union {T x, r;};
			union {T y, g;};
			union {T z, b;};
			private:
				[[no_unique_address]]
				std::conditional_t<tl::IsSimd<T>, T, Empty> __padding;
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
			static constexpr std::size_t value {tl::SimdAlignment<tl::SimdExtension::eSSE2, T>::value};
		};

	} // namespace __internals


	template <tl::Arithmetic T, std::size_t D>
	class alignas(__internals::VectorAlignment<T>::value) Vector : public __internals::VectorLayout<T, D> {
		public:
	};


	// non-simd type
	static_assert(alignof(Vector<char, 2>) == alignof(char));
	static_assert(alignof(Vector<char, 3>) == alignof(char));
	static_assert(alignof(Vector<char, 4>) == alignof(char));

	static_assert(sizeof(Vector<char, 2>) == 2*sizeof(char));
	static_assert(sizeof(Vector<char, 3>) == 3*sizeof(char));
	static_assert(sizeof(Vector<char, 4>) == 4*sizeof(char));

	// simd type
	static_assert(alignof(Vector<float, 2>) == tl::SimdAlignment<tl::SimdExtension::eSSE2, float>::value);
	static_assert(alignof(Vector<float, 3>) == tl::SimdAlignment<tl::SimdExtension::eSSE2, float>::value);
	static_assert(alignof(Vector<float, 4>) == tl::SimdAlignment<tl::SimdExtension::eSSE2, float>::value);

	static_assert((tl::IsSimd<float> && sizeof(Vector<float, 2>) == tl::SimdSize<tl::SimdExtension::eSSE2, float>::value) || sizeof(Vector<float, 2>) == 2*sizeof(float));
	static_assert((tl::IsSimd<float> && sizeof(Vector<float, 3>) == tl::SimdSize<tl::SimdExtension::eSSE2, float>::value) || sizeof(Vector<float, 3>) == 3*sizeof(float));
	static_assert((tl::IsSimd<float> && sizeof(Vector<float, 4>) == tl::SimdSize<tl::SimdExtension::eSSE2, float>::value) || sizeof(Vector<float, 4>) == 4*sizeof(float));

} // namespace tl 
