#pragma once
#include <vector>
#include <iostream>

namespace MathLibrary
{
	class DifferentialEquations
	{
	public:
		static std::vector<std::vector<double>> eulerMethod(double x0, double y0, double xStart, double xEnd, double step, double(*function)(double, double), double(*secondFunction)(double));
		static std::vector<std::vector<double>> heunMethod(double x0, double y0, double xStart, double xEnd, double step, double(*function)(double, double), double(*secondFunction)(double));
		static std::vector<std::vector<double>> rkMethod(double x0, double y0, double xStart, double xEnd, double step, double(*function)(double, double), double(*secondFunction)(double));
	};
}