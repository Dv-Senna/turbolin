#include <TestItNow/TestItNow.hpp>

#include <iostream>

#include <turbolin/vector.hpp>



TIN_START_TEST(vector)
{
	turbolin::Vector<float, 4> vec0 {};
	turbolin::Vector<float, 4> vec1 {1.f, 2.f, 3.f, 4.f};
	turbolin::Vector<float, 2> vec2_tmp {1.f, 2.f};
	turbolin::Vector<float, 4> vec2 {vec2_tmp, 3.f, 4.f};

	TIN_NAMED_MANDATORY_CHECK("FLOAT - vec0 init", ((float*)(&vec0))[0] == 0 && ((float*)(&vec0))[1] == 0 && ((float*)(&vec0))[2] == 0 && ((float*)(&vec0))[3] == 0);
	TIN_NAMED_MANDATORY_CHECK("FLOAT - vec1 init", ((float*)(&vec1))[0] == 1.f && ((float*)(&vec1))[1] == 2.f && ((float*)(&vec1))[2] == 3.f && ((float*)(&vec1))[3] == 4.f);
	TIN_NAMED_MANDATORY_CHECK("FLOAT - vec2 init", ((float*)(&vec2))[0] == 1.f && ((float*)(&vec2))[1] == 2.f && ((float*)(&vec2))[2] == 3.f && ((float*)(&vec2))[3] == 4.f);

	TIN_NAMED_MANDATORY_CHECK("FLOAT - vec0 self equality", vec0 == vec0);
	TIN_NAMED_MANDATORY_CHECK("FLOAT - vec1 self equality", vec1 == vec1);

	TIN_NAMED_MANDATORY_CHECK("FLOAT - vec1/vec2 equality",   vec1 == vec2);
	TIN_NAMED_MANDATORY_CHECK("FLOAT - vec0/vec1 inequality", vec0 != vec1);

	TIN_NAMED_CHECK("FLOAT - vec1 += vec2", (vec1 += vec2) == turbolin::Vector<float, 4> {2.f, 4.f, 6.f, 8.f});
	TIN_NAMED_CHECK("FLOAT - vec1 -= vec2", (vec1 -= vec2) == turbolin::Vector<float, 4> {1.f, 2.f, 3.f, 4.f});
	TIN_NAMED_CHECK("FLOAT - vec1 *= vec2", (vec1 *= vec2) == turbolin::Vector<float, 4> {1.f, 4.f, 9.f, 16.f});

	vec1 = {1.f, 2.f, 3.f, 4.f};

	TIN_NAMED_CHECK("FLOAT - vec1 + vec2", (vec1 + vec2) == turbolin::Vector<float, 4> {2.f, 4.f, 6.f, 8.f});
	TIN_NAMED_CHECK("FLOAT - vec1 - vec2", (vec1 - vec2) == turbolin::Vector<float, 4> {0.f, 0.f, 0.f, 0.f});
	TIN_NAMED_CHECK("FLOAT - vec1 * vec2", (vec1 * vec2) == turbolin::Vector<float, 4> {1.f, 4.f, 9.f, 16.f});

	TIN_NAMED_CHECK("FLOAT - dot product vec1/vec2", turbolin::dot(vec1, vec2) == 30.f);
}

{
	turbolin::Vector<int, 4> vec0 {};
	turbolin::Vector<int, 4> vec1 {1, 2, 3, 4};
	turbolin::Vector<int, 2> vec2_tmp {1, 2};
	turbolin::Vector<int, 4> vec2 {vec2_tmp, 3, 4};

	TIN_NAMED_MANDATORY_CHECK("INT - vec0 init", ((int*)(&vec0))[0] == 0 && ((int*)(&vec0))[1] == 0 && ((int*)(&vec0))[2] == 0 && ((int*)(&vec0))[3] == 0);
	TIN_NAMED_MANDATORY_CHECK("INT - vec1 init", ((int*)(&vec1))[0] == 1 && ((int*)(&vec1))[1] == 2 && ((int*)(&vec1))[2] == 3 && ((int*)(&vec1))[3] == 4);
	TIN_NAMED_MANDATORY_CHECK("INT - vec2 init", ((int*)(&vec2))[0] == 1 && ((int*)(&vec2))[1] == 2 && ((int*)(&vec2))[2] == 3 && ((int*)(&vec2))[3] == 4);

	TIN_NAMED_MANDATORY_CHECK("INT - vec0 self equality", vec0 == vec0);
	TIN_NAMED_MANDATORY_CHECK("INT - vec1 self equality", vec1 == vec1);

	TIN_NAMED_MANDATORY_CHECK("INT - vec1/vec2 equality",   vec1 == vec2);
	TIN_NAMED_MANDATORY_CHECK("INT - vec0/vec1 inequality", vec0 != vec1);

	TIN_NAMED_CHECK("INT - vec1 += vec2", (vec1 += vec2) == turbolin::Vector<int, 4> {2, 4, 6, 8});
	TIN_NAMED_CHECK("INT - vec1 -= vec2", (vec1 -= vec2) == turbolin::Vector<int, 4> {1, 2, 3, 4});
	TIN_NAMED_CHECK("INT - vec1 *= vec2", (vec1 *= vec2) == turbolin::Vector<int, 4> {1, 4, 9, 16});

	vec1 = {1, 2, 3, 4};

	TIN_NAMED_CHECK("INT - vec1 + vec2", (vec1 + vec2) == turbolin::Vector<int, 4> {2, 4, 6, 8});
	TIN_NAMED_CHECK("INT - vec1 - vec2", (vec1 - vec2) == turbolin::Vector<int, 4> {0, 0, 0, 0});
	TIN_NAMED_CHECK("INT - vec1 * vec2", (vec1 * vec2) == turbolin::Vector<int, 4> {1, 4, 9, 16});

	vec1 = {1, 2, 3, 4};
	vec2 = {1, 2, 3, 4};

	TIN_NAMED_CHECK("INT - dot product vec1/vec2", turbolin::dot(vec1, vec2) == 30);
}
TIN_END_TEST(vector, "Test of Turbolin's vector implementation")

