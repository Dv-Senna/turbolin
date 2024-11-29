#pragma once

#include <cinttypes>
#include <ostream>
#include <type_traits>

#ifdef __cpp_lib_format
	#include <format>
#endif



namespace turbolin {
	template <typename T>
	concept VectorType = std::is_same_v<float, T> || std::is_same_v<std::int32_t, T>;

	template <typename T>
	struct VectorAlignement {
		static constexpr std::size_t alignment {16};
	};


	template <turbolin::VectorType T, std::size_t D>
	struct VectorLayout;

	template <turbolin::VectorType T>
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

	template <turbolin::VectorType T>
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

	template <turbolin::VectorType T>
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


	template <turbolin::VectorType T, std::size_t D>
	class alignas(turbolin::VectorAlignement<T>::alignment) Vector : public turbolin::VectorLayout<T, D> {
		public:
			template <turbolin::VectorType ...Args>
			Vector(Args&& ...args) noexcept;

			template <turbolin::VectorType T2, std::size_t D2, turbolin::VectorType ...Args>
			Vector(const turbolin::Vector<T2, D2> &vector, Args&& ...args) noexcept;
			template <turbolin::VectorType T2>
			const turbolin::Vector<T, D> &operator=(const turbolin::Vector<T2, D> &vector) noexcept;

			template <turbolin::VectorType T2>
			bool operator==(const turbolin::Vector<T2, D> &vector) const noexcept;

			template <turbolin::VectorType T2>
			const turbolin::Vector<T, D> &operator+=(const turbolin::Vector<T2, D> &vector) noexcept;
			template <turbolin::VectorType T2>
			const turbolin::Vector<T, D> &operator-=(const turbolin::Vector<T2, D> &vector) noexcept;
			template <turbolin::VectorType T2>
			const turbolin::Vector<T, D> &operator*=(const turbolin::Vector<T2, D> &vector) noexcept;
			template <turbolin::VectorType T2>
			const turbolin::Vector<T, D> &operator*=(T2 scalar) noexcept;

			template <turbolin::VectorType T2>
			inline turbolin::Vector<T, D> operator+(const turbolin::Vector<T2, D> &vector) const noexcept {auto copy {*this}; return copy += vector;}
			template <turbolin::VectorType T2>
			inline turbolin::Vector<T, D> operator-(const turbolin::Vector<T2, D> &vector) const noexcept {auto copy {*this}; return copy -= vector;}
			template <turbolin::VectorType T2>
			inline turbolin::Vector<T, D> operator*(const turbolin::Vector<T2, D> &vector) const noexcept {auto copy {*this}; return copy *= vector;}
			template <turbolin::VectorType T2>
			inline turbolin::Vector<T, D> operator*(T2 scalar) const noexcept {auto copy {*this}; return copy *= scalar;}
	};


	template <turbolin::VectorType T, turbolin::VectorType T2, std::size_t D>
	T dot(const turbolin::Vector<T, D> &lhs, const turbolin::Vector<T2, D> &rhs);

	template <turbolin::VectorType T, turbolin::VectorType T2>
	turbolin::Vector<T, 3> cross(const turbolin::Vector<T, 3> &lhs, const turbolin::Vector<T2, 3> &rhs);

	template <turbolin::VectorType T, turbolin::VectorType T2, std::size_t D>
	inline turbolin::Vector<T, D> operator*(T2 scalar, turbolin::Vector<T, D> vector) noexcept {return vector *= scalar;}

	template <turbolin::VectorType T, std::size_t D>
	std::ostream &operator<<(std::ostream &stream, const turbolin::Vector<T, D> &vector);

} // namespace turbolin


#ifdef __cpp_lib_format
	template <turbolin::VectorType T, std::size_t D>
	struct std::formatter<turbolin::Vector<T, D>> {
		constexpr auto parse(std::format_parse_context &ctx) {
			if (*ctx.begin() != '}')
				throw std::format_error("turbolin::Vector does not accept any format args");
			return ctx.begin();
		}

		auto format(const turbolin::Vector<T, D> &vector, std::format_context &ctx) const {
			if constexpr (D == 2) {
				return std::format_to(ctx.out(), "({}, {})", vector.x, vector.y);
			}
			else if constexpr (D == 3) {
				return std::format_to(ctx.out(), "({}, {}, {})", vector.x, vector.y, vector.z);
			}
			else {
				return std::format_to(ctx.out(), "({}, {}, {}, {})", vector.x, vector.y, vector.z, vector.w);
			}
		}
	};
#endif


#include "turbolin/vector.inl"
