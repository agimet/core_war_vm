/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_lib2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimet <agimet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 12:18:12 by agimet            #+#    #+#             */
/*   Updated: 2019/05/03 15:01:08 by agimet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr(char const *s)
{
	int i;

	i = 0;
	if (s == NULL)
		return ;
	if (s != NULL)
	{
		while (s[i])
		{
			ft_putchar(s[i]);
			i++;
		}
	}
}

void	ft_putendl_fd(char const *s, int fd)
{
	int	i;

	i = 0;
	if (s != NULL && fd != 0)
	{
		while (s[i])
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
		ft_putchar_fd('\n', fd);
	}
}
