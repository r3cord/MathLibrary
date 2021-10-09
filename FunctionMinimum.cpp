#include "FunctionMinimum.h"

namespace MathLibrary
{
	double FunctionMinimum::goldenRatio(double(*function)(double), double xStart, double xEnd, double accuracy)
	{
		//Deklaracja i definicja z�otej liczby
		const double goldenNumber = 0.61803398;
		//Zmienne odpowiadaj�ce za zaw�anie przedzia�u
		double xLeft, xRight;

		//P�tla dzia�aj�ca, dop�ki nie zostanie osi�gni�ta ��dana dok�adno��
		while ((xEnd - xStart) > accuracy)
		{
			//Obliczenie zmiennych zaw�aj�cych przedzia�
			xLeft = xEnd - goldenNumber * (xEnd - xStart);
			xRight = xStart + goldenNumber * (xEnd - xStart);

			//Dla r�nych warunk�w odpowiednie zaw�enie i przepisanie przedzia�u
			if (function(xLeft) > function(xRight))
			{
				xStart = xLeft;
			}
			else if (function(xLeft) < function(xRight))
			{
				xEnd = xRight;
			}
		}
		//Zwr�cenie warto�ci ko�cowej
		return xStart;
	}
}