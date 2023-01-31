NAME		=	minishell
NAME_SAN	=	minishellitized
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g3
FLAGS 		=	-Wall -Wextra -Werror -fsanitize=address -g3
LFLAGS		=	-lreadline
INCLUDES	=	./includes
SRCS		=	srcs_2/cpy_from_two_pos.c\
				srcs_2/cut_from_pos.c\
				srcs_2/do_end.c\
				srcs_2/do_pipe.c\
				srcs_2/do_red.c\
				srcs_2/do_white.c\
				srcs_2/ft_lstnew.c\
				srcs_2/goats.c\
				srcs_2/ins.c\
				srcs_2/int_err.c\
				srcs_2/join.c\
				srcs_2/nex_.c\
				srcs_2/ft_mem.c\
				srcs_2/insides.c\
				srcs_2/kote.c\
				srcs_2/set_struct.c\
				srcs_2/list.c\
				srcs_2/main.c\
				srcs_2/next_hd.c\
				srcs_2/next_kote.c\
				srcs_2/piece_of_string.c\
				srcs_2/repartiteur.c\
				srcs_2/str_comp.c\
				srcs_2/tab_et_et.c\
				srcs/cpy_from_two_pos.c\
				srcs/cut_from_pos.c\
				srcs/dollar.c\
				srcs/find_env.c\
				srcs/ft_is.c\
				srcs/ft_itoaa.c\
				srcs/ft_strlen.c\
				srcs/ins.c\
				srcs/str_c.c\
				srcs/join.c\
				srcs/char_err.c\
				srcs/malicious.c\
				srcs/where_is_charly.c\
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
				execute/srcs/heredoc.c\
				execute/srcs/heredoc_utils.c\


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

clean		:
				@rm -rf $(OBJS)
				@$(MAKE) -C ./execute/libft clean

fclean		:	clean
				@rm -rf $(NAME) $(NAME_SAN)
				@$(MAKE) -C ./execute/libft fclean

re			:	fclean all

.PHONY		:	all clean fclean re sanity
.SILENT		:
