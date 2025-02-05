#pragma once

#include <concepts>
#include <cstdint>


namespace tl {
	template <typename T>
	concept Arithmetic = std::is_arithmetic_v<T>;

	template <typename T>
	concept IsSimd = std::same_as<T, float> || std::same_as<T, std::uint32_t>;


	template <typename T>
	struct SimdStrictestAlignment {
		static constexpr std::size_t value {16};
	};

} // namespace tl
