#include <iostream>
#include <vector>
#include "island.h"
#include <limits>
#include <fstream>
using namespace std;


int N, M; // Переменные для ввода границ карты

vector<vector<char>> island; // Вектор для карты
vector<vector<bool>> visited; // Вспомогательный вектор для отметки посещенных ячеек

int main() {
	char choice; 
	setlocale(LC_ALL, "Russian");
	while (true) {
		cout << "Для чтения входных данных их файла введите F, для ручного ввода введите C\n";
		cin >> choice;

		if (choice == 'F' || choice == 'f') {
			if (inputFile("../Island1/Input_Files/Input.txt"))
				continue;
			break;
		}
		else if (choice == 'C' || choice == 'c') {
			inputConsole();
			break;
		}
		else {
			cout << "Введите корректное значение.\n";
		}
	}
	//Поиск "Земли" и создание границ вокруг неё
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (island[i][j] == land && !visited[i][j]) {
				createBoarder(i, j);
			}
		}
	}
	output();
	system("PAUSE");
	return 0;

}
// Проверка соответствия вводных данных заданным условиям
bool isValid(int x, int y) {
	return x >= 0 && x < N && y >= 0 && y < M;
}
// Проверка корректности и соответствия вводных данных
bool isValidInput() {
	if (!(MinSize <= N && N <= MaxSize) || !(MinSize <= M && M <= MaxSize)) return 0;
	else if (island.size() != 0)
	{
		if (island.size() == N || island[0].size() == M)
			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < M; ++j) {
					if (island[i][j] != water && island[i][j] != land)
						return 0;
				}
			}
	}
	return 1;
}
// Функция создания границ для острова
void createBoarder(int x, int y) {
	visited[x][y] = true;

	int dx[] = { 0, 1, 0, -1, 1, -1, 1, -1 };
	int dy[] = { 1, 0, -1, 0, 1, -1, -1, 1 };
	// Перебор ближайших к ячейке осстрова ячеек и заполнение граничащих 
	for (int i = 0; i < 8; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (isValid(nx, ny) && !visited[nx][ny]) {
			if (island[nx][ny] == water) {
				island[nx][ny] = border;
				//cout << nx + 1 << " " << ny + 1 << endl;
			}
			else if (island[nx][ny] == land) {
				createBoarder(nx, ny);
			}
		}
	}
}
// Функция обработки вводных данных через консоль
void inputConsole()
{
	while (true) {
		cout << "Введите N(3<=N<=100)\n" << endl;
		cin >> N;
		if (cin) {
			cout << "Введите M(3<=M<=100)\n" << endl;
			cin >> M;
		} 
		if (!isValidInput() || cin.fail())
		{
			cin.seekg(0, ios::end);
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			//system("cls");
			printf("\033[31mЗначения M или N некорректны! \033[0m\n");
			continue;
		}
		island.assign(N, vector<char>(M));
		visited.assign(N, vector<bool>(M, false));
		cout << "Введите карту острова\n" << endl;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				cin >> island[i][j];
			}
		}
		if (!isValidInput() || cin.fail())
		{
			//system("cls");
			printf("\033[31mВведенная карта острова некорректна \033[0m\n");
			cin.seekg(0, ios::end);
			cin.clear();
		}
		else break;
	}

}
// Функция обработки вводных данных из файла
int inputFile(const string& filename) {
	ifstream file(filename);
	if (!file.is_open()) {
		cerr << "Не удалось открыть файл " << filename << std::endl;
		return 1;
	}

	while (true) {
		file >> N >> M;
		if (!isValidInput() || file.fail()) {
			//system("cls");
			cout << "\033[31mЗначения M или N некорректны! \033[0m\n";
			file.seekg(0, ios::end);
			file.clear();
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return 1;
		}

		island.assign(N, vector<char>(M));
		visited.assign(N, vector<bool>(M, false));

		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				file >> island[i][j];
			}
		}

		if (!isValidInput() || file.fail()) {
			//system("cls");
			cout << "\033[31mВведенная карта острова некорректна \033[0m\n";
			file.seekg(0, ios::end);
			file.clear();
			return 1;
		}
		else break;
	}
	file.close();
	return 0;
}
// Вывод результатов обработки острова
void output()
{
	cout << "Координаты границ острова:\n";
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (island[i][j] == border) {
				printf("[%d;%d]", i + 1, j + 1);
				cout << "\n";
			}
		}
	}
	cout << "Карта острова:\n";
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (island[i][j] == land) {
				printf("\033[31m%2c\033[0m", island[i][j]);
			}
			else if (island[i][j] == border) {
				printf("\033[32m%2c\033[0m", island[i][j]);
			}
			else {
				printf("%2c", island[i][j]);
			}
		}
		cout << "\n";
	}

}

