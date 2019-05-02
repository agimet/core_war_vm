/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_init_arena.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimet <agimet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:06:12 by agimet            #+#    #+#             */
/*   Updated: 2019/05/02 16:45:06 by agimet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			ft_load_champions(t_all *a)
{
	int			i;
	int			pos;

	i = 0;
	pos = 0;
	ft_bzero(a->whose, sizeof(a->whose));
	ft_bzero(a->ar, sizeof(a->ar));
	ft_memset(&a->whose, 0, M_S);
	if (*(int*)a->pl[i].size_instru > CHAMP_MAX_SIZE)
		exit(2);
	while (i < a->nb_pl)
	{
		pos = a->pl[i].pos;
		ft_memset(&(a->whose[pos]), a->pl[i].num_player,
				*(int*)(a->pl[i].size_instru));
		ft_memcpy(&(a->ar[pos]), a->pl[i].champion, CHAMP_MAX_SIZE);
		i++;
	}
}

void			ft_init_process(t_all *a, int pos, int num_proc, int index)
{
	t_process	*tmp;
	static int	j = 0;
	int			i;

	i = 1;
	tmp = a->process;
	while (i < (a->nb_pl - j))
	{
		tmp = tmp->next;
		i++;
	}
	tmp->index = index;
	tmp->pc = pos;
	tmp->carry = 0;
	tmp->nb_live = 0;
	tmp->next_instruction = 0;
	tmp->cycle_before_exec = -1;
	tmp->num_process = num_proc;
	tmp->pl = j + 1;
	tmp->r[0] = 0xffffffff - j;
	j++;
}

void			ft_init_player(t_all *a)
{
	int			pl;
	int			i;
	int			pos;

	pos = 0;
	i = 0;
	pl = 1;
	while (i < a->nb_pl)
	{
		if (a->pl[i].num_player == pl && a->pl[i].init == 0)
		{
			ft_init_process(a, pos, a->nb_processes, i);
			a->pl[i].init = 1;
			a->pl[i].pos = pos;
			i = 0;
			pos = pos + (M_S / a->nb_pl);
			pl++;
		}
		else
			i++;
	}
}

void			ft_create_process(t_all *a)
{
	t_process	*new;
	int			i;
	int			j;
	int			pos;

	pos = 0;
	j = 0;
	i = -1;
	new = NULL;
	while (++i < a->nb_pl)
	{
		a->pl[i].num_player == 0 ? a->pl[i].num_player = i + 1 : (0);
		a->nb_processes++;
		if (!(new = (t_process*)malloc(sizeof(t_process))))
			return ;
		new->next = NULL;
		while (j < REG_NUMBER)
			new->r[j++] = 0;
		j = 0;
		new->next = (a->process == NULL) ? NULL : a->process;
		a->process = new;
	}
	ft_init_player(a);
}

void			ft_init_arena(t_all *a)
{
	ft_create_process(a);
	ft_load_champions(a);
}
