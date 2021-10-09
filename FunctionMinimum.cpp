#include "FunctionMinimum.h"

namespace MathLibrary
{
	double FunctionMinimum::goldenRatio(double(*function)(double), double xStart, double xEnd, double accuracy)
	{
		//Deklaracja i definicja z³otej liczby
		const double goldenNumber = 0.61803398;
		//Zmienne odpowiadaj¹ce za zawê¿anie przedzia³u
		double xLeft, xRight;

		//Pêtla dzia³aj¹ca, dopóki nie zostanie osi¹gniêta ¿¹dana dok³adnoœæ
		while ((xEnd - xStart) > accuracy)
		{
			//Obliczenie zmiennych zawê¿aj¹cych przedzia³
			xLeft = xEnd - goldenNumber * (xEnd - xStart);
			xRight = xStart + goldenNumber * (xEnd - xStart);

			//Dla ró¿nych warunków odpowiednie zawê¿enie i przepisanie przedzia³u
			if (function(xLeft) > function(xRight))
			{
				xStart = xLeft;
			}
			else if (function(xLeft) < function(xRight))
			{
				xEnd = xRight;
			}
		}
		//Zwrócenie wartoœci koñcowej
		return xStart;
	}
}