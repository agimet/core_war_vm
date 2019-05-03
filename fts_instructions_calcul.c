/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_instructions_calcul.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimet <agimet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:56:30 by agimet            #+#    #+#             */
/*   Updated: 2019/05/03 14:45:11 by agimet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


void	ft_add_sub(t_all *a, t_process *p, int val[2])
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

void	ft_and_or_xor(t_all *a, t_process *p, int val[2])
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

// int		ft_test_encode_add_sub(int *pc, t_u1 encode)
// {
// 	if (encode != RRR)
// 	{
// 		*pc += 2;
// 		*pc %= M_S;
// 		return (0);
// 	}
// 	return (1);
// }

// int		ft_test_encode_and_or_xor(int *pc, t_u1 encode)
// {
// 	if (encode != RRR && encode != RIR && encode != RDR && encode != DRR
// 		&& encode != DDR && encode != DIR && encode != IRR && encode != IIR
// 		&& encode != IDR)
// 	{
// 		*pc += 2;
// 		*pc %= M_S;
// 		return (0);
// 	}
// 	return (1);
// }
