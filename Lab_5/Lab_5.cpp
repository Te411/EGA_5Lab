#include <iostream>
#include <vector>
#include <random>
#include <locale.h>
#include <numeric>
using namespace std;
const int N = 5; // число городов

int SearchDistance(vector<int> rowDistance, int& index, vector <int> X) {
	int min = 999;
	int number = 0;
	for (int i = 0; i < X.size(); i++) {
		number = X[i];
		if (min > rowDistance[number] && rowDistance[number] != 0) {
			min = rowDistance[number];
			index = number;
		}
	}
	return min;
}
int main() {
	setlocale(LC_ALL, "rus");
	vector<vector<int>> distance(N, vector<int>(N)); // матрица расстояний
	vector<int> S; // обход городов
	vector<int> Q; // длина обхода
	vector <int> rowDistance;
	int Xi = 0; // текущий город
	int index = 0; // индекс города
	int step = 0; // шаг
	int next = 0; // следующий город
	random_device rd;
	mt19937 gen(rd());

	vector<int> X; //города
	for (int i = 0; i < N; i++) {
		X.push_back(i);
	}
	uniform_int_distribution<> dis(1, 9);
	cout << "Матрица расстояний: " << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == j) {
				distance[i][j] = 0;
				cout << " " << distance[i][j];
			}
			else {
				distance[i][j] = dis(gen);
				cout << " " << distance[i][j];
			}
		}
		cout << endl;
	}
	cout <<"Количество городов: " << X.size()<< endl << endl;
	uniform_int_distribution<>diss(0, N-1);
	index = diss(gen);
	Xi = X[index];
	int FirstCity = Xi;
	X.erase(X.begin() + index);
	S.push_back(Xi);
	while (step < N-1) {
		cout << "Шаг " << step + 1 << endl;

		cout << "Текущий обход:";
		if (S.size() != 0) {
			for (int j = 0; j < S.size(); j++) {
			cout << " " << S[j];
		}
		cout << endl;
		}

		cout << "Выбираемый город: " << Xi << endl;

		cout << "Расстояние от предыдущего до выбранного: ";
		rowDistance = distance[Xi];
		next = SearchDistance(rowDistance, index, X);
		cout << next << endl;

		cout << "Длина текущего обхода: ";
		Q.push_back(next);
		cout << round(accumulate(Q.begin(), Q.end(), 0)) << endl;
		Xi = index;
		for (int k = 0; k < X.size(); k++) {
			if (Xi == X[k]) {
				X.erase(X.begin() + k);
			}
		}
		S.push_back(Xi);
		step++;
	}
	cout << "Шаг " << N << endl;
	cout << "Текущий обход: ";
	for (int city : S) {
		cout << city << " ";
	}
	cout << endl;

	cout << "Возвращаемся в начальный город: " << FirstCity << endl;
	S.push_back(FirstCity );

    cout << "Расстояние до него: " << distance[Xi][FirstCity] << endl;
	Q.push_back(distance[Xi][FirstCity]);

	cout << "Текущая длина обхода: " << round(accumulate(Q.begin(), Q.end(), 0)) << endl;
	cout << endl;

	cout << "Итоговый обход: ";
	for (int city : S) {
		cout << city << " ";
	}
	cout << endl;

	cout << "Итоговый путь: ";
	for (int distance : Q) {
		cout << distance << " ";
	}
	cout << endl;
	cout << "Длина итогового пути: " << round(accumulate(Q.begin(), Q.end(), 0)) << endl;

	return 0;
}