#pragma once

#include <cinttypes>
#include <type_traits>



namespace turbolin {
	namespace {
		template <typename T>
		concept MatrixType = std::is_same_v<T, float> || std::is_same_v<T, std::int32_t>;

	#ifdef __AVX__
		template <turbolin::MatrixType T>
		struct MatrixAlignment {
			static constexpr std::size_t alignment {32};
		};
	#else
		template <turbolin::MatrixType T>
		struct MatrixAlignment {
			static constexpr std::size_t alignment {16};
		};
	#endif

		template <turbolin::MatrixType T, std::size_t D>
		class MatrixLayout;

		template <turbolin::MatrixType T>
		struct MatrixLayout<T, 2> {
			private:
				T __content[8];
		};

		template <turbolin::MatrixType T>
		struct MatrixLayout<T, 3> {
			private:
				T __content[16];
		};

		template <turbolin::MatrixType T>
		struct MatrixLayout<T, 4> {
			private:
				T __content[16];
		};
	}
} // namespace turbolin
