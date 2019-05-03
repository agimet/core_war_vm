/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimet <agimet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 13:58:44 by agimet            #+#    #+#             */
/*   Updated: 2019/05/03 15:46:31 by agimet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		ft_read_magic_or_instruc_size(t_all *a, int fd, int j, int mode) // test instru size max ??
{
	if (mode == 1)
	{
		read(fd, &(a->pl[j].magic_nb[3]), 1);
		read(fd, &(a->pl[j].magic_nb[2]), 1);
		read(fd, &(a->pl[j].magic_nb[1]), 1);
		read(fd, &(a->pl[j].magic_nb[0]), 1);
	}
	if (mode == 2)
	{
		read(fd, &(a->pl[j].size_instru[3]), 1);
		read(fd, &(a->pl[j].size_instru[2]), 1);
		read(fd, &(a->pl[j].size_instru[1]), 1);
		read(fd, &(a->pl[j].size_instru[0]), 1);
	}
}

int			ft_nb_ac(int n_param, int d_param)
{
	if ((n_param == 0 && d_param == 1) || (n_param != 0 && d_param == 0))
		return (3);
	else if (d_param != 0 && d_param == 1)
		return (5);
	return (1);
}

int			ft_read_each_part(t_all *a, int j, int fd, int part) // mettre putstr_fd pour ecrire sur meme sortie que putend_fd
{
	int i;
	int ret;

	i = -1;
	ret = 0;
	while (++i < part)
	{
		part == PROG_NAME_LENGTH ? ret = read(fd, &(a->pl[j].name), 1) : (0);
		part ==	COMMENT_LENGTH ? ret = ead(fd, &(a->pl[j].comment), 1) : (0);
		part == CHAMP_MAX_SIZE ? ret = ead(fd, &(a->pl[j].champion), 1) : (0);
		if (ret == -1 || (ret == 0 && i < part))
		{
			part == PROG_NAME_LENGTH ? ft_putstr("HEADER : ") : (0);
			part ==	COMMENT_LENGTH ? ft_putstr("COMMENT : ") : (0);
			part == CHAMP_MAX_SIZE ? ft_putstr("CHAMPION : ") : (0);
			if (ret == -1)
				return (ft_error("Missing."));
			else
				return (ft_error("Error length."));
		}
	}
	return (1);
}

int			ft_read(t_all *a, int fd, char **av)
{
	int		i;
	int		j;

	j = -1;
	i = ft_nb_ac(a->num_param, a->dump_param);
	while (++j < a->nb_pl)
	{
		if ((fd = open(av[i], O_RDONLY)) == -1)
			return (ft_error("Can't open file."));
		ft_read_magic_or_instruc_size(a, fd, j, 1);
		if (*(t_u4 *)a->pl[j].magic_nb != COREWAR_EXEC_MAGIC)
			return (ft_error("Wrong magic number."));
		if (!ft_read_each_part(a->pl[j].name, fd, j, PROG_NAME_LENGTH))
			return (0);
		if (lseek(fd, 4, SEEK_CUR) == -1)
			return (ft_error("lseek padding 1 fail."));
		ft_read_magic_or_instruc_size(a, fd, j, 2);
		if (!ft_read_each_part(a->pl[j].comment, fd, j, COMMENT_LENGTH))
			return (0);
		if (lseek(fd, 4, SEEK_CUR) == -1)
			return (ft_error("lseek padding 2 fail."));
		if (!ft_read_each_part(a->pl[j].champion, fd, j, CHAMP_MAX_SIZE))
			return (0);
		close(fd);
		(a->num_param != 0) ? (i += 3) : (i += 1);
	}
	return (1);
}
