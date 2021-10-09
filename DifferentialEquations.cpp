#include "DifferentialEquations.h"

namespace MathLibrary
{
	std::vector<std::vector<double>> DifferentialEquations::eulerMethod(double x0, double y0, double xStart, double xEnd, double step, double(*function)(double, double), double(*secondFunction)(double))
	{
		//Policzenie ilo�ci potrzebnych krok�w
		int N = abs(xEnd - x0) / step + 0.00000000000004;

		//Zarezerwowanie miejsca na wyniki
		std::vector<std::vector<double>> points(N, std::vector<double>(N));

		//Deklaracja zmiennej obpowiadaj�cej za policzenie b��du
		double mistake = 0;

		//Obliczenie punkt�w
		for (int i = 0; i < N; i++)
		{
			//Je�eli nie jest to pierwszy krok to wykorzystujemy poprzednie wyliczenia
			if (i != 0)
			{
				points[i][0] = points[i - 1][0] + step;
				points[i][1] = points[i - 1][1] + step * function(points[i - 1][0], points[i - 1][1]);
			}
			else
			{
				//Je�eli jest to pierwszy krok to wykorzystujemy dostarczone dane
				points[i][0] = x0 + step;
				points[i][1] = y0 + step * function(x0, y0);
			}
			//Obliczenie b��du
			mistake += abs(secondFunction(points[i][0]) - points[i][1]);
		}

		std::cout << "Miscalculation: " << mistake << std::endl;

		//Wypisanie danych (do usuni�cia)
		for (int i = 0; i < N; i++)
		{
			std::cout << "x: " << points[i][0] << " y: " << points[i][1] << std::endl;
		}

		//Zwr�cenie wynik�w
		return points;
	}

	std::vector<std::vector<double>> DifferentialEquations::heunMethod(double x0, double y0, double xStart, double xEnd, double step, double(*function)(double, double), double(*secondFunction)(double))
	{
		//Obliczenie liczby krok�w
		int N = abs(xEnd - x0) / step + 0.00000000000004;

		//Zarezerwowanie miejsca na wyniki
		std::vector<std::vector<double>> points(N, std::vector<double>(2));

		//Zmienna pomocnicza
		double tempFunRes;

		//Deklaracja zmiennej obpowiadaj�cej za policzenie b��du
		double mistake = 0;

		//P�tla obliczaj�ca wyniki (punkty)
		for (int i = 0; i < N; i++)
		{
			//Je�eli nie jest to pierwszy krok to wykorzystujemy poprzednie wyliczenia
			if (i != 0)
			{
				//Obliczenia funkcji do zmiennej pomocniczej
				tempFunRes = function(points[i - 1][0], points[i - 1][1]);
				//Obliczenie warto�ci y
				points[i][1] = points[i - 1][1] + ((step / 2) * (tempFunRes + function(points[i - 1][0] + step, points[i - 1][1] + step * tempFunRes)));
				//Obliczenie warto�ci x
				points[i][0] = points[i - 1][0] + step;
			}
			else
			{
				//Je�eli jest to pierwszy krok to wykorzystujemy dostarczone dane
				//Obliczenia funkcji do zmiennej pomocniczej
				tempFunRes = function(x0, y0);
				//Obliczenie warto�ci y
				points[i][1] = y0 + ((step / 2) * (tempFunRes + function(x0 + step, y0 + step * tempFunRes)));
				//Obliczenie warto�ci x
				points[i][0] = x0 + step;
			}
			mistake += abs(secondFunction(points[i][0]) - points[i][1]);
		}

		//Wypisanie wynik�w
		std::cout << "Heun: " << std::endl;
		for (int i = 0; i < N; i++)
		{
			std::cout << "x: " << points[i][0] << " y: " << points[i][1] << std::endl;
		}

		//Wypisanie obliczonego b��du
		std::cout << "Miscalculation: " << mistake << std::endl;

		//Zwr�cenie obliczonych punkt�w
		return points;

	}

	std::vector<std::vector<double>> DifferentialEquations::rkMethod(double x0, double y0, double xStart, double xEnd, double step, double(*function)(double, double), double(*secondFunction)(double))
	{
		//Obliczenie liczby krok�w
		int N = abs(xEnd - x0) / step + 0.00000000000004;

		//Utworzenie zmiennych pomocniczych
		double k1, k2, k3, k4;

		//Deklaracja zmiennej obpowiadaj�cej za policzenie b��du
		double mistake = 0;

		//Zarezerwowanie miejsca na wyniki
		std::vector<std::vector<double>> points(N, std::vector<double>(2));

		//P�tla obliczaj�ca wyniki (punkty)
		for (int i = 0; i < N; i++)
		{
			//Je�eli nie jest to pierwszy krok to wykorzystujemy poprzednie wyliczenia
			if (i != 0)
			{
				//obliczenie potrzebnych zmiennych do wzoru
				k1 = step * function(points[i - 1][0], points[i - 1][1]);
				k2 = step * function(points[i - 1][0] + 0.5 * step, points[i - 1][1] + 0.5 * k1);
				k3 = step * function(points[i - 1][0] + 0.5 * step, points[i - 1][1] + 0.5 * k2);
				k4 = step * function(points[i - 1][0] + step, points[i - 1][1] + k3);
				//Obliczenie warto�ci y
				points[i][1] = points[i - 1][1] + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
				//Obliczenie warto�ci x
				points[i][0] = points[i - 1][0] + step;
			}
			else
			{
				//Je�eli jest to pierwszy krok to wykorzystujemy dostarczone dane
				//obliczenie potrzebnych zmiennych do wzoru
				k1 = step * function(x0, y0);
				k2 = step * function(x0 + 0.5 * step, y0 + 0.5 * k1);
				k3 = step * function(x0 + 0.5 * step, y0 + 0.5 * k2);
				k4 = step * function(x0 + step, y0 + k3);
				//Obliczenie warto�ci y
				points[i][1] = y0 + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
				//Obliczenie warto�ci x
				points[i][0] = x0 + step;
			}
			mistake += abs(secondFunction(points[i][0]) - points[i][1]);
		}

		//Wypisanie wynik�w
		std::cout << "RK: " << std::endl;
		for (int i = 0; i < N; i++)
		{
			std::cout << "x: " << points[i][0] << " y: " << points[i][1] << std::endl;
		}
		std::cout << "Miscalculation: " << mistake << std::endl;

		//Zwr�cenie obliczonych punkt�w
		return points;
	}
}