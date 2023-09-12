/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bhoitzin <bhoitzin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/29 10:38:18 by bhoitzin      #+#    #+#                 */
/*   Updated: 2023/01/22 19:38:43 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	*monitorPhilosophers( t_data *data, int ix )
{
	while ( 1 )
	{
		if ( pthread_mutex_lock( &data->lock[0] ) != 0 )
			return ( NULL );
		checkEatStatus( data );
		ix = checkDeathStatus( data );
		if ( data->sim_status != CONTINUE )
		{
			if ( data->sim_status == DONE_EATING )
				write( 1, "Philosophers are done eating\n", 29 );
			if ( pthread_mutex_unlock( &data->lock[0] ) != 0 )
				return ( NULL );
			if ( dropForks( data, ix ) == NULL )
				return ( NULL );
			return ( "STOPPED" );
		}
		if ( pthread_mutex_unlock( &data->lock[0] ) != 0 )
			return ( NULL );
		usleep( 500 );
	}
}

static void	*startThread( void *args )
{
	t_data		*data;
	static int	index = 0;
	int			ix, ret;

	data = ( t_data * )args;
	if ( pthread_mutex_lock(&data->lock[1] ) != 0 )
		return ( NULL );
	ix = index;
	index++;
	if ( pthread_mutex_unlock( &data->lock[1] ) != 0 )
		return ( NULL );
	while ( 1 )
	{
		if ( ix == data->philosophers[INPUT][N_PHILO] )
		{
			if ( monitorPhilosophers( data, 0 ) == NULL )
				return ( NULL );
			return ( "STOPPED" );
		}
		else
		{
			ret = PhilosopherLoop( data, ix );
			if ( ret == 0 )
				continue ;
			if ( ret == -1 )
				return ( NULL );
			return ( "STOPPED" );
		}
	}
	return ( "STOPPED" );
}

static int	runSimulation( t_data *data )
{
	pthread_t	*thread = ( pthread_t * )malloc( sizeof( pthread_t ) * ( data->philosophers[INPUT][N_PHILO] + 1 ) );

	if ( thread == NULL )
		return ( MALLOC_ERR );
	for ( int ix = 0; ix <= data->philosophers[INPUT][N_PHILO]; ++ix ) {
		if ( pthread_create( &thread[ix], NULL, startThread, ( void * )data ) )
		{
			for (; ix >= 0; --ix ) {
				free( thread[ix] );
			}
			return ( THREAD_ERR );
		}
	}
	if ( !joinThreads( data, thread ) )
		return ( 0 ) ;
	return ( JOIN_ERR );
}

static int	parseInput( char **av, int ac )
{
	int	i, j, ret;
	
	if ( ac < 5 || ac > 6 || ( ac == 6 && ft_atoi( av[5] ) == 0 ) )
		return ( INPUT_ERR );
	i = 1;
	while ( av[i] != NULL )
	{
		j = 0;
		if ( av[i][j] == '\0' )
			return ( INPUT_ERR );
		while ( av[i][j] != '\0' )
		{
			if ( av[i][j] < '0' || av[i][j] > '9' || j > 6 )
				return ( INPUT_ERR );
			j++;
		}
		ret = ft_atoi( av[i] );
		if ( ret == -1 )
			return ( INPUT_ERR );
		i++;
	}
	if ( av[1][0] == '0' )
		return ( INPUT_ERR );
	return ( 0 );
}

int	main( int ac, char **av )
{
	t_data	data;
	int		error;

	if ( ( error = parseInput( av, ac ) ) )
		return ( printError( error, &data ) );
	if ( ( error = initiateStruct( &data, av, ac ) ) )
		return ( printError( error, &data ) );
	if ( ( error = runSimulation( &data ) ) )
		return ( printError( error, &data ) );
	return ( 0 );
}
