/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_dump_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimet <agimet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:27:56 by agimet            #+#    #+#             */
/*   Updated: 2019/05/08 16:17:43 by agimet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			ft_color(int pc, int pl)
{
	if (pc == 1 && pl == 0)
		ft_putstr_fd("\x1B[47m", 1);
	if (pc == 1 && pl == 1)
		ft_putstr_fd("\x1B[42m", 1);
	if (pc == 1 && pl == 2)
		ft_putstr_fd("\x1B[44m", 1);
	if (pc == 1 && pl == 3)
		ft_putstr_fd("\x1B[41m", 1);
	if (pc == 1 && pl == 4)
		ft_putstr_fd("\x1B[46m", 1);
	if (pc == 0 && pl == 1)
		ft_putstr_fd("\x1B[32m", 1);
	if (pc == 0 && pl == 2)
		ft_putstr_fd("\x1B[34m", 1);
	if (pc == 0 && pl == 3)
		ft_putstr_fd("\x1B[31m", 1);
	if (pc == 0 && pl == 4)
		ft_putstr_fd("\x1B[36m", 1);
}

void			ft_dec_to_hex(int x, int pl, int pc, int mode)
{
	char		tab[5];
	int			i;
	int			nb;
	int			size;

	nb = 0;
	i = 0;
	size = (mode == 0) ? 1 : 3;
	tab[0] = '0';
	tab[1] = '0';
	tab[2] = (mode == 0) ? '\0' : '0';
	tab[3] = (mode == 0) ? '\0' : '0';
	tab[4] = '\0';
	while (x > 0)
	{
		nb = x % 16;
		x /= 16;
		while (i < nb)
			i++;
		tab[size--] = HEXA[i];
		i = 0;
	}
	ft_color(pc, pl);
	ft_putstr_fd(tab, 1);
	ft_putstr_fd("\x1B[0:49m", 1);
}

void			ft_dump_bis(t_all *a, t_process *tmp, int line, int count)
{
	int			i;

	a->dump = 0;
	i = -1;
	while (++i < M_S)
	{
		while (tmp != NULL)
		{
			tmp->pc == i ? a->dump = 1 : (0);
			tmp = tmp->next;
		}
		ft_dec_to_hex(a->ar[i], a->whose[i], a->dump, 0);
		a->dump = 0;
		tmp = a->process;
		(i + 1 == M_S) ? ft_putstr_fd(" \n", 1) : ft_putstr_fd(" ", 1);
		if (i + 1 != M_S && count == 63)
		{
			line += 64;
			ft_putstr_fd("\n0x", 1);
			ft_dec_to_hex(line, count = 0, 0, 1);
			ft_putstr_fd(" : ", 1);
		}
		else
			count++;
	}
}

void			ft_dump(t_all *a)
{
	int			i;
	int			line;
	int			count;
	int			pc;
	t_process	*tmp;

	tmp = a->process;
	i = 0;
	pc = 0;
	count = 0;
	line = 0;
	ft_putstr_fd("0x", 1);
	ft_dec_to_hex(line, 0, 0, 1);
	ft_putstr_fd(" : ", 1);
	ft_dump_bis(a, tmp, line, count);
	a->dump = 1;
}
