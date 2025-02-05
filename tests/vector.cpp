#include <TestItNow/TestItNow.hpp>

#include <turbolin/vector.hpp>



TIN_START_TEST(float_vector)
	tl::Vector<float, 4> vec0 {};
	tl::Vector<float, 4> vec1 {1.f, 2.f, 3.f, 4.f};
	tl::Vector<float, 2> vec2_tmp {1.f, 2.f};
	tl::Vector<float, 4> vec2 {vec2_tmp, 3.f, 4.f};

	TIN_NAMED_MANDATORY_CHECK("vec0 init", ((float*)(&vec0))[0] == 0 && ((float*)(&vec0))[1] == 0 && ((float*)(&vec0))[2] == 0 && ((float*)(&vec0))[3] == 0);
	TIN_NAMED_MANDATORY_CHECK("vec1 init", ((float*)(&vec1))[0] == 1.f && ((float*)(&vec1))[1] == 2.f && ((float*)(&vec1))[2] == 3.f && ((float*)(&vec1))[3] == 4.f);
	TIN_NAMED_MANDATORY_CHECK("vec2 init", ((float*)(&vec2))[0] == 1.f && ((float*)(&vec2))[1] == 2.f && ((float*)(&vec2))[2] == 3.f && ((float*)(&vec2))[3] == 4.f);

	TIN_NAMED_MANDATORY_CHECK("vec0 alignment check", (std::size_t)(&vec0) % 16 == 0);
	TIN_NAMED_MANDATORY_CHECK("vec1 alignment check", (std::size_t)(&vec1) % 16 == 0);
	TIN_NAMED_MANDATORY_CHECK("vec2 alignment check", (std::size_t)(&vec2) % 16 == 0);

	TIN_NAMED_MANDATORY_CHECK("vec0 self equality", vec0 == vec0);
	TIN_NAMED_MANDATORY_CHECK("vec1 self equality", vec1 == vec1);

	TIN_NAMED_MANDATORY_CHECK("vec1/vec2 equality",   vec1 == vec2);
	TIN_NAMED_MANDATORY_CHECK("vec0/vec1 inequality", vec0 != vec1);

	TIN_NAMED_CHECK("vec1 += vec2", (vec1 += vec2) == tl::Vector<float, 4> {2.f, 4.f, 6.f, 8.f});
	TIN_NAMED_CHECK("vec1 -= vec2", (vec1 -= vec2) == tl::Vector<float, 4> {1.f, 2.f, 3.f, 4.f});
	TIN_NAMED_CHECK("vec1 *= vec2", (vec1 *= vec2) == tl::Vector<float, 4> {1.f, 4.f, 9.f, 16.f});

	vec1 = {1.f, 2.f, 3.f, 4.f};

	TIN_NAMED_CHECK("vec1 + vec2", (vec1 + vec2) == tl::Vector<float, 4> {2.f, 4.f, 6.f, 8.f});
	TIN_NAMED_CHECK("vec1 - vec2", (vec1 - vec2) == tl::Vector<float, 4> {0.f, 0.f, 0.f, 0.f});
	TIN_NAMED_CHECK("vec1 * vec2", (vec1 * vec2) == tl::Vector<float, 4> {1.f, 4.f, 9.f, 16.f});

	TIN_NAMED_CHECK("dot product vec1/vec2", tl::dot(vec1, vec2) == 30.f);
	TIN_NAMED_CHECK("dot product vec0/vec1", tl::dot(vec0, vec1) == 0.f);
	TIN_NAMED_CHECK("dot product vec0/vec2", tl::dot(vec0, vec2) == 0.f);


	tl::Vector<float, 3> vec3 {1.f, 2.f, 3.f};
	tl::Vector<float, 3> vec4 {2.f, 3.f, 4.f};
	tl::Vector<float, 3> vec5 {-1.5f, -0.5f, 7.f};

	TIN_NAMED_CHECK("cross product vec3/vec3", tl::cross(vec3, vec3) == tl::Vector<float, 3> {0.f, 0.f, 0.f});
	TIN_NAMED_CHECK("cross product vec3/vec4", tl::cross(vec3, vec4) == tl::Vector<float, 3> {-1.f, 2.f, -1.f});
	TIN_NAMED_CHECK("cross product vec4/vec3", tl::cross(vec4, vec3) == tl::Vector<float, 3> {1.f, -2.f, 1.f});
	TIN_NAMED_CHECK("cross product vec3/vec5", tl::cross(vec3, vec5) == tl::Vector<float, 3> {15.5f, -11.5f, 2.5f});
	TIN_NAMED_CHECK("cross product vec5/vec3", tl::cross(vec5, vec3) == tl::Vector<float, 3> {-15.5f, 11.5f, -2.5f});
