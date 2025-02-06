#include <iostream>
#include <locale.h>

using namespace std;

// Рекурсивное решение головоломки "Ханойская башня".
void solveHanoi(int numDisks, char sourceRod, char targetRod, char auxiliaryRod)
{
    if (numDisks == 1)
    {
        cout << "Переместить диск 1 с стержня " << sourceRod << " на стержень " << targetRod << endl;
        return;
    }

    // 1. Переместить (n-1) дисков со source на auxiliary
    solveHanoi(numDisks - 1, sourceRod, auxiliaryRod, targetRod);

    // 2. Переместить самый большой диск (n) с source на target
    cout << "Переместить диск " << numDisks << " с стержня " << sourceRod << " на стержень " << targetRod << endl;

    // 3. Переместить (n-1) дисков с auxiliary на target
    solveHanoi(numDisks - 1, auxiliaryRod, targetRod, sourceRod);
}

int main()
{
    
    setlocale(LC_ALL, "ru_RU"); 

    int numDisks;

    cout << "--- Решение Ханойской башни ---" << endl;
    cout << "Введите количество дисков: ";
    cin >> numDisks;

    if (numDisks <= 0)
    {
        cerr << "Ошибка: Количество дисков должно быть положительным целым числом." << endl;
        return 1;
    }

    cout << endl << "Действия для " << numDisks << " дисков:" << endl;
    solveHanoi(numDisks, 'A', 'C', 'B');

    cout << endl << "--- Решение завершено ---" << endl;
    return 0;
}