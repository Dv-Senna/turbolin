#include <TestItNow/TestItNow.hpp>

#include <turbolin/vector.hpp>



TIN_START_TEST(vector)
	turbolin::Vector<float, 4> vec4 {};
	
	TIN_NAMED_MANDATORY_CHECK("Equality", true);
TIN_END_TEST(vector, "Test of Turbolin's vector implementation")

