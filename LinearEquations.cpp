#include "LinearEquations.h"

namespace MathLibrary
{
	double* LinearEquations::gaussElimination(double** tab, int size)
	{
		//Sprawdzenie, czy dostarczona tablica jest macierz� minimum stopnia 1
		if (size < 1)
		{
			std::cout << "Macierz musi byc minimum stopnia 1!" << '\a' << std::endl;
			exit(-1);
		}

		//Sprawdzenie, czy elementy na przekatnej macierzy wynosz� 0
		//Je�eli tak program jest przerywany (zapobieganie dzieleniu przez 0)
		for (int i = 0; i < size; i++)
		{
			if (tab[i][i] == 0)
			{
				std::cout << "Wartosci na przekatnej macierzy nie moga wynosic 0!" << '\a' << std::endl;
				exit(-2);
			}
		}

		//Utworzenie macierzy tymczasowej w celu zapobiegni�ciu
		//utraty danych z oryginalnej macierzy
		double** tempTab = new double* [size];
		for (int i = 0; i < size; i++)
		{
			tempTab[i] = new double[size + 1];
		}

		//Przepisanie danych to macierzy tymczasowej
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size + 1; j++)
			{
				tempTab[i][j] = tab[i][j];
			}
		}

		//Przeprowadzenie eliminacji Gaussa
		//P�tla odpowiadaj�ca za przechodzenie przez kolumny
		for (int i = 0; i < size - 1; i++)
		{
			//P�tla odpowiadaj�ca za przechodzenie przez wiersze
			//zawsze i+1, poniewa� pomijamy pierwszy wiersz
			for (int j = i + 1; j < size; j++)
			{
				//Zmienna przechowuj�ca lewy element macierzy, kt�ra jest obecnie przeliczana
				double temp = tempTab[j][i];
				//P�tla odpowiadaj�ca za przechpdzene przez elementy w jednym wierszu (kolumnami)
				for (int k = i; k < size + 1; k++)
				{
					//Obliczenia wed�ug wzoru
					tempTab[j][k] = tempTab[j][k] - ((temp / tempTab[i][i]) * tempTab[i][k]);
				}
			}
		}

		//Zmienna przechowuj�ca wyniki
		double* results = new double[size];

		//P�tla przechodz�ca od prawego dolnego rogu przekszta�conej macierzy
		//poniewa� tak naj�atwiej wyliczy� x
		for (int i = size - 1; i >= 0; i--)
		{
			//Przepisanie wyrazu wolnego aktualnego wiersza (element b w macierzy)
			results[i] = tempTab[i][size];
			//P�tla przechodz�ca przez kolumny wierszy (wiersze od prawej do lewej)
			for (int j = size - 1; j >= i; j--)
			{
				//Je�eli element nie jest na przek�tnej to mno�ymy
				//go przez wcze�niej wyliczone parametry xn,...,x3,x2
				//i odejmujemy od wyrazu wolnego r�wnania r�wnania
				if (j != i)
				{
					results[i] -= tempTab[i][j] * results[j];
				}
				else
				{
					//Je�eli jest na przek�tnej to znaczy, �e ju� wszystkie 
					//warto�ci przenie�li�my na praw� stron� i je odj�li�my 
					//wi�c wystarczy podzieli� praw� stron� przez warto�� lewej, 
					//aby otrzyma� samego x
					results[i] = results[i] / tempTab[i][j];
				}
			}
		}

		//Zwolnienie pami�cie (usuni�cie macierzy tymczasowej) 
		for (int i = 0; i < size; i++)
		{
			delete[] tempTab[i];
		}
		delete[] tempTab;

		return results;
	}
}