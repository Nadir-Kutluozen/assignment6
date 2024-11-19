#include <iostream>
#include <pthread.h>
#include <unistd.h> 
/**
 * Nadir Kutluozen -
 * Simulates the Thread_1 writing the information into Shared Variable
 * & Thread_2 reading the Information from that Shared Data
 */
using namespace std;

int sharedVariable = 0; // I'm using this shared variable between threads
pthread_mutex_t mutex; // I'm putting this mutex here to control access to shared variable

// Thread 1: Writes to the shared variable
void* writeFunction(void* arg) {
    // I'm locking the mutex so only this thread can modify sharedVariable
    pthread_mutex_lock(&mutex);
    sharedVariable = 42; // Writing a value to the shared variable
    cout << "Thread 1: Wrote value " << sharedVariable << " to shared variable" << endl;
    pthread_mutex_unlock(&mutex); // Unlocking the mutex to let others use it
    return NULL;
}

// Thread 2: Reads the shared variable
void* readFunction(void* arg) {
    sleep(1); // Adding a small delay so Thread 1 gets a chance to write first
    pthread_mutex_lock(&mutex); // Locking the mutex to safely read the shared variable
    cout << "Thread 2: Read value " << sharedVariable << " from shared variable" << endl;
    pthread_mutex_unlock(&mutex); // Unlocking the mutex after reading
    return NULL;
}

int main() {
    pthread_t thread1, thread2; // Creating thread identifiers!

    // Initializing the mutex!
    pthread_mutex_init(&mutex, NULL);

    // Creating Thread 1 to write to sharedVariable!
    pthread_create(&thread1, NULL, writeFunction, NULL);
    // Creating Thread 2 to read from sharedVariable!
    pthread_create(&thread2, NULL, readFunction, NULL);

    // Waiting for both threads to finish before ending the program!
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroying the mutex since its's done!
    pthread_mutex_destroy(&mutex);

    return 0;
}
