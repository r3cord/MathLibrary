#pragma once
#include <vector>
#include <iostream>

namespace MathLibrary
{
	class Approximation
	{
	public:
		//Declaration of the leastSquaresApproximation.
		static std::vector<double> leastSquaresApproximation(std::vector<std::vector<double>> points);
		//Declaration of the leastSquaresPolynomialApproximation.
		static std::vector<double> leastSquaresPolynomialApproximation(std::vector<double> x, std::vector<double> y, int degree);
	};
}