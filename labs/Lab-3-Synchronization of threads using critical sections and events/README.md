# Task

#### Synchronization objects :

* Event (with manual reset) - in the work thread sets the signal for the main thread (to output the array) and for the CountElement thread (which signals the start of calculations).
* The critical section - the synchronization of the CountElement and the main thread (the output of the CountElement result);

#### The main thread should execute the following actions:

* initialize necessary events and critical sections.
* create an array, the elements of which are symbols, the dimension and elements of which are entered by the user from the console;
* display the dimension and elements of the initial array on the console;
* run the work thread;
* run the CountElement flow;
* Get a signal from the work thread to output the array (use an event with manual reset);
* Output the result of the CountElement thread;

#### The work thread should do the following:

* ask the user for the time interval required to rest after preparing one element in the array;
* Search the array for tokens starting with a number (separated by a space and a dash). The obtained tokens should be placed in the array on the left side, and the extra elements should be filled in with the underscore character: "\_" ). The elements are symbols.
* notify the main thread and the CountElement thread of the beginning of the summing (the moment of starting will occur after the total array is formed), use an event (manual reset);

####

#### The CountElement thread has to do the following:

* wait for a message from the work thread about the beginning of calculations (use event);
* calculate the elements (up to underscore characters: "\_") of the resulting array;
* signal the main thread to output the result (use the critical section);

<br>

# Code Documentation


``` cpp
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
```

These lines include the necessary header files for input/output (`iostream`), vector manipulation (`vector`), string handling (`string`), and the Windows API (`windows.h`).

<br>

``` cpp
CRITICAL_SECTION cs;
HANDLE event;

std::vector<std::string> array;
int count = 0;
```

Here, we define a critical section (`CRITICAL_SECTION`) and an event object (`HANDLE`) to synchronize access to shared resources. We also declare a vector called `array` to store strings and an integer variable `count` to keep track of the number of non-digit elements in the array.

<br>

``` cpp
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
```

The `workThread` function is the entry point for the worker thread. It prompts the user to enter a time interval, which determines the duration of the sleep between processing each element. It then iterates over each element in the `array`. If the first character of an element is a digit, it extracts the substring before the first space character. Otherwise, it replaces the element with an underscore (`_`). After processing all elements, the function signals the event using `SetEvent` to indicate that the work is done. It returns 0 to exit the thread.

<br>

``` cpp
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
```

The `countElementThread` function serves as the entry point for the counting thread. It waits for the event to be signaled by the worker thread using `WaitForSingleObject`. This ensures that the counting thread starts processing the array only after the worker thread has finished modifying it. After waiting, it enters the critical section using `EnterCriticalSection` to ensure exclusive access to the `count` variable. It then iterates over each element in the `array` and increments `count` whenever an element is not equal to an underscore. Finally, it leaves the critical section using `LeaveCriticalSection` and returns 0 to exit the thread.

<br>

``` cpp
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
```

In the `main` function, we initialize the critical section using `InitializeCriticalSection` and create an event object using `CreateEvent`. The event is initially nonsignaled (`FALSE`) and manual-reset (`TRUE`).

The user is prompted to enter the size of the array, and then the array elements are read and stored in the `array` vector. The initial array elements are printed to the console.

Two threads are created using `CreateThread`. The first thread (`hWorkThread`) executes the `workThread` function, and the second thread (`hCountElementThread`) executes the `countElementThread` function.

The program waits for the event to be signaled using `WaitForSingleObject`. This ensures that the main thread waits until both the worker thread and counting thread have completed their tasks.

After the event is signaled, the processed array elements are printed to the console. The critical section is entered to print the value of `count` to ensure exclusive access. Then, the critical section is left.

The main thread waits for both worker and counting threads to finish using `WaitForSingleObject` and then closes the thread handles using `CloseHandle`.

Finally, the critical section and event object are cleaned up using `DeleteCriticalSection` and `CloseHandle`, respectively.
