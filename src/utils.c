/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bhoitzin <bhoitzin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/29 11:09:03 by bhoitzin      #+#    #+#                 */
/*   Updated: 2023/01/22 19:18:14 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	ft_atoi( char *str )
{
	long long unsigned int	i = 0, n = 0;

	while ( str[i] != '\0' )
	{
		n = n * 10 + str[i] - 48;
		i++;
	}
	i = INT_MAX;
	if ( n > i )
		return ( -1 );
	return ( n );
}

void	*dropForks( t_data *data, int ix )
{
	if ( pthread_mutex_unlock( &data->fork[ix] ) )
		return ( NULL );
	if ( ix == 0 )
	{
		if ( pthread_mutex_unlock( &data->fork[data->philosophers[INPUT][N_PHILO] - 1] ) )
			return ( NULL );
	}
	else
	{
		if ( pthread_mutex_unlock( &data->fork[ix - 1] ) )
			return ( NULL );
	}
	return ( "OK" );
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	int				i;
	int				j;
	unsigned char	*str1;
	unsigned char	*str2;

	if (s1 == NULL || s2 == NULL)
		return (-1);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (n != 0)
	{
		if (str1[i] == '\0' && str2[i] == '\0')
			return (0);
		if (str1[i] != str2[i])
		{
			j = str1[i] - str2[i];
			return (j);
		}
		i++;
		n--;
	}
	return (0);
}

void freeData( t_data *data )
{
	for ( int i = 0; data->philosophers[i]; i++ ) {
		free( data->philosophers[i] );
	}
	if ( data->philosophers )
		free( data->philosophers );
	if ( data->fork )
		free( data->fork );
	if ( data->lock )
		free( data->lock );
}

int	printError( int error, t_data *data )
{
	if ( error == INPUT_ERR ) 
		write( 2, "arguments should be: [number of philosophers (not 0)] [time to die] [time to eat] [time to sleep] and optionally [number of times to eat (not 0)]\n", 147 );
	if ( error == MALLOC_ERR ) 
		write( 2, "Error allocating memory\n", 25 );
	if ( error == INIT_ERR ) 
		write( 2, "Error  initializing mutexes\n", 29 );
	freeData( data );
	return ( 1 );
}
