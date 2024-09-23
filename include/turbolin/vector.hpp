#pragma once

#include <cinttypes>

#include "turbolin/isNumber.hpp"



namespace turbolin {
	namespace {
		template <typename T>
		struct VectorAlignement {
			static constexpr std::size_t alignment {16};
		};


		template <turbolin::IsNumber T, std::size_t D>
		struct VectorLayout;

		template <turbolin::IsNumber T>
		struct VectorLayout<T, 2> {
			union {
				T x;
				T u;
				T w;
			};

			union {
				T y;
				T v;
				T h;
			};

			private:
				T __padding[2];
		};

		template <turbolin::IsNumber T>
		struct VectorLayout<T, 3> {
			union {
				T x;
				T r;
				T w;
			};

			union {
				T y;
				T g;
				T h;
			};

			union {
				T z;
				T b;
				T d;
			};

			private:
				T __padding[1];
		};

		template <turbolin::IsNumber T>
		struct VectorLayout<T, 4> {
			union {
				T x;
				T r;
			};

			union {
				T y;
				T g;
			};

			union {
				T z;
				T b;
			};

			union {
				T w;
				T a;
			};
		};

	} // namespace


	template <turbolin::IsNumber T, std::size_t D>
	class alignas(turbolin::VectorAlignement<T>::alignment) Vector : public turbolin::VectorLayout<T, D> {
		public:
			Vector() = default;
	};

} // namespace turbolin
