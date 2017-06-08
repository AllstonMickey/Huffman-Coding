# include <pthread.h>
# include <getopt.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>

uint8_t enableMutex = 0;
pthread_mutex_t mutex;

void *threadFunc(void *args);
void increment(uint32_t *n);

/* threadIncr:
 *
 * increments the count by the number of iterations
 */
struct threadIncr
{
	uint32_t iters;
	uint32_t count;
};

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
	
	
	pthread_mutex_init(&mutex, NULL); // Initialize the mutex.	
	struct threadIncr incr = { .iters = 1000, .count = 0 };
	pthread_t *threads = (pthread_t *) calloc(threadCount, sizeof(pthread_t));
	
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
		pthread_create(&threads[i], NULL, threadFunc, &incr);
	}

	// Wait for each thread to be done executing.
	for (uint32_t i = 0; i < threadCount; i += 1)
	{
		pthread_join(threads[i], NULL);

	}

	pthread_mutex_destroy(&mutex); // Done with multithreading, destroy the mutex.

	printf("%u\n", incr.count);

	return 0;
}

/* threadFunc:
 *
 * Serves as the entry point for the thread (taken as a pointer in pthread_create)
 *
 * @param arg: any argument being passed by the thread
 */
void *threadFunc(void *args)
{
	struct threadIncr *arg = (struct threadIncr *) args;
	for (uint16_t i = 0; i < arg->iters; i += 1)
	{
		increment(&arg->count);
	}
	return NULL;
}

void increment(uint32_t *n)
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
