#include <turbolin/vector.hpp>

#include <print>


auto main(int, char**) -> int {
	tl::Vector<float, 3> vec {};
	std::println("{}", vec);

	vec += tl::Vector{1.f, 2.f, 3.f};
	std::println("{}", vec);

	std::println("{}", tl::Vector<float, 3> (tl::Vector<float, 2> (1.f, 2.f), 3.f));

	return 0;
}
