#include "NonlinearEquations.h"

namespace MathLibrary
{
	double NonlinearEquations::bisectionMethod(double(*function)(double), double xStart, double xEnd, double accuracy)
	{
		//Sprawdzenie wymaganego za³o¿enia
		if (xStart >= xEnd)
			exit(-1);
		else if (function(xStart) * function(xEnd) >= 0)
			exit(-2);

		//Obliczenie i sprawdzenie, czy pierwiastkiem nie jest punkt x1
		double x1 = (xStart + xEnd) / 2;
		if (function(x1) == 0)
			return x1;

		//Pêtla dzia³aj¹ca dopóki nie osi¹gniemy zadanej dok³adnoœci
		while (abs(xStart - xEnd) > accuracy)
		{
			//Sprawdzenie warunków i odpowiednie ograniczenie przedzia³u
			if (function(x1) * function(xStart) < 0)
				xEnd = x1;
			else if (function(x1) * function(xEnd) < 0)
				xStart = x1;

			//Obliczenie nowego punktu (pierwiastka)
			x1 = (xStart + xEnd) / 2;
		}
		//Zwrócenie pierwiastka równania
		return x1;
	}

	double NonlinearEquations::newtonRaphsonMethod(double(*function)(double), double(*derivativeFunction)(double), double xStart, double xEnd, double accuracy)
	{
		//Sprawdzenie wymaganego za³o¿enia
		if (xStart >= xEnd)
			exit(-1);
		else if (function(xStart) * function(xEnd) >= 0)
			exit(-2);

		//Wybranie punktu startowego
		double x1 = xStart;

		//Pêtla dzia³aj¹ca dopóki nie zostanie osiagniêty warunek stopu
		while (abs(function(x1)) > accuracy)
		{
			//Obliczenia wed³ug wzoru rekurencyjnego
			x1 = x1 - (function(x1) / derivativeFunction(x1));
		}
		//Zwrócenie pierwiastka równania
		return x1;
	}
}