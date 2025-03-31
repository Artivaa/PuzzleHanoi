#include <iostream>
#include <locale.h>

using namespace std;

int getRodIndex(char rod) {
    if (rod < 'A') {
        return -1;
    }
    if (rod > 'C') {
        return -1;
    }
    return rod - 'A';
}


void displayRods(int* sizes, int** rods) {
    for (int i = 0; i < 3; ++i) {
        cout << "Стержень " << (char)('A' + i) << ":";
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

bool moveDisk(char fromRod, char toRod, int* sizes, int** rods) {
    int from = getRodIndex(fromRod);
    int to = getRodIndex(toRod);

    if (from == -1) {
        cerr << "Ошибка: Недопустимый стержень." << endl;
        return false;
    }

    if (to == -1) {
        cerr << "Ошибка: Недопустимый стержень." << endl;
        return false;
    }


    if (sizes[from] == 0) {
        cerr << "Ошибка: Стержень " << fromRod << " пуст." << endl;
        return false;
    }

    if (sizes[to] > 0) {  // Если на столбце 'to' уже есть хотя бы один диск
        if (rods[from][sizes[from] - 1] > rods[to][sizes[to] - 1]) {  // Если диск, который переносится, больше верхнего диска на 'to'
            cerr << "Ошибка: Нельзя переместить больший диск ("
                << rods[from][sizes[from] - 1]
                << ") на меньший ("
                << rods[to][sizes[to] - 1] << ")." << endl;
            return false;
        }
    }


    int disk = rods[from][sizes[from] - 1];
    rods[to][sizes[to]++] = disk;
    sizes[from]--;

    cout << "Переместить диск " << disk << " с стержня " << fromRod
        << " на стержень " << toRod << endl;
    displayRods(sizes, rods);
    return true;
}

void solveHanoi(int numDisks, char sourceRod, char targetRod, char auxRod,
    int* sizes, int** rods) {
    if (numDisks > 0) {
        solveHanoi(numDisks - 1, sourceRod, auxRod, targetRod, sizes, rods);
        moveDisk(sourceRod, targetRod, sizes, rods);
        solveHanoi(numDisks - 1, auxRod, targetRod, sourceRod, sizes, rods);
    }
}

int main() {
    setlocale(LC_ALL, "ru_RU");

    cout << "--- Решение Ханойской башни ---" << endl;
    int numDisks;
    cout << "Введите количество дисков: ";
    cin >> numDisks;

    if (numDisks <= 0) {
        cerr << "Ошибка: Количество дисков должно быть положительным целым числом." << endl;
        return 1;
    }

    int* rods[3];
    int sizes[3] = { numDisks, 0, 0 };

    for (int i = 0; i < 3; ++i) {
        rods[i] = new int[numDisks];
    }

    for (int i = 0; i < numDisks; ++i) {
        rods[0][i] = numDisks - i;
    }

    cout << endl << "Начальное состояние:" << endl;
    displayRods(sizes, rods);

    solveHanoi(numDisks, 'A', 'C', 'B', sizes, rods);

    for (int i = 0; i < 3; ++i) {
        delete[] rods[i];
        rods[i] = nullptr;
    }

    cout << endl << "--- Решение завершено ---" << endl;
    return 0;
}