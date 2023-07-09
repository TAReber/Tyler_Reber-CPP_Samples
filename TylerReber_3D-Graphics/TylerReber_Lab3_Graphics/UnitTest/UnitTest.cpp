#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(Vector3_Addition_Operator)
		{
			vector3 a(1, 2, 3);
			vector3 b(4, 5, 6);
			vector3 c = a + b;
			Assert::AreEqual(5.0f, c.x);
			Assert::AreEqual(7.0f, c.y);
			Assert::AreEqual(9.0f, c.z);
		}

		TEST_METHOD(vector3_Initialization) {
			vector4 a;
			Assert::AreEqual(0.0f, a.x);
			Assert::AreEqual(0.0f, a.y);
			Assert::AreEqual(0.0f, a.z);

		}

		TEST_METHOD(vector4_Zero_Init) {
			vector4 a;
			Assert::AreEqual(0.0f, a.x);
			Assert::AreEqual(0.0f, a.y);
			Assert::AreEqual(0.0f, a.z);
			Assert::AreEqual(0.0f, a.w);
		}

		TEST_METHOD(vector4_Value_Init) {
			vector4 a(1,2,3,4);
			Assert::AreEqual(1.0f, a.x);
			Assert::AreEqual(2.0f, a.y);
			Assert::AreEqual(3.0f, a.z);
			Assert::AreEqual(4.0f, a.w);
		}

		TEST_METHOD(Vector4_Addition_Operator)
		{
			vector4 a(1, 2, 3, 4);
			vector4 b(5, 6, 7, 8);
			vector4 c = a + b;
			Assert::AreEqual(6.0f, c.x);
			Assert::AreEqual(8.0f, c.y);
			Assert::AreEqual(10.0f, c.z);
			Assert::AreEqual(1.0f, c.w);
		}

		TEST_METHOD(Transform_Zero_Init) {
			Transform T;
			for (int x = 0; x < 4; x++) {
				for (int y = 0; y < 4; y++) {
					Assert::AreEqual(T.transform[x][y], 0.0f);
				}
			}
		}

		TEST_METHOD(Transform_array2_Init) {
			float a2[4][4] = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16} };
			
			Transform T(a2);
			int i = 1;
			for (int x = 0; x < 4; x++) {
				for (int y = 0; y < 4; y++) {
					Assert::AreEqual(T.transform[x][y], (float)i);
					i++;
				}
			}
		}

		TEST_METHOD(Transform_V4_Mult) {
			float a2[4][4] = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16} };
			Transform T(a2);
			vector4 V(1, 2, 3, 4);

			vector4 C = T * V;
			Assert::AreEqual(C.x, 90.0f);
			Assert::AreEqual(C.y, 100.0f, C.y);
			Assert::AreEqual(C.z, 110.0f, C.z);
			Assert::AreEqual(C.w, 120.0f, C.w);

		}

		TEST_METHOD(Matrix4_X_Matrix4) {
			float arr1[4][4] = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16} };
			float arr2[4][4] = { {17,18,19,20}, {21,22,23,24}, {25,26,27,28}, {29,30,31,32} };
			float expected[4][4]{ {250,260,270,280}, {618,644,670,696}, {986,1028,1070,1112}, {1354,1412,1470,1528} };
			Transform a(arr1);
			Transform b(arr2);
			Transform c = a * b;

			for (int x = 0; x < 4; x++) {
				for (int y = 0; y < 4; y++) {
					Assert::AreEqual(expected[x][y], c.transform[x][y]);
				}
			}
		}

		TEST_METHOD(Fast_Matrix_Inverse) {
			float arr[4][4] = { {1,0,0,0}, {0,0.309f,0.951f,0}, {0,-0.951f,0.309f,0}, {7,-2.282,9.153,1} };
			float expected[4][4] = { {1,0,0,0}, {0,0.309f,-0.951f,0}, {0,0.951f,0.309f,0}, {-7,-8,-5,1} };
			Transform a(arr);
			a.SetTransform(arr);
			Transform b = FastInverse(a);

			for (int x = 0; x < 4; x++) {
				for (int y = 0; y < 4; y++) {
					Assert::AreEqual(expected[x][y], b.transform[x][y]);
				}
			}
		}

		TEST_METHOD(Implicite_Line_Test) {
			vector4 start(-50, 0, 0, 0);
			vector4 end(50, 0, 0, 0);
			Line ln(start, end, 0);
			for (int i = -50; i < 51; i++) {
				float a = ImpliciteLineEquation(ln, vector4(i, 0, 0, 0));
				Assert::AreEqual(0.0f, a);
			}


		}
	};
}
