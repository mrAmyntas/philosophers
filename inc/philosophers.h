#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

enum {
	DONE = 1,
	INPUT_ERR,
	INIT_ERR,
	MALLOC_ERR,
	THREAD_ERR,
	JOIN_ERR,
	ERROR = -1
};

enum {
	N_PHILO,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	N_TIMES_TO_EAT
};

enum {
	INPUT,
	N_TIMES_EATEN,
	INDEX,
	TIME_LAST_EAT
};

enum {
	CONTINUE,
	PHILO_DEAD,
	DONE_EATING
};

enum {
	FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
};

typedef struct s_data
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	*lock;
	struct timeval	tv;
	uint64_t		ms_offset;
	int				sim_status;
	int				**philosophers;
}					t_data;

int			ft_atoi( char * );
int			initiateStruct( t_data *, char **, int );
uint64_t	ft_time( t_data *, int, int );
int			PhilosopherLoop( t_data *, int );
void		*dropForks( t_data *, int );
void		ft_sleep( t_data *, int );
char		*ft_itoa( uint64_t );
int			ft_strlen( char * );
char		*printMessage( t_data *, int, int, int );
char		*ft_strjoin( char *, char *, int, int );
int			ft_strncmp( char *, char *, size_t );
int			joinThreads( t_data *, pthread_t * );
int			printError( int, t_data * );
int			checkDeathStatus( t_data * );
void		checkEatStatus( t_data * );
void		freeData( t_data * );

#endif
