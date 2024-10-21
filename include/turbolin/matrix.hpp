#pragma once

#include <cinttypes>
#include <type_traits>


#if defined(__AVX__) && !defined(TURBOLIN_SMALL_ALIGNMENT_MATRIX)
	#define TURBOLIN_USE_AVX_MATRIX
#endif


namespace turbolin {
	namespace {
		template <typename T>
		concept MatrixType = std::is_same_v<T, float> || std::is_same_v<T, std::int32_t>;

	#ifdef TURBOLIN_USE_AVX_MATRIX
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


	template <turbolin::MatrixType T, std::size_t D>
	class alignas(turbolin::MatrixAlignment<T>::alignment) Matrix : public turbolin::MatrixLayout<T, D> {
		public:
			template <turbolin::MatrixType ...Args>
			Matrix(Args&& ...args);

			template <turbolin::MatrixType T2>
			Matrix(const turbolin::Matrix<T2, D> &matrix);
			template <turbolin::MatrixType T2>
			const turbolin::Matrix<T, D> &operator=(const turbolin::Matrix<T2, D> &matrix);

			template <turbolin::MatrixType T2>
			bool operator==(const turbolin::Matrix<T2, D> &matrix) const noexcept;
	};

} // namespace turbolin



#include "turbolin/matrix.inl"
