/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_lib.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 21:52:10 by rsiah             #+#    #+#             */
/*   Updated: 2025/03/31 16:16:38 by rsiah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*output;
	size_t	n;

	if (nmemb == 0 || size == 0)
		return (NULL);
	n = nmemb * size;
	if (n / nmemb != size)
		return (NULL);
	output = malloc(n);
	if (!output)
		return (write(2, "malloc error\n", 14), output);
	return (ft_bzero(output, n), output);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;
	unsigned char	*tmp;

	i = 0;
	tmp = (unsigned char *)s;
	while (i < n)
	{
		tmp[i] = 0;
		i++;
	}
}

// Returns 2048 if string is only digits
int	ft_aredigits(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (2048);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	return (0);
}

/**
 * Convert char type to int type.
 */
int	ft_atoi(const char *nptr)
{
	int	i;
	int	output;
	int	sign;

	i = 0;
	output = 0;
	sign = 1;
	if (nptr[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (ft_isdigit(nptr[i]))
	{
		output *= 10;
		output += nptr[i] - '0';
		i++;
	}
	return (output * sign);
}
