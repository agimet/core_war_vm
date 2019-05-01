/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_init_free_struct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimet <agimet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:11:00 by agimet            #+#    #+#             */
/*   Updated: 2019/05/01 12:56:44 by agimet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			ft_init_struct(t_all **a)
{
	int			i;

	i = 0;
	if (!(*a = malloc(sizeof(t_all))))
		return ;
	ft_bzero(*a, sizeof(t_all));
	(*a)->cycle_to_die = CYCLE_TO_DIE;
}

int				ft_free_all(t_all *a)
{
	t_process	*tmp;

	tmp = a->process;
	while (a->process != NULL)
	{
		a->process = a->process->next;
		free(tmp);
		tmp = NULL;
		tmp = a->process;
	}
	if (a != NULL)
		free(a);
	a = NULL;
	return (0);
}
