#pragma once

#include <array>
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
		eNone = 0,
		eSSE42 = 1,
		eAVX  = 2,
		eAll  = 3
	};

	template <typename T>
	concept IsSimd = std::same_as<T, float> || std::same_as<T, std::int32_t>;

	template <typename T>
	concept IsSSE42 = std::same_as<T, float> || std::same_as<T, std::int32_t>;

	template <typename T>
	concept IsAVX = std::same_as<T, float> || std::same_as<T, std::int32_t>;


	inline auto isSimdExtensionSupported(SimdExtension extension) noexcept -> bool {
		static bool supported[static_cast<std::size_t> (SimdExtension::eAll)] {};
		static bool firstTime {true};
		if (!firstTime)
			return supported[static_cast<std::size_t> (extension)];

		firstTime = false;
		supported[static_cast<std::size_t> (SimdExtension::eNone)] = true;
		supported[static_cast<std::size_t> (SimdExtension::eSSE42)] = !!__builtin_cpu_supports("sse4.2");
		supported[static_cast<std::size_t> (SimdExtension::eAVX)] = !!__builtin_cpu_supports("avx");
		return isSimdExtensionSupported(extension);
	}


	template <typename Func, Func ...funcs, typename ...Args>
	requires (sizeof...(funcs) <= static_cast<std::size_t> (SimdExtension::eAll))
	auto simdRuntimeDispatcher(Args &&...args) noexcept {
		if consteval {
			std::array<Func, sizeof...(funcs)> functions {funcs...};
			return functions[0](args...);
		}
		else {
			static Func impl {nullptr};
			if (impl != nullptr)
				return impl(args...);

			std::array<Func, sizeof...(funcs)> functions {funcs...};
			for (std::size_t i {functions.size()}; i-- != 0;) {
				if (functions[i] == nullptr || !isSimdExtensionSupported(static_cast<SimdExtension> (i)))
					continue;
				impl = functions[i];
				break;
			}
			return impl(args...);
		}
	}


	template <SimdExtension EXT, Arithmetic T>
	struct SimdAlignment {
		static constexpr std::size_t value {alignof(T)};
	};

	template <SimdExtension EXT, Arithmetic T>
	struct SimdSize {
		static constexpr std::size_t value {0};
	};


	template <IsSSE42 T>
	struct SimdAlignment<SimdExtension::eSSE42, T> {
		static constexpr std::size_t value {16};
	};

	template <IsSSE42 T>
	struct SimdSize<SimdExtension::eSSE42, T> {
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
			SimdAlignment<SimdExtension::eSSE42, T>::value,
			SimdAlignment<SimdExtension::eAVX, T>::value
		)};
	};

	template <Arithmetic T>
	struct SimdStrictestSize {
		static constexpr std::size_t value {tl::max(
			SimdSize<SimdExtension::eSSE42, T>::value,
			SimdSize<SimdExtension::eAVX, T>::value
		)};
	};

} // namespace tl
