#include <iostream>
#include <random>
#include <windows.h>
#include <cmath>
#include "thread"
#include "algorithm"
using namespace std;

struct Structure
{
private:
    int sleep_time;
    int* array;
    void DeepCopy(int* array)
    {
        int array_size = _msize(array) / sizeof(int);
        this->array = new int[array_size];
        for (int i = 0; i < array_size; i++)
        {
            this->array[i] = array[i];
        }
    }
public:
    Structure(int sleep_time, int* array)
    {
        this->sleep_time = sleep_time;
        DeepCopy(array);
    }
    int* GetArray()
    {
        return this->array;
    }
    int GetSleepTime()
    {
        return this->sleep_time;
    }
};

int* CreateArray(int size) {
    int* array = new int[size];
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 100;
    }
    return array;
}

DWORD WINAPI getSquareRootSum(LPVOID  structure)
{
    Structure& p = *reinterpret_cast<Structure*>(structure);
    int array_size = _msize(p.GetArray()) / sizeof(int);
    int sum = 0;
    int time = 200;
    for (int i = 0; i < array_size; i++)
    {
        sum += sqrt(p.GetArray()[i]);
        Sleep(time);
    }
    cout << sum;
    return 0;
}

int main()
{
    int size = 0, time = 0;
    cout << "Enter the size of array: ";
    cin >> size;
    cout << "Enter the time in milliseconds:";
    cin >> time;
    int* array = CreateArray(size);
    cout << "Array: ";
    for (int i = 0; i < size; i++)
    {
        cout << array[i] << " ";
    }
    cout << "\n";
    Structure object(time, array);
    DWORD workerid;
    HANDLE worker = CreateThread(NULL, 0, &getSquareRootSum, &object, 0, &workerid);
    if (worker == NULL)
    {
        return GetLastError();
    }

    SuspendThread(worker);
    ResumeThread(worker);
    WaitForSingleObject(worker, INFINITY);
    CloseHandle(worker);
    return 0;
}
