/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimet <agimet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 13:58:44 by agimet            #+#    #+#             */
/*   Updated: 2019/05/01 14:32:21 by agimet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		ft_read_magic(t_all *a, int fd, int j)
{
	read(fd, &(a->pl[j].magic_nb[3]), 1);
	read(fd, &(a->pl[j].magic_nb[2]), 1);
	read(fd, &(a->pl[j].magic_nb[1]), 1);
	read(fd, &(a->pl[j].magic_nb[0]), 1);
}

void		ft_read_instruc_size(t_all *a, int fd, int j)
{
	read(fd, &(a->pl[j].size_instru[3]), 1);
	read(fd, &(a->pl[j].size_instru[2]), 1);
	read(fd, &(a->pl[j].size_instru[1]), 1);
	read(fd, &(a->pl[j].size_instru[0]), 1);
}

int			ft_nb_ac(int n_param, int d_param)
{
	if ((n_param == 0 && d_param == 1) || (n_param != 0 && d_param == 0))
		return (3);
	else if (d_param != 0 && d_param == 1)
		return (5);
	return (1);
}

int			ft_read(t_all *a, int fd, char **av)
{
	int		i;
	int		j;

	j = 0;
	i = ft_nb_ac(a->num_param, a->dump_param);
	while (j < a->nb_pl)
	{
		if ((fd = open(av[i], O_RDONLY)) == -1)
			return (ft_error("Can't open file."));
		ft_read_magic(a, fd, j);
		if (*(t_u4 *)a->pl[j].magic_nb != COREWAR_EXEC_MAGIC)
			return (ft_error("Wrong magic number."));
		read(fd, &(a->pl[j].name), PROG_NAME_LENGTH);
		lseek(fd, 4, SEEK_CUR);
		ft_read_instruc_size(a, fd, j);
		read(fd, &(a->pl[j].comment), COMMENT_LENGTH);
		lseek(fd, 4, SEEK_CUR);
		read(fd, &(a->pl[j++].champion), CHAMP_MAX_SIZE);
		close(fd);
		(a->num_param != 0) ? (i += 3) : (i += 1);
	}
	return (1);
}
