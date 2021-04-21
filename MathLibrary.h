#pragma once

namespace MathLibrary
{
	class DefiniteIntegral
	{
	public:
		static double rectangleMethod(double(*function)(double), int numberOfRectangles, double xStart, double xEnd);
		static double trapezeMethod(double(*function)(double), int numberOfTrapezes, double xStart, double xEnd);
		static double simpsonMethod(double(*function)(double), int n, double xp, double xk);
		static double monteCarloMethod(double(*function)(double), int n, double xp, double xk);
	};
}