#include "LinearEquations.h"

namespace MathLibrary
{
	double* LinearEquations::gaussElimination(double** tab, int size)
	{
		//Sprawdzenie, czy dostarczona tablica jest macierz¹ minimum stopnia 1
		if (size < 1)
		{
			std::cout << "Macierz musi byc minimum stopnia 1!" << '\a' << std::endl;
			exit(-1);
		}

		//Sprawdzenie, czy elementy na przekatnej macierzy wynosz¹ 0
		//Je¿eli tak program jest przerywany (zapobieganie dzieleniu przez 0)
		for (int i = 0; i < size; i++)
		{
			if (tab[i][i] == 0)
			{
				std::cout << "Wartosci na przekatnej macierzy nie moga wynosic 0!" << '\a' << std::endl;
				exit(-2);
			}
		}

		//Utworzenie macierzy tymczasowej w celu zapobiegniêciu
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
		//Pêtla odpowiadaj¹ca za przechodzenie przez kolumny
		for (int i = 0; i < size - 1; i++)
		{
			//Pêtla odpowiadaj¹ca za przechodzenie przez wiersze
			//zawsze i+1, poniewa¿ pomijamy pierwszy wiersz
			for (int j = i + 1; j < size; j++)
			{
				//Zmienna przechowuj¹ca lewy element macierzy, która jest obecnie przeliczana
				double temp = tempTab[j][i];
				//Pêtla odpowiadaj¹ca za przechpdzene przez elementy w jednym wierszu (kolumnami)
				for (int k = i; k < size + 1; k++)
				{
					//Obliczenia wed³ug wzoru
					tempTab[j][k] = tempTab[j][k] - ((temp / tempTab[i][i]) * tempTab[i][k]);
				}
			}
		}

		//Zmienna przechowuj¹ca wyniki
		double* results = new double[size];

		//Pêtla przechodz¹ca od prawego dolnego rogu przekszta³conej macierzy
		//poniewa¿ tak naj³atwiej wyliczyæ x
		for (int i = size - 1; i >= 0; i--)
		{
			//Przepisanie wyrazu wolnego aktualnego wiersza (element b w macierzy)
			results[i] = tempTab[i][size];
			//Pêtla przechodz¹ca przez kolumny wierszy (wiersze od prawej do lewej)
			for (int j = size - 1; j >= i; j--)
			{
				//Je¿eli element nie jest na przek¹tnej to mno¿ymy
				//go przez wczeœniej wyliczone parametry xn,...,x3,x2
				//i odejmujemy od wyrazu wolnego równania równania
				if (j != i)
				{
					results[i] -= tempTab[i][j] * results[j];
				}
				else
				{
					//Je¿eli jest na przek¹tnej to znaczy, ¿e ju¿ wszystkie 
					//wartoœci przenieœliœmy na praw¹ stronê i je odjêliœmy 
					//wiêc wystarczy podzieliæ praw¹ stronê przez wartoœæ lewej, 
					//aby otrzymaæ samego x
					results[i] = results[i] / tempTab[i][j];
				}
			}
		}

		//Zwolnienie pamiêcie (usuniêcie macierzy tymczasowej) 
		for (int i = 0; i < size; i++)
		{
			delete[] tempTab[i];
		}
		delete[] tempTab;

		return results;
	}
}