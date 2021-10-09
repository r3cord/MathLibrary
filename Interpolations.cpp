#include "Interpolations.h"

namespace MathLibrary
{
	double Interpolation::lagrangeInterpolation(double** coordinates, int quantity, double x)
	{
		if (quantity < 2) //Sprawdzenie, czy zosta³a podana minimalna iloœæ punktów
		{
			std::cout << "Musisz podac minimum 2 punkty!" << std::endl;
			std::cout << '\a' << std::endl;
			exit(-1);
		}
		double max = std::numeric_limits<double>::lowest(); //Utworzenie maksymalnej liczby, któr¹ obecnie jest najmniejsza mo¿liwa liczba
		double min = std::numeric_limits<double>::max(); //Utworzenie minimalnej liczby, któr¹ obecnie jest najwiêksza mo¿liwa liczba
		for (int i = 0; i < quantity; i++) //Pêtla przechodz¹ca przez ca³¹ tablicê, w której sprawdzam kilka wa¿nych warunków
		{
			if (coordinates[i][0] > max) //Pozyskanie maksymalnej wartoœci przedzia³u
			{
				max = coordinates[i][0];
			}
			if (coordinates[i][0] < min) //Pozyskanie minimalnej wartoœci przedzia³u
			{
				min = coordinates[i][0];
			}
			if (i < quantity - 1)
			{
				if (coordinates[i][0] == coordinates[i + 1][0]) //Sprawdzenie, czy nie istniej¹ dwie takie same wartoœci x (zapobieganie dzieleniu przez 0)
				{
					std::cout << "Podane wartosci sa niewlasciwe. Nie moga byc podane dwie takie same wartosci x (dzielenie przez 0)" << std::endl;
					std::cout << '\a' << std::endl;
					exit(-2);
				}
			}
		}
		if (!((x >= min) && (x <= max))) //Sprawdzenie, czy podana wartoœæ nale¿y do przedzia³u
		{
			std::cout << "Podana wartosc nie jest w przedzialne od xmin do xmax!" << std::endl;
			std::cout << '\a' << std::endl;
			exit(-3);
		}
		double value = 0.0; //Zmienna przechowuj¹ca wynik
		double lagrangeFactor = 1.0; //Zmienna przechowuj¹ca wspó³czynnik lagrange (pocz¹tkowa wartoœæ 1.0, poniewa¿ jest to mnozenie)
		int help = 0; //Zmienna pomocnicza zapobiegaj¹ca przypadku, w którym dzielilibyœmy przez 0
		for (int i = 0; i < quantity; i++) //Pêtla przechodz¹ca przez wszystkie elementy tablicy
		{
			for (int j = 0; j < quantity; j++) //Pêtla przechodz¹ca ponownie przez elementy tablicy, ale bez elmentu i
			{
				if (j != help)
				{
					lagrangeFactor = lagrangeFactor * ((x - coordinates[j][0]) / (coordinates[help][0] - coordinates[j][0])); //Obliczenie wspó³czynnika lagrange'a
				}
			}
			//std::cout << lagrangeFactor << std::endl;
			value = value + lagrangeFactor * coordinates[i][1]; //Obliczenie wartoœci dla obecnego elementu tablicy
			help++; //iteracja zmiennej pomocniczej
			lagrangeFactor = 1.0; //"wyzerowanie" wspó³czynnika lagrange'a
		}
		return value; //Zwrócenie obliczonej wartoœci
	}

	double Interpolation::newtonInterpolation(double** coordinates, int quantity, double x)
	{
		if (quantity < 2) //Sprawdzenie, czy zosta³a podana minimalna iloœæ punktów
		{
			std::cout << "Musisz podac minimum 2 punkty!" << std::endl;
			std::cout << '\a' << std::endl;
			exit(-1);
		}
		double max = std::numeric_limits<double>::lowest(); //Utworzenie maksymalnej liczby, któr¹ obecnie jest najmniejsza mo¿liwa liczba
		double min = std::numeric_limits<double>::max(); //Utworzenie minimalnej liczby, któr¹ obecnie jest najwiêksza mo¿liwa liczba
		for (int i = 0; i < quantity; i++) //Pêtla przechodz¹ca przez ca³¹ tablicê, w której sprawdzam kilka wa¿nych warunków
		{
			if (coordinates[i][0] > max) //Pozyskanie maksymalnej wartoœci przedzia³u
			{
				max = coordinates[i][0];
			}
			if (coordinates[i][0] < min) //Pozyskanie minimalnej wartoœci przedzia³u
			{
				min = coordinates[i][0];
			}
			if (i < quantity - 1)
			{
				if (coordinates[i][0] == coordinates[i + 1][0]) //Sprawdzenie, czy nie istniej¹ dwie takie same wartoœci x (zapobieganie dzieleniu przez 0)
				{
					std::cout << "Podane wartosci sa niewlasciwe. Nie moga byc podane dwie takie same wartosci x (dzielenie przez 0)" << std::endl;
					std::cout << '\a' << std::endl;
					exit(-2);
				}
			}
		}
		if (!((x >= min) && (x <= max))) //Sprawdzenie, czy podana wartoœæ nale¿y do przedzia³u
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
		{	//Obliczenia wykonane dla rzêdu pierwszego
			if (i == 0)
			{	//Pêtla przechodz¹dza przez wszystkie punkty
				for (int j = 0; j < tempQuantity; j++)
				{	//Obliczenie ilorazów ró¿nicowych potrzebnych do kolejnych etapów algorytmu
					factors[j] = (coordinates[j + 1][1] - coordinates[j][1]) / (coordinates[j + 1][0] - coordinates[j][0]);
					if (j == 0)
					{	//Pierwszy iloraz ró¿nicowy w tym rzêdzie jest wykorzystany we wzorze na wielomian
						value = value + factors[j] * (x - coordinates[0][0]);
					}
				}
			}
			else //Obliczenia wykonane dla reszy rzêdów
			{	//Pêtla przechodz¹ca przez wszystkie wczeœniej policzone ilorazy ró¿nicowe
				for (int k = 0; k < tempQuantity - i; k++)
				{	//Obliczenie ilorazów ró¿nicowych
					factors[k] = (factors[k + 1] - factors[k]) / (coordinates[k + i + 1][0] - coordinates[k][0]);
					if (k == 0)
					{	//Pierwszy iloraz ró¿nicowy w ka¿dym rzêdzie jest wykorzystany we wzorze na wielomian
						//Doliczenie odpowiedniego ilorazu do zmiennej tymczasowej, która pó¿niej zostanie dodana
						//do zmiennej value
						tempValue = tempValue * factors[k];
						//Pêtla przechodz¹ca i razy w celu policzenia odpowiedniej iloœci razy 
						//równania: (x-x0)(x-x1)*...*(x-xn-1)
						for (int m = 0; m <= i; m++)
						{
							tempValue = tempValue * (x - coordinates[m][0]);
						}
						//Aktualizacja wartoœci
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