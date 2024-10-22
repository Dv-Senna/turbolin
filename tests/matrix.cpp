#include <TestItNow/TestItNow.hpp>

#include <iostream>

#include <turbolin/matrix.hpp>



TIN_START_TEST(float_matrix)
	{
		turbolin::Matrix<float, 2> mat2_0 {};
		turbolin::Matrix<float, 2> mat2_1 {1, 2, 3, 4};
		turbolin::Matrix<float, 2> mat2_2 {1, 2};
		turbolin::Matrix<float, 2> mat2_3 {1.f};

		TIN_NAMED_MANDATORY_CHECK("2D-zero initialisation",
			((float*)&mat2_0)[0] == 0 && ((float*)&mat2_0)[1] == 0 && ((float*)&mat2_0)[2] == 0 && ((float*)&mat2_0)[3] == 0
			&& ((float*)&mat2_0)[4] == 0 && ((float*)&mat2_0)[5] == 0 && ((float*)&mat2_0)[6] == 0 && ((float*)&mat2_0)[7] == 0
		);
		TIN_NAMED_MANDATORY_CHECK("2D-complete initialisation",
			((float*)&mat2_1)[0] == 1 && ((float*)&mat2_1)[1] == 2 && ((float*)&mat2_1)[2] == 0 && ((float*)&mat2_1)[3] == 0
			&& ((float*)&mat2_1)[4] == 3 && ((float*)&mat2_1)[5] == 4 && ((float*)&mat2_1)[6] == 0 && ((float*)&mat2_1)[7] == 0
		);
		TIN_NAMED_MANDATORY_CHECK("2D-partial initialisation",
			((float*)&mat2_2)[0] == 1 && ((float*)&mat2_2)[1] == 2 && ((float*)&mat2_2)[2] == 0 && ((float*)&mat2_2)[3] == 0 &&
			((float*)&mat2_2)[4] == 0 && ((float*)&mat2_2)[5] == 0 && ((float*)&mat2_2)[6] == 0 && ((float*)&mat2_2)[7] == 0
		);
		TIN_NAMED_MANDATORY_CHECK("2D-diagonal initialisation",
			((float*)&mat2_3)[0] == 1 && ((float*)&mat2_3)[1] == 0 && ((float*)&mat2_3)[2] == 0 && ((float*)&mat2_3)[3] == 0 &&
			((float*)&mat2_3)[4] == 0 && ((float*)&mat2_3)[5] == 1 && ((float*)&mat2_3)[6] == 0 && ((float*)&mat2_3)[7] == 0
		);


		turbolin::Matrix<float, 3> mat3_0 {};
		turbolin::Matrix<float, 3> mat3_1 {1, 2, 3, 4, 5, 6, 7, 8, 9};
		turbolin::Matrix<float, 3> mat3_2 {1, 2, 3};
		turbolin::Matrix<float, 3> mat3_3 {1};

		TIN_NAMED_MANDATORY_CHECK("3D-zero initialisation",
			((float*)&mat3_0)[0] == 0 && ((float*)&mat3_0)[1] == 0 && ((float*)&mat3_0)[2] == 0 && ((float*)&mat3_0)[3] == 0
			&& ((float*)&mat3_0)[4] == 0 && ((float*)&mat3_0)[5] == 0 && ((float*)&mat3_0)[6] == 0 && ((float*)&mat3_0)[7] == 0
			&& ((float*)&mat3_0)[8] == 0 && ((float*)&mat3_0)[9] == 0 && ((float*)&mat3_0)[10] == 0 && ((float*)&mat3_0)[11] == 0
			&& ((float*)&mat3_0)[12] == 0 && ((float*)&mat3_0)[13] == 0 && ((float*)&mat3_0)[14] == 0 && ((float*)&mat3_0)[15] == 0
		);
		TIN_NAMED_MANDATORY_CHECK("3D-complete initialisation",
			((float*)&mat3_1)[0] == 1 && ((float*)&mat3_1)[1] == 2 && ((float*)&mat3_1)[2] == 3 && ((float*)&mat3_1)[3] == 0
			&& ((float*)&mat3_1)[4] == 4 && ((float*)&mat3_1)[5] == 5 && ((float*)&mat3_1)[6] == 6 && ((float*)&mat3_1)[7] == 0
			&& ((float*)&mat3_1)[8] == 7 && ((float*)&mat3_1)[9] == 8 && ((float*)&mat3_1)[10] == 9 && ((float*)&mat3_1)[11] == 0
			&& ((float*)&mat3_1)[12] == 0 && ((float*)&mat3_1)[13] == 0 && ((float*)&mat3_1)[14] == 0 && ((float*)&mat3_1)[15] == 0
		);
		TIN_NAMED_MANDATORY_CHECK("3D-partial initialisation",
			((float*)&mat3_2)[0] == 1 && ((float*)&mat3_2)[1] == 2 && ((float*)&mat3_2)[2] == 3 && ((float*)&mat3_2)[3] == 0
			&& ((float*)&mat3_2)[4] == 0 && ((float*)&mat3_2)[5] == 0 && ((float*)&mat3_2)[6] == 0 && ((float*)&mat3_2)[7] == 0
			&& ((float*)&mat3_2)[8] == 0 && ((float*)&mat3_2)[9] == 0 && ((float*)&mat3_2)[10] == 0 && ((float*)&mat3_2)[11] == 0
			&& ((float*)&mat3_2)[12] == 0 && ((float*)&mat3_2)[13] == 0 && ((float*)&mat3_2)[14] == 0 && ((float*)&mat3_2)[15] == 0
		);
		TIN_NAMED_MANDATORY_CHECK("3D-diagonal initialisation",
			((float*)&mat3_3)[0] == 1 && ((float*)&mat3_3)[1] == 0 && ((float*)&mat3_3)[2] == 0 && ((float*)&mat3_3)[3] == 0
			&& ((float*)&mat3_3)[4] == 0 && ((float*)&mat3_3)[5] == 1 && ((float*)&mat3_3)[6] == 0 && ((float*)&mat3_3)[7] == 0
			&& ((float*)&mat3_3)[8] == 0 && ((float*)&mat3_3)[9] == 0 && ((float*)&mat3_3)[10] == 1 && ((float*)&mat3_3)[11] == 0
			&& ((float*)&mat3_3)[12] == 0 && ((float*)&mat3_3)[13] == 0 && ((float*)&mat3_3)[14] == 0 && ((float*)&mat3_3)[15] == 0
		);


		turbolin::Matrix<float, 4> mat4_0 {};
		turbolin::Matrix<float, 4> mat4_1 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
		turbolin::Matrix<float, 4> mat4_2 {1, 2, 3, 4};
		turbolin::Matrix<float, 4> mat4_3 {1};

		TIN_NAMED_MANDATORY_CHECK("4D-zero initialisation",
			((float*)&mat4_0)[0] == 0 && ((float*)&mat4_0)[1] == 0 && ((float*)&mat4_0)[2] == 0 && ((float*)&mat4_0)[3] == 0
			&& ((float*)&mat4_0)[4] == 0 && ((float*)&mat4_0)[5] == 0 && ((float*)&mat4_0)[6] == 0 && ((float*)&mat4_0)[7] == 0
			&& ((float*)&mat4_0)[8] == 0 && ((float*)&mat4_0)[9] == 0 && ((float*)&mat4_0)[10] == 0 && ((float*)&mat4_0)[11] == 0
			&& ((float*)&mat4_0)[12] == 0 && ((float*)&mat4_0)[13] == 0 && ((float*)&mat4_0)[14] == 0 && ((float*)&mat4_0)[15] == 0
		);
		TIN_NAMED_MANDATORY_CHECK("4D-complete initialisation",
			((float*)&mat4_1)[0] == 1 && ((float*)&mat4_1)[1] == 2 && ((float*)&mat4_1)[2] == 3 && ((float*)&mat4_1)[3] == 4
			&& ((float*)&mat4_1)[4] == 5 && ((float*)&mat4_1)[5] == 6 && ((float*)&mat4_1)[6] == 7 && ((float*)&mat4_1)[7] == 8
			&& ((float*)&mat4_1)[8] == 9 && ((float*)&mat4_1)[9] == 10 && ((float*)&mat4_1)[10] == 11 && ((float*)&mat4_1)[11] == 12
			&& ((float*)&mat4_1)[12] == 13 && ((float*)&mat4_1)[13] == 14 && ((float*)&mat4_1)[14] == 15 && ((float*)&mat4_1)[15] == 16
		);
		TIN_NAMED_MANDATORY_CHECK("4D-partial initialisation",
			((float*)&mat4_2)[0] == 1 && ((float*)&mat4_2)[1] == 2 && ((float*)&mat4_2)[2] == 3 && ((float*)&mat4_2)[3] == 4
			&& ((float*)&mat4_2)[4] == 0 && ((float*)&mat4_2)[5] == 0 && ((float*)&mat4_2)[6] == 0 && ((float*)&mat4_2)[7] == 0
			&& ((float*)&mat4_2)[8] == 0 && ((float*)&mat4_2)[9] == 0 && ((float*)&mat4_2)[10] == 0 && ((float*)&mat4_2)[11] == 0
			&& ((float*)&mat4_2)[12] == 0 && ((float*)&mat4_2)[13] == 0 && ((float*)&mat4_2)[14] == 0 && ((float*)&mat4_2)[15] == 0
		);
		TIN_NAMED_MANDATORY_CHECK("4D-diagonal initialisation",
			((float*)&mat4_3)[0] == 1 && ((float*)&mat4_3)[1] == 0 && ((float*)&mat4_3)[2] == 0 && ((float*)&mat4_3)[3] == 0
			&& ((float*)&mat4_3)[4] == 0 && ((float*)&mat4_3)[5] == 1 && ((float*)&mat4_3)[6] == 0 && ((float*)&mat4_3)[7] == 0
			&& ((float*)&mat4_3)[8] == 0 && ((float*)&mat4_3)[9] == 0 && ((float*)&mat4_3)[10] == 1 && ((float*)&mat4_3)[11] == 0
			&& ((float*)&mat4_3)[12] == 0 && ((float*)&mat4_3)[13] == 0 && ((float*)&mat4_3)[14] == 0 && ((float*)&mat4_3)[15] == 1
		);
	}


	turbolin::Matrix<float, 2> mat2_0 {};
	turbolin::Matrix<float, 3> mat3_0 {};
	turbolin::Matrix<float, 4> mat4_0 {};

	turbolin::Matrix<float, 2> mat2_1 {1.f, 2.f, 3.f, 4.f};
	turbolin::Matrix<float, 3> mat3_1 {1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f};
	turbolin::Matrix<float, 4> mat4_1 {1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f};

	TIN_NAMED_MANDATORY_CHECK("mat2_0 - mat2_0 : equality check",   mat2_0 == mat2_0);
	TIN_NAMED_MANDATORY_CHECK("mat2_1 - mat2_1 : equality check",   mat2_1 == mat2_1);
	TIN_NAMED_MANDATORY_CHECK("mat2_1 - mat2_0 : inequality check", mat2_1 != mat2_0);
	TIN_NAMED_MANDATORY_CHECK("mat2_0 - mat2_1 : inequality check", mat2_0 != mat2_1);

	TIN_NAMED_MANDATORY_CHECK("mat3_0 - mat3_0 : equality check",   mat3_0 == mat3_0);
	TIN_NAMED_MANDATORY_CHECK("mat3_1 - mat3_1 : equality check",   mat3_1 == mat3_1);
	TIN_NAMED_MANDATORY_CHECK("mat3_1 - mat3_0 : inequality check", mat3_1 != mat3_0);
	TIN_NAMED_MANDATORY_CHECK("mat3_0 - mat3_1 : inequality check", mat3_0 != mat3_1);

	TIN_NAMED_MANDATORY_CHECK("mat4_0 - mat4_0 : equality check",   mat4_0 == mat4_0);
	TIN_NAMED_MANDATORY_CHECK("mat4_1 - mat4_1 : equality check",   mat4_1 == mat4_1);
	TIN_NAMED_MANDATORY_CHECK("mat4_1 - mat4_0 : inequality check", mat4_1 != mat4_0);
	TIN_NAMED_MANDATORY_CHECK("mat4_0 - mat4_1 : inequality check", mat4_0 != mat4_1);

	turbolin::Matrix<float, 2> mat2_2 {1.f, 2.f};
	turbolin::Matrix<float, 4> mat4_2 {1.f, 2.f, 3.f, 4.f};

	TIN_NAMED_CHECK("mat2_1 += mat2_2", (mat2_1 += mat2_2) == turbolin::Matrix<float, 2> (2.f, 4.f, 3.f, 4.f));
	TIN_NAMED_CHECK("mat2_1 -= mat2_2", (mat2_1 -= mat2_2) == turbolin::Matrix<float, 2> (1.f, 2.f, 3.f, 4.f));
