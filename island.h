#ifndef ISLAND_HPP
#define ISLAND_HPP

#include <vector>


// �������, ������������ ��� ������������� ��������� �������
const char water = '.';
const char land = '#';
const char border = '*';

// ����������� � ������������ ������� �������
const int MinSize = 3;
const int MaxSize = 100;

// �������� ������������ ������� ������ �������� ��������
bool isValid(int x, int y);

// �������� ������� �������
void createBoarder(int x, int y);

// �������� ������������ � ������������ ������� ������
bool isValidInput();

// ������� ��������� ������� ������ ����� �������
void inputConsole();

// ������� ��������� ������� ������ �� �����
int inputFile(const std::string& filename);

// ������� ����������� ������������ ���������� ��������� ������� ������ �� ������ � ��������� �����������
void listFilesInDirectory(const std::string& directory);

// ������� ������ ������ �� ��������
void runTests();

// ����� ����������� ��������� �������
void output();

#endif
