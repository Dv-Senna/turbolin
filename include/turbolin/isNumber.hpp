#pragma once

#include <type_traits>



namespace turbolin {
	template <typename T>
	concept IsNumber = std::is_arithmetic_v<T>;
};