//	TIN_NAMED_CHECK("mat2_1 *= mat2_2", (mat2_1 *= mat2_2) == turbolin::Matrix<float, 2> (2.f, 4.f, 3.f, 4.f));

	TIN_NAMED_CHECK("mat4_1 += mat4_2", (mat4_1 += mat4_2) == turbolin::Matrix<float, 4> (2.f, 4.f, 6.f, 8.f, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16));
	TIN_NAMED_CHECK("mat4_1 -= mat4_2", (mat4_1 -= mat4_2) == turbolin::Matrix<float, 4> (1.f, 2.f, 3.f, 4.f, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16));
//	TIN_NAMED_CHECK("mat4_1 *= mat4_2", (mat4_1 *= mat4_2) == turbolin::Matrix<float, 4> (2.f, 4.f, 3.f, 4.f));

	mat2_1 = turbolin::Matrix<float, 2> (1.f, 2.f, 3.f, 4.f);
	mat4_1 = turbolin::Matrix<float, 4> (1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);

	TIN_NAMED_CHECK("mat2_1 + mat2_2", mat2_1 + mat2_2 == turbolin::Matrix<float, 2> (2.f, 4.f, 3.f, 4.f));
	TIN_NAMED_CHECK("mat2_1 - mat2_2", mat2_1 - mat2_2 == turbolin::Matrix<float, 2> (0.f, 0.f, 3.f, 4.f));
