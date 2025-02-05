#include <turbolin/vector.hpp>

#include <iostream>


auto main(int, char**) -> int {
	tl::Vector<float, 3> vec {};
	std::cout << vec << std::endl;

	tl::Vector<std::uint64_t, 2> vec2 {};
	std::cout << vec2 << std::endl;

	return 0;
}
