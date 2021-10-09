#include "Approximations.h"

namespace MathLibrary
{
	std::vector<double> Approximation::leastSquaresApproximation(std::vector<std::vector<double>> points)
	{
		//Pobranie iloœci dostarczonych punktów
		int numberOfPoints = points.size();

		//Je¿eli nie dostarczono minimum 2 punktów to program jest przerywany
		if (numberOfPoints < 2)
		{
			std::cout << "You have to provide atleat 2 points!" << std::endl;
			exit(-1);
		}

		//Utworzenie zmiennych przechowuj¹cych wyniki
		double a = 0, b = 0, R = 0;
		std::vector<double> results;

		//Utworzenie zmiennych pomocniczych
		double h1 = 0, h2 = 0, h3 = 0, h4 = 0, h5 = 0;

		//Pêtla przechodz¹ca przez odpowiedni¹ iloœc punktów
		for (int i = 0; i < numberOfPoints; i++)
		{
			//wymagane sprawdzenie, czy do programu zosta³y
			//przekazane wspó³rzêdne x i y
			if (points[i].size() != 2)
			{
				//Je¿eli nie to program jest przerywany
				std::cout << "You have to insert correct coords!" << std::endl;
				exit(-1);
			}

			//Policzenie odpowiednich sum, które
			//zostan¹ wykorzystane we wzorze
			h1 += points[i][0] * points[i][1];
			h2 += points[i][0];
			h3 += points[i][1];
			h4 += pow(points[i][0], 2);
			h5 += pow(points[i][1], 2);
		}

		//Obliczenie liczników i mianowników do wzorów
		double upper = numberOfPoints * h1 - h2 * h3;
		double lower = numberOfPoints * h4 - pow(h2, 2);
		double lower2 = numberOfPoints * h5 - pow(h3, 2);

		//Obliczenie liczby przy x
		a = upper / lower;
		//Obliczenie wyrazu wolnego
		b = (h3 * h4 - h2 * h1) / lower;
		//Obliczeni wspó³czynnika korelacji
		R = upper / (sqrt(lower) * sqrt(lower2));

		//Saving result to the result vector
		results.push_back(a);
		results.push_back(b);
		results.push_back(R);

		return results;
	}

	std::vector<double> Approximation::leastSquaresPolynomialApproximation(std::vector<double> x, std::vector<double> y, int degree)
	{
		//Zabezpieczenia przeciw dostarczeniu niew³aœciwych danych
		if (x.size() == 0 || y.size() == 0)
		{
			std::cout << "The size of x and y arrays must be greater than 0" << std::endl;
			exit(-1);
		}
		if (x.size() != y.size())
		{
			std::cout << "The size of x and y arrays are not equal" << std::endl;
			exit(-2);
		}

		//Pobranie iloœci punktów
		size_t numberOfPoints = x.size();

		//Zarezerowanie miejsca na wartoœci sigmy (xi^2n)
		std::vector<double> sigma(2 * degree + 1);

		//Obliczenie sumy x, które s¹ podniesione do kwadratów
		for (int i = 0; i < 2 * degree + 1; i++)
		{
			sigma[i] = 0;
			for (int j = 0; j < numberOfPoints; j++)
			{
				sigma[i] += pow(x[j], i);
			}
		}

		//Macierz przechowuj¹ca równanie
		std::vector<std::vector<double>> B(degree + 1, std::vector<double>(degree + 2));

		//Przepisanie wyliczonych sum do macierzy
		for (int i = 0; i <= degree; i++)
		{
			for (int j = 0; j <= degree; j++)
			{
				B[i][j] = sigma[i + j];
			}
		}

		//Wektor przechowuj¹cy wartoœci sigmy (xi^n *yi)
		std::vector<double> Y(degree + 1);

		//Obliczenie sumy y
		for (int i = 0; i < degree + 1; i++)
		{
			Y[i] = 0;
			for (int j = 0; j < numberOfPoints; j++)
			{
				Y[i] += pow(x[j], i) * y[j];
			}
		}

		//Zapisanie wartoœci Y jako ostatni¹ kolumne w macierzy B
		for (int i = 0; i <= degree; i++)
		{
			B[i][degree + 1] = Y[i];
		}

		//Potrzebne zmienne
		degree += 1;
		double tmp;

		//Wypisanie obliczonej macierzy
		std::cout << "Macierz:" << std::endl;
		for (int i = 0; i < degree; i++)
		{
			for (int j = 0; j <= degree; j++)
				std::cout << B[i][j] << "  ";
			std::cout << std::endl;
		}

		//Rozwi¹zanie uk³adu równañ metod¹ eliminacji Gaussa

		//Transformacja macierzy
		for (int i = 0; i < degree; i++)
		{
			for (int k = i + 1; k < degree; k++)
			{
				if (B[i][i] < B[k][i])
					for (int j = 0; j <= degree; j++)
					{
						tmp = B[i][j];
						B[i][j] = B[k][j];
						B[k][j] = tmp;
					}
			}
		}

		//Wykonanie eliminacji Gaussa
		for (int i = 0; i < (degree - 1); i++)
		{
			for (int k = i + 1; k < degree; k++)
			{
				double t = B[k][i] / B[i][i];
				for (int j = 0; j <= degree; j++)
					B[k][j] -= t * B[i][j];
			}
		}

		//Wektor przechowuj¹cy koñcowe wartoœci
		std::vector<double> a(degree);

		//Zapisanie poprawnych wyników do wektora koñcowego
		for (int i = degree - 1; i >= 0; i--)
		{
			a[i] = B[i][degree];
			for (int j = 0; j < degree; j++)
			{
				if (j != i)
					a[i] -= B[i][j] * a[j];
			}
			a[i] = a[i] / B[i][i];
		}

		//Zwrócenie wektora koñcowego
		return a;
	}
}