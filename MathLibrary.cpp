#include "MathLibrary.h"
#include <iostream>
#include <random>

namespace MathLibrary
{
	double DefiniteIntegral::rectangleMethod(double(*function)(double), int numberOfRectangles, double xStart, double xEnd)
	{
		//Checking required conditions
		if (xStart >= xEnd)
			exit(-1);
		else if (numberOfRectangles < 1)
			exit(-2);

		//Calculating width of rectangles 
		double dx = (xEnd - xStart) / numberOfRectangles;
		//Declaring end variable
		double value = 0.0;
		//Loop summing up all heights of rectangles
		for (double i = xStart; i < xEnd; i += dx)
		{
			//Calculating and summing up heights of rectangles
			value = value + function(i + dx);
		}
		//Multiplying sum of heights by width of rectangles (calculating the area)
		value *= dx;
		//Returning end value
		return value;
	}

	double DefiniteIntegral::trapezeMethod(double(*function)(double), int numberOfTrapezes, double xStart, double xEnd)
	{
		//Checking required conditions
		if (xStart >= xEnd)
			exit(-1);
		else if (numberOfTrapezes < 1)
			exit(-2);

		//Calculating width of trapezes
		double dx = (xEnd - xStart) / numberOfTrapezes;
		//Declaring end variable
		double value = 0.0;
		//Loop calculating and summing up areas of all trapezes
		for (double i = xStart; i < xEnd; i += dx)
		{
			//Calculating and summing up areas of rectangles
			value = value + ((function(i) + function(i + dx)) / 2) * dx;
		}
		//Returning end value
		return value;
	}

	double DefiniteIntegral::simpsonMethod(double(*function)(double), int numberOfParables, double xStart, double xEnd)
	{
		//Checking required conditions
		if (xStart >= xEnd)
			exit(-1);
		else if (numberOfParables < 1)
			exit(-2);
		else if (numberOfParables % 2 == 1)
			exit(-3);

		//Calculating width of parables
		double h = (xEnd - xStart) / numberOfParables;
		//Declaring end variable
		double value = 0.0;

		//Loop going trough all required points
		for (double i = xStart; i + 2 * h <= xEnd; i += 2 * h)
		{
			//Calculating the approximate value of the integral
			value += (function(i) + 4 * function(i + h) + function(i + 2 * h)) * (h / 3);
		}
		//Returning end value
		return value;
	}

	double DefiniteIntegral::monteCarloMethod(double(*function)(double), int numberOfPoints, double xStart, double xEnd)
	{
		//Checking required conditions
		if (xStart >= xEnd)
			exit(-1);
		else if (numberOfPoints < 1)
			exit(-2);

		//Declaring variables used for the draw
		std::random_device rd;
		std::mt19937_64 gen(rd());
		//Setting the draw interval
		std::uniform_real_distribution<> dis(xStart, xEnd);

		//Declaring end variable
		double value = 0.0;
		//Loop going trough all required points
		for (double i = 0; i < numberOfPoints; i++)
		{
			//Drawing values of points and calculating tha average value of all points
			value += function(dis(gen)) / numberOfPoints;
		}
		//Calculating the approximate value of the integral
		value *= abs(xEnd - xStart);
		//Returning end value
		return value;
	}
}