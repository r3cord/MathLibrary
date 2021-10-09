#include "NonlinearEquations.h"

namespace MathLibrary
{
	double NonlinearEquations::bisectionMethod(double(*function)(double), double xStart, double xEnd, double accuracy)
	{
		//Sprawdzenie wymaganego za�o�enia
		if (xStart >= xEnd)
			exit(-1);
		else if (function(xStart) * function(xEnd) >= 0)
			exit(-2);

		//Obliczenie i sprawdzenie, czy pierwiastkiem nie jest punkt x1
		double x1 = (xStart + xEnd) / 2;
		if (function(x1) == 0)
			return x1;

		//P�tla dzia�aj�ca dop�ki nie osi�gniemy zadanej dok�adno�ci
		while (abs(xStart - xEnd) > accuracy)
		{
			//Sprawdzenie warunk�w i odpowiednie ograniczenie przedzia�u
			if (function(x1) * function(xStart) < 0)
				xEnd = x1;
			else if (function(x1) * function(xEnd) < 0)
				xStart = x1;

			//Obliczenie nowego punktu (pierwiastka)
			x1 = (xStart + xEnd) / 2;
		}
		//Zwr�cenie pierwiastka r�wnania
		return x1;
	}

	double NonlinearEquations::newtonRaphsonMethod(double(*function)(double), double(*derivativeFunction)(double), double xStart, double xEnd, double accuracy)
	{
		//Sprawdzenie wymaganego za�o�enia
		if (xStart >= xEnd)
			exit(-1);
		else if (function(xStart) * function(xEnd) >= 0)
			exit(-2);

		//Wybranie punktu startowego
		double x1 = xStart;

		//P�tla dzia�aj�ca dop�ki nie zostanie osiagni�ty warunek stopu
		while (abs(function(x1)) > accuracy)
		{
			//Obliczenia wed�ug wzoru rekurencyjnego
			x1 = x1 - (function(x1) / derivativeFunction(x1));
		}
		//Zwr�cenie pierwiastka r�wnania
		return x1;
	}
}