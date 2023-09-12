/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_death.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bhoitzin <bhoitzin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/31 16:00:36 by bhoitzin      #+#    #+#                 */
/*   Updated: 2023/01/22 19:10:11 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

uint64_t	ft_time(t_data *data, int eat, int ix )
{
	uint64_t	ms;

	gettimeofday( &data->tv, NULL );
	ms = ( data->tv.tv_sec * 1000 ) + ( data->tv.tv_usec / 1000 ) - data->ms_offset;
	if ( eat == 1 )
		data->philosophers[TIME_LAST_EAT][ix] = ms;
	return ( ms );
}

void	ft_sleep(t_data *data, int x)
{
	uint64_t	ms_now;
	uint64_t	y;

	gettimeofday(&data->tv, NULL);
	ms_now = ( data->tv.tv_sec * 1000 ) + ( data->tv.tv_usec / 1000 ) - data->ms_offset;
	y = x;
	if ( y == 0 )
		y = 2;
	while ( ( ft_time( data, 0, 0 ) - ms_now ) < y )
		usleep(100);
	return ;
}

int	checkDeathStatus( t_data *data )
{
	uint64_t	ms_now, x;
	int			ms_no;
	int			ix;

	gettimeofday( &data->tv, NULL );
	ms_now = ( data->tv.tv_sec * 1000 ) + ( data->tv.tv_usec / 1000 ) - data->ms_offset;
	ms_no = ms_now;
	ix = 0;
	while ( ix < data->philosophers[INPUT][N_PHILO] )
	{
		x = data->philosophers[TIME_LAST_EAT][ix];
		if ( data->philosophers[TIME_LAST_EAT][ix] == -1 )
			x = 0;
		if (data->philosophers[INPUT][TIME_TO_DIE] <= ( ms_now - x ) )
		{
			if ( !printMessage( data, ix, 4, 0 ) )
				return ( -1 );
			data->sim_status = PHILO_DEAD;
			return ( ix );
		}
		ix++;
	}
	return ( 0 );
}

void	checkEatStatus( t_data *data )
{
	int	i;

	i = 0;
	while ( i < data->philosophers[INPUT][N_PHILO] )
	{
		if (data->philosophers[N_TIMES_EATEN][i] != data->philosophers[INPUT][N_TIMES_TO_EAT] )
			break ;
		i++;
	}
	if (i == data->philosophers[INPUT][N_PHILO] )
		data->sim_status = DONE_EATING;
}
