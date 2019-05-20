/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_utilities_for_instru.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimet <agimet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:59:54 by agimet            #+#    #+#             */
/*   Updated: 2019/05/05 13:53:23 by agimet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				ft_reg_to_arena_bis(t_all *a, int add, t_u1 res[4], int pl)
{
	add %= 4096;
	a->ar[add < 0 ? ((4096 + add) % M_S) : ((add % M_S))] = res[0];
	a->ar[add + 1 < 0 ? ((4096 + add + 1) % M_S) : ((add + 1) % M_S)] = res[1];
	a->ar[add + 2 < 0 ? ((4096 + add + 2) % M_S) : ((add + 2) % M_S)] = res[2];
	a->ar[add + 3 < 0 ? ((4096 + add + 3) % M_S) : ((add + 3) % M_S)] = res[3];
	a->whose[add < 0 ? ((4096 + add) % M_S) : (add % M_S)] = pl;
	a->whose[add + 1 < 0 ? ((4096 + add + 1) % M_S) : ((add + 1) % M_S)] = pl;
	a->whose[add + 2 < 0 ? ((4096 + add + 2) % M_S) : ((add + 2) % M_S)] = pl;
	a->whose[add + 3 < 0 ? ((4096 + add + 3) % M_S) : ((add + 3) % M_S)] = pl;
}

void				ft_reg_to_arena(t_all *a, t_u4 value, int addr, int pl)
{
	int				i;
	int				j;
	t_u4			nb;
	t_u1			x[2];
	t_u1			res[4];

	j = 4;
	i = 0;
	nb = 0;
	x[1] = 0;
	x[0] = 0;
	while (--j >= 0)
	{
		nb = value % 16;
		value /= 16;
		x[1] = nb;
		nb = value % 16;
		value /= 16;
		x[0] = nb;
		res[j] = (x[0] * 16) + x[1];
		x[1] = 0;
		x[0] = 0;
		i = 0;
	}
	ft_reg_to_arena_bis(a, addr, res, pl);
}

void				ft_wrong_reg(int *pc, t_u1 size[3])
{
	*pc += (2 + size[0] + size[1] + size[2]) % M_S;
	return ;
}

int					ft_real_player(int nb_pl, int value)
{
	int				i;

	i = 0;
	nb_pl = 0;
	if (value == -1)
		return (1);
	if (value == -2)
		return (1);
	if (value == -3)
		return (1);
	if (value == -4)
		return (1);
	return (0);
}

void				ft_winner(t_all *a)
{
	ft_putstr_fd("\"", 1);
	if (a->pl[0].num_player == a->last_alive)
		ft_putstr_fd((char *)a->pl[0].name, 1);
	if (a->pl[1].num_player == a->last_alive)
		ft_putstr_fd((char *)a->pl[1].name, 1);
	if (a->pl[2].num_player == a->last_alive)
		ft_putstr_fd((char *)a->pl[2].name, 1);
	if (a->pl[3].num_player == a->last_alive)
		ft_putstr_fd((char *)a->pl[3].name, 1);
	ft_putstr_fd("\"", 1);
}
