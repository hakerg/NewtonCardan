// NewtonCardan.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <math.h>
#include <vector>


double F3(double x, double a, double b, double c, double d)
{
	return d + x * (c + x * (b + x * a));
}

double FPrim3(double x, double a, double b, double c)
{
	return 3 * x*(a*x + 2 * b) + c;
}


double Newton(double a, double b, double c, double d, double x, double tolerance, unsigned maxIterations, unsigned * iterations)
{
	*iterations = 0;
	double fx = F3(x, a, b, c, d);
	while (abs(fx) > tolerance && *iterations < maxIterations)
	{
		x = x - fx / FPrim3(x, a, b, c);
		fx = F3(x, a, b, c, d);
		(*iterations)++;
	}
	return x;
}


std::vector<double> Cardano(double a, double b, double c, double d)
{
	std::vector<double> solutions;

	double f = c / a - b * b / (3 * a*a);
	double g = 2 * b*b*b / (27 * a*a*a) - b * c / (3 * a*a) + d / a;
	double h = g * g / 4 + f * f*f / 27;

	if (h > 0)
	{
		solutions.push_back(cbrt(-g / 2 + sqrt(h)) + cbrt(-g / 2 - sqrt(h)) - b / (3 * a));
	}
	else if (f == 0 && g == 0)
	{
		double x = -cbrt(d / a);
		solutions.push_back(x);
		solutions.push_back(x);
		solutions.push_back(x);
	}
	else
	{
		double i = sqrt(g*g / 4 - h);
		double j = cbrt(i);
		double k = acos(-g / (2 * i));
		double m = cos(k / 3);
		double n = sqrt(3)*sin(k / 3);
		double p = -b / (3 * a);
		solutions.push_back(2 * j*m + p);
		solutions.push_back(-j * (m + n) + p);
		solutions.push_back(-j * (m - n) + p);
	}

	return solutions;
}


int main()
{
	double a, b, c, d, x0, tolerance;
	unsigned iterations;

	std::cout << "a = "; std::cin >> a;
	std::cout << "b = "; std::cin >> b;
	std::cout << "c = "; std::cin >> c;
	std::cout << "d = "; std::cin >> d;
	std::cout << "x0 = "; std::cin >> x0;
	std::cout << "tolerance = "; std::cin >> tolerance;
	std::cout << std::endl << "f(x) = " << a << "x^3 + " << b << "x^2 + " << c << "x + " << d << " = 0\n";
	x0 = Newton(a, b, c, d, x0, tolerance, 1000000, &iterations);
	std::cout << "x = " << x0 << std::endl;
	std::cout << "iteracje: " << iterations << std::endl;
	std::cout << "\nWg metody Cardano:\n";
	auto roots = Cardano(a, b, c, d);
	for (auto r : roots)
	{
		std::cout << "x = " << r << std::endl;
	}
	double error = abs(roots[0] - x0);
	for (int n = 1; n < roots.size(); n++)
	{
		double t = abs(roots[n] - x0);
		if (t < error) error = t;
	}
	std::cout << "\nblad: " << error << std::endl;

	system("pause");
	return 0;
}

