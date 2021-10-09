#include "Interpolations.h"

namespace MathLibrary
{
	double Interpolation::lagrangeInterpolation(double** coordinates, int quantity, double x)
	{
		if (quantity < 2) //Sprawdzenie, czy zosta�a podana minimalna ilo�� punkt�w
		{
			std::cout << "Musisz podac minimum 2 punkty!" << std::endl;
			std::cout << '\a' << std::endl;
			exit(-1);
		}
		double max = std::numeric_limits<double>::lowest(); //Utworzenie maksymalnej liczby, kt�r� obecnie jest najmniejsza mo�liwa liczba
		double min = std::numeric_limits<double>::max(); //Utworzenie minimalnej liczby, kt�r� obecnie jest najwi�ksza mo�liwa liczba
		for (int i = 0; i < quantity; i++) //P�tla przechodz�ca przez ca�� tablic�, w kt�rej sprawdzam kilka wa�nych warunk�w
		{
			if (coordinates[i][0] > max) //Pozyskanie maksymalnej warto�ci przedzia�u
			{
				max = coordinates[i][0];
			}
			if (coordinates[i][0] < min) //Pozyskanie minimalnej warto�ci przedzia�u
			{
				min = coordinates[i][0];
			}
			if (i < quantity - 1)
			{
				if (coordinates[i][0] == coordinates[i + 1][0]) //Sprawdzenie, czy nie istniej� dwie takie same warto�ci x (zapobieganie dzieleniu przez 0)
				{
					std::cout << "Podane wartosci sa niewlasciwe. Nie moga byc podane dwie takie same wartosci x (dzielenie przez 0)" << std::endl;
					std::cout << '\a' << std::endl;
					exit(-2);
				}
			}
		}
		if (!((x >= min) && (x <= max))) //Sprawdzenie, czy podana warto�� nale�y do przedzia�u
		{
			std::cout << "Podana wartosc nie jest w przedzialne od xmin do xmax!" << std::endl;
			std::cout << '\a' << std::endl;
			exit(-3);
		}
		double value = 0.0; //Zmienna przechowuj�ca wynik
		double lagrangeFactor = 1.0; //Zmienna przechowuj�ca wsp�czynnik lagrange (pocz�tkowa warto�� 1.0, poniewa� jest to mnozenie)
		int help = 0; //Zmienna pomocnicza zapobiegaj�ca przypadku, w kt�rym dzieliliby�my przez 0
		for (int i = 0; i < quantity; i++) //P�tla przechodz�ca przez wszystkie elementy tablicy
		{
			for (int j = 0; j < quantity; j++) //P�tla przechodz�ca ponownie przez elementy tablicy, ale bez elmentu i
			{
				if (j != help)
				{
					lagrangeFactor = lagrangeFactor * ((x - coordinates[j][0]) / (coordinates[help][0] - coordinates[j][0])); //Obliczenie wsp�czynnika lagrange'a
				}
			}
			//std::cout << lagrangeFactor << std::endl;
			value = value + lagrangeFactor * coordinates[i][1]; //Obliczenie warto�ci dla obecnego elementu tablicy
			help++; //iteracja zmiennej pomocniczej
			lagrangeFactor = 1.0; //"wyzerowanie" wsp�czynnika lagrange'a
		}
		return value; //Zwr�cenie obliczonej warto�ci
	}

	double Interpolation::newtonInterpolation(double** coordinates, int quantity, double x)
	{
		if (quantity < 2) //Sprawdzenie, czy zosta�a podana minimalna ilo�� punkt�w
		{
			std::cout << "Musisz podac minimum 2 punkty!" << std::endl;
			std::cout << '\a' << std::endl;
			exit(-1);
		}
		double max = std::numeric_limits<double>::lowest(); //Utworzenie maksymalnej liczby, kt�r� obecnie jest najmniejsza mo�liwa liczba
		double min = std::numeric_limits<double>::max(); //Utworzenie minimalnej liczby, kt�r� obecnie jest najwi�ksza mo�liwa liczba
		for (int i = 0; i < quantity; i++) //P�tla przechodz�ca przez ca�� tablic�, w kt�rej sprawdzam kilka wa�nych warunk�w
		{
			if (coordinates[i][0] > max) //Pozyskanie maksymalnej warto�ci przedzia�u
			{
				max = coordinates[i][0];
			}
			if (coordinates[i][0] < min) //Pozyskanie minimalnej warto�ci przedzia�u
			{
				min = coordinates[i][0];
			}
			if (i < quantity - 1)
			{
				if (coordinates[i][0] == coordinates[i + 1][0]) //Sprawdzenie, czy nie istniej� dwie takie same warto�ci x (zapobieganie dzieleniu przez 0)
				{
					std::cout << "Podane wartosci sa niewlasciwe. Nie moga byc podane dwie takie same wartosci x (dzielenie przez 0)" << std::endl;
					std::cout << '\a' << std::endl;
					exit(-2);
				}
			}
		}
		if (!((x >= min) && (x <= max))) //Sprawdzenie, czy podana warto�� nale�y do przedzia�u
		{
			std::cout << "Podana wartosc nie jest w przedzialne od xmin do xmax!" << std::endl;
			std::cout << '\a' << std::endl;
			exit(-3);
		}

		//Deklaracja wymaganych zmiennych
		int tempQuantity = quantity - 1;
		double* factors = new double[tempQuantity - 1];
		double value = coordinates[0][1];
		double tempValue = 1.0;
		for (int i = 0; i < tempQuantity; i++)
		{	//Obliczenia wykonane dla rz�du pierwszego
			if (i == 0)
			{	//P�tla przechodz�dza przez wszystkie punkty
				for (int j = 0; j < tempQuantity; j++)
				{	//Obliczenie iloraz�w r�nicowych potrzebnych do kolejnych etap�w algorytmu
					factors[j] = (coordinates[j + 1][1] - coordinates[j][1]) / (coordinates[j + 1][0] - coordinates[j][0]);
					if (j == 0)
					{	//Pierwszy iloraz r�nicowy w tym rz�dzie jest wykorzystany we wzorze na wielomian
						value = value + factors[j] * (x - coordinates[0][0]);
					}
				}
			}
			else //Obliczenia wykonane dla reszy rz�d�w
			{	//P�tla przechodz�ca przez wszystkie wcze�niej policzone ilorazy r�nicowe
				for (int k = 0; k < tempQuantity - i; k++)
				{	//Obliczenie iloraz�w r�nicowych
					factors[k] = (factors[k + 1] - factors[k]) / (coordinates[k + i + 1][0] - coordinates[k][0]);
					if (k == 0)
					{	//Pierwszy iloraz r�nicowy w ka�dym rz�dzie jest wykorzystany we wzorze na wielomian
						//Doliczenie odpowiedniego ilorazu do zmiennej tymczasowej, kt�ra p�niej zostanie dodana
						//do zmiennej value
						tempValue = tempValue * factors[k];
						//P�tla przechodz�ca i razy w celu policzenia odpowiedniej ilo�ci razy 
						//r�wnania: (x-x0)(x-x1)*...*(x-xn-1)
						for (int m = 0; m <= i; m++)
						{
							tempValue = tempValue * (x - coordinates[m][0]);
						}
						//Aktualizacja warto�ci
						value = value + tempValue;
						//Wyzerowanie zmiennej pomocniczej
						tempValue = 1.0;
					}
				}
			}
		}
		return value;
	}
}