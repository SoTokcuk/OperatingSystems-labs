# Task

Write programs for the console process Boss and the console processes Parent, Child. To simulate message passing introduce special events (with automatic reset) which denote "A", "B", "C", "D" and end of session for Parent and Child.

Only 3 ACTIVE Child processes can send messages (use semaphore) and one ACTIVE Parent process (use mutex), all the rest should be blocked (on hold).

<br>

### Boss process:

1. Initializes synchronization objects;
2. it asks the user to specify the number of Parent and the number of Child processes to execute;
3. prompts the number of messages received from Parent or Child the total number of messages sent and received must match\)\. messages received \(the total number of messages sent and received must be the same\)
4. it starts a given number of Parent\, Child processes;
5. receives messages from each process Parent\, Child\, outputs and who sent it to the console in one line\.
6. finishes its work\.

<br>

### Parent process:

1. synchronize the work of Parent processes using a mutex
2. implement the transfer of messages using events
3. asks for messages consisting of "A" or "B" from the console and sends them \(one by one\) to the Boss process;
4. terminates its work\.

<br>

### The Child process:

1. synchronize the work of Child processes using a semaphore
2. It sends messages to the processes through events
3. It queries the C or D messages from the console and sends them to the Boss process\, one by one; 4;
4. terminates its work\.

<br>

# Project Documentation

This project consists of three files: main.cpp, parent.cpp, and child.cpp. The project involves creating multiple parent and child processes in a synchronized manner and exchanging messages between them using events and semaphores. Here's an overview of each file's purpose and functionality:

<br>

### main.cpp:

* This file contains the `main()` function and serves as the entry point for the program.
* It includes necessary headers and defines the required libraries.
* The program creates a mutex and a semaphore using `CreateMutexW` and `CreateSemaphoreW` functions, respectively.
* It prompts the user to input the number of parent and child processes.
* It then creates the specified number of parent and child processes using `CreateProcessW` and passes the appropriate command-line arguments.
* Events are created for each parent and child process using `CreateEventW` to enable synchronization.
* The program waits for events to occur using `WaitForMultipleObjects` and displays messages based on the event type.
* Finally, it waits for all processes to finish, closes handles, and returns 0.

<br>

### parent.cpp:

* This file represents the code for the parent process.
* It includes necessary headers and defines the required libraries.
* The program opens the mutex created in main.cpp using `OpenMutexW` and the corresponding parent event and ending event using `OpenEventW`.
* It enters a loop based on the number of messages received as a command-line argument.
* Within the loop, it waits for the mutex using `WaitForSingleObject`, reads a message from the user, sets the parent event using `SetEvent`, and releases the mutex using `ReleaseMutex`.
* After sending all the messages, it sets the ending event using `SetEvent`.
* Finally, it closes handles and returns 0.

<br>

### child.cpp:

* This file represents the code for the child process.
* It includes necessary headers and defines the required libraries.
* The program opens the semaphore created in main.cpp using `OpenSemaphoreW` and the corresponding child event and ending event using `OpenEventW`.
* It enters a loop based on the number of messages received as a command-line argument.
* Within the loop, it waits for the semaphore using `WaitForSingleObject`, reads a message from the user, sets the child event using `SetEvent`, and releases the semaphore using `ReleaseSemaphore`.
* After sending all the messages, it sets the ending event using `SetEvent`.
Finally, it closes handles and returns 0.

