#include "philo.h"

int init_philos(t_data *data)
{
    int i = 0;
    data->philos = malloc(sizeof(t_philo) * data->n_philos);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
    data->threads = malloc(sizeof(pthread_t) * data->n_philos);

    for (i = 0; i < data->n_philos; i++)
    {
        t_philo *philo = &data->philos[i];
        philo->id = i + 1;
        philo->n_philos = data->n_philos;
        philo->start = get_time();
        philo->tt_die = data->t_die;
        philo->tt_eat = data->t_eat;
        philo->tt_sleep = data->t_sleep;
        philo->dead_lock = &data->dead_lock;
        philo->meals_n = 0;
        philo->time_now = 0;
        philo->meals_max = data->food_access;
        philo->global_mutex = &data->global_mutex;
        philo->dead = &data->dead;
        philo->meals_lock = &data->meals_lock;
        philo->left_fork = &data->forks[i];
        philo->right_fork = &data->forks[(i + 1) % data->n_philos];

        if (pthread_mutex_init(&data->forks[i], NULL) != 0)
            return 1;
    }

    if (pthread_mutex_init(&data->meals_lock, NULL) != 0)
        return 1;
    if (pthread_mutex_init(&data->global_mutex, NULL) != 0)
        return 1;
    if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
        return 1;
    if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
        return 1;

    return 0;
}

int end_of_sim(t_philo *data)
{
    unsigned long time_now = get_time() ;
    pthread_mutex_lock(data->dead_lock);
	if(*data->dead == 1)
    {
        pthread_mutex_unlock(data->dead_lock);
        return(0);
    }
    if (time_now - data->time_now >= (unsigned long)data->tt_die && data->flag == 1)
    {
        printf("%ld %d died\n", (time_now - data->time_now), data->id);
        *data->dead = 1;
        pthread_mutex_unlock(data->dead_lock);
        return 0;
    }
    if((data->meals_n >= data->meals_max) && data->meals_max > 0)
    {
        pthread_mutex_unlock(data->dead_lock);
        return 0;
    }
	pthread_mutex_unlock(data->dead_lock);
	return(1);
}

void *routing(void *arg)
{
    t_philo *data = arg;

    if(data->id % 2 == 0)
            usleep(100);
    data->flag = 0;
    // data->time_now = data->start;
    while(end_of_sim(data))
    {
        printf("%ld %d is thinking \n" , (get_time() - data->start),data->id);
        pthread_mutex_lock(data->left_fork);
        printf("%ld %d has taken a fork\n", (get_time() - data->start), data->id);
        pthread_mutex_lock(data->right_fork);
        printf("%ld %d has taken a fork\n", (get_time() - data->start), data->id);

        printf("%ld %d is eating\n", (get_time() - data->start), data->id);
        while (get_time() - data->time_now < (unsigned long)data->tt_eat)
            usleep(200);
        pthread_mutex_lock(data->global_mutex);
        data->time_now = get_time();
        pthread_mutex_unlock(data->global_mutex);            
        pthread_mutex_unlock(data->right_fork);
        pthread_mutex_unlock(data->left_fork);
        printf("%ld %d is sleeping\n", (get_time() - data->start), data->id);
        data->time_now2 = get_time();
        while (get_time() - data->time_now2 < (unsigned long)data->tt_sleep)
            usleep(200);
        pthread_mutex_lock(data->meals_lock);
            data->meals_n++;
        pthread_mutex_unlock(data->meals_lock);
        data->flag = 1;
    }
    return(NULL);

}

int wait_threads(t_data *data)
{
    int i = 0;
    while(i < data->n_philos)
    {
        pthread_join(data->threads[i],NULL);
        i++;
    }
    return 0;
}

int start_threads(t_data *data)
{
    if(init_philos(data))
        return(1);
    int i = 0;
    while (i < data->n_philos)
    {
        pthread_create(&data->threads[i],NULL,&routing,&data->philos[i]);
        i++;
    }
    return 0;
}