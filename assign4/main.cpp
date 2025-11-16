/**
* Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @author Brynn Grofcsik & Bijan Moradi
 * @brief The main program for the producer consumer problem.
 * @version 0.1
 */

#include <iostream>
#include "buffer.h"
#include <cstring>
#include <unistd.h> 
#include <semaphore.h> 
#include <pthread.h>

using namespace std;

// global buffer object
Buffer buffer;

//Lock and Semaphore declaration 
pthread_mutex_t mutexSem;
sem_t emptySem;
sem_t fullSem;


// Producer thread function
void *producer(void *param) {
    // Each producer insert its own ID into the buffer
    // For example, thread 1 will insert 1, thread 2 will insert 2, and so on.
    buffer_item item = *((int *) param);

    while (true) {
        /* sleep for a random period of time */
        usleep(rand()%1000000);

        //Lock empty sem and mutex lock. Code referenced from Zybooks
        sem_wait(&emptySem);
        pthread_mutex_lock(&mutexSem);

        //debug to ensure code could be accessed after lock
        //cout << "hit" <<endl;

        //critical section
        if (buffer.insert_item(item)) {
            cout << "Producer " << item << ": Inserted item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Producer error condition"  << endl;    // shouldn't come here
        }

        //release of both locks
        pthread_mutex_unlock(&mutexSem);
        sem_post(&fullSem);

    }
}

// Consumer thread function
// TODO: Add your implementation of the consumer thread here
void *consumer(void *param) {
    buffer_item item;
    while (true) {

        /* sleep for a random period of time */
        usleep(rand() % 1000000);

        //lock wait semaphore and mutex lock, code referenced from Zybooks
        sem_wait(&fullSem);
        pthread_mutex_lock(&mutexSem);

        // critical section entered
        //since this is a FIFO algorithm our item consumed will be at the first index currently within the buffer.
        item = buffer.getBufferFront();

        //debug to check critical section functionality
        //cout << "hit2" <<endl;
        if (buffer.remove_item(&item)) {
            cout << "Consumer Removed item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Consumer error condition" << endl;    // shouldn't come here
        }

        //release of both locks 
        pthread_mutex_unlock(&mutexSem);
        sem_post(&emptySem);
    }
}

int main(int argc, char *argv[]) {

    /* Get command line arguments argv[1],argv[2],argv[3] */
    int sleep = atoi(argv[1]); //how long the main thread sleeps before terminating 
    int producerThreads(atoi(argv[2])); //number of producer threads
    int consumerThreads(atoi(argv[3])); //number of consumer threads

    /* Initialization of mutex lock and semaphores */
    pthread_mutex_init(&mutexSem, NULL); 
    sem_init(&emptySem, 0, buffer.get_size());
    sem_init(&fullSem, 0, 0);

    /* Creation of Producer Threads */
    pthread_t producerArray[producerThreads]; //array of producer threads
    for(int i = 0; i < producerThreads; i++){
        int *id = new int(i + 1); //Thread ID, starting from 1
        pthread_create(&producerArray[i], NULL, producer, (void *)id); //creation of each thread, built through producer function
   }

    /* TODO: 4. Create consumer thread(s) */
    pthread_t consumerArray[consumerThreads]; //array of consumer threads
    for(int i = 0; i < consumerThreads; i++){
        int *id = new int(i + 1); //Thread ID, starting from 1
        //cout << "creating"<<endl;
        pthread_create(&consumerArray[i], NULL, consumer, (void *)id); //creation of each thread, built through consumer function
    }

    /* Main thread sleep, multiply it by a million to convert given number into seconds*/
    usleep(sleep * 1000000);

    /* Exit */
    exit(0);
}
