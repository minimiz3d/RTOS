/******************************************************************************
* Author: 			Dler Hasan
* FILE: 			main.c
* DESCRIPTION:		Using pthreads condition variables and timers.
* LAST REVISED: 	04/18/2017
******************************************************************************/

// Include Library
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Define Global Variables
#define NUM_THREADS 2

int timer = 0;
pthread_mutex_t mutex_timer;
pthread_cond_t timer_expired_cv;

// Function: Thread signals when timer has expired
void *watch_timer(void *timer){

	// Declare variable holding waiting time
	int waiting_time = *((int*)timer);

	// Print waiting time
	printf("Starting watch_timer(), thread is waiting %d second(s):\n", waiting_time);


	// Run while loop until timer has expired
	while(waiting_time > 0){

		// Thread sleeps until timer has expired
		sleep(1);

		printf("Timer is: %d second(s).\n", waiting_time);

		// Lock mutex
		pthread_mutex_lock(&mutex_timer);

		// Decrement timer by 1
		waiting_time--;

		// Unlock mutex
		pthread_mutex_unlock(&mutex_timer);
		// Check if timer is 0
		if (waiting_time == 0)
		{
			// Notify other thread that time has expired
			pthread_cond_signal(&timer_expired_cv);
			printf("Sends notification to the other thread that timer has expired.\n");
		} // End if statement
	} // End while statement
	pthread_exit(NULL);
	//return 0;
}

// Function: Print timer has expired
void *timer_has_expired(void *t){

	// Insert passing variable to new variable
	long my_thread = *(long*)t;

	// Lock mutex
	pthread_mutex_lock(&mutex_timer);

	// Wait for signal and mutex state
	pthread_cond_wait(&timer_expired_cv, &mutex_timer);
	printf("Timer has expired and thread number %ld is notified. \n", my_thread);

	// Unlock mutex
	pthread_mutex_unlock(&mutex_timer);
	pthread_exit(NULL);
}

void getUserInput(){
	// Ask user to select timer limit.
	printf("Hello, please set timer limit\n");
	scanf("%d",&timer);
	printf("Timer limit is set too: %d\n", timer);
}


int main(int argc, char *argv[]){

	// Declare variables
	int i;
	pthread_t threads[2];
	pthread_attr_t attr;
	long thread1=1;

	// Ask user to define timer limit.
	getUserInput();


	// Initialize Mutex and Conition Variable
	pthread_mutex_init(&mutex_timer, NULL);
	pthread_cond_init(&timer_expired_cv, NULL);


	// Create pthreads with a joinable state
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	pthread_create(&threads[0], &attr, watch_timer, (void *)&timer);
	pthread_create(&threads[1], &attr, timer_has_expired, (void *)&thread1);

	// Wait for all threads to be completed
	for (i = 0; i < NUM_THREADS; i++) {
	  pthread_join(threads[i], NULL);
	}
	printf ("Main(): Waited and joined with %d threads. Execution completed.\n", NUM_THREADS);

	// Clean up and exit
	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&mutex_timer);
	pthread_cond_destroy(&timer_expired_cv);
	pthread_exit(NULL);

	// Wait for all threads to complete?
	// Clean up and exit

	return 0;
}
