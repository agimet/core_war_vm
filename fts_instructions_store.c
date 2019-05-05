/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_instructions_store.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimet <agimet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:55:49 by agimet            #+#    #+#             */
/*   Updated: 2019/05/05 16:49:21 by agimet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


void	ft_st(t_all *a, t_process *p, int val[3])
{
	if (a->encode == RR)
		p->r[a->ar[p->pc + 3] - 1] = p->r[a->ar[p->pc + 2] - 1];
	if (a->encode == RI)
		ft_reg_to_arena(a, val[0], (p->pc + (val[1] % IDX_MOD)) % M_S, p->pl);
	p->pc += (2 + a->size[0] + a->size[1] + a->size[2]);
	p->pc %= M_S;
}

void	ft_sti(t_all *a, t_process *p, int val[3])
{
	ft_putstr_fd("val 0 = ", 1);ft_putnbr(val[0]);ft_putstr_fd(" val 1 = ", 1);ft_putnbr(val[1]);ft_putstr_fd(" val 2 = ", 1);ft_putnbr(val[2]);ft_putstr_fd("\n", 1);
	ft_putstr_fd("et donc : ", 1);ft_putnbr((p->pc + ((val[1] + val[2]) % IDX_MOD)) % M_S);ft_putstr_fd("\n", 1);
	
	ft_reg_to_arena(a, val[0], (p->pc + ((val[1] + val[2]) % IDX_MOD)) % M_S, p->pl);
	p->pc += (2 + a->size[0] + a->size[1] + a->size[2]);
	p->pc %= M_S;
}
