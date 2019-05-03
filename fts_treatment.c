/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_treatment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimet <agimet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 12:15:58 by agimet            #+#    #+#             */
/*   Updated: 2019/05/03 15:05:37 by agimet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ft_test_code(int code, t_process *p)
{
	int		types[2];

	types[0] = 0;
	types[1] = 0;
	types[2] = 0;
	if (code == 0b111)
	{

	}
	if (code == )
}

int		ft_number_reg(t_all *a, t_process *p, int pos)
{
	if (a->ar[(p->pc + pos) % M_S] <= 0 || a->ar[(p->pc + pos) % M_S] > 16)
		return (0);
	return (1);
}

void	ft_which_instru(t_all *a, t_process *p)
{
	int args;
	int pos;
	int value[2];

	args = 0;
	pos = 2;
	value[0] = 0;
	value[1] = 0;
	value[2] = 0;
	a->encode = a->ar[(p->pc + 1) % M_S];
	if (!ft_test_code())
		return ;
	ft_get_type(a->encode, &(a->type), &(a->size), g_op_tab[p->next_instruction].direct_address);
	while (args < g_op_tab[p->next_instruction].nargs)
	{
		if (a->type[args] == T_REG && !ft_number_reg(a, p, pos))
			return (ft_wrong_reg(&(p->pc), a->size));
		value[args] = ft_get_value(a, p->pc + pos, p, g_op_tab[p->next_instruction].spec_addr);
		pos += a->size[args];
	}
	g_op_tab[p->next_instruction].instr(a, p, value);
}