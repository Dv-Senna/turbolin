#include <turbolin/vector.hpp>

#include <iostream>


auto main(int, char**) -> int {
	tl::Vector<float, 3> vec {};
	std::cout << vec << std::endl;

	vec += tl::Vector{1.f, 2.f, 3.f};
	std::cout << vec << std::endl;

	std::cout << tl::Vector<float, 3> (tl::Vector<float, 2> (1.f, 2.f), 3.f) << std::endl;

	return 0;
}
