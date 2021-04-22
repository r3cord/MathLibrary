#pragma once

namespace MathLibrary
{
	class DefiniteIntegral
	{
	public:
		//Declaration of the rectangleMethod.
		static double rectangleMethod(double(*function)(double), int numberOfRectangles, double xStart, double xEnd);
		//Declaration of the trapezeMethod.
		static double trapezeMethod(double(*function)(double), int numberOfTrapezes, double xStart, double xEnd);
		//Declaration of the simpsonMethod.
		static double simpsonMethod(double(*function)(double), int numberOfParables, double xStart, double xEnd);
		//Declaration of the monteCarloMethod.
		static double monteCarloMethod(double(*function)(double), int numberOfPoints, double xStart, double xEnd);
	};
}