
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <random>
#include <algorithm>
#include <limits>
#include <windows.h>

// Максимальні розміри даних
const int MAX_TASKS = 1000;
const int MAX_TASK_LENGTH = 500;
const int MAX_VARIANTS = 100;
const int MAX_TASKS_PER_VARIANT = 50;

// Масив текстів завдань
char tasks[MAX_TASKS][MAX_TASK_LENGTH];

// Матриця індексів завдань для варіантів
int variants[MAX_VARIANTS][MAX_TASKS_PER_VARIANT];

// Кількість завдань, зчитаних із файлу
int taskCount = 0;

bool loadTasks(const char* filename,char tasks[][MAX_TASK_LENGTH],int& taskCount) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Помилка відкриття файлу: "
                  << filename << '\n';
        return false;
    }
    taskCount = 0;
    std::string line;
    while (std::getline(file, line)) {
        // Пропускаємо порожні рядки
        if (line.find_first_not_of(" \t\r") == std::string::npos) {
            continue;
        }
        // Перевіряємо кількість завдань
        if (taskCount >= MAX_TASKS) {
            std::cerr << "Перевищено максимальну кількість завдань.\n";
            return false;
        }
        // Перевіряємо довжину тексту
        if (line.length() >= MAX_TASK_LENGTH) {
            std::cerr << "Занадто довгий текст завдання.\n";
            return false;
        }
        // Копіюємо текст у масив
        std::strcpy(tasks[taskCount], line.c_str());
        taskCount++;
    }
    if (file.bad()) {
        std::cerr << "Помилка читання файлу.\n";
        return false;
    }
    if (taskCount == 0) {
        std::cerr << "Файл не містить завдань.\n";
        return false;
    }
    return true;
}

int readPositiveInteger(const char* prompt){
    int value;

    std::cout << prompt;
    std::cin >> value;

    return value;
}


int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "Генератор варіантів контрольної роботи\n\n";

    if (!loadTasks("task.txt", tasks, taskCount)) {return 1;}

    std::cout << "Завантажено завдань: "<< taskCount << "\n\n";

    int variantCount = readPositiveInteger("Введіть кількість варіантів: ");

    int tasksPerVariant = readPositiveInteger("Введіть кількість завдань у варіанті: ");

    std::cout << "\nПараметри генерації:\n";
    std::cout << "Кількість варіантів: "<< variantCount << '\n';
    std::cout << "Завдань у кожному варіанті: "<< tasksPerVariant << '\n';
    return 0;
}

