#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <time.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
#include <stdlib.h>


#define NO_PAR -1

typedef struct s_philo
{
    int id;
    int n_philos;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *global_mutex;
    pthread_mutex_t *meals_lock;
    pthread_mutex_t *dead_lock;
    int tt_die;
    int tt_sleep;
    int tt_eat;
    int meals_max;
    unsigned long start;
    unsigned long time_now;
    unsigned long time_now2;
    int meals_n;
    int *dead;
    int flag;
}t_philo;


typedef struct s_data
{
    int n_philos;
    int t_die;
    int t_sleep;
    int t_eat;
    int food_access;
    int dead;
    t_philo *philos;
    pthread_t *threads;
    pthread_mutex_t *forks;
    pthread_mutex_t global_mutex;
    pthread_mutex_t meals_lock;
    pthread_mutex_t dead_lock;
    pthread_mutex_t meal_lock;
    int meals_n;
    
} t_data;



unsigned long get_time(void);
int	ft_atoi(const char *str);
int start_threads(t_data *data);
int wait_threads(t_data *data);
int	ft_isdigit(int d);
int ft_space(char c);
int init_philos(t_data *data);
int dead_philos(t_data *data);
#endif
