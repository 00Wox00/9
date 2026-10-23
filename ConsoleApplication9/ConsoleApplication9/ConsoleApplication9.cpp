#include <iostream>
#include <ctime>
#include <cstdlib>
#include <clocale>
using namespace std;

#define SIZE 5
#define COMM 50
#define MIN_SUM 1000

void com1(double* data, int size)
{
    for (int i = 0; i < size; i++)
    {
        data[i] = data[i] * 0.99;
    }
}

void com3(double* data, int size)
{
    for (int i = 0; i < size; i++)
    {
        data[i] = data[i] * 0.97;
    }
}

void fixcom(double* data, int size)
{
    for (int i = 0; i < size; i++)
    {
        data[i] = data[i] - COMM;
        if (data[i] < 0)
        {
            data[i] = 0;
        }
    }
}

void com2OverLimit(double* data, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (data[i] >= MIN_SUM)
        {
            data[i] = data[i] * 0.98;
        }
    }
}

void applyProc(double* data, int size, void (*processor)(double*, int))
{
    if (processor != nullptr)
    {
        processor(data, size);
    }
}
void inputData(double* data, double* original, int size)
{
    for (int i = 0; i < size; i++)
    {
        data[i] = rand() % 3000 + 100;
        original[i] = data[i];
    }
}

void printData(double* data, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << data[i] << " ";
    }
    cout << endl;
}

void resetData(double* data, double* original, int size)
{
    for (int i = 0; i < size; i++)
    {
        data[i] = original[i];
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    double data[SIZE] = { 0 };
    double copy[SIZE] = { 0 };

    void (*processors[])(double*, int) = {
        com1,
        com3,
        fixcom,
        com2OverLimit
    };

    void (*processor)(double*, int) = nullptr;

    int menuitem     = 0;
    int number = 0;

    while (menuitem != 5)
    {
        cout << endl;
        cout << "1. Заполнить случайными данными" << endl;
        cout << "2. Показать данные" << endl;
        cout << "3. Выбрать и выполнить обработку" << endl;
        cout << "4. Восстановить исходные данные" << endl;
        cout << "5. Выход" << endl;
        cout << "Выбор: ";
        cin >> menuitem;

        switch (menuitem)
        {
        case 1:
            inputData(data, copy, SIZE);
            break;
        case 2:
            printData(data, SIZE);
            break;
        case 3:
            cout << "1. Комиссия 1%" << endl;
            cout << "2. Комиссия 3%" << endl;
            cout << "3. Фиксированная комиссия (" << COMM << ")" << endl;
            cout << "4. Комиссия 2% для сумм от " << MIN_SUM << endl;
            cout << "Номер операции: ";
            cin >> number;
            if (number >= 1 && number <= 4)
            {
                processor = processors[number - 1];
                cout << "До обработки: ";
                printData(data, SIZE);
                applyProc(data, SIZE, processor);
                cout << "После обработки: ";
                printData(data, SIZE);
            }
            else
            {
                cout << "Неверный номер операции" << endl;
            }
            break;
        case 4:
            resetData(data, copy, SIZE);
            cout << "Данные восстановлены" << endl;
            break;
        case 5:
            cout << "Выход" << endl;
            break;
        default:
            cout << "Неверный пункт меню" << endl;
        }
    }

    return 0;
}