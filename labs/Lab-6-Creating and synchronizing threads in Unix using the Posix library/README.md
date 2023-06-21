# Task

#### Implement lab 3 using the POSIX library under UNIX
<br>
<br>

# Code Overview

The code consists of several components:

<br>

1. ### Required Libraries:

    * `iostream`: Provides input/output stream handling.
    * `vector`: Implements a dynamic array data structure.
    * `string`: Defines the string data type and operations.
    * `pthread.h`: Provides functions and types for thread management.
    * `unistd.h`: Defines miscellaneous constants and types.

<br>

2. ### Global Variables:
    * `pthread_mutex_t mutex`: A mutex variable for thread synchronization.
    * `pthread_cond_t cond`: A condition variable for thread signaling.
    * `std::vector<std::string> array`: The dynamic array to be processed.
    * `int count`: A counter variable to hold the count of non-blank elements.
    * `bool done`: A flag to indicate if the work thread has finished processing the array.

<br>

3. ### Work Thread (`workThread` function):
    * Accepts a time interval from the user to define the delay between array element modifications.
    * Iterates through each element in the array and modifies it:
        * If the first character of the element is a digit, it removes any text after the first space.
        * If the first character is not a digit, it replaces the element with an underscore (`_`).
    * Uses the `sleep` function from `unistd.h` to introduce a delay between modifications.
    * Signals the condition variable (`cond`) to indicate that it has finished processing the array.

<br>

4. ### Count Element Thread (`countElementThread` function):
    * Waits for the condition variable (`cond`) to be signaled by the work thread.
    * Once signaled, it locks the mutex and counts the non-blank elements in the array.
    * Increments the `count` variable for each non-blank element.
    * Unlocks the mutex.

<br>

5. ### Main Function (`main`):
    * Takes user input for the array size and elements.
    * Prints the initial array.
    * Creates two threads using `pthread_create`:
        * `work_thread`: Executes the `workThread` function.
        * `count_thread`: Executes the `countElementThread` function.
    * Waits for both threads to complete using `pthread_join`.
    * Prints the processed array.
    * Locks the mutex and prints the count of non-blank elements.
    * Unlocks the mutex and returns 0 to terminate the program.

    <br>

# Code Execution Flow

1. The main function prompts the user for the array size and elements.
2. The initial array is printed to the console.
3. Two threads are created: `work_thread` and `count_thread`.
4. `work_thread` executes the `workThread` function:
    * Asks the user for the time interval between modifications.
    * Iterates through the array, modifies each element, and introduces a delay.
    * Signals the condition variable to indicate completion.
5. `count_thread` executes the `countElementThread` function:
    * Waits for the condition variable to be signaled.
    * Locks the mutex and counts the non-blank elements.
    * Unlocks the mutex.
6. The main thread waits for both threads to complete using `pthread_join`.
7. The processed array is printed to the console.
8. The mutex is locked, and the count of non-blank elements is printed.
9. The mutex is unlocked, and the program terminates.

<br>

# Usage Example

``` cpp
Enter array size: 5
Enter array elements: 123 45a 7b8 9c0 x11
Initial array: 123 45a 7b8 9c0 x11 
Processed array: 123 _ 7 _ x 
Count: 2
```

In this example, the user enters an array size of 5 and five elements: "123", "45a", "7b8", "9c0", and "x11". The program modifies the elements based on the defined rules and introduces a delay between modifications. The processed array is then displayed, showing that the elements "45a" and "9c0" have been replaced with underscores. The count of non-blank elements is printed as 2.
