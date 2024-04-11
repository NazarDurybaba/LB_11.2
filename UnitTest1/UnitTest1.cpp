#include "pch.h"
#include "CppUnitTest.h"
#include "../LB_11.2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(TestCountExcellentStudents)
        {
            std::vector<Student> students = {
                {"Student1", 1, ComputerScience, 5, 5, {5}},
                {"Student2", 1, Informatics, 4, 5, {5}},
                {"Student3", 1, MathAndEconomics, 5, 5, {5}}
            };
            Assert::AreEqual(2, countExcellentStudents(students));
        }

        TEST_METHOD(TestCalculatePhysics5Percentage)
        {
            std::vector<Student> students = {
                {"Student1", 1, ComputerScience, 5, 5, {5}},
                {"Student2", 1, Informatics, 4, 5, {5}},
                {"Student3", 1, MathAndEconomics, 5, 5, {5}}
            };
            Assert::AreEqual(66.66667, calculatePhysics5Percentage(students), 0.00001);
        }
	};
}
