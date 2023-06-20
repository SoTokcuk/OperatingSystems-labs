#include <iostream> 
#include <vector> 
#include <string> 
#include <windows.h> 

CRITICAL_SECTION cs;
HANDLE event;

std::vector<std::string> array;
int count = 0;

DWORD WINAPI workThread(LPVOID lpParam) {
    int interval;
    std::cout << "Enter time interval: ";
    std::cin >> interval;

    for (auto& element : array) {
        if (isdigit(element[0])) {
            element = element.substr(0, element.find(" "));
        }
        else {
            element = "_";
        }
        Sleep(interval);
    }

    SetEvent(event);
    return 0;
}

DWORD WINAPI countElementThread(LPVOID lpParam) {
    WaitForSingleObject(event, INFINITE);

    EnterCriticalSection(&cs);
    for (const auto& element : array) {
        if (element != "_") {
            count++;
        }
    }
    LeaveCriticalSection(&cs);
    return 0;
}

int main() {
    InitializeCriticalSection(&cs);
    event = CreateEvent(NULL, TRUE, FALSE, NULL);

    int size;
    std::cout << "Enter array size: ";
    std::cin >> size;

    std::string input;
    std::cout << "Enter array elements: ";
    for (int i = 0; i < size; i++) {
        std::cin >> input;
        array.push_back(input);
    }

    std::cout << "Initial array: ";
    for (const auto& element : array) {
        std::cout << element << " ";
    }
    std::cout << "\n";

    HANDLE hWorkThread = CreateThread(NULL, 0, workThread, NULL, 0, NULL);
    HANDLE hCountElementThread = CreateThread(NULL, 0, countElementThread, NULL, 0, NULL);

    WaitForSingleObject(event, INFINITE);

    std::cout << "Processed array: ";
    for (const auto& element : array) {
        std::cout << element << " ";
    }

    EnterCriticalSection(&cs);
    std::cout << "\nCount: " << count;
    LeaveCriticalSection(&cs);

    WaitForSingleObject(hWorkThread, INFINITE);
    WaitForSingleObject(hCountElementThread, INFINITE);

    CloseHandle(hWorkThread);
    CloseHandle(hCountElementThread);

    DeleteCriticalSection(&cs);
    CloseHandle(event);

    return 0;
}