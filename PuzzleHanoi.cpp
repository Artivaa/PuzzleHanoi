
#include <iostream>
#include <locale.h>

using namespace std;

// Константы для стержней
const char ROD_A = 'A';
const char ROD_B = 'B';
const char ROD_C = 'C';

// Глобальные переменные для стержней и их размеров
int* rods[3];
int sizes[3] = { 0, 0, 0 };

// Функция для получения индекса стержня по его имени
int getRodIndex(char rod) {
    if (rod >= ROD_A && rod <= ROD_C) {
        return rod - ROD_A;
    }
    return -1; // Недопустимый стержень
}

// Функция для отображения состояния стержней
void displayRods() {
    for (int i = 0; i < 3; ++i) {
        cout << "Стержень " << (char)(ROD_A + i) << ":";
        if (sizes[i] == 0) {
            cout << " (пусто)" << endl;
        }
        else {
            cout << endl;
            for (int j = sizes[i] - 1; j >= 0; --j) {
                for (int k = 0; k < rods[i][j]; ++k) {
                    cout << '*';
                }
                cout << endl;
            }
        }
    }
    cout << "-----" << endl;
}

// Функция для перемещения диска между стержнями
bool moveDisk(char fromRod, char toRod) {
    int from = getRodIndex(fromRod);
    int to = getRodIndex(toRod);

    // Проверка на корректность стержней
    if (from == -1 || to == -1) {
        cerr << "Ошибка: Недопустимый стержень." << endl; return false;
    }
    // Проверка, что исходный стержень не пуст
    if (sizes[from] == 0) {
        cerr << "Ошибка: Стержень " << fromRod << " пуст." << endl; return false;
    }
    // Проверка правила: больший диск не должен ложиться на меньший
    if (sizes[to] > 0) {
        if (rods[from][sizes[from] - 1] > rods[to][sizes[to] - 1]) {
            cerr << "Ошибка: Нельзя переместить больший диск ("
                << rods[from][sizes[from] - 1]
                << ") на меньший ("
                << rods[to][sizes[to] - 1] << ")." << endl;
            return false;
        }
    }


    // Перемещаем верхний диск
    int disk = rods[from][sizes[from] - 1];
    rods[to][sizes[to]++] = disk;
    sizes[from]--;

    // Выводим действие и состояние
    cout << "Переместить диск " << disk << " с стержня " << fromRod << " на стержень " << toRod << endl;
    displayRods();
    return true;
}

// Рекурсивное решение Ханойской башни
void solveHanoi(int numDisks, char sourceRod, char targetRod, char auxRod) {
    if (numDisks > 0) {
        // Шаг 1: Переместить n-1 дисков с source на auxiliary
        solveHanoi(numDisks - 1, sourceRod, auxRod, targetRod);
        // Шаг 2: Переместить n-й диск с source на target
        moveDisk(sourceRod, targetRod);
        // Шаг 3: Переместить n-1 дисков с auxiliary на target
        solveHanoi(numDisks - 1, auxRod, targetRod, sourceRod);
    }
}

// Главная функция: настройка и решение Ханойской башни
int main() {
    setlocale(LC_ALL, "ru_RU");

    cout << "--- Решение Ханойской башни ---" << endl;
    int numDisks;
    cout << "Введите количество дисков: ";
    cin >> numDisks;

    // Проверка корректности ввода
    if (numDisks <= 0) {
        cerr << "Ошибка: Количество дисков должно быть положительным целым числом." << endl;
        return 1;
    }

    // Выделяем память для стержней
    for (int i = 0; i < 3; ++i) {
        rods[i] = new int[numDisks];
    }

    // Инициализируем стержень A
    sizes[0] = numDisks;
    sizes[1] = 0;
    sizes[2] = 0;
    for (int i = 0; i < numDisks; ++i) {
        rods[0][i] = numDisks - i;
    }

    // Отображаем начальное состояние
    cout << endl << "Начальное состояние:" << endl;
    displayRods();

    // Решаем задачу
    solveHanoi(numDisks, ROD_A, ROD_C, ROD_B);

    // Освобождаем память
    for (int i = 0; i < 3; ++i) {
        delete[] rods[i];
        rods[i] = nullptr;
    }

    cout << endl << "--- Решение завершено ---" << endl;
    return 0;
}