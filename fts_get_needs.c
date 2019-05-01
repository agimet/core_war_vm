/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_get_needs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimet <agimet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 12:44:22 by agimet            #+#    #+#             */
/*   Updated: 2019/05/01 19:14:22 by agimet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			ft_get_args(t_u1 arena[M_S], int pc, int size)
{
	t_u1	tab1[2];
	t_u1	tab2[4];

	if (size == 2)
	{
		tab1[0] = arena[(pc + 1) % M_S];
		tab1[1] = arena[pc % M_S];
		return (*(short*)tab1);
	}
	if (size == 4)
	{
		tab2[0] = arena[(pc + 3) % M_S];
		tab2[1] = arena[(pc + 2) % M_S];
		tab2[2] = arena[(pc + 1) % M_S];
		tab2[3] = arena[pc % M_S];
		return (*(int*)tab2);
	}
	return (-1);
}

int			ft_get_value(t_all *a, int pos, t_process *proc, int spec)
{
	int		ret;

	ret = 0;
	if (a->type[a->args] == T_REG)
		return (proc->r[a->ar[(pos) % M_S] - 1]);
	if (a->type[a->args] == T_DIR)
		return (ft_get_args(a->ar, pos, a->size[a->args]));
	if (a->type[a->args] == T_IND)
	{
		ret = ft_get_args(a->ar, pos, a->size[a->args]);
		if (spec == 0)
			return (ret);
		else
			return (ft_get_args(a->ar, proc->pc + (ret % 512), 4));
	}
	return (0);
}

void		ft_get_type(t_u1 encoded, t_u1 (*type)[3], t_u1 (*size)[3], int m)
{
	int		bitwise;

	bitwise = 6;
	(*type)[2] = 0;
	(*size)[2] = 0;
	while (bitwise > 0)
	{
		if (((encoded >> bitwise) & 0b11) == 2)
		{
			(*type)[((bitwise / 2) - 3) * -1] = T_DIR;
			(*size)[((bitwise / 2) - 3) * -1] = (m == 1) ? DIR_SIZE : IND_SIZE;
		}
		else if (((encoded >> bitwise) & 0b11) == 1)
		{
			(*type)[((bitwise / 2) - 3) * -1] = T_REG;
			(*size)[((bitwise / 2) - 3) * -1] = 1;
		}
		else if (((encoded >> bitwise) & 0b11) == 3)
		{
			(*type)[((bitwise / 2) - 3) * -1] = T_IND;
			(*size)[((bitwise / 2) - 3) * -1] = IND_SIZE;
		}
		bitwise -= 2;
	}
}
