#pragma once

#include <cinttypes>
#include <type_traits>



namespace turbolin {
	namespace {
		template <typename T>
		concept IsVectorType = std::is_same_v<float, T> || std::is_same_v<std::int32_t, T>;

		template <typename T>
		struct VectorAlignement {
			static constexpr std::size_t alignment {16};
		};


		template <turbolin::IsVectorType T, std::size_t D>
		struct VectorLayout;

		template <turbolin::IsVectorType T>
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

		template <turbolin::IsVectorType T>
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

		template <turbolin::IsVectorType T>
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


	template <turbolin::IsVectorType T, std::size_t D>
	class alignas(turbolin::VectorAlignement<T>::alignment) Vector : public turbolin::VectorLayout<T, D> {
		public:
			template <turbolin::IsVectorType ...Args>
			Vector(Args&& ...args) noexcept;

			template <turbolin::IsVectorType T2, std::size_t D2, turbolin::IsVectorType ...Args>
			Vector(const turbolin::Vector<T2, D2> &vector, Args&& ...args) noexcept;
			template <turbolin::IsVectorType T2>
			const turbolin::Vector<T, D> &operator=(const turbolin::Vector<T2, D> &vector) noexcept;

			template <turbolin::IsVectorType T2>
			bool operator==(const turbolin::Vector<T2, D> &vector) const noexcept;

			template <turbolin::IsVectorType T2>
			const turbolin::Vector<T, D> &operator+=(const turbolin::Vector<T2, D> &vector) noexcept;
			template <turbolin::IsVectorType T2>
			const turbolin::Vector<T, D> &operator-=(const turbolin::Vector<T2, D> &vector) noexcept;
			template <turbolin::IsVectorType T2>
			const turbolin::Vector<T, D> &operator*=(const turbolin::Vector<T2, D> &vector) noexcept;

			template <turbolin::IsVectorType T2>
			inline turbolin::Vector<T, D> operator+(const turbolin::Vector<T2, D> &vector) const noexcept {auto copy {*this}; return copy += vector;}
			template <turbolin::IsVectorType T2>
			inline turbolin::Vector<T, D> operator-(const turbolin::Vector<T2, D> &vector) const noexcept {auto copy {*this}; return copy -= vector;}
			template <turbolin::IsVectorType T2>
			inline turbolin::Vector<T, D> operator*(const turbolin::Vector<T2, D> &vector) const noexcept {auto copy {*this}; return copy *= vector;}
	};


	template <turbolin::IsVectorType T, turbolin::IsVectorType T2, std::size_t D>
	T dot(const turbolin::Vector<T, D> &lhs, const turbolin::Vector<T2, D> &rhs);


} // namespace turbolin


#include "turbolin/vector.inl"
