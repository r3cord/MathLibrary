#pragma once
#include <iostream>

namespace MathLibrary
{
	class NonlinearEquations
	{
	public:
		static double bisectionMethod(double(*function)(double), double xStart, double xEnd, double accuracy);
		static double newtonRaphsonMethod(double(*function)(double), double(*derivativeFunction)(double), double xStart, double xEnd, double accuracy);
	};
}