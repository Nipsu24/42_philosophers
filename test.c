#include <pthread.h>
#include <stdio.h>

void	*routine(void *arg)
{
	pthread_mutex_t *mutex = (pthread_mutex_t *)arg;
	int	i;

	i = 0;
	while (i < 1000000)
	{
		pthread_mutex_lock(mutex);
		i++;
		pthread_mutex_unlock(mutex);
	}
	printf("Iteration: %d\n", i);
	return (0);
}

int	main(void)
{
	pthread_t		t1;
	pthread_t		t2;
	pthread_mutex_t	mutex;

	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, &routine, &mutex) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine, &mutex) != 0)
		return (1);
	if (pthread_join(t1, NULL) != 0) // waits for thread to be executed
		return (1);
	if (pthread_join(t2, NULL) != 0) // waits for thread to be executed
		return (1);
	pthread_mutex_destroy(&mutex);
	return (0);
}