/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopherLoop.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bhoitzin <bhoitzin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/12 19:48:01 by bhoitzin      #+#    #+#                 */
/*   Updated: 2023/01/22 19:43:47 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static int	ft_check_dead_done(t_data *data, int num, int x, int eat)
{
	if ( data->sim_status != CONTINUE )
	{
		if ( x == 1 )
		{
			if ( pthread_mutex_unlock( &data->fork[num] ) )
				return ( ERROR );
		}
		if ( x == 2 )
		{
			if ( ft_drop_forks( data, num ) == NULL )
				return ( ERROR );
		}
		if ( pthread_mutex_unlock( &data->lock[0] ) != 0 )
			return ( ERROR );
		return ( DONE );
	}
	if ( eat == 1 )
	{
		if ( !printMessage( data, num, 1, 1 ) )
			return ( ERROR );
	}
	return ( 0 );
}

static int	SleepIfOdd( t_data *data, int num )
{
	if ( data->philosophers[N_TIMES_EATEN][num] == -1 )
	{
		if ( pthread_mutex_lock( &data->lock[0] ) != 0 )
			return ( ERROR );
		data->philosophers[N_TIMES_EATEN][num] = 0;
		if ( pthread_mutex_unlock( &data->lock[0] ) != 0 )
			return ( ERROR );
		if ( data->philosophers[INDEX][num] == 1 )
		{
			if ( data->philosophers[INPUT][TIME_TO_EAT] < 2 )
			{
				usleep( 2000 );
				return ( 0 );
			}
			usleep( ( data->philosophers[INPUT][TIME_TO_EAT] * 1000 ) - 2000 );
		}
	}
	return ( 0 );
}

static int	ft_think_eat_sleep3(t_data *data, int ix, int y)
{
	if (!printMessage(data, ix, 2, 0))
		return ( ERROR );
	if (pthread_mutex_unlock(&data->lock[0]) != 0)
		return ( ERROR );
	ft_sleep(data, data->philosophers[3]);
	if (pthread_mutex_lock(&data->lock[0]) != 0)
		return ( ERROR );
	y = ft_check_dead_done(data, ix, 0, 0);
	if (y != 0)
		return (y);
	if (!printMessage(data, ix, 3, 0))
		return ( ERROR );
	if (pthread_mutex_unlock(&data->lock[0]) != 0)
		return ( ERROR );
	return (0);
}

static int	ft_think_eat_sleep2( t_data *data, int ix, int y )
{
	if ( y != 0 )
		return ( y );
	if (!printMessage( data, ix, 0, 0 ) )
		return ( ERROR );
	y = ft_check_dead_done( data, ix, 2, 1 );
	if ( y != 0 )
		return ( y );
	if (pthread_mutex_unlock( &data->lock[0] ) != 0 )
		return ( ERROR );
	ft_sleep( data, data->philosophers[2] );
	if ( ft_drop_forks( data, ix ) == NULL )
		return ( ERROR );
	if ( pthread_mutex_lock(&data->lock[0]) != 0 )
		return ( ERROR );
	if ( data->philosophers[N_TIMES_EATEN][ix] > 0 )
		data->philosophers[N_TIMES_EATEN][ix]++;
	y = ft_check_dead_done( data, ix, 0, 0 );
	if ( y != 0 )
		return ( y );
	y = ft_think_eat_sleep3( data, ix, y );
	return ( y );
}

int	PhilosopherLoop( t_data *data, int ix )
{
	int	y = 0;
	int	x = ix - 1;

	if ( ix == 0 )
		x = ( data->philosophers[0] - 1 );
	y = SleepIfOdd( data, ix );
	if ( y != 0 )
		return ( y );
	if ( pthread_mutex_lock( &data->fork[ix] ) )
		return ( ERROR );
	if ( pthread_mutex_lock( &data->lock[0] ) != 0 )
		return ( ERROR );
	y = ft_check_dead_done( data, ix, 1, 0 );
	if ( y != 0 )
		return ( y );
	if ( !printMessage( data, ix, 0, 0 ) )
		return ( ERROR );
	if ( pthread_mutex_unlock( &data->lock[0] ) != 0 )
		return ( ERROR );
	if ( pthread_mutex_lock( &data->fork[x] ) )
		return ( ERROR );
	if ( pthread_mutex_lock( &data->lock[0] ) != 0 )
		return ( ERROR );
	y = ft_check_dead_done( data, ix, 2, 0 );
	y = ft_think_eat_sleep2( data, ix, y );
	return ( y );
}
