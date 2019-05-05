/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_treatment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimet <agimet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 12:15:58 by agimet            #+#    #+#             */
/*   Updated: 2019/05/05 16:59:15 by agimet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ft_test_code(int x, t_process *p)
{
	int encode;
	int i;

	i = p->next_instruction;
	encode = 1;
	if (i == 16 && x != R)
		encode = 0;
	if (i == 3 && x != RI && x != RR)
		encode = 0;
	if ((i == 4 || i == 5) && x != RRR)
		encode = 0;
	if ((i == 2 || i == 13) && x != IR && x != DR)
		encode = 0;
	if (i == 11 && x != RDR && x != RIR && x != RRR && x != RDD
		&& x != RID && x != RRD)
		encode = 0;
	if ((i == 10 || i == 14) && x != RRR && x != RDR && x != DDR
		&& x != DRR && x != IDR && x != IRR)
		encode = 0;
	if ((i == 6 || i == 7 || i == 8) && x != RRR && x != RIR && x != RDR
		&& x != DRR && x != DDR && x != DIR && x != IRR && x != IIR && x != IDR)
		encode = 0;
	if (encode == 0)
		p->pc = (p->pc + 2) % M_S;
	return (encode);
}

int		ft_number_reg(t_all *a, t_process *p, int pos)
{
	if (a->ar[(p->pc + pos) % M_S] <= 0 || a->ar[(p->pc + pos) % M_S] > 16)
		return (0);
	return (1);
}

void	ft_which_instru(t_all *a, t_process *p)
{
	int pos;
	int value[3];

	a->args = 0;
	pos = 2;
	value[0] = 0;
	value[1] = 0;
	value[2] = 0;
	// ft_putstr_fd("\n", 1);
	a->encode = a->ar[(p->pc + 1) % M_S];
	if (!ft_test_code(a->encode, p))
		return ;
	ft_get_type(a->encode, &(a->type), &(a->size), g_op_tab[p->next_instruction].direct_address);
	// ft_putstr_fd("pl : ", 1);ft_putnbr(p->pl);ft_putstr_fd("\tinstru : ", 1);ft_putstr_fd((char*)g_op_tab[p->next_instruction].name, 1);ft_putstr_fd("\tnargs = ", 1);ft_putnbr(g_op_tab[p->next_instruction].nargs);ft_putstr_fd("\n", 1);
	// ft_putstr_fd("type0 = ", 1);ft_putnbr(a->type[0]);ft_putstr_fd(" type1 = ", 1);ft_putnbr(a->type[1]);ft_putstr_fd(" type2 = ", 1);ft_putnbr(a->type[2]);ft_putstr_fd("\n", 1);
	while (a->args < g_op_tab[p->next_instruction].nargs)
	{
		// ft_putstr_fd("pos = ", 1);ft_putnbr(pos);ft_putstr_fd("\n", 1);
		if (a->type[a->args] == T_REG && !ft_number_reg(a, p, pos))
		{
			// ft_putstr_fd("faiiiiil\n", 1);
			return (ft_wrong_reg(&(p->pc), a->size));
		}
		// ft_putstr_fd("spec addre = ", 1);ft_putnbr(g_op_tab[p->next_instruction].spec_addr);ft_putstr_fd("\n", 1);
		value[a->args] = ft_get_value(a, p->pc + pos, p, g_op_tab[p->next_instruction].spec_addr);
		pos += a->size[a->args];
		a->args++;
	}
	// ft_putstr_fd("succeed :", 1);ft_putstr_fd("pl : ", 1);ft_putnbr(p->pl);ft_putstr_fd("\tinstru : ", 1);ft_putstr_fd((char*)g_op_tab[p->next_instruction].name, 1);ft_putstr_fd("\n", 1);
	// ft_putstr_fd("size0 = ", 1);ft_putnbr(a->size[0]);ft_putstr_fd(" size1 = ", 1);ft_putnbr(a->size[1]);ft_putstr_fd(" size2 = ", 1);ft_putnbr(a->size[2]);ft_putstr_fd("\n", 1);
	g_op_tab[p->next_instruction].instr(a, p, value);
	// ft_putstr_fd("\n", 1);
}