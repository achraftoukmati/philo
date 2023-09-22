#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

# define NO_PAR -1
struct s_data;

typedef struct s_philo
{
	int				id;
	int				n_philos;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				tt_die;
	int				tt_sleep;
	int				tt_eat;
	int				meals_max;
	unsigned long	start;
	unsigned long	time_now;
	unsigned long	time_now2;
	int				meals_n;
	int				*flag;
	int				*s;
	pthread_mutex_t *print_mutex;
	pthread_mutex_t *dead_mutex;
	pthread_mutex_t meals_mutex;
	pthread_mutex_t flag_mutex;
	struct s_data	*data_ptr;
	
}					t_philo;

typedef struct s_data
{
	int				n_philos;
	int				t_die;
	int				t_sleep;
	int				t_eat;
	int				food_access;
	int				dead;
	int				flag;
	t_philo			*philos;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t print_mutex;
	pthread_mutex_t dead_mutex;
	int				meals_n;

}					t_data;

void				free_all(t_data *data);
void				printing(char *s, t_philo *data);
unsigned long		get_time(void);
int					ft_atoi(const char *str);
int					start_threads(t_data *data);
int					wait_threads(t_data *data);
int					ft_isdigit(int d);
int					ft_space(char c);
int					init_philos(t_data *data);
int					error(t_data *data, char *msg);
void				mutex_destroy(t_data *data);
void				*routing(void *arg);
int					check_data(t_data *input);
int 				not_dead(t_philo *philo);

#endif
