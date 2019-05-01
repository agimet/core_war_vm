/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimet <agimet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 15:04:46 by agimet            #+#    #+#             */
/*   Updated: 2019/05/01 15:29:59 by agimet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <stdint.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "op.h"

# define HEXA "0123456789abcdef"
# define ADDR 2
# define DIRECT 4
# define TEST "FF1"

# define RR 80
# define RD 96
# define RI 112

# define R 64
# define D 128
# define I 192

# define DR 144
# define DD 160
# define DI 176

# define IR 208
# define ID 224
# define II 240

# define RRR 84
# define RRD 88
# define RRI 92
# define RDR 100
# define RDD 104
# define RDI 108
# define RIR 116
# define RID 120
# define RII 124

# define DRR 148
# define DRD 152
# define DRI 156
# define DDR 164
# define DDD 168
# define DDI 172
# define DIR 180
# define DID 184
# define DII 188

# define IRR 212
# define IRD 216
# define IRI 220
# define IDR 228
# define IDD 232
# define IDI 236
# define IIR 244
# define IID 248
# define III 252

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
	int						cycle;
	int						nb_pl;
	int						succed;
	t_u1					encode;
	t_u1					ar[M_S];
	t_u1					type[3];
	t_u1					size[3];
	t_process				*process;
	int						nb_checks;
	int						num_param;
	t_u1					whose[M_S];
	int						dump_param;
	int						dump_cycle;
	int						last_alive;
	int						count_init;
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
	void					(*instr)(t_all *a, t_process *proc);
}							t_op;

int							ft_read(t_all *a, int fd, char **av);
int							ft_error(char *str);
void						ft_dump(t_all *a);
int							ft_free_all(t_all *a);
void						ft_init_arena(t_all *a);
void						ft_init_struct(t_all **a);
int							ft_valid_args(t_all *a, char **av, int ac);
void						ft_live(t_all *a, t_process *p);
void						ft_ld(t_all *a, t_process *p);
void						ft_st(t_all *a, t_process *p);
void						ft_add_sub(t_all *a, t_process *p);
void						ft_and_or_xor(t_all *a, t_process *p);
void						ft_zjmp(t_all *a, t_process *p);
void						ft_ldi(t_all *a, t_process *p);
void						ft_sti(t_all *a, t_process *p);
void						ft_fork(t_all *a, t_process *p);
void						ft_lld(t_all *a, t_process *p);
void						ft_lldi(t_all *a, t_process *p);
void						ft_lfork(t_all *a, t_process *p);
void						ft_aff(t_all *a, t_process *p);
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
int							ft_isprint(int c);
int							ft_isdigit(int c);
void						*ft_memcpy(void *dest, const void *src, size_t len);
void						*ft_memset(void *s, int c, size_t n);
void						ft_bzero(void *s, size_t n);
void						ft_putchar(char c);
void						ft_putchar_fd(char c, int fd);
void						ft_putendl_fd(char const *s, int fd);
void						ft_putstr(char const *s);
void						ft_putnbr(int nb);
size_t						ft_strlen(const char *s);

extern t_op					g_op_tab[17];

#endif
