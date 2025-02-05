#pragma once

#include <concepts>
#include <cstdint>
#include <tuple>


namespace tl {
	template <typename T>
	concept Arithmetic = std::is_arithmetic_v<T>;

	template <Arithmetic First, Arithmetic ...Args>
	constexpr auto max(First first, Args ...args) noexcept -> First {
		if constexpr (sizeof...(Args) == 0)
			return first;
		else if constexpr (sizeof...(Args) == 1)
			return first >= static_cast<First> (std::get<0> (std::make_tuple(args...))) ? first : static_cast<First> (std::get<0> (std::make_tuple(args...)));
		else {
			auto other {tl::max(args...)};
			return first >= static_cast<First> (other) ? first : static_cast<First> (other);
		}
	}
	

	enum class SimdExtension {
		eNone,
		eSSE2,
		eAVX,
		eAll
	};

	template <typename T>
	concept IsSimd = std::same_as<T, float> || std::same_as<T, std::uint32_t>;

	template <typename T>
	concept IsSSE2 = std::same_as<T, float> || std::same_as<T, std::uint32_t>;

	template <typename T>
	concept IsAVX = std::same_as<T, float> || std::same_as<T, std::uint32_t>;



	template <SimdExtension EXT, Arithmetic T>
	struct SimdAlignment {
		static constexpr std::size_t value {alignof(T)};
	};

	template <SimdExtension EXT, Arithmetic T>
	struct SimdSize {
		static constexpr std::size_t value {0};
	};


	template <IsSSE2 T>
	struct SimdAlignment<SimdExtension::eSSE2, T> {
		static constexpr std::size_t value {16};
	};

	template <IsSSE2 T>
	struct SimdSize<SimdExtension::eSSE2, T> {
		static constexpr std::size_t value {4 * sizeof(T)};
	};


	template <IsAVX T>
	struct SimdAlignment<SimdExtension::eAVX, T> {
		static constexpr std::size_t value {32};
	};

	template <IsAVX T>
	struct SimdSize<SimdExtension::eAVX, T> {
		static constexpr std::size_t value {8 * sizeof(T)};
	};


	template <Arithmetic T>
	struct SimdStrictestAlignment {
		static constexpr std::size_t value {tl::max(
			SimdAlignment<SimdExtension::eSSE2, T>::value,
			SimdAlignment<SimdExtension::eAVX, T>::value
		)};
	};

	template <Arithmetic T>
	struct SimdStrictestSize {
		static constexpr std::size_t value {tl::max(
			SimdSize<SimdExtension::eSSE2, T>::value,
			SimdSize<SimdExtension::eAVX, T>::value
		)};
	};

} // namespace tl
