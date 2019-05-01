/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_play.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimet <agimet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 15:05:38 by agimet            #+#    #+#             */
/*   Updated: 2019/05/01 15:41:29 by agimet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			ft_check_bis(t_all *a, int head, t_process **t, t_process **p)
{
	if ((*t)->nb_live == 0)
	{
		if ((*t) == a->process)
		{
			a->process = a->process->next;
			free((*t));
			(*t) = NULL;
			(*t) = a->process;
			head = 1;
		}
		else
		{
			(*p)->next = (*t)->next;
			free((*t));
			(*t) = NULL;
			(*t) = (*p);
		}
		a->nb_processes--;
	}
	else
		(*t)->nb_live = 0;
}

void			ft_check_alive_process(t_all *a)
{
	t_process	*tmp;
	t_process	*prev;
	int			head;

	head = 0;
	prev = a->process;
	tmp = a->process;
	while (tmp != NULL)
	{
		ft_check_bis(a, head, &tmp, &prev);
		prev = tmp;
		if (head == 0 && tmp != NULL)
			tmp = tmp->next;
		else
			head = 0;
	}
}

void			ft_exec_instructions(t_all *a)
{
	t_process	*p;
	int			i;

	i = 0;
	p = NULL;
	p = a->process;
	while (p != NULL)
	{
		if (a->ar[(p->pc) % M_S] > 0 && a->ar[(p->pc) % M_S] <= 16
			&& p->cycle_before_exec == -1)
		{
			p->cycle_before_exec = g_op_tab[a->ar[(p->pc) % M_S]].nb_cycle - 1;
			p->next_instruction = g_op_tab[a->ar[(p->pc) % M_S]].opcode;
		}
		else if (a->ar[(p->pc) % M_S] <= 0 || a->ar[(p->pc) % M_S] > 16)
			p->pc = ((p->pc + 1) % M_S);
		else if (p->cycle_before_exec == 0)
		{
			g_op_tab[p->next_instruction].instr(a, p);
			p->cycle_before_exec = -1;
		}
		if (p->cycle_before_exec != -1)
			p->cycle_before_exec--;
		p = p->next;
	}
}

void			ft_update_arena(t_all *a)
{
	int			modif;

	modif = 0;
	if (a->before_cycle_to_die == a->cycle_to_die)
	{
		if (a->nb_live_call >= NBR_LIVE)
		{
			a->cycle_to_die -= CYCLE_DELTA;
			a->nb_checks = 0;
			modif = 1;
		}
		else
			a->nb_checks += 1;
		if (modif == 0 && a->nb_checks >= MAX_CHECKS)
		{
			a->cycle_to_die -= CYCLE_DELTA;
			a->nb_checks = 0;
		}
		a->nb_live_call = 0;
		a->before_cycle_to_die = 0;
		modif = 0;
	}
	a->before_cycle_to_die++;
	a->cycle++;
}

void			ft_lets_play(t_all *a)
{
	while (a->process != NULL && a->cycle_to_die >= 0)
	{
		if (a->dump_param == 1 && a->cycle == a->dump_cycle)
		{
			ft_dump(a);
			break ;
		}
		ft_update_arena(a);
		ft_exec_instructions(a);
		if (a->before_cycle_to_die == a->cycle_to_die)
			ft_check_alive_process(a);
	}
	if (a->dump_param == 0)
	{
		if (a->last_alive == 0)
		{
			ft_putstr("No one lived.\n");
			return ;
		}
		ft_putstr("Champion ");
		ft_putnbr(a->last_alive);
		ft_putstr(" alias ");
		ft_winner(a);
		ft_putstr(" has won !\n");
	}
}