//	TIN_NAMED_CHECK("mat2_1 + mat2_2", mat2_1 + mat2_2 == turbolin::Matrix<float, 2> ());

	TIN_NAMED_CHECK("mat4_1 + mat4_2", mat4_1 + mat4_2 == turbolin::Matrix<float, 4> (2.f, 4.f, 6.f, 8.f, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16));
	TIN_NAMED_CHECK("mat4_1 - mat4_2", mat4_1 - mat4_2 == turbolin::Matrix<float, 4> (0.f, 0.f, 0.f, 0.f, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16));
//	TIN_NAMED_CHECK("mat4_1 + mat4_2", mat4_1 + mat4_2 == turbolin::Matrix<float, 4> ());

TIN_END_TEST(float_matrix, "Test of Turbolin's float matrix implementation")



TIN_START_TEST(int_matrix)
	{
		turbolin::Matrix<int, 2> mat2_0 {};
		turbolin::Matrix<int, 2> mat2_1 {1, 2, 3, 4};
		turbolin::Matrix<int, 2> mat2_2 {1, 2};
		turbolin::Matrix<int, 2> mat2_3 {1};

		TIN_NAMED_MANDATORY_CHECK("2D-zero initialisation",
			((int*)&mat2_0)[0] == 0 && ((int*)&mat2_0)[1] == 0 && ((int*)&mat2_0)[2] == 0 && ((int*)&mat2_0)[3] == 0
			&& ((int*)&mat2_0)[4] == 0 && ((int*)&mat2_0)[5] == 0 && ((int*)&mat2_0)[6] == 0 && ((int*)&mat2_0)[7] == 0
		);
		TIN_NAMED_MANDATORY_CHECK("2D-complete initialisation",
			((int*)&mat2_1)[0] == 1 && ((int*)&mat2_1)[1] == 2 && ((int*)&mat2_1)[2] == 0 && ((int*)&mat2_1)[3] == 0
			&& ((int*)&mat2_1)[4] == 3 && ((int*)&mat2_1)[5] == 4 && ((int*)&mat2_1)[6] == 0 && ((int*)&mat2_1)[7] == 0
		);
		TIN_NAMED_MANDATORY_CHECK("2D-partial initialisation",
			((int*)&mat2_2)[0] == 1 && ((int*)&mat2_2)[1] == 2 && ((int*)&mat2_2)[2] == 0 && ((int*)&mat2_2)[3] == 0 &&
			((int*)&mat2_2)[4] == 0 && ((int*)&mat2_2)[5] == 0 && ((int*)&mat2_2)[6] == 0 && ((int*)&mat2_2)[7] == 0
		);
		TIN_NAMED_MANDATORY_CHECK("2D-diagonal initialisation",
			((int*)&mat2_3)[0] == 1 && ((int*)&mat2_3)[1] == 0 && ((int*)&mat2_3)[2] == 0 && ((int*)&mat2_3)[3] == 0 &&
			((int*)&mat2_3)[4] == 0 && ((int*)&mat2_3)[5] == 1 && ((int*)&mat2_3)[6] == 0 && ((int*)&mat2_3)[7] == 0
		);


		turbolin::Matrix<int, 3> mat3_0 {};
		turbolin::Matrix<int, 3> mat3_1 {1, 2, 3, 4, 5, 6, 7, 8, 9};
		turbolin::Matrix<int, 3> mat3_2 {1, 2, 3};
		turbolin::Matrix<int, 3> mat3_3 {1};

		TIN_NAMED_MANDATORY_CHECK("3D-zero initialisation",
			((int*)&mat3_0)[0] == 0 && ((int*)&mat3_0)[1] == 0 && ((int*)&mat3_0)[2] == 0 && ((int*)&mat3_0)[3] == 0
			&& ((int*)&mat3_0)[4] == 0 && ((int*)&mat3_0)[5] == 0 && ((int*)&mat3_0)[6] == 0 && ((int*)&mat3_0)[7] == 0
			&& ((int*)&mat3_0)[8] == 0 && ((int*)&mat3_0)[9] == 0 && ((int*)&mat3_0)[10] == 0 && ((int*)&mat3_0)[11] == 0
			&& ((int*)&mat3_0)[12] == 0 && ((int*)&mat3_0)[13] == 0 && ((int*)&mat3_0)[14] == 0 && ((int*)&mat3_0)[15] == 0
		);
		TIN_NAMED_MANDATORY_CHECK("3D-complete initialisation",
			((int*)&mat3_1)[0] == 1 && ((int*)&mat3_1)[1] == 2 && ((int*)&mat3_1)[2] == 3 && ((int*)&mat3_1)[3] == 0
			&& ((int*)&mat3_1)[4] == 4 && ((int*)&mat3_1)[5] == 5 && ((int*)&mat3_1)[6] == 6 && ((int*)&mat3_1)[7] == 0
			&& ((int*)&mat3_1)[8] == 7 && ((int*)&mat3_1)[9] == 8 && ((int*)&mat3_1)[10] == 9 && ((int*)&mat3_1)[11] == 0
			&& ((int*)&mat3_1)[12] == 0 && ((int*)&mat3_1)[13] == 0 && ((int*)&mat3_1)[14] == 0 && ((int*)&mat3_1)[15] == 0
		);
		TIN_NAMED_MANDATORY_CHECK("3D-partial initialisation",
			((int*)&mat3_2)[0] == 1 && ((int*)&mat3_2)[1] == 2 && ((int*)&mat3_2)[2] == 3 && ((int*)&mat3_2)[3] == 0
			&& ((int*)&mat3_2)[4] == 0 && ((int*)&mat3_2)[5] == 0 && ((int*)&mat3_2)[6] == 0 && ((int*)&mat3_2)[7] == 0
			&& ((int*)&mat3_2)[8] == 0 && ((int*)&mat3_2)[9] == 0 && ((int*)&mat3_2)[10] == 0 && ((int*)&mat3_2)[11] == 0
			&& ((int*)&mat3_2)[12] == 0 && ((int*)&mat3_2)[13] == 0 && ((int*)&mat3_2)[14] == 0 && ((int*)&mat3_2)[15] == 0
		);
		TIN_NAMED_MANDATORY_CHECK("3D-diagonal initialisation",
			((int*)&mat3_3)[0] == 1 && ((int*)&mat3_3)[1] == 0 && ((int*)&mat3_3)[2] == 0 && ((int*)&mat3_3)[3] == 0
			&& ((int*)&mat3_3)[4] == 0 && ((int*)&mat3_3)[5] == 1 && ((int*)&mat3_3)[6] == 0 && ((int*)&mat3_3)[7] == 0
			&& ((int*)&mat3_3)[8] == 0 && ((int*)&mat3_3)[9] == 0 && ((int*)&mat3_3)[10] == 1 && ((int*)&mat3_3)[11] == 0
			&& ((int*)&mat3_3)[12] == 0 && ((int*)&mat3_3)[13] == 0 && ((int*)&mat3_3)[14] == 0 && ((int*)&mat3_3)[15] == 0
		);


		turbolin::Matrix<int, 4> mat4_0 {};
		turbolin::Matrix<int, 4> mat4_1 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
		turbolin::Matrix<int, 4> mat4_2 {1, 2, 3, 4};
		turbolin::Matrix<int, 4> mat4_3 {1};

		TIN_NAMED_MANDATORY_CHECK("4D-zero initialisation",
			((int*)&mat4_0)[0] == 0 && ((int*)&mat4_0)[1] == 0 && ((int*)&mat4_0)[2] == 0 && ((int*)&mat4_0)[3] == 0
			&& ((int*)&mat4_0)[4] == 0 && ((int*)&mat4_0)[5] == 0 && ((int*)&mat4_0)[6] == 0 && ((int*)&mat4_0)[7] == 0
			&& ((int*)&mat4_0)[8] == 0 && ((int*)&mat4_0)[9] == 0 && ((int*)&mat4_0)[10] == 0 && ((int*)&mat4_0)[11] == 0
			&& ((int*)&mat4_0)[12] == 0 && ((int*)&mat4_0)[13] == 0 && ((int*)&mat4_0)[14] == 0 && ((int*)&mat4_0)[15] == 0
		);
		TIN_NAMED_MANDATORY_CHECK("4D-complete initialisation",
			((int*)&mat4_1)[0] == 1 && ((int*)&mat4_1)[1] == 2 && ((int*)&mat4_1)[2] == 3 && ((int*)&mat4_1)[3] == 4
			&& ((int*)&mat4_1)[4] == 5 && ((int*)&mat4_1)[5] == 6 && ((int*)&mat4_1)[6] == 7 && ((int*)&mat4_1)[7] == 8
			&& ((int*)&mat4_1)[8] == 9 && ((int*)&mat4_1)[9] == 10 && ((int*)&mat4_1)[10] == 11 && ((int*)&mat4_1)[11] == 12
			&& ((int*)&mat4_1)[12] == 13 && ((int*)&mat4_1)[13] == 14 && ((int*)&mat4_1)[14] == 15 && ((int*)&mat4_1)[15] == 16
		);
		TIN_NAMED_MANDATORY_CHECK("4D-partial initialisation",
			((int*)&mat4_2)[0] == 1 && ((int*)&mat4_2)[1] == 2 && ((int*)&mat4_2)[2] == 3 && ((int*)&mat4_2)[3] == 4
			&& ((int*)&mat4_2)[4] == 0 && ((int*)&mat4_2)[5] == 0 && ((int*)&mat4_2)[6] == 0 && ((int*)&mat4_2)[7] == 0
			&& ((int*)&mat4_2)[8] == 0 && ((int*)&mat4_2)[9] == 0 && ((int*)&mat4_2)[10] == 0 && ((int*)&mat4_2)[11] == 0
			&& ((int*)&mat4_2)[12] == 0 && ((int*)&mat4_2)[13] == 0 && ((int*)&mat4_2)[14] == 0 && ((int*)&mat4_2)[15] == 0
		);
		TIN_NAMED_MANDATORY_CHECK("4D-diagonal initialisation",
			((int*)&mat4_3)[0] == 1 && ((int*)&mat4_3)[1] == 0 && ((int*)&mat4_3)[2] == 0 && ((int*)&mat4_3)[3] == 0
			&& ((int*)&mat4_3)[4] == 0 && ((int*)&mat4_3)[5] == 1 && ((int*)&mat4_3)[6] == 0 && ((int*)&mat4_3)[7] == 0
			&& ((int*)&mat4_3)[8] == 0 && ((int*)&mat4_3)[9] == 0 && ((int*)&mat4_3)[10] == 1 && ((int*)&mat4_3)[11] == 0
			&& ((int*)&mat4_3)[12] == 0 && ((int*)&mat4_3)[13] == 0 && ((int*)&mat4_3)[14] == 0 && ((int*)&mat4_3)[15] == 1
		);
	}


	turbolin::Matrix<int, 2> mat2_0 {};
	turbolin::Matrix<int, 3> mat3_0 {};
	turbolin::Matrix<int, 4> mat4_0 {};

	turbolin::Matrix<int, 2> mat2_1 {1, 2, 3, 4};
	turbolin::Matrix<int, 3> mat3_1 {1, 2, 3, 4, 5, 6, 7, 8, 9};
	turbolin::Matrix<int, 4> mat4_1 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

	TIN_NAMED_MANDATORY_CHECK("mat2_0 - mat2_0 : equality check",   mat2_0 == mat2_0);
	TIN_NAMED_MANDATORY_CHECK("mat2_1 - mat2_1 : equality check",   mat2_1 == mat2_1);
	TIN_NAMED_MANDATORY_CHECK("mat2_1 - mat2_0 : inequality check", mat2_1 != mat2_0);
	TIN_NAMED_MANDATORY_CHECK("mat2_0 - mat2_1 : inequality check", mat2_0 != mat2_1);

	TIN_NAMED_MANDATORY_CHECK("mat3_0 - mat3_0 : equality check",   mat3_0 == mat3_0);
	TIN_NAMED_MANDATORY_CHECK("mat3_1 - mat3_1 : equality check",   mat3_1 == mat3_1);
	TIN_NAMED_MANDATORY_CHECK("mat3_1 - mat3_0 : inequality check", mat3_1 != mat3_0);
	TIN_NAMED_MANDATORY_CHECK("mat3_0 - mat3_1 : inequality check", mat3_0 != mat3_1);

	TIN_NAMED_MANDATORY_CHECK("mat4_0 - mat4_0 : equality check",   mat4_0 == mat4_0);
	TIN_NAMED_MANDATORY_CHECK("mat4_1 - mat4_1 : equality check",   mat4_1 == mat4_1);
	TIN_NAMED_MANDATORY_CHECK("mat4_1 - mat4_0 : inequality check", mat4_1 != mat4_0);
	TIN_NAMED_MANDATORY_CHECK("mat4_0 - mat4_1 : inequality check", mat4_0 != mat4_1);

	{
		turbolin::Matrix<float, 4> mat4_0f {};
		TIN_NAMED_MANDATORY_CHECK("mix type equality check : float - int", mat4_0f == mat4_0);
		TIN_NAMED_MANDATORY_CHECK("mix type equality check : int - float", mat4_0 == mat4_0f);
	}


	turbolin::Matrix<int, 2> mat2_2 {1, 2};
	turbolin::Matrix<int, 4> mat4_2 {1.f, 2.f, 3.f, 4.f};

	TIN_NAMED_CHECK("mat2_1 += mat2_2", (mat2_1 += mat2_2) == turbolin::Matrix<int, 2> (2, 4, 3, 4));
	TIN_NAMED_CHECK("mat2_1 -= mat2_2", (mat2_1 -= mat2_2) == turbolin::Matrix<int, 2> (1, 2, 3, 4));
