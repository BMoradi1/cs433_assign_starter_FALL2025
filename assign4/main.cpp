/**
* Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @author ??? (TODO: your name)
 * @brief The main program for the producer consumer problem.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include <iostream>
#include "buffer.h"
#include <cstring>
#include <unistd.h> //handles sleep
#include <semaphore.h> 
#include <pthread.h>

using namespace std;

#define NUM_THREADS 5


// global buffer object
Buffer buffer;

//Semaphore declaration 
sem_t mutex;
sem_t fullSem;
sem_t emptySem;


// Producer thread function
// TODO: Add your implementation of the producer thread here
void *producer(void *param) {
    // Each producer insert its own ID into the buffer
    // For example, thread 1 will insert 1, thread 2 will insert 2, and so on.
    buffer_item item = *((int *) param);

    while (true) {
        /* sleep for a random period of time */
        usleep(rand()%1000000);
        // TODO: Add synchronization code here
        //item = rand(); //generates a random item (zybooks)
        sem_wait(&emptySem);
        sem_wait(&mutex);
        if (buffer.insert_item(item)) {
            cout << "Producer " << item << ": Inserted item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Producer error condition"  << endl;    // shouldn't come here
        }
        sem_post(&mutex);
        sem_post(&emptySem);

    }
}

// Consumer thread function
// TODO: Add your implementation of the consumer thread here
void *consumer(void *param) {
    buffer_item item;

    while (true) {
        /* sleep for a random period of time */
        usleep(rand() % 1000000);
        sem_wait(&fullSem);
        sem_wait(&mutex);
        // TODO: Add synchronization code here
        if (buffer.remove_item(&item)) {
            cout << "Consumer " << item << ": Removed item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Consumer error condition" << endl;    // shouldn't come here
        }
        sem_post(&mutex);
        sem_post(&emptySem);
    }
}

int main(int argc, char *argv[]) {

    /* TODO: 1. Get command line arguments argv[1],argv[2],argv[3] */
    
    int sleep = atoi(argv[1]); //how long the main thread sleeps before terminating 
    int producerThreads(atoi(argv[2])); //number of producer threads
    int consumerThreads(atoi(argv[3])); //number of consumer threads

    sem_init(&mutex,0, 1);
    sem_init(&fullSem,0 , 0);
    sem_init(&emptySem, 0, NULL);
    
    int i, scope;
    pthread_t tid[NUM_THREADS];
    pthread_attr_t attr; 
    int uniqueID = 1;
    /* Default Attributes*/
    pthread_attr_init(&attr);

    if(pthread_attr_getscope(&attr, &scope) != 0)
    {
        cerr << "Unable to get scheduling scope\n" << endl;
    }
    else 
    {
        if (scope = PTHREAD_SCOPE_PROCESS)
        printf("PTHREAD_SCOPE_PROCESS\n");
        else if (scope = PTHREAD_SCOPE_SYSTEM)
        printf("PTHREAD_SCOPE_SYSTEM\n");
        else 
        fprintf(stderr, "Illegal scope value.\n");
    }
    /* TODO: 2. Initialize buffer and synchronization primitives */
    /* TODO: 3. Create producer thread(s).
     * You should pass an unique int ID to each producer thread, starting from 1 to number of threads */
    /* TODO: 4. Create consumer thread(s) */
    /* TODO: 5. Main thread sleep */
    /* TODO: 6. Exit */
}
