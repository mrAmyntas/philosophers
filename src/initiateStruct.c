/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initiateStruct.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bhoitzin <bhoitzin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/30 16:11:47 by bhoitzin      #+#    #+#                 */
/*   Updated: 2023/01/22 19:05:12 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"


static int	allocArrays( t_data *data )
{
	data->philosophers[N_TIMES_EATEN] = ( int * )malloc( sizeof( int ) * data->philosophers[INPUT][N_PHILO] );
	if ( data->philosophers[N_TIMES_EATEN] == NULL )
		return ( MALLOC_ERR );
	data->philosophers[INDEX] = ( int * )malloc( sizeof( int ) * data->philosophers[INPUT][N_PHILO] );
	if ( data->philosophers[INDEX] == NULL )
		return ( MALLOC_ERR );
	data->philosophers[TIME_LAST_EAT] = ( int * )malloc( sizeof( int ) * data->philosophers[INPUT][N_PHILO] );
	if ( data->philosophers[TIME_LAST_EAT] == NULL )
		return ( MALLOC_ERR );
	data->fork = ( pthread_mutex_t * )malloc( sizeof( pthread_mutex_t ) * data->philosophers[INPUT][N_PHILO] );
	if ( data->fork == NULL )
		return ( MALLOC_ERR );
	data->lock = ( pthread_mutex_t * )malloc( sizeof( pthread_mutex_t ) * 2 );
	if ( data->lock == NULL )
		return ( MALLOC_ERR );
	return ( 0 );
}

static int	initArrays( t_data *data, int ac )
{
	data->ms_offset = 0;
	data->sim_status = CONTINUE;
	for ( int i = 0; i < data->philosophers[INPUT][N_PHILO]; ++i ) {
		data->philosophers[N_TIMES_EATEN][i] = -1;
		data->philosophers[INDEX][i] = 0;
		data->philosophers[TIME_LAST_EAT] = -1;
		double x = i;
		if ( ( x / 2 ) != ( i / 2 ) )
			data->philosophers[INDEX][i] = 1;
	}
	if ( pthread_mutex_init( &data->lock[0], NULL ) != 0 )
		return ( INIT_ERR );
	if ( pthread_mutex_init( &data->lock[1], NULL ) != 0 )
		return ( INIT_ERR );
	for ( int i = 0; i < data->philosophers[INPUT][N_PHILO]; ++i ) {
		if ( pthread_mutex_init( &data->fork[i], NULL ) != 0 )
			return ( INIT_ERR );
	}
	return ( 0 );
}

int	initiateStruct( t_data *data, char **av, int ac )
{
	data->philosophers = ( int ** )malloc( sizeof( int * ) *  4 );
	if ( data->philosophers == NULL )
		return ( MALLOC_ERR );
	data->philosophers[INPUT] = ( int * )malloc( sizeof( int ) * ( ac - 1 ) );
	if ( data->philosophers[INPUT] == NULL )
		return ( MALLOC_ERR );
	for ( int i = 1; i < ac; ++i ) {
		data->philosophers[INPUT][i - 1] = ft_atoi( av[i] );
		i++;
	}
	if ( allocArrays( data ) )
		return ( MALLOC_ERR );
	if ( initArrays( data, ac ) )
		return ( INIT_ERR );
	gettimeofday( &data->tv, NULL );
	data->ms_offset = ( data->tv.tv_sec * 1000 ) + ( data->tv.tv_usec / 1000 );
	return ( 0 );
}
