/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bhoitzin <bhoitzin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/26 18:04:50 by bhoitzin      #+#    #+#                 */
/*   Updated: 2023/01/22 19:32:49 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static char	*ft_allocmem( char *s1, char *s2, int x )
{
	char	*buff;

	if ( ( s1 == NULL ) || ( s2 == NULL ) )
		return ( NULL );
	x = ft_strlen( s1 ) + ft_strlen( s2 ) + 2;
	buff = ( char * )malloc( sizeof( char ) * x );
	if ( buff == NULL )
		return ( NULL );
	return ( buff );
}

char	*ft_strjoin(char *s1, char *s2, int y, int i)
{
	char	*buff;
	int		x;

	buff = ft_allocmem(s1, s2, 0);
	if (buff == NULL)
		return (NULL);
	x = 0;
	while (s1[x] != '\0')
	{
		buff[x] = s1[x];
		x++;
	}
	buff[x] = ' ';
	while (s2[i] != '\0')
	{
		buff[x + 1] = s2[i];
		i++;
		x++;
	}
	buff[x + 1] = '\0';
	free(s1);
	if (y == 1)
		free(s2);
	return (buff);
}

int	ft_strlen( char *str )
{
	int	i = 0;

	if ( str == NULL )
		return ( -1 );
	while ( str[i] != '\0' )
		i++;
	return ( i );
}

int	joinThreads( t_data *data, pthread_t *thread )
{
	int		ix = 0;
	void	*ret;

	while ( ix <= data->philosophers[INPUT][N_PHILO] )
	{
		if ( pthread_join( thread[ix], &ret ) != 0 || ret == NULL )
		{
			free( thread );
			freeData( data );
			return ( -1 );
		}
		if ( ix == data->philosophers[INPUT][N_PHILO] )
		{
			free( thread );
			freeData( data );
			return ( 0 );
		}
		ix++;
	}
	return ( -1 );
}
