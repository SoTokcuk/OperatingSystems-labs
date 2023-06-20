#include <iostream> 
#include <vector> 
#include <string> 
#include <pthread.h> 
#include <unistd.h> 
 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; 
 
std::vector<std::string> array; 
int count = 0; 
bool done = false; 
 
void* workThread(void* arg) { 
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
        sleep(interval); 
    } 
 
    pthread_mutex_lock(&mutex); 
    done = true; 
    pthread_cond_signal(&cond); 
    pthread_mutex_unlock(&mutex); 
    return nullptr; 
} 
 
void* countElementThread(void* arg) { 
    pthread_mutex_lock(&mutex); 
    while (!done) { 
        pthread_cond_wait(&cond, &mutex); 
    } 
    pthread_mutex_unlock(&mutex); 
 
    pthread_mutex_lock(&mutex); 
    for (const auto& element : array) { 
        if (element != "_") { 
            count++; 
        } 
    } 
    pthread_mutex_unlock(&mutex); 
    return nullptr; 
} 
 
int main() { 
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
 
    pthread_t work_thread, count_thread; 
    pthread_create(&work_thread, nullptr, workThread, nullptr); 
    pthread_create(&count_thread, nullptr, countElementThread, nullptr); 
 
    pthread_join(work_thread, nullptr); 
    pthread_join(count_thread, nullptr); 
 
    std::cout << "Processed array: "; 
    for (const auto& element : array) { 
        std::cout << element << " "; 
    } 
 
    pthread_mutex_lock(&mutex); 
    std::cout << "\nCount: " << count; 
    pthread_mutex_unlock(&mutex); 
 
    return 0; 
}
