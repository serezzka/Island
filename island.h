#ifndef ISLAND_HPP
#define ISLAND_HPP

#include <vector>


// Символы, используемые для представления элементов острова
const char water = '.';
const char land = '#';
const char border = '*';

// Минимальный и максимальный размеры острова
const int MinSize = 3;
const int MaxSize = 100;

// Проверка соответствия вводных данных заданным условиям
bool isValid(int x, int y);

// Создание границы острова
void createBoarder(int x, int y);

// Проверка корректности и соответствия вводных данных
bool isValidInput();

// Функция обработки вводных данных через консоль
void inputConsole();

// Функция обработки вводных данных из файла
int inputFile(const std::string& filename);

// Функция проверяющая соответствие результата обработки вводных данных из файлов с ожидаемым результатом
void listFilesInDirectory(const std::string& directory);

// Функция вывода файлов из каталога
void runTests();

// Вывод результатов обработки острова
void output();

#endif