//	TIN_NAMED_CHECK("mat2_1 *= mat2_2", (mat2_1 *= mat2_2) == turbolin::Matrix<float, 2> (2.f, 4.f, 3.f, 4.f));

	TIN_NAMED_CHECK("mat4_1 += mat4_2", (mat4_1 += mat4_2) == turbolin::Matrix<int, 4> (2, 4, 6, 8, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16));
	TIN_NAMED_CHECK("mat4_1 -= mat4_2", (mat4_1 -= mat4_2) == turbolin::Matrix<int, 4> (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16));
//	TIN_NAMED_CHECK("mat4_1 *= mat4_2", (mat4_1 *= mat4_2) == turbolin::Matrix<float, 4> (2.f, 4.f, 3.f, 4.f));


	mat2_1 = turbolin::Matrix<int, 2> (1, 2, 3, 4);
	mat4_1 = turbolin::Matrix<int, 4> (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

	TIN_NAMED_CHECK("mat2_1 + mat2_2", mat2_1 + mat2_2 == turbolin::Matrix<int, 2> (2, 4, 3, 4));
	TIN_NAMED_CHECK("mat2_1 - mat2_2", mat2_1 - mat2_2 == turbolin::Matrix<int, 2> (0, 0, 3, 4));
//	TIN_NAMED_CHECK("mat2_1 + mat2_2", mat2_1 + mat2_2 == turbolin::Matrix<int, 2> ());

	TIN_NAMED_CHECK("mat4_1 + mat4_2", mat4_1 + mat4_2 == turbolin::Matrix<int, 4> (2, 4, 6, 8, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16));
	TIN_NAMED_CHECK("mat4_1 - mat4_2", mat4_1 - mat4_2 == turbolin::Matrix<int, 4> (0, 0, 0, 0, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16));
//	TIN_NAMED_CHECK("mat4_1 + mat4_2", mat4_1 + mat4_2 == turbolin::Matrix<int, 4> ());
TIN_END_TEST(int_matrix, "Test  Turbolin's int matrix implementation")
