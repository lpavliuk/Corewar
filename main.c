#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>

void * thread_func(void *arg)
{
	int i;
	int loc_id = * (int *) arg;
	for (i = 0; i < 4; i++)
	{
		printf("Thread %i is running\n", loc_id);
		sleep(1);
	}
	return (arg);
}

int main(int argc, char * argv[])
{
	pthread_t tid[4];
	int i;

	i = 0;
	while (i < 4)
	{
		pthread_create(&tid[i], NULL, thread_func, &i);
		i++;
	}
	while (1);
	// i = 0;
	// while (i < 2)
	// {
	// 	pthread_join(tid[i], NULL);
	// 	i++;
	// }
	return EXIT_SUCCESS;
}


#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;

void * thread_func(void *arg)
{
	int i;
	int loc_id = * (int *) arg;

	sem_post(&sem);
	for (i = 0; i < 4; i++) {
		printf("Thread %i is running\n", loc_id);
		sleep(1);
	}
}

int main(int argc, char * argv[])
{
	int id, result;
	pthread_t thread1, thread2;

	id = 1;
	sem_init(&sem, 0, 0);
	result = pthread_create(&thread1, NULL, thread_func, &id);
	if (result != 0) {
		perror("Creating the first thread");
		return EXIT_FAILURE;
	}
	sem_wait(&sem);
	id = 2;
	result = pthread_create(&thread2, NULL, thread_func, &id);
	if (result != 0) {
		perror("Creating the second thread");
		return EXIT_FAILURE;
	}
	result = pthread_join(thread1, NULL);
	if (result != 0) {
		perror("Joining the first thread");
		return EXIT_FAILURE;
	}
	result = pthread_join(thread2, NULL);
	if (result != 0) {
		perror("Joining the second thread");
		return EXIT_FAILURE;
	}
	sem_destroy(&sem);
	printf("Done\n");
	return EXIT_SUCCESS;
}
