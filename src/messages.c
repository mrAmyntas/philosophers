/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   messages.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bhoitzin <bhoitzin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/27 15:52:26 by bhoitzin      #+#    #+#                 */
/*   Updated: 2023/01/22 18:25:18 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static char	*ft_reverse_buff(char *buff)
{
	int		i;
	int		j;
	char	str;

	i = 0;
	while (buff[i] != '\0')
		i++;
	i--;
	j = 0;
	if (buff[j] == '-')
		j++;
	while (i >= j)
	{
		str = buff[i];
		buff[i] = buff[j];
		buff[j] = str;
		i--;
		j++;
	}
	return (buff);
}

static char	*ft_fillbuff(uint64_t n, char *buff, int z)
{
	int			i;
	long int	y;

	y = 10;
	i = 0;
	while (i < z)
	{
		buff[i] = (n % y / (y / 10) + 48);
		i++;
		y = y * 10;
	}
	buff[i] = '\0';
	return (buff);
}

char	*ft_itoa( uint64_t n )
{
	char	*buff;
	int		z;
	int		y;

	y = 10;
	z = 1;
	while ( n / y >= 1 )
	{
		y = y * 10;
		z++;
	}
	buff = ( char * )malloc( sizeof( char ) * ( z + 1 ) );
	if ( buff == NULL )
		return ( NULL );
	buff = ft_fillbuff( n, buff, z );
	buff = ft_reverse_buff( buff );
	return ( buff );
}

static char	*ft_wr_mes2( char *str1, char *str2, int x )
{
	int	i;

	str1 = ft_strjoin( str1, str2, 1, 0 );
	if ( str1 == NULL )
	{
		free( str1 );
		free( str2 );
		return ( NULL );
	}
	if ( x == FORK )
		str1 = ft_strjoin(str1, "has taken a fork\n", 0, 0);
	else if (x == 1)
		str1 = ft_strjoin(str1, "is eating\n", 0, 0);
	else if (x == 2)
		str1 = ft_strjoin(str1, "is sleeping\n", 0, 0);
	else if (x == 3)
		str1 = ft_strjoin(str1, "is thinking\n", 0, 0);
	else if (x == 4)
		str1 = ft_strjoin(str1, "is dead\n", 0, 0);
	i = ft_strlen(str1);
	write(1, str1, i);
	free(str1);
	return ("OK");
}

char	*printMessage(t_data *data, int msg, int x, int eat)
{
	char		*str1;
	char		*str2;
	uint64_t	tijd;
	uint64_t	msg2;

	msg2 = msg;
	tijd = ft_time(data, eat, msg);
	str1 = ft_itoa(tijd);
	if (str1 == NULL)
		return (NULL);
	str2 = ft_itoa(msg2);
	if (str2 == NULL)
	{
		free(str1);
		return (NULL);
	}
	if (ft_wr_mes2(str1, str2, x) == NULL)
		return (NULL);
	return ("OK");
}
