/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 05:13:07 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/27 14:57:30 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../execute/libft/libft.h"

# define ERROR 1
# define OK 0
# define FRI -4
# define SWITCH_KEEP -5
# define SWITCH_NORMAL -6
# define ERR -1
# define TXT 0
# define PIPE 1
# define REDIR 2

typedef struct s_list
{
	char			*str;
	int				type;
	struct s_list	*next;
}					t_list;

typedef struct s_mimi
{
	int		y;
	int		x;
	int		z;
	int		s;
	int		run;
	int		end;
	int		ret;
	int		fin;
	int		tip;
	int		type;
	int		nb_hd;
	int		index;
	int		ferme;
	int		quote;
	int		size;
	int		ret_line;
	t_list	*list;
	t_list	*envlist;
	char	*str;
	char	*args;
	char	*line;
	char	*command;
	char	**tab;
	char	**env;
	char	instr[9];
	int		save_fd[3];
}				t_mimi;

extern int		g_ret;//globale

char			*ft_itoaa(int n);

char	*nexy(t_mimi *shell, char *msg, int ret, char c);
char	*char_err(char *msg, int ret);
int		int_err(char *msg, int ret);
int		ft_is_alpha(char c);
char	**next_hd(t_mimi *shell, int x);
int		ft_is_nb(char c);
char	*johnny(char *s1, char *s2);
char	*repartiteur(t_mimi *shell, int x, char *str);
char	*do_end(t_mimi *shell);
char	*cut_from_pos(char *str, int e);
char	*malicious(const char *str);
char	*cut_in(char *str, int x);
char	*get_in(char *str, int x);
void	free_list(t_mimi *shell);
char	*cpy_from_two_pos(char *str, int s, int e);
int		next_kote(char *str, char c, int x);
char	*join(char *s1, char *s2);
//char	*check_the_bill(char *str, int x);
char	*inside_kote_34(char *str, t_mimi *shell, int x, int c_pos);
char	*inside_kote_39(char *str, t_mimi *shell, int x, int c_pos);
char	*goats(t_mimi *shell, int x);
char	*dollary(char *str, t_mimi *shell, int x);
char	*find_env(char *str, t_mimi *shell);
char	*cpy_from_two_pos(char *str, int s, int e);
//char	*check_the_bill(char *str, int x);
int		char_is_in_str(char c, char *str, int x);
int		str_c(char *str, char c);
char	*join(char *s1, char *s2);
char	*cut_from_pos(char *str, int e);
char	*cut_in(char *str, int x);
int		next_kote(char *str, char c, int x);
void	set_struct(t_mimi *shell, char **envp);
int		ret_nb(int ret, char *msg, t_mimi *shell);
size_t	ft_memlen(void *s);
void	*ft_memcpy(void *dst, const void *src, size_t size);
char	**malloc_char_et_et(int size);
char	*copy_char_et(char *str);
char	**error_copy_char_et_et(char **tmp, int size);
char	**copy_char_et_et(char **str);
char	*new_quote(t_mimi *shell, char c, int x);
char	*rm_start(int x, char *str);
int		mani(t_mimi *shell);
char	*do_red(t_mimi *shell, int x, char c);
char	*do_white(t_mimi *shell, int x);
char	*do_pipe(t_mimi *shell, int x);
char	*do_quote(t_mimi *shell, int x, char c);
int		where_is_charly(char *str, int x, char c);
void	ft_lstadd_back(t_list **alst, t_list *new);
t_list	*ft_listnew(char *content, int x);
t_list	*ft_lstnew(char *content);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*piece_of_string(char *str, int deb, int fin);
int		parse(t_mimi *shell);
int		str_comp(char *str, char *comp);
int		errors(void);
int		is_alpha_num_o_(char c);
int		find_pipe(t_mimi *shell, int x);
char	*quotenapping(char *str);
char	*clean_space(char *str);
int		keep_the_line(t_mimi *shell, int x, int y);
void	parcours_la_chaine(t_mimi *shell);
int		main(int ac, char **av, char **envp);

#endif
