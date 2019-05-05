/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_instructions_calcul.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimet <agimet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:56:30 by agimet            #+#    #+#             */
/*   Updated: 2019/05/05 14:11:57 by agimet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


void	ft_add_sub(t_all *a, t_process *p, int val[3])
{
	int pos;

	pos = 1 + a->size[0] + a->size[1] + a->size[2];
	if (p->next_instruction == 4)
		p->r[a->ar[(p->pc + pos) % M_S] - 1] = val[0] + val[1];
	if (p->next_instruction == 5)
		p->r[a->ar[(p->pc + pos)] - 1] = val[0] - val[1];
	p->carry = (p->r[a->ar[(p->pc + pos) % M_S] - 1] == 0) ? 1 : 0;
	p->pc = (p->pc + (pos + 1)) % M_S;
}

void	ft_and_or_xor(t_all *a, t_process *p, int val[3])
{
	int pos;

	pos = 1 + a->size[0] + a->size[1] + a->size[2];
	if (p->next_instruction == 6)
		p->r[a->ar[(p->pc + pos) % M_S] - 1] = val[0] & val[1];
	if (p->next_instruction == 7)
		p->r[a->ar[(p->pc + pos) % M_S] - 1] = val[0] | val[1];
	if (p->next_instruction == 8)
		p->r[a->ar[(p->pc + pos) % M_S] - 1] = val[0] ^ val[1];
	p->carry = (p->r[a->ar[(p->pc + pos) % M_S] - 1] == 0) ? 1 : 0;
	p->pc = (p->pc + (pos + 1)) % M_S;
}
