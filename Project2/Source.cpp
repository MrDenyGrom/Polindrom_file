#include <iostream>
#include <fstream>
#include <string>

using namespace std;
string createFile();
bool fileExists(string&);
bool isPalindrome(string&);
void processFile(string&, string&);
void printFile(string& filename);

string createFile() {
	string filename;
	cout << "Введите имя файла: ";
	cin >> filename;
	ofstream file(filename);
	if (file.is_open()) {
		cout << "Файл " << filename << " успешно создан." << endl;
		cout << "Введите строки для записи в файл (введите пустую строку для завершения):" << endl;
			string line;
		cin.ignore();
		while (true) {
			getline(cin, line);
			if (line.empty())
				break;
			file << line << endl;
		}
		file.close();
		return filename;
	}
	else {
		cout << "Ошибка при создании файла." << endl;
		return "";
	}
}
bool fileExists(string& filename) {
	ifstream file(filename);
	return file.good();
}
bool isPalindrome(string& word) {
	int left = 0;
	int right = word.size() - 1;
	while (left < right) {
		if (tolower(word[left]) != tolower(word[right])) {
			return false;
		}
		++left;
		--right;
	}
	return true;
}
void processFile(string& inputFilename, string& outputFilename) {
	ifstream inputFile(inputFilename);
	ofstream outputFile(outputFilename);
		if (inputFile.is_open() && outputFile.is_open()) {
			string line;
			int wordCount = 1;
			bool firstWord = true;
			while (getline(inputFile, line)) {
				string word;
				for (char c : line) {
					if (isalpha(c)) {
						word += c;
					}
					else if (!word.empty()) {
						if (isPalindrome(word)) {
							if (!firstWord) {
								outputFile << ", ";
							}
							outputFile << wordCount << " - " << word;
							wordCount++;
							firstWord = false;
						}
						word.clear();
					}
				}
				if (!word.empty() && isPalindrome(word)) {
					if (!firstWord) {
						outputFile << ", ";
					}
					outputFile << wordCount << " - " << word;
					wordCount++;
					firstWord = false;
				}
			}
			inputFile.close();
			outputFile.close();
			cout << "Файл успешно обработан. Результат записан в " << outputFilename <<
				endl;
		}
		else {
			cout << "Ошибка при открытии файлов." << endl;
		}
}
void printFile(string& filename) {
	ifstream file(filename);
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			cout << line << endl;
		}
		file.close();
	}
	else {
		cout << "Ошибка при открытии файла " << filename << endl;
	}
}
int main() {
	setlocale(LC_ALL, "Russian");
	string inputFilename, outputFilename;
	cout << "Введите имя входного файла: ";
	cin >> inputFilename;
		if (!fileExists(inputFilename)) {
			cout << "Входной файл не найден. Создать новый файл? (y/n): ";
			char answer;
			cin >> answer;
			if (tolower(answer) == 'y') {
				inputFilename = createFile();
				if (inputFilename.empty()) {
					cout << "Попробуйте занаво(\n" << endl;
					main();
				}
			}
			else {
				cout << "Попробуйте ещё!\n" << endl;
				main();
			}
		}
	cout << "Введите имя выходного файла: ";
	cin >> outputFilename;
	processFile(inputFilename, outputFilename);
	cout << "Содержимое выходного файла:" << endl;
	printFile(outputFilename);
	return 0;
}
