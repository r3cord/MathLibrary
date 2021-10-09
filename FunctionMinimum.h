#pragma once

namespace MathLibrary
{
	class FunctionMinimum
	{
		static double goldenRatio(double(*function)(double), double xStart, double xEnd, double accuracy);
	};
}