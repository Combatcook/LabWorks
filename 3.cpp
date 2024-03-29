#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

// набор значений №2
const double a = 0;
const double b = 2;
const double c = 0;
const double d = 1;
const int m = 20;
const double eps = 1e-3;

// коэффициенты и узлы для квадратур Гаусса
double gauss_c3[3] = { 5.0/9, 8.0/9, 5.0/9 };
double gauss_x3[3] = { -sqrt(3.0 / 5), 0, sqrt(3.0 / 5) };
double gauss_c4[4] = { 0.347855, 0.652145, 0.652145, 0.347855 };
double gauss_x4[4] = { -0.861136, -0.339981, 0.339981, 0.861136 };

double f(double x, double t) { // 6 вариант
	return sqrt(t / (6 + x*x) + x);
}

double getSumRectangle(int n, double t) { // формула прямоугольников
	double h = (b - a) / n;
	double sum = 0;
	double xi = a;
	for (int i = 0; i < n; i++) {
		sum += f(xi + h/2, t);
		xi += h;
	}
	return h * sum;
}

double getSumTrapeze(int n, double t) { // формула трапеций
	double h = (b - a) / n;
	double sum = 0;
	double xi = a;
	for (int i = 0; i <= n; i++) {
		if (i == 0 || i == n)
			sum += f(xi, t) / 2;
		else
			sum += f(xi, t);
		xi += h;
	}
	return h * sum;
}

double getSumSimpson(int n, double t) { // формула Симпсона
	double h = (b - a) / n;
	double sum = 0;
	double xi = a;
	for (int i = 0; i <= n; i++) {
		if (i == 0 || i == n)
			sum += f(xi, t);
		else if (i % 2 == 1)
			sum += f(xi, t) * 2;
		else
			sum += f(xi, t) * 4;
		xi += h;
	}
	return h * sum / 3;
}

vector<double> ans1, ans2, ans3;

int main()
{
	setlocale(0, "");
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);

	cout << "Метод удвоения числа шагов с использованием квадратурной формулы прямоугольников:\n" << endl;
	double shag = (d - c) / m;
	double tj = c;

	for (int i = 0; i <= m; i++) {
		int N = 2;
		double curSum = getSumRectangle(N, tj);
		double nextSum = getSumRectangle(2 * N, tj);
		while (abs(curSum - nextSum) > eps) {
			curSum = nextSum;
			N *= 2;
			nextSum = getSumRectangle(2 * N, tj);
		}
		cout << setw(2) << i << ") F(" << fixed << setprecision(2) << tj << ") = " << setprecision(4) << curSum << endl;
		ans1.push_back(curSum);
		tj += shag;
	}

	/*----------------------------------------------*/

	cout << "\nКвадратура Гаусса с 3 узлами:\n" << endl;
	tj = c;
	for (int j = 0; j < 3; j++) {
		gauss_c3[j] *= (b - a) / 2;
		gauss_x3[j] = (b - a) / 2 * gauss_x3[j] + (b + a) / 2;
	}

	for (int i = 0; i <= m; i++) {
		double sum = 0;
		for (int j = 0; j < 3; j++)
			sum += f(gauss_x3[j], tj) * gauss_c3[j];
		cout << setw(2) << i << ") F(" << fixed << setprecision(2) << tj << ") = " << setprecision(4) << sum << endl;
		ans2.push_back(sum);
		tj += shag;
	}

	/*----------------------------------------------*/

	cout << "\nКвадратура Гаусса с 4 узлами:\n" << endl;
	tj = c;
	for (int j = 0; j < 4; j++) {
		gauss_c4[j] *= (b - a) / 2;
		gauss_x4[j] = (b - a) / 2 * gauss_x4[j] + (b + a) / 2;
	}

	for (int i = 0; i <= m; i++) {
		double sum = 0;
		for (int j = 0; j < 4; j++)
			sum += f(gauss_x4[j], tj) * gauss_c4[j];
		cout << setw(2) << i << ") F(" << fixed << setprecision(2) << tj << ") = " << setprecision(4) << sum << endl;
		ans3.push_back(sum);
		tj += shag;
	}

	/*----------------------------------------------*/

	cout << "\nСравнительная таблица\n";
	cout << "\n            t        Н.-К.    Гаусс 3    Гаусс 4\n" << endl;
	tj = c;
	for (int i = 0; i <= m; i++) {
		cout << setw(2) << i << ")  " << fixed << setprecision(2) << setw(10) << tj 
			 << " " << setprecision(4) << setw(10) << ans1[i] << " " << setw(10) << ans2[i] << " " << setw(10) << ans3[i] << endl;
		tj += shag;
	}

	return 0;
}