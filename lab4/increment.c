# include <pthread.h>
# include <getopt.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>

pthread_mutex_t mutex;

void *threadFunc(void *arg);
void incr(uint32_t *n);

int main(int argc, char **argv)
{
	uint32_t threadCount = 1;
	int opt;
	while ((opt = getopt(argc, argv, "n:")) != -1)
	{
		switch (opt)
		{
			case 'n':
			{
				threadCount = atoi(optarg);
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
	
	uint64_t counter = 0;

	for (int i = 0; i < threadCount; i += 1)
	{
		pthread_t thread;
		pthread_mutex_init(&mutex, NULL); // initialize mutex
		pthread_create(&thread, NULL, threadFunc, &counter); // create a thread
		pthread_join(thread, NULL); // wait for the thread to be done doing whatever
		pthread_mutex_destroy(&mutex); // destroy the mutex
	}

	printf("%u\n", counter);

	return 0;
}

void *threadFunc(void *arg)
{
	uint32_t *n = (uint32_t *) arg;
	for (uint16_t i = 0; i < 1000; i += 1)
	{
		incr(n);
	}
}

void incr(uint32_t *n)
{
	pthread_mutex_lock(&mutex);
	*n += 1;
	pthread_mutex_unlock(&mutex);
}
