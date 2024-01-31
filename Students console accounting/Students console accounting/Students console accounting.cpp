#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>
#include <fstream> // работа с фаилами
#include <conio.h> // 47 строчка

struct Student {
	std::string name;
	int age = 0;
	float avg = 0.0f;
};
void saveStudents(const std::vector<Student>& students) {
	std::ofstream outputFile("Students.txt", std::ios::app);

	if (outputFile.is_open()) {
		for (const auto& student : students) {
			outputFile << "Имя: " << student.name << "\n";
			outputFile << "Возраст: " << student.age << "\n";
			outputFile << "Средний балл: " << student.avg << "\n";
			outputFile << "----------------------" << "\n";

		}

		outputFile.close();
		std::cout << "Список студентов успешно сохранен в файле students.txt\n";
		Sleep(1500);
		system("cls");
	}
	else {
		std::cout << "Не удалось открыть файл для сохранения\n";
		Sleep(1500);
		system("cls");
	}
}
void addStudent(std::vector<Student>& students) {
	Student newStudent;
	system("cls");
	std::cout << "Введите имя студента: ";
	std::cin >> newStudent.name;
	std::cout << "Введите возраст студента: ";
	std::cin >> newStudent.age;
	std::cout << "Введите средний балл студента: ";
	std::cin >> newStudent.avg;
	if (newStudent.avg > 5.0) {
		std::cout << "Балл не может быть больше 5.00\n";
		Sleep(2000);
		system("cls");
	}
	else {
		students.push_back(newStudent);
		std::cout << "Студент успешно добавлен!\n";
		saveStudents(students);
		Sleep(1500);
		system("cls");
	}

}
void printStudentsFromFile() {
	std::ifstream inputFile("Students.txt");

	if (inputFile.is_open()) {
		system("cls");
		char ch;
		while (inputFile.get(ch)) {
			std::cout << ch;
		}
		inputFile.close();
		std::cout << "\nНажмите Enter для выхода в меню.";

		// Ожидание нажатия клавиши Enter
		while (_getch() != 13) {}
		system("cls");
	}
	else {
		system("cls");
		std::cout << "Не удалось открыть файл для чтения\n";
		Sleep(1500);
		system("cls");
	}
}
void removeStudent(std::vector<Student>& students) {
	std::string name;
	std::vector<Student>::iterator it;
	printStudentsFromFile();
	std::cout << "Введите имя студента, которого хотите удалить: ";
	std::cin >> name;
	it = std::find_if(students.begin(), students.end(), [&name](const Student& student) {
		return student.name == name;
		});
	if (it != students.end()) {
		students.erase(it);
		std::cout << "Студент успешно удален!\n";
		Sleep(1500);
		system("cls");
	}
	else {
		std::cout << "Студент не найден.\n";
		Sleep(1500);
		system("cls");
	}
}
void sortStudentsByAvg() {
	std::ifstream inputFile("Students.txt");
	std::vector<Student> students;

	if (inputFile.is_open()) {
		while (true) {
			Student student;
			std::string temp;


			std::getline(inputFile, temp);
			if (temp.empty()) break; 
			student.name = temp.substr(temp.find(":") + 2);

			std::getline(inputFile, temp);
			student.age = std::stoi(temp.substr(temp.find(":") + 2));


			std::getline(inputFile, temp);
			student.avg = std::stof(temp.substr(temp.find(":") + 2));

			std::getline(inputFile, temp);

			students.push_back(student);
		}

		inputFile.close();

		std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
			return a.avg > b.avg;
			});

		system("cls");
		std::cout << "Студенты отсортированы по среднему баллу:\n";
		for (const auto& student : students) {
			std::cout << "Имя: " << student.name << "\n";
			std::cout << "Возраст: " << student.age << "\n";
			std::cout << "Средний балл: " << student.avg << "\n";
			std::cout << "----------------------" << "\n";
		}

		std::cout << "\nНажмите Enter для выхода в меню.";
		// Ожидание нажатия клавиши Enter
		while (_getch() != 13) {}
		system("cls");
	}
	else {
		system("cls");
		std::cout << "Не удалось открыть файл для чтения\n";
		Sleep(1500);
		system("cls");
	}
}
void sortStudentsByName(std::vector<Student>& students) {
	system("cls");
	std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
		return a.name < b.name;
		});
	std::cout << "Студенты отсортированы по имени:\n";
	printStudentsFromFile();; // Выводим отсортированный список студентов
	system("cls");
}
void loadStudents(std::vector<Student>& students) {
	std::ifstream inputfile("Students.txt");

	if (inputfile.is_open()) {
		system("cls");
		char ch;
		while (inputfile.get(ch)) {
			std::cout << ch;
		}
		inputfile.close();
		std::cout << "Нажмите Enter для выхода в меню.";

		// Ожидание нажатия клавиши Enter
		while (_getch() != 13) {}
		std::cout << "\nСписок студентов успешно загружен из файла students.txt\n";
		system("cls");
	}
	else {
		system("cls");
		std::cout << "Не удалось открыть файл для загрузки\n";
		Sleep(1500);
		system("cls");
	}
}
int main()
{

	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
	setlocale(LC_ALL, "Rus");
	std::vector<Student> students;
	//loadStudents(students);
	int choise = 0;
	while (true) {
		std::cout << "===================================" << std::endl;
		std::cout << "[1] Посмотреть список всех студентов" << std::endl;
		std::cout << "[2] Cохранить студентов в фаиле" << std::endl;
		std::cout << "[3] Список студентов по среднему баллу" << std::endl;
		std::cout << "[4] Список студентов в алфавитном порядке" << std::endl;
		std::cout << "[5] Добавить студента" << std::endl;
		std::cout << "[6] Удалить студента" << std::endl;
		std::cout << "===================================" << std::endl;
		std::cout << "Выберите категорию: ";// << std::endl;
		std::cin >> choise;
		switch (choise) {
		case 1:
			printStudentsFromFile();;
			break;

		case 2:
			saveStudents(students);
			break;

		case 3:
			sortStudentsByAvg();
			break;

		case 4:
			sortStudentsByName(students);
			break;

		case 5:
			addStudent(students);
			break;

		case 6:
			removeStudent(students);
			break;
		default:
			system("cls");
			break;
		}

	}

}