#include "DefiniteIntegrals.h"

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

	double DefiniteIntegral::gaussianSquaringMethod(double coordsX[4], double coordsY[4])
	{
		//Deklaracja i definicja wag
		double weight[2] = { 1.0, 1.0 };
		//Deklaracja i definicja punktów ca³kowania (Gaussa)
		double point[2] = { -0.5773502692, 0.5773502692 };
		//Deklaracja funkcji kszta³tu
		double shapeFunction[2][2][4];
		//Deklaracja pochodnych i wyznacznika
		double derivativeKsi[2][4], derivativeNi[2][4], funDetj[2][2];

		//Pêtla przechodz¹dza przez odpowiednie elementy
		//tablic pochodnych oraz funkcji kszta³tu
		for (int i = 0; i < 2; i++)
		{
			//Pêtla przechodz¹ca przez odpowiednie elementy
			//tablicy funkcji kszta³tu
			for (int j = 0; j < 2; j++)
			{
				//Obliczenie funkcji kszta³tu dla poszczególnych punktów ca³kowania
				//Potrzebne na przysz³oœæ
				shapeFunction[i][j][0] = 0.25 * (1.0 - point[j]) * (1.0 - point[i]);
				shapeFunction[i][j][1] = 0.25 * (1.0 + point[j]) * (1.0 - point[i]);
				shapeFunction[i][j][2] = 0.25 * (1.0 + point[j]) * (1.0 + point[i]);
				shapeFunction[i][j][3] = 0.25 * (1.0 - point[j]) * (1.0 + point[i]);
			}
			//Obliczenie odpowiednich pochodnych funkcji kszta³tu
			derivativeNi[i][0] = -0.25 * (1.0 - point[i]);
			derivativeNi[i][1] = -0.25 * (1.0 + point[i]);
			derivativeNi[i][2] = 0.25 * (1.0 + point[i]);
			derivativeNi[i][3] = 0.25 * (1.0 - point[i]);
			derivativeKsi[i][0] = -0.25 * (1.0 - point[i]);
			derivativeKsi[i][1] = 0.25 * (1.0 - point[i]);
			derivativeKsi[i][2] = 0.25 * (1.0 + point[i]);
			derivativeKsi[i][3] = -0.25 * (1.0 + point[i]);
		}

		//Deklaracja zmiennych odpowiadaj¹cych za pochodne
		double dxdKsi = 0, dydKsi = 0, dxdNi = 0, dydNi = 0;
		for (int i = 0; i < 2; i++)
		{
			//Suma pochodnych funkcji kszta³tu razy wartoœci wspó³rzêdnych
			dxdKsi = derivativeKsi[i][0] * coordsX[0] + derivativeKsi[i][1] * coordsX[1] + derivativeKsi[i][2] * coordsX[2] + derivativeKsi[i][3] * coordsX[3];
			dydKsi = derivativeKsi[i][0] * coordsY[0] + derivativeKsi[i][1] * coordsY[1] + derivativeKsi[i][2] * coordsY[2] + derivativeKsi[i][3] * coordsY[3];

			for (int j = 0; j < 2; j++)
			{
				//Suma pochodnych funkcji kszta³tu razy wartoœci wspó³rzêdnych
				dxdNi = derivativeNi[j][0] * coordsX[0] + derivativeNi[j][1] * coordsX[1] + derivativeNi[j][2] * coordsX[2] + derivativeNi[j][3] * coordsX[3];
				dydNi = derivativeNi[j][0] * coordsY[0] + derivativeNi[j][1] * coordsY[1] + derivativeNi[j][2] * coordsY[2] + derivativeNi[j][3] * coordsY[3];
				//Obliczenie wyznacznika macierzy Jakobiego w punktach ca³kowania
				funDetj[i][j] = dxdKsi * dydNi - dxdNi * dydKsi;
			}
		}

		//Deklaracja zmiennej odpowiadaj¹cej za przechowywanie powierzchni
		double surface = 0;
		//W pêtlach obliczenie powierzchni
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				surface += abs(funDetj[i][j]) * weight[i] * weight[j];
			}
		}
		//Zwrócenie wartoœci powierzchni (wynik ca³kowania)
		return surface;
	}
}