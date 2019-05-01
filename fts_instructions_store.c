/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_instructions_store.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimet <agimet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:55:49 by agimet            #+#    #+#             */
/*   Updated: 2019/05/01 13:43:53 by agimet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_st(t_all *a, t_process *p)
{
	int	s;
	int	value[3];

	a->args = 0;
	s = 2;
	a->encode = a->ar[(p->pc + 1) % M_S];
	if (a->encode != RI && a->encode != RR)
		return ;
	ft_get_type(a->encode, &(a->type), &(a->size), 0);
	while (a->args < 3)
	{
		if (a->type[a->args] == T_REG && (a->ar[(p->pc + s) % M_S] <= 0
			|| a->ar[(p->pc + s) % M_S] > 16))
			return (ft_wrong_reg(&(p->pc), a->size));
		value[a->args] = ft_get_value(a, p->pc + s, p, 0);
		s += a->size[a->args++];
	}
	if (a->encode == RR)
		p->r[a->ar[p->pc + 3] - 1] = p->r[a->ar[p->pc + 2] - 1];
	if (a->encode == RI)
		ft_reg_to_arena(a, value[0], (p->pc
		+ (value[1] % IDX_MOD)) % M_S, p->pl);
	p->pc += (2 + a->size[0] + a->size[1] + a->size[2]);
	p->pc %= M_S;
}

void	ft_sti(t_all *a, t_process *p)
{
	int	s;
	int	value[3];

	a->args = 0;
	s = 2;
	a->encode = a->ar[(p->pc + 1) % M_S];
	if (a->encode != RDR && a->encode != RIR && a->encode != RRR
		&& a->encode != RDD && a->encode != RID && a->encode != RRD)
		return ;
	ft_get_type(a->encode, &(a->type), &(a->size), 0);
	while (a->args < 3)
	{
		if (a->type[a->args] == T_REG && (a->ar[(p->pc + s) % M_S] <= 0
			|| a->ar[(p->pc + s) % M_S] > 16))
			return (ft_wrong_reg(&(p->pc), a->size));
		value[a->args] = ft_get_value(a, p->pc + s, p, 1);
		s += a->size[a->args++];
	}
	ft_reg_to_arena(a, value[0], (p->pc
		+ ((value[1] + value[2]) % IDX_MOD)) % M_S, p->pl);
	p->pc += (2 + a->size[0] + a->size[1] + a->size[2]);
	p->pc %= M_S;
}
