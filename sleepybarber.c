//Worked with Alexandra Gonzalez
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex;
sem_t chair;
sem_t waitingCustomer;
int num_customers[100]; //array for number of customers 
int emptyChairs = 20; //number of chairs in the waiting room


void *customer(void *a)
{
    while (1)
    {
        sem_wait(&mutex); //customer gets to barbershop
        if (emptyChairs == 0)
        {
            sem_post(&mutex); // if there are no empty chairs the customer leaves 
            continue;
        }

        emptyChairs--; //if customer gets a seat decrement empty chairs

        printf("Customer %d is taking a seat\n", *((int *)a));

        sem_post(&mutex); //increment mutex
        sem_post(&waitingCustomer); // increment a waiting customer
        sem_wait(&chair); //decrement an available chair

        printf("Customer %d wakes up the barber\n", *((int *)a)); //customer wakes up the barber
        printf("Customer %d is getting a haircut\n", *((int *)a)); //customer gets a haircut
    }
}
void *barber(void *b)
{
    while (1)
    {
        // barber waits for a customer
        sem_wait(&waitingCustomer); //if barber gets a customer decrement waitingCustomer
        sem_wait(&mutex); //decrement mutex

        emptyChairs++; //when barber takes a customer an empty chair becomes available

        printf("Barber is taking a customer\n");

        sem_post(&mutex); //increment mutex semaphore
        sem_post(&chair); //increment chair semaphore
    
        printf("Barber is giving a haircut\n"); //Barber gives haircut
    }
}
int main(int argc, char *argv[])
{
    pthread_t customer_threads[100]; //declare customer thread
    pthread_t barber_thread; //declare barber thread
    
    sem_init(&mutex, 0, 1); //initialize mutex semaphore
    sem_init(&chair, 0, 1); //initialize chair semaphore
    sem_init(&waitingCustomer, 0, 0); //initialize waitingCustomer semaphore
   
    pthread_create(&barber_thread, NULL, barber, NULL); //creates thread for barber
   
    for (int i = 0; i < 100; i++){
        num_customers[i] = i + 1; //update customer count
        pthread_create(&customer_threads[i], NULL, customer, &num_customers[i]); //creates thread for customers
    }
 
    for (int i = 0; i < 100; i++){ //iterating through all customer threads
        pthread_join(customer_threads[i], NULL); 
    }
  
    sem_destroy(&mutex); //destroy mutex semaphore
    sem_destroy(&chair); //destroy chair semaphore
    sem_destroy(&waitingCustomer); // destroy waitingCustomer Semaphore
    return 0;
}