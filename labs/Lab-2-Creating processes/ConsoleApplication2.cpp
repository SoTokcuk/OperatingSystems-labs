#include <iostream>
#include <conio.h> 

using namespace std;

void nSort(int a[], int n)
{
    int* posArr = new int[n];
    int posCount = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] > 0)
        {
            posArr[posCount] = a[i];
            posCount++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (i < posCount)
        {
            a[i] = posArr[i];
        }
        else
        {
            a[i] = 0;
        }
    }
    delete[] posArr;
}

int main(int argc, char* argv[]) {
    int i;
    int* array = new int[argc];
    for (i = 0; i < argc; i++) {
        array[i] = atoi(argv[i]);
        cout << array[i] << endl;
    }

    nSort(array, argc);

    cout << "Sorted array: ";
    for (i = 0; i < argc; i++) {
        cout << array[i] << " ";
    }
    cout << endl;

    _cputs("\nPress any key to finish.\n");
    _getch();
    return 0;
}
