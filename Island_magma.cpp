#include <iostream>
#include <vector>
#include "island.h"
#include <limits>
#include <filesystem>
#include <fstream>
using namespace std;
namespace fs = std::filesystem;

int N, M; // Переменные для ввода границ карты
bool outputMode = true; // Вспомогательная переменная, служащая для определения режима вывода(true - вывод и в консоль, и в файл, false - вывод 

//Пути к директориям вводных, ожидаемых и результирующих файлов
const string inputDirectory = "Input_Files/";
const string expectedDirectory = "Expected_Files/";
const string outputDirectory = "Result_Files/";

string createdFile; // Переменная включающая расположение и название результирующего файла 
vector<vector<char>> island; // Вектор для карты
vector<vector<bool>> visited; // Вспомогательный вектор для отметки посещенных ячеек

int main() {
	char choice;
	setlocale(LC_ALL, "Russian");

	while (true) {
		cout << "Для чтения входных данных их файла введите F, для ручного ввода введите C. Для запуска тестов введите T\n";
		cin >> choice;

		if (choice == 'F' || choice == 'f') {
			cout << "Доступные файлы в папке Input_Files:" << endl;
			listFilesInDirectory(inputDirectory);

			while (true) {
				cout << "Выберите номер файла для чтения (1, 2, и т.д.): ";
				cin >> choice;
				int fileIndex = choice - '0';
				string selectedFile = inputDirectory + "Input" + to_string(fileIndex) + ".txt";
				createdFile = outputDirectory + "Result" + to_string(fileIndex) + ".txt";

				if (fs::exists(selectedFile)) {
					if (inputFile(selectedFile))
						continue;
					else
						cout << "Также был сформирован файл с результатом выполнения Result" << to_string(fileIndex) << ".txt\n";
					break;

				}
				else {
					cout << "Файл с номером " << fileIndex << " не найден. Попробуйте снова." << endl;
				}
			}
			break;
		}
		else if (choice == 'C' || choice == 'c') {
			createdFile = outputDirectory + "Result_Output.txt";
			inputConsole();
			cout << "Также был сформирован файл с результатом выполнения Result_Output.txt\n";
			break;
		}
		else if (choice == 'T' || choice == 't') {
			outputMode = false;
			runTests();
			break;
		}
		else {
			cout << "Введите корректное значение.\n";
		}
	}
	//Поиск "Земли" и создание границ вокруг неё
	if (outputMode)
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (island[i][j] == land && !visited[i][j]) {
				createBoarder(i, j);
			}
		}
	}
	if (outputMode)
	output();
	system("PAUSE");
	return 0;

}

// Функция вывода файлов из каталога
void listFilesInDirectory(const string& directory) {
	int index = 1;
	for (const auto& entry : fs::directory_iterator(directory)) {
		cout << index << ". " << entry.path().filename().string() << endl;
		index++;
	}
}

// Функция проверяющая соответствие результата обработки вводных данных из файлов с ожидаемым результатом
void runTests() {
	int index = 1;
	for (const auto& entry : fs::directory_iterator(inputDirectory)) {
		
		string expectedFileName = expectedDirectory + "Expected" + to_string(index) + ".txt";
		string resultFileName = outputDirectory + "Result" + to_string(index) + ".txt";
		
		string selectedFile = inputDirectory + "Input" + to_string(index) + ".txt";
		createdFile = outputDirectory + "Result" + to_string(index) + ".txt";
		if (!inputFile(selectedFile)) {

			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < M; ++j) {
					if (island[i][j] == land && !visited[i][j]) {
						createBoarder(i, j);
					}
				}
			}
			output();
		}
		ifstream expectedFile(expectedFileName);
		ifstream resultFile(resultFileName);

		string expectedLine, resultLine;
		bool passed = true;
		
		while (getline(expectedFile, expectedLine) && getline(resultFile, resultLine)) {
			if (expectedLine != resultLine) {
				passed = false;
				break;
			}
		}
		
		if (passed) {
			cout << "Тест " << index << ": Пройден успешно" << endl;
		}
		else {
			cout << "Тест " << index << ": Не пройден. Ожидаемый и фактический результаты не совпадают." << endl;
		}
		
		index++;
		expectedFile.close();
		resultFile.close();
	}
	cout << "Посмотреть причины непройденных тестов вы можете в разделе вывода файлов (Result_Files)"<< endl;
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
int inputFile(const string& inputFilename) {
	ifstream file(inputFilename);
	ofstream result(createdFile);
	if (!file.is_open()) {
		cerr << "Не удалось открыть файл " << inputFilename << std::endl;
		return 1;
	}

	while (true) {
		file >> N >> M;
		if (!isValidInput() || file.fail()) {
			//system("cls");
			if (outputMode)
				cout << "\033[31mЗначения M или N некорректны! \033[0m\n";
			result << "Значения M или N некорректны! \n";
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
			if (outputMode)
				cout << "\033[31mВведенная карта острова некорректна \033[0m\n";
			result << "Введенная карта острова некорректна \n";
			file.seekg(0, ios::end);
			file.clear();
			return 1;
		}
		else break;
	}
	file.close();
	result.close();
	return 0;
}
// Вывод результатов обработки острова
void output()
{
	ofstream result(createdFile);
	if (outputMode)
	cout << "Координаты границ острова:\n";
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (island[i][j] == border) {
				if (outputMode) {
					printf("[%d;%d]", i + 1, j + 1);
					cout << "\n";
				}
				result << "[" << i + 1 << " " << j + 1 << "]\n";
			}
		}
	}
	if (outputMode)
		cout << "Карта острова:\n";
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (island[i][j] == land) {
				if (outputMode)
					printf("\033[31m%2c\033[0m", island[i][j]);
				result << island[i][j];
			}
			else if (island[i][j] == border) {
				if (outputMode)
					printf("\033[32m%2c\033[0m", island[i][j]);
				result << island[i][j];
			}
			else {
				if (outputMode)
					printf("%2c", island[i][j]);
				result << island[i][j];
			}
		}
		if (outputMode)
			cout << "\n";
		result << "\n";
	}
	result.close();
}

