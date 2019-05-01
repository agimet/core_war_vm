/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_instructions_calcul.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimet <agimet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:56:30 by agimet            #+#    #+#             */
/*   Updated: 2019/05/01 13:09:23 by agimet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ft_test_encode_and_or_xor(t_u1 encode)
{
	if (encode != RRR && encode != RIR && encode != RDR && encode != DRR
		&& encode != DDR && encode != DIR && encode != IRR && encode != IIR
		&& encode != IDR)
		return (0);
	else
		return (1);
}

void	ft_add_sub(t_all *a, t_process *p)
{
	int	s;
	int	val[3];

	a->args = 0;
	s = 2;
	a->encode = a->ar[(p->pc + 1) % M_S];
	if (a->encode != RRR)
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
	if (p->next_instruction == 4)
		p->r[a->ar[(p->pc + s) % M_S] - 1] = val[0] + val[1];
	if (p->next_instruction == 5)
		p->r[a->ar[(p->pc + s)] - 1] = val[0] - val[1];
	p->carry = (p->r[a->ar[(p->pc + s) % M_S] - 1] == 0) ? 1 : 0;
	p->pc = (p->pc + (s + 1)) % M_S;
}

void	ft_and_or_xor(t_all *a, t_process *p)
{
	int	s;
	int	val[3];

	a->args = 0;
	s = 2;
	a->encode = a->ar[(p->pc + 1) % M_S];
	if (!ft_test_encode_and_or_xor(a->encode))
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
	if (p->next_instruction == 6)
		p->r[a->ar[(p->pc + s - 1) % M_S] - 1] = val[0] & val[1];
	if (p->next_instruction == 7)
		p->r[a->ar[(p->pc + s - 1) % M_S] - 1] = val[0] | val[1];
	if (p->next_instruction == 8)
		p->r[a->ar[(p->pc + s - 1) % M_S] - 1] = val[0] ^ val[1];
	p->carry = (p->r[a->ar[(p->pc + s - 1) % M_S] - 1] == 0) ? 1 : 0;
	p->pc = (p->pc + (s)) % M_S;
}
