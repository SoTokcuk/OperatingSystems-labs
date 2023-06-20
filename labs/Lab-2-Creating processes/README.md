# Task

Write programs for two console processes Parent and Child which execute.

**Parent process:**

* Enter the size of the array, enter the elements of the array;
* Forms a command line that contains information about the size of the array, the elements;
* Sets a new title for the Child window.

<br>
**The Child process:**

* Search for elements >0 in the array (place them in the array on the left, fill the remaining elements of the array with zeros). Output the resulting array. Type of elements - integers

# Code Documentation

### osi\_lab2.cpp file
<br>

1. **Include Statements:**
    * `#include "iostream"`: Includes the standard input/output stream library for input/output operations.
    * `<conio.h>`: Includes the console input/output library for functions like `_getch()` used for keyboard input.
    * `<sstream>`: Includes the string stream library for string manipulation.
    * `<map>`: Includes the map library for using map data structures.
    * `"windows.h"`: Includes the Windows API library for various Windows-related functions.
    * `<string>`: Includes the string library for string manipulation.
    * `"stdio.h"`: Includes the standard input/output library for functions like `printf()` and `scanf()`.
    * `"winuser.h"`: Includes the Windows API library for user-related functions.
    * `#pragma warning(disable : 4996)`: Disables a specific warning (warning 4996) in the code.
2. **Namespace Declaration:**
    * `using namespace std;`: Specifies that the program will use the `std` namespace, which contains standard C++ functions and objects.
3. **`main()` Function:**
    * The entry point of the program.
4. **Variable Declarations:**
    * `char child_process_name[]`: Declares a character array to store the path of the child process executable.
    * `STARTUPINFO startup_info`: Declares a `STARTUPINFO` structure that contains information about how to create the child process.
    * `PROCESS_INFORMATION process_information`: Declares a `PROCESS_INFORMATION` structure that receives identification information about the newly created process.
5. **`ZeroMemory(&startup_info, sizeof(STARTUPINFO))`:**
    * Fills the `startup_info` structure with zeros.
6. **Input:**
    * `int size`: Declares an integer variable to store the size of the array.
    * `cout << "Enter size of array: ";`: Displays a message to enter the size of the array.
    * `cin >> size;`: Reads the input size from the user.
    * `int* array = new int[size];`: Allocates dynamic memory for an integer array of size `size`.
    * `for (int i = 0; i < size; i++) { ... }`: Iterates over the array to read values from the user.
7. **Array Conversion:**
    * `string temp = "";`: Declares an empty string to store the converted array.
    * `for (int i = 0; i < size; i++) { ... }`: Iterates over the array to convert each element to a string and concatenate them into `temp`.
    * `char* command_line = new char[temp.length() + 1];`: Allocates dynamic memory for a character array to store the command line.
    * `strcpy(command_line, temp.c_str());`: Copies the contents of `temp` to `command_line`.
8. **Child Process Creation:**
    * `if (CreateProcess(child_process_name, command_line, NULL, NULL, false, CREATE_NEW_CONSOLE, NULL, NULL, &startup_info, &process_information)) { ... }`:
        * Attempts to create a child process using the specified `child_process_name` and `command_line`.
    * `SetConsoleTitle("Child Process");`: Sets the title of the child process console window.
    * `WaitForSingleObject(process_information.hProcess, INFINITE);`: Waits until the child process completes.
    * `CloseHandle(process_information.hProcess);`: Closes the handle to the child process.
    * `CloseHandle(process_information.hThread);`: Closes the handle to the child process's primary thread.
9. **Error Handling:**
    * `else { ... }`:
        * Executes if the child process creation fails, displaying an error message.
10. **Return Statement:**
    * Returns 0 to indicate successful execution of the program.
    <br>

### ConsoleApplication2.cpp file

1. **Include Statements:**
<br>

    * `<iostream>`: Includes the standard input/output stream library for input/output operations.
    * `<conio.h>`: Includes the console input/output library for functions like `_getch()` used for keyboard input.
    <br>
2. **Namespace Declaration:**
<br>

    * `using namespace std;`: Specifies that the program will use the `std` namespace, which contains standard C++ functions and objects.
    <br>
3. **`nSort()` Function:**
<br>

    * Takes an integer array `a[]` and its size `n` as parameters.
    * Creates a new integer array `posArr` to store positive elements.
    * Initializes a counter variable `posCount` to track the number of positive elements.
    * Iterates over the array and copies positive elements to `posArr`, incrementing `posCount`.
    * Updates the original array `a[]` by placing positive elements from `posArr` at the beginning and filling the remaining elements with zeros.
    * Deletes the dynamically allocated memory for `posArr`.
    <br>
4. **`main()` Function:**
<br>

    * The entry point of the program.
    * Declares an integer variable `i`.
    * Allocates dynamic memory for an integer array `array[]` with a size of `argc`.
    * Iterates over the command-line arguments (`argc` and `argv[]`), converting and storing them in `array[]`.
    * Prints the elements of `array[]`.
    * Calls the `nSort()` function to sort the array by moving positive elements to the beginning.
    * Prints the sorted array elements.
    * Displays a message to press any key to finish.
    * Waits for a key press using `_getch()`.
    * Returns 0 to indicate successful execution of the program.