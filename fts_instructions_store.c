/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_instructions_store.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimet <agimet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:55:49 by agimet            #+#    #+#             */
/*   Updated: 2019/05/03 14:45:24 by agimet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


void	ft_st(t_all *a, t_process *p, int val[2])
{
	if (a->encode == RR)
		p->r[a->ar[p->pc + 3] - 1] = p->r[a->ar[p->pc + 2] - 1];
	if (a->encode == RI)
		ft_reg_to_arena(a, val[0], (p->pc + (val[1] % IDX_MOD)) % M_S, p->pl);
	p->pc += (2 + a->size[0] + a->size[1] + a->size[2]);
	p->pc %= M_S;
}

void	ft_sti(t_all *a, t_process *p, int val[2])
{
	ft_reg_to_arena(a, val[0], (p->pc + ((val[1] + val[2]) % IDX_MOD)) % M_S, p->pl);
	p->pc += (2 + a->size[0] + a->size[1] + a->size[2]);
	p->pc %= M_S;
}

// int		ft_test_encode_st_family(int *pc, t_u1 encode, int which)
// {
// 	if (which == 1 && encode != RI && encode != RR)
// 	{
// 		*pc += 2;
// 		*pc %= M_S;
// 		return (0);
// 	}
// 	if (which == 2 && encode != RDR && encode != RIR && encode != RRR
// 		&& encode != RDD && encode != RID && encode != RRD)
// 	{
// 		*pc += 2;
// 		*pc %= M_S;
// 		return (0);
// 	}
// 	return (1);
// }