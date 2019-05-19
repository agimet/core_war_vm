/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_instructions_others.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimet <agimet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:58:29 by agimet            #+#    #+#             */
/*   Updated: 2019/05/09 15:27:37 by agimet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			ft_live(t_all *a, t_process *p, int val[3])
{
	p->nb_live++;
	a->nb_live_call++;
	val[0] = ft_get_args(a->ar, p->pc + 1, 4);
	if (ft_real_player(a->nb_pl, val[0]) && a->dump == 0)
	{
			ft_putstr_fd("cycle = ", 1);ft_putnbr(a->cycle);ft_putstr_fd("\n", 1);
		a->last_alive = (-1 * val[0]);
		if (a->quiet == 0)
		{
			ft_putstr_fd("\nThe player \"", 1);
			ft_putnbr(a->last_alive);
			if (a->pl[0].num_player == -1 * val[0])
				ft_putstr_fd((char *)a->pl[0].name, 1);
			if (a->pl[1].num_player == -1 * val[0])
				ft_putstr_fd((char *)a->pl[1].name, 1);
			if (a->pl[2].num_player == -1 * val[0])
				ft_putstr_fd((char *)a->pl[2].name, 1);
			if (a->pl[3].num_player == -1 * val[0])
				ft_putstr_fd((char *)a->pl[3].name, 1);
			ft_putstr_fd("\" is alive !\n", 1);
		}
	}
	p->pc = (p->pc + 5) % M_S;
}

void			ft_fork(t_all *a, t_process *p, int val[3])
{
	t_process	*new;
	int			i;

	i = -1;
	new = NULL;
	a->nb_processes++;
	if (!(new = (t_process*)malloc(sizeof(t_process))))
		return ;
	new->next = a->process;
	new->pl = p->pl;
	val[0] = ft_get_args(a->ar, p->pc + 1, 2) % IDX_MOD;
	new->pc = (p->pc + val[0]) % M_S;
	if (new->pc < 0)
		new->pc = ((new->pc % 4096) + 4096) % M_S;
	new->cycle_before_exec = -1;
	new->next_instruction = 0;
	new->nb_live = p->nb_live;
	new->carry = p->carry;
	a->process = new;
	new->num_process = new->next->num_process + 1;
	while (++i < REG_NUMBER)
		new->r[i] = p->r[i];
	p->pc = (p->pc + 3) % M_S;
}

void			ft_lfork(t_all *a, t_process *p, int val[3])
{
	t_process	*new;
	int			i;

	i = -1;
	new = NULL;
	a->nb_processes++;
	if (!(new = (t_process*)malloc(sizeof(t_process))))
		return ;
	new->next = a->process;
	new->pl = p->pl;
	val[0] = ft_get_args(a->ar, p->pc + 1, 2);
	new->pc = (p->pc + val[0]) % M_S;
	if (new->pc < 0)
		new->pc = ((new->pc % 4096) + 4096) % M_S;
	new->cycle_before_exec = -1;
	new->next_instruction = 0;
	new->nb_live = p->nb_live;
	new->carry = p->carry;
	a->process = new;
	new->num_process = new->next->num_process + 1;
	while (++i < REG_NUMBER)
		new->r[i] = p->r[i];
	p->pc = (p->pc + 3) % M_S;
}

void			ft_aff(t_all *a, t_process *p, int val[3])
{
	a->encode = a->ar[(p->pc + 1) % M_S];
	if (a->encode != R)
	{
		p->pc += 2;
		p->pc %= M_S;
		return ;
	}
	if (a->ar[(p->pc + 2) % M_S] > 0 && a->ar[(p->pc + 2) % M_S] <= 16)
	{
		val[0] = p->r[a->ar[(p->pc + 2) % M_S] - 1];
		val[0] %= 256;
		if (val[0] >= 32 && val[0] <= 126)
		{
			ft_putstr_fd("AFF : ", 1);
			ft_putchar_fd(val[0], 1);
			ft_putchar_fd('\n', 1);
		}
	}
	p->pc = (p->pc + 3) % M_S;
}

void			ft_zjmp(t_all *a, t_process *p, int val[3])
{
	a->args = 0;
	if (p->carry == 1)
	{
		val[0] = ft_get_args(a->ar, p->pc + 1, 2) % IDX_MOD;
		p->pc = (p->pc + val[0]) % M_S;
		if (p->pc < 0)
			p->pc = ((p->pc % 4096) + 4096) % M_S;
	}
	else
		p->pc = (p->pc + 3) % M_S;
}
