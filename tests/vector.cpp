#include <TestItNow/TestItNow.hpp>

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
}

TIN_END_TEST(vector, "Test of Turbolin's vector implementation")

