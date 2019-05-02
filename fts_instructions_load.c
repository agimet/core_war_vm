/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_instructions_load.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimet <agimet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:55:11 by agimet            #+#    #+#             */
/*   Updated: 2019/05/01 19:53:40 by agimet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			ft_test_encode_ld_family(int *pc, t_u1 encode, int which)
{
	if (which == 1 && encode != IR && encode != DR)
	{
		*pc += 2;
		*pc %= M_S;
		return (0);
	}
	if (which == 2 && encode != RRR && encode != RDR && encode != DDR
		&& encode != DRR && encode != IDR && encode != IRR)
	{
		*pc += 2;
		*pc %= M_S;
		return (0);
	}
	return (1);
}

void		ft_ld(t_all *a, t_process *p)
{
	int		s;
	int		val[3];

	a->args = 0;
	s = 2;
	a->encode = a->ar[(p->pc + 1) % M_S];
	if (!ft_test_encode_ld_family(&(p->pc), a->encode, 1))
		return ;
	ft_get_type(a->encode, &(a->type), &(a->size), 1);
	while (a->args < 3)
	{
		if (a->type[a->args] == T_REG && (a->ar[(p->pc + s) % M_S] <= 0
			|| a->ar[(p->pc + s) % M_S] > 16))
			return (ft_wrong_reg(&(p->pc), a->size));
		val[a->args] = ft_get_value(a, p->pc + s, p, 1);
		s += a->size[a->args++];
	}
	s = 1 + a->size[0] + a->size[1] + a->size[2];
	p->r[a->ar[(p->pc + s) % M_S] - 1] = val[0];
	p->carry = (val[0] == 0) ? 1 : 0;
	p->pc = (p->pc + s + 1) % M_S;
}

void		ft_lld(t_all *a, t_process *p)
{
	int		s;
	int		val[3];

	a->args = 0;
	s = 2;
	a->encode = a->ar[(p->pc + 1) % M_S];
	if (!ft_test_encode_ld_family(&(p->pc), a->encode, 1))
		return ;
	ft_get_type(a->encode, &(a->type), &(a->size), 1);
	while (a->args < 3)
	{
		if (a->type[a->args] == T_REG && (a->ar[(p->pc + s) % M_S] <= 0
			|| a->ar[(p->pc + s) % M_S] > 16))
			return (ft_wrong_reg(&(p->pc), a->size));
		val[a->args] = ft_get_value(a, p->pc + s, p, 0);
		s += a->size[a->args++];
	}
	s = 1 + a->size[0] + a->size[1] + a->size[2];
	if (a->encode == DR)
		p->r[a->ar[(p->pc + s) % M_S] - 1] = val[0];
	if (a->encode == IR)
		p->r[a->ar[(p->pc + s) % M_S] - 1] = ft_get_args(a->ar, p->pc
		+ val[0], 4);
	p->carry = (p->r[a->ar[(p->pc + s) % M_S] - 1] == 0) ? 1 : 0;
	p->pc = (p->pc + s + 1) % M_S;
}

void		ft_ldi(t_all *a, t_process *p)
{
	int		s;
	int		val[3];

	a->args = 0;
	s = 2;
	a->encode = a->ar[(p->pc + 1) % M_S];
	if (!ft_test_encode_ld_family(&(p->pc), a->encode, 2))
		return ;
	ft_get_type(a->encode, &(a->type), &(a->size), 0);
	while (a->args < 3)
	{
		if (a->type[a->args] == T_REG && (a->ar[(p->pc + s) % M_S] <= 0
			|| a->ar[(p->pc + s) % M_S] > 16))
			return (ft_wrong_reg(&(p->pc), a->size));
		val[a->args] = ft_get_value(a, p->pc + s, p, 1);
		s += a->size[a->args++];
	}
	s = 1 + a->size[0] + a->size[1] + a->size[2];
	p->r[a->ar[p->pc + s] - 1] = ft_get_args(a->ar, p->pc
		+ ((val[0] + val[1]) % IDX_MOD), REG_SIZE);
	p->pc = (p->pc + s + 1) % M_S;
}

void		ft_lldi(t_all *a, t_process *p)
{
	int		s;
	int		val[3];

	a->args = 0;
	s = 2;
	a->encode = a->ar[(p->pc + 1) % M_S];
	if (!ft_test_encode_ld_family(&(p->pc), a->encode, 2))
		return ;
	ft_get_type(a->encode, &(a->type), &(a->size), 0);
	while (a->args < 3)
	{
		if (a->type[a->args] == T_REG && (a->ar[(p->pc + s) % M_S] <= 0
			|| a->ar[(p->pc + s) % M_S] > 16))
			return (ft_wrong_reg(&(p->pc), a->size));
		val[a->args] = ft_get_value(a, p->pc + s, p, 0);
		s += a->size[a->args++];
	}
	s = 1 + a->size[0] + a->size[1] + a->size[2];
	p->r[a->ar[(p->pc + s) % M_S] - 1] = ft_get_args(a->ar, p->pc
		+ val[0] + val[1], REG_SIZE);
	p->carry = (p->r[a->ar[(p->pc + s) % M_S] - 1] == 0) ? 1 : 0;
	p->pc = (p->pc + s + 1) % M_S;
}
