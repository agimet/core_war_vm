/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimet <agimet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 13:58:44 by agimet            #+#    #+#             */
/*   Updated: 2019/05/05 15:15:53 by agimet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			ft_read_magic_or_instruc_size(t_all *a, int fd, int j, int mode)
{
	int test;
	int i;

	i = 4;
	test = 0;
	if (mode == 1)
	{
		while (--i >= 0)
		{
			test = read(fd, &(a->pl[j].magic_nb[i]), 1);
			if (test == 0 || test == -1)
				return (ft_error("Problem with exec number."));
		}
	}
	if (mode == 2)
	{
		while (--i >= 0)
		{
			test = read(fd, &(a->pl[j].size_instru[i]), 1);
			if (test == 0 || test == -1)
				return (ft_error("Problem with instruction size."));
		}
	}
	return (1);
}

int			ft_nb_ac(int n_param, int d_param)
{
	if ((n_param == 0 && d_param == 1) || (n_param != 0 && d_param == 0))
		return (3);
	else if (d_param != 0 && d_param == 1)
		return (5);
	return (1);
}

int			ft_read_each_part(t_all *a, int fd, int j, int part) // CHERCHE UNE COMPARAISON POSSIBLE AVEC INSTRU SIZE ET CHAMP
{
	int i;
	int ret;

	i = -1;
	ret = 0;
	while (++i < part)
	{
		part == PROG_NAME_LENGTH ? ret = read(fd, &(a->pl[j].name[i]), 1) : (0);
		part ==	COMMENT_LENGTH ? ret = read(fd, &(a->pl[j].comment[i]), 1) : (0);
		part == CHAMP_MAX_SIZE ? ret = read(fd, &(a->pl[j].champion[i]), 1) : (0);
		if (ret == -1 || (ret == 0 && i < part && part != CHAMP_MAX_SIZE))
		{
			part == PROG_NAME_LENGTH ? ft_putstr_fd("HEADER : ", 2) : (0);
			part ==	COMMENT_LENGTH ? ft_putstr_fd("COMMENT : ", 2) : (0);
			part == CHAMP_MAX_SIZE ? ft_putstr_fd("CHAMPION : ", 2) : (0);
			if (ret == -1)
				return (ft_error("Missing."));
			else
				return (ft_error("Error length."));
		}
	}
	return (1);
}

int			ft_read_bis(t_all *a, int fd, int j)
{
	if (!ft_read_each_part(a, fd, j, PROG_NAME_LENGTH))
			return (0);
	if (lseek(fd, 4, SEEK_CUR) == -1)
		return (ft_error("lseek padding 1 fail."));
	if (!ft_read_magic_or_instruc_size(a, fd, j, 2))
		return (0);
	if (*(t_u4 *)a->pl[j].size_instru == 0)
		return (ft_error("Instruction size indication equal to zero."));
	if (*(t_u4 *)a->pl[j].size_instru > CHAMP_MAX_SIZE)
		return (ft_error("Instruction size indication superior to champ size."));
	if (!ft_read_each_part(a, fd, j, COMMENT_LENGTH))
		return (0);
	if (lseek(fd, 4, SEEK_CUR) == -1)
		return (ft_error("lseek padding 2 fail."));
	if (!ft_read_each_part(a, fd, j, CHAMP_MAX_SIZE))
		return (0);
	return (1);
}

int			ft_read(t_all *a, int fd, char **av) // COMPARAISON size instruc et champ max size
{
	int		i;
	int		j;

	j = -1;
	i = 1;
	if ((a->num_param == 0 && a->dump_param == 1) || (a->num_param != 0 && a->dump_param == 0))
		i = 3;
	else if (a->dump_param != 0 && a->dump_param == 1)
		i = 5;
	while (++j < a->nb_pl)
	{
		if ((fd = open(av[i], O_RDONLY)) == -1)
			return (ft_error("Can't open file."));
		if (!ft_read_magic_or_instruc_size(a, fd, j, 1))
			return (0);
		if (*(t_u4 *)a->pl[j].magic_nb != COREWAR_EXEC_MAGIC)
			return (ft_error("Wrong magic number."));
		if (!ft_read_bis(a, fd, j))
			return (0);
		close(fd);
		(a->num_param != 0) ? (i += 3) : (i += 1);
	}
	return (1);
}