TIN_END_TEST(float_vector, "Test of Turbolin's float vector implementation")

TIN_START_TEST(int_vector)
	tl::Vector<int, 4> vec0 {};
	tl::Vector<int, 4> vec1 {1, 2, 3, 4};
	tl::Vector<int, 2> vec2_tmp {1, 2};
	tl::Vector<int, 4> vec2 {vec2_tmp, 3, 4};

	TIN_NAMED_MANDATORY_CHECK("vec0 init", ((int*)(&vec0))[0] == 0 && ((int*)(&vec0))[1] == 0 && ((int*)(&vec0))[2] == 0 && ((int*)(&vec0))[3] == 0);
	TIN_NAMED_MANDATORY_CHECK("vec1 init", ((int*)(&vec1))[0] == 1 && ((int*)(&vec1))[1] == 2 && ((int*)(&vec1))[2] == 3 && ((int*)(&vec1))[3] == 4);
	TIN_NAMED_MANDATORY_CHECK("vec2 init", ((int*)(&vec2))[0] == 1 && ((int*)(&vec2))[1] == 2 && ((int*)(&vec2))[2] == 3 && ((int*)(&vec2))[3] == 4);

	TIN_NAMED_MANDATORY_CHECK("vec0 alignment check", (std::size_t)(&vec0) % 16 == 0)
	TIN_NAMED_MANDATORY_CHECK("vec1 alignment check", (std::size_t)(&vec1) % 16 == 0);
	TIN_NAMED_MANDATORY_CHECK("vec2 alignment check", (std::size_t)(&vec2) % 16 == 0);

	TIN_NAMED_MANDATORY_CHECK("vec0 self equality", vec0 == vec0);
	TIN_NAMED_MANDATORY_CHECK("vec1 self equality", vec1 == vec1);

	TIN_NAMED_MANDATORY_CHECK("vec1/vec2 equality",   vec1 == vec2);
	std::println("{} != {}", vec0, vec1);
	TIN_NAMED_MANDATORY_CHECK("vec0/vec1 inequality", vec0 != vec1);

	TIN_NAMED_CHECK("vec1 += vec2", (vec1 += vec2) == tl::Vector<int, 4> {2, 4, 6, 8});
	TIN_NAMED_CHECK("vec1 -= vec2", (vec1 -= vec2) == tl::Vector<int, 4> {1, 2, 3, 4});
	TIN_NAMED_CHECK("vec1 *= vec2", (vec1 *= vec2) == tl::Vector<int, 4> {1, 4, 9, 16});

	vec1 = {1, 2, 3, 4};

	TIN_NAMED_CHECK("vec1 + vec2", (vec1 + vec2) == tl::Vector<int, 4> {2, 4, 6, 8});
	TIN_NAMED_CHECK("vec1 - vec2", (vec1 - vec2) == tl::Vector<int, 4> {0, 0, 0, 0});
	TIN_NAMED_CHECK("vec1 * vec2", (vec1 * vec2) == tl::Vector<int, 4> {1, 4, 9, 16});

	TIN_NAMED_CHECK("dot product vec1/vec2", tl::dot(vec1, vec2) == 30);
	TIN_NAMED_CHECK("dot product vec0/vec1", tl::dot(vec0, vec1) == 0);
	TIN_NAMED_CHECK("dot product vec0/vec2", tl::dot(vec0, vec2) == 0);


	tl::Vector<int, 3> vec3 {1, 2, 3};
	tl::Vector<int, 3> vec4 {2, 3, 4};
	tl::Vector<int, 3> vec5 {-1, 0, 7};

	TIN_NAMED_CHECK("cross product vec3/vec3", tl::cross(vec3, vec3) == tl::Vector<int, 3> {0, 0, 0});
	TIN_NAMED_CHECK("cross product vec3/vec4", tl::cross(vec3, vec4) == tl::Vector<int, 3> {-1, 2, -1});
	TIN_NAMED_CHECK("cross product vec4/vec3", tl::cross(vec4, vec3) == tl::Vector<int, 3> {1, -2, 1});
	TIN_NAMED_CHECK("cross product vec3/vec5", tl::cross(vec3, vec5) == tl::Vector<int, 3> {14, -10, 2});
	TIN_NAMED_CHECK("cross product vec5/vec3", tl::cross(vec5, vec3) == tl::Vector<int, 3> {-14, 10, -2});
TIN_END_TEST(int_vector, "Test of Turbolin's int vector implementation")

