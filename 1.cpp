#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

const double EPS = 1e-9;

int main()
{
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);

	int n;
	cin >> n;
	vector<vector<double>> a(n);
	for (int i = 0; i < n; i++) {
		a[i].resize(n + 1);
		for (int j = 0; j <= n; j++) cin >> a[i][j];
	}
	cout << "Исходная матрица\n\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) cout << fixed << setprecision(4) << setw(10) << (abs(a[i][j]) < EPS ? abs(a[i][j]) : a[i][j]) << " ";
		cout << "| " << fixed << setprecision(4) << setw(10) << (abs(a[i][n]) < EPS ? abs(a[i][n]) : a[i][n]) << "\n";
	}
	cout << "\n";

	vector<int> flag(n + 1, 0);

	for (int col = 0, row = 0; col < n && row < n; col++) {
		int sel = row;
		for (int i = row; i < n; i++)
			if (abs(a[i][col]) > abs(a[sel][col]))
				sel = i;
		if (abs(a[sel][col]) < EPS)
			continue;
		for (int i = col; i <= n; i++)
			swap(a[sel][i], a[row][i]);
		flag[col] = 1;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) cout << fixed << setprecision(4) << setw(10) << (abs(a[i][j]) < EPS ? abs(a[i][j]) : a[i][j]) << " ";
			cout << "| " << fixed << setprecision(4) << setw(10) << (abs(a[i][n]) < EPS ? abs(a[i][n]) : a[i][n]) << "\n";
		}
		cout << "\n";

		double del = a[row][col];
		for (int i = col; i <= n; i++)
			a[row][i] /= del;

		for (int i = 0; i < n; i++)
			if (i != row) {
				double c = a[i][col] / a[row][col];
				for (int j = col; j <= n; j++)
					a[i][j] -= a[row][j] * c;
			}
		++row;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) cout << fixed << setprecision(4) << setw(10) << (abs(a[i][j]) < EPS ? abs(a[i][j]) : a[i][j]) << " ";
			cout << "| " << fixed << setprecision(4) << setw(10) << (abs(a[i][n]) < EPS ? abs(a[i][n]) : a[i][n]) << "\n";
		}
		cout << "\n";
	}

	bool infinity = false;
	vector<int> free;
	vector<double> ans(n, 0);
	for (int i = 0; i < n; i++)
		if (flag[i])
			ans[i] = a[i][n] / a[i][i];
		else {
			infinity = true;
			free.push_back(i + 1);
		}

	for (int i = 0; i < n; i++) {
		double sum = 0;
		for (int j = 0; j < n; j++)
			sum += ans[j] * a[i][j];
		if (abs(sum - a[i][n]) > EPS) {
			cout << "Нет решений";
			return 0;
		}		
	}
	
	if (!infinity) {
		cout << "1 решение\n";
		for (int i = 0; i < n; i++) cout << "x" << i + 1 << " = " << fixed << setprecision(4) << setw(10) << (abs(ans[i]) < EPS ? abs(ans[i]) : ans[i]) << endl;
		return 0;
	}

	cout << Бесконеченое число решений\n";
	for (int i = 0; i < n; i++)
		if (flag[i]) {
			cout << "x" << i + 1 << " = ";
			for (int j = 0; j < n; j++)
				if (!flag[j])
					cout << fixed << setprecision(4) << setw(10) << (a[i][j] / a[i][i]) * (-1) << "x" << j + 1 << " + ";
			cout << fixed << setprecision(4) << setw(10) << a[i][n] / a[i][i] << "\n";
		}
		else cout << "x" << i + 1 << " = x" << i + 1 << "\n";

	sort(free.begin(), free.end());
	cout << "где ";
	for (int i = 0; i < free.size() - 1; i++)
		cout << "x" << free[i] << ", ";
	cout << "x" << free[free.size() - 1] << (free.size() == 1 ? " - свободное значение" : " - свободные значения");

	return 0;
}

/*
4
-2 3 3 -3 7
0 0 0 0 0
6 4 1 0 5
4 7 4 -3 12
*/