#pragma once
#include <climits>
#include <iostream>

namespace MathLibrary
{
	class Interpolation
	{
	public:
		static double lagrangeInterpolation(double** coordinates, int quantity, double x);
		static double newtonInterpolation(double** coordinates, int quantity, double x);
	};
}