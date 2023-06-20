# Task

Write a program for a console process that consists of two threads: main and worker.
The main thread has to perform the following actions:
1\. Create an array of integers\, the dimension and elements of which are entered from the console \(or randomly generated\)\.
2\. Input the time to stop and start the worker thread\.
3\. Create a worker thread\, pass the data into the thread: array size\, array\, etc\.
4\. Suspend the worker thread \(SuspendThread\)\, then start it again after some time\.
5\. Know how to create a thread with the \_beginthreadex command
6\. Wait for the worker thread to terminate\.
7\. Output the result of the worker thread to the console
8\. Finish the work\.

The worker thread should do the next job:
Find the sum of the square roots of the elements. After each sum of the elements "sleep" for 200 milliseconds. Finish his work.

# Documaentation
<br>

1. Libraries:
    * iostream: Provides input/output operations.
    * random: Provides random number generation.
    * windows.h: Provides Windows-specific functions and data types.
    * cmath: Provides mathematical functions, including sqrt().
    * thread: Provides support for multi-threading.
    * algorithm: Provides algorithms for operations on sequences of elements.
2. Structure:
    * The code defines a structure named "Structure" that holds the sleep time and array information.
    * Private Members:
        * sleep\_time: Represents the time interval for sleeping in milliseconds.
        * array: Pointer to the array of integers.
        * DeepCopy(int\* array): A private function that creates a deep copy of the input array.
    * Public Members:
        * Structure(int sleep\_time, int\* array): Constructor for the Structure.
        * GetArray(): Returns the array pointer.
        * GetSleepTime(): Returns the sleep time value.
3. CreateArray(int size):
    * Function that creates and returns a dynamically allocated array of random integers.
    * Parameters:
        * size: The size of the array to be created.
    * Returns:
        * int\*: Pointer to the created array.
4. getSquareRootSum(LPVOID structure):
    * The thread function that calculates the square root sum of the array.
    * Parameters:
        * structure: A void pointer to the Structure object.
    * Returns:
        * DWORD: Thread exit status (always 0 in this code).
5. main():
    * The main function where the program execution starts.
    * It prompts the user to enter the size of the array and the sleep time.
    * It creates an array of random integers using CreateArray() function.
    * Displays the generated array.
    * Creates an instance of the Structure object with the input sleep time and array.
    * Creates a thread and passes the address of getSquareRootSum() function as the thread function.
    * Suspends the thread immediately after creation using SuspendThread() function.
    * Resumes the suspended thread using ResumeThread() function.
    * Waits for the thread to finish its execution using WaitForSingleObject() function.
    * Closes the thread handle using CloseHandle() function.
    * Returns 0 to indicate successful program execution.