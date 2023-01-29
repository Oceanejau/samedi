NAME		=	minishell
NAME_SAN	=	minishellitized
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror 
FLAGS 		=	-Wall -Wextra -Werror -fsanitize=address -g3
LFLAGS		=	-lreadline
INCLUDES	=	./includes
SRCS		=	srcs/main.c\
				srcs/ft_strjoin.c\
				srcs/ft_strlen.c\
				srcs/piece_of_string.c\
				srcs/ins.c\
				srcs/repartiteur.c\
				srcs/do_end.c\
				srcs/do_red.c\
				srcs/ft_lstnew.c\
				srcs/cut_from_pos.c\
				srcs/next_hd.c\
				srcs/do_white.c\
				srcs/do_pipe.c\
				srcs/str_comp.c\
				srcs/ft_is.c\
				srcs/find_env.c\
				srcs/int_err.c\
				srcs/char_err.c\
				srcs/tab_et_et.c\
				srcs/malicious.c\
				srcs/goats.c\
				srcs/join.c\
				srcs/cpy_from_two_pos.c\
				srcs/next_kote.c\
				srcs/dollar.c\
				srcs/list.c\
				srcs/kote.c\
				execute/srcs/better_exec.c\
				execute/srcs/builtin_lookup.c\
				execute/srcs/create_args.c\
				execute/srcs/deal_with_redir.c\
				execute/srcs/exec_bin.c\
				execute/srcs/execute_stuff.c\
				execute/srcs/find_cmd.c\
				execute/srcs/find_path.c\
				execute/srcs/ft_tabstradd.c\
				execute/srcs/infile_modif.c\
				execute/srcs/is_redir.c\
				execute/srcs/list_to_block.c\
				execute/srcs/nb_cmd.c\
				execute/srcs/outfile_dou_modif.c\
				execute/srcs/outfile_modif.c\
				execute/srcs/skip_redir.c\
				execute/builtin/ft_cd.c\
				execute/builtin/ft_echo.c\
				execute/builtin/ft_env.c\
				execute/builtin/ft_exit.c\
				execute/builtin/ft_export.c\
				execute/builtin/ft_pwd.c\
				execute/builtin/ft_unset.c\
				execute/srcs/envlist.c\
				execute/srcs/signal_stuff.c\
				execute/srcs/reset_fd.c\
				execute/srcs/free_shell.c\
				execute/builtin/builtin_utils.c\

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

.c.o		:
				$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $(<:.c=.o)

$(NAME)		:	$(OBJS)
				@$(MAKE) -C ./execute/libft bonus
				@$(CC) $(CFLAGS) -I $(INCLUDES) $(OBJS) $(LFLAGS) -o $(NAME) execute/libft/libft.a

sanity		:	$(NAME_SAN)

$(NAME_SAN)	:	$(OBJS)
				@$(MAKE) -C ./execute/libft bonus
				$(CC) $(FLAGS) -I $(INCLUDES) $(OBJS) $(LFLAGS) -o $(NAME_SAN) execute/libft/libft.a

#.c.o:
#	$(CC) $(FLAGS) -I $(INCLUDES) -c $< -o $(<:.c=.o)

clean		:
				@rm -rf $(OBJS)
				@$(MAKE) -C ./execute/libft clean

fclean		:	clean
				@rm -rf $(NAME) $(NAME_SAN)
				@$(MAKE) -C ./execute/libft fclean

re			:	fclean all

.PHONY		:	all clean fclean re sanity
.SILENT		:
