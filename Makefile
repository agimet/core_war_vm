# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agimet <agimet@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/31 14:51:09 by agimet            #+#    #+#              #
#    Updated: 2019/05/02 16:44:45 by agimet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


EXEC = corewar
CC = gcc
SRCS = main.c \
		fts_read.c \
		fts_check_args.c \
		fts_init_arena.c op.c \
		fts_play.c \
		fts_instructions_calcul.c \
		fts_instructions_load.c \
		fts_instructions_others.c \
		fts_instructions_store.c \
		fts_utilities_for_instru.c \
		fts_get_needs.c \
		fts_init_free_struct.c \
		fts_dump_memory.c \
		fts_lib.c \
		fts_lib2.c \
		fts_lib3.c
OBJ = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

all: $(EXEC)

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(EXEC)

re:	fclean all

.PHONY: all clean fclean re
