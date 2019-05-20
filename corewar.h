/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimet <agimet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 15:04:46 by agimet            #+#    #+#             */
/*   Updated: 2019/05/09 15:58:29 by agimet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "op.h"

# define HEXA "0123456789abcdef"

# define R 64

# define RR 80
# define RI 112
# define DR 144
# define IR 208

# define RRR 84
# define RRD 88
# define RDR 100
# define RDD 104
# define RIR 116
# define RID 120

# define DRR 148
# define DDR 164
# define DDI 172
# define DIR 180

# define IRR 212
# define IDR 228
# define IIR 244

typedef unsigned char		t_u1;
typedef unsigned int		t_u4;

typedef struct				s_process
{
	unsigned int			pl;
	int						pc;
	int						index;
	int						carry;
	int						nb_live;
	int						num_process;
	int						r[REG_NUMBER];
	int						next_instruction;
	int						cycle_before_exec;
	struct s_process		*next;
}							t_process;

typedef struct				s_player
{
	int						pos;
	int						init;
	int						num_player;
	t_u1					magic_nb[4];
	t_u1					size_instru[4];
	t_u1					name[PROG_NAME_LENGTH + 1];
	t_u1					comment[COMMENT_LENGTH + 1];
	t_u1					champion[CHAMP_MAX_SIZE + 1];
}							t_player;

typedef struct				s_all
{
	int						dump;
	int						args;
	int						quiet;
	int						cycle;
	int						nb_pl;
	t_u1					encode;
	t_u1					ar[M_S];
	t_u1					type[3];
	t_u1					size[3];
	t_process				*process;
	int						nb_checks;
	int						num_param;
	t_u1					whose[M_S];
	int						dump_cycle;
	int						last_alive;
	int						nb_processes;
	int						nb_live_call;
	int						cycle_to_die;
	t_player				pl[MAX_PLAYERS];
	int						before_cycle_to_die;
}							t_all;

typedef struct				s_op_tab
{
	char					*name;
	int						nargs;
	t_arg_type				arg[3];
	int						opcode;
	int						nb_cycle;
	char					*description;
	int						codage_octal;
	int						direct_address;
	int						spec_addr;
	void					(*instr)(t_all *a, t_process *proc, int val[2]);
}							t_op;

int							ft_read(t_all *a, int fd, char **av);
int							ft_error(char *str);
void						ft_dump(t_all *a);
int							ft_free_all(t_all *a);
void						ft_init_arena(t_all *a);
void						ft_init_struct(t_all **a);
int							ft_valid_args(t_all *a, char **av, int ac);
void						ft_live(t_all *a, t_process *p, int val[3]);
void						ft_ld(t_all *a, t_process *p, int val[3]);
void						ft_st(t_all *a, t_process *p, int val[3]);
void						ft_add_sub(t_all *a, t_process *p, int val[3]);
void						ft_and_or_xor(t_all *a, t_process *p, int val[3]);
void						ft_zjmp(t_all *a, t_process *p, int val[3]);
void						ft_ldi(t_all *a, t_process *p, int val[3]);
void						ft_sti(t_all *a, t_process *p, int val[3]);
void						ft_fork(t_all *a, t_process *p, int val[3]);
void						ft_lld(t_all *a, t_process *p, int val[3]);
void						ft_lldi(t_all *a, t_process *p, int val[3]);
void						ft_lfork(t_all *a, t_process *p, int val[3]);
void						ft_aff(t_all *a, t_process *p, int val[3]);
int							ft_real_player(int nb_pl, int value);
void						ft_winner(t_all *a);
void						ft_wrong_reg(int *pc, t_u1 size[3]);
void						ft_reg_to_arena(t_all *a, t_u4 v, int b, int p);
void						ft_lets_play(t_all *a);
int							ft_get_types(int type);
int							ft_get_args(t_u1 arena[M_S], int pc, int size);
int							ft_get_value(t_all *a, int w, t_process *p, int s);
void						ft_get_type(t_u1 e, t_u1 (*t)[3],
								t_u1 (*s)[3], int m);
int							ft_atoi(const char *str);
void						ft_putstr_fd(char const *s, int fd);
void						ft_bzero(void *s, size_t n);
void						ft_putchar_fd(char c, int fd);
void						ft_putnbr(int nb);
size_t						ft_strlen(const char *s);
void						ft_which_instru(t_all *a, t_process *p);

extern t_op					g_op_tab[17];

#endif
