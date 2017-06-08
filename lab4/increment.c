# include <pthread.h>
# include <getopt.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>

uint8_t enableMutex = 0;
pthread_mutex_t mutex;

void *threadFunc(void *arg);
void incr(uint32_t *n);


int main(int argc, char **argv)
{
	uint32_t threadCount = 1;
	int opt;
	while ((opt = getopt(argc, argv, "n:m")) != -1)
	{
		switch (opt)
		{
			case 'n':
			{
				threadCount = atoi(optarg);
				break;
			}
			case 'm':
			{
				enableMutex = 1;
				break;
			}
			case '?':
			{
				break;
			}
			default:
			{
				break;
			}
		}
	}
	
	uint64_t counter = 0; // Argument to be passed to the thread.
	pthread_mutex_init(&mutex, NULL); // Initialize the mutex.	
	pthread_t threads[threadCount]; // Declare the requested threads.

	// Initialize the threads.
	for (uint32_t i = 0; i < threadCount; i += 1)
	{
		/* pthread_create:
		 * 
		 * @param thread     The thread to initialize.
		 * @param NULL       Set default attributes to the thread.
		 * @param threadFunc A void pointer to a function that the thread will execute.
		 * @param counter    Any argument that the thread will need to use in execution.
		 */
		pthread_create(&threads[i], NULL, threadFunc, &counter);
	}

	// Wait for each thread to be done executing.
	for (uint32_t i = 0; i < threadCount; i += 1)
	{
		pthread_join(threads[i], NULL);

	}

	pthread_mutex_destroy(&mutex); // Done with multithreading, destroy the mutex.

	printf("%lu\n", counter);

	return 0;
}

/* threadFunc:
 *
 * Serves as the entry point for the thread (taken as a pointer in pthread_create)
 *
 * @param arg: any argument being passed by the thread
 */
void *threadFunc(void *arg)
{
	uint32_t *n = (uint32_t *) arg;
	for (uint16_t i = 0; i < 1000; i += 1)
	{
		incr(n);
	}
	return NULL;
}

void incr(uint32_t *n)
{
	if (enableMutex)
	{
		pthread_mutex_lock(&mutex);
		*n += 1;
		pthread_mutex_unlock(&mutex);
	}
	else
	{
		*n += 1;
	}
}
