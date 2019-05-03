/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_lib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimet <agimet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 12:13:18 by agimet            #+#    #+#             */
/*   Updated: 2019/05/03 15:03:02 by agimet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			*ft_memcpy(void *dest, const void *src, size_t len)
{
	size_t		i;
	char		*cdest;
	char		*csrc;

	cdest = (char *)dest;
	csrc = (char *)src;
	i = 0;
	while (i < len && dest != src)
	{
		cdest[i] = csrc[i];
		i++;
	}
	return (dest);
}

int				ft_atoi(const char *str)
{
	long long	x;
	int			i;
	int			count;

	count = 0;
	i = 1;
	x = 2;
	while ((str[count] > 7 && str[count] < 14) || str[count] == 32)
		count++;
	if (str[count] == 45)
		i = -1;
	if (str[count] == 45 || str[count] == 43)
		count++;
	if (str[count] > 47 && str[count] < 58)
	{
		x = (str[count++] - 48);
		while (str[count] > 47 && str[count] < 58)
			x = x * 10 + (str[count++] - 48);
	}
	else
		return (0);
	(x > 2147483647) ? (x = 2147483647) : (0);
	return (x * i);
}

void			*ft_memset(void *s, int c, size_t n)
{
	size_t		i;
	char		*d;

	d = (char *)s;
	i = 0;
	while (i < n)
	{
		d[i] = (unsigned char)c;
		i++;
	}
	return (d);
}

size_t	ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putnbr(int nb)
{
	unsigned int n;

	n = nb;
	if (nb < 0)
	{
		ft_putchar('-');
		n = nb * -1;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		ft_putchar(n + '0');
	}
}