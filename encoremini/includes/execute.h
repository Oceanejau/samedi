/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:23:17 by wmari             #+#    #+#             */
/*   Updated: 2023/01/23 15:56:51 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "../execute/libft/libft.h"
# include "minishell.h"

enum	e_redir
{
	NOT_REDIR,
	INFILE,
	D_INFILE,
	OUTFILE,
	D_OUTFILE,
};

/*________EXEC___________*/
int		nb_cmd(char ***block);
int		is_redir(char *str);
char	*find_path(char *cmd, t_mimi *shell);
char	*find_cmd(char **block);
void	skip_redir(char **block, int *n);
char	**create_args(char **block);
int		deal_with_redir(char **block, int n, int fd[2]);
int		outfile_dou_modif(char *file, int fd);
int		outfile_modif(char *file, int fd);
int		infile_modif(char *file, int fd);
int		exec_bin(char ***block, int index, t_mimi *shell);
int		execute_stuff(char ***block, int index,
			int *fd_btw_pipe, t_mimi *shell);
int		better_exec(char ***block, t_mimi *shell);
char	**ft_tabstradd(char **old, char *new_str);
char	***list_to_block(t_list *list);
int		exec_parent(int *pipefd, char ***block,
			int index, int *fd_btw_pipe);
int		preroutine(char **cmd_line);
int		check_same_till_equals(const char *s1, const char *s2);
char	**envlist_to_env(t_list *envlist);
void	make_envlist(t_mimi *shell);
void	free_envchar(t_mimi *shell);
int		free_args(char **args);
int		set_fd(int **savefd);
int		reset_fd(int **savefd);
void	free_list(t_mimi *shell);

/*________BUILTIN__________*/
int		builtin_finder(char *name);
int		exec_builtin(char ***block, int index, t_mimi *shell);
int		exec_prebuiltin(char ***block, int index,
			int *fd_btw_pipe, t_mimi *shell);
int		exec_solobuiltin(char ***block, int index, t_mimi *shell);
int		ft_pwd( char ***block, int index, t_mimi *shell);
int		ft_echo( char ***block, int index, t_mimi *shell);
int		ft_env(char ***block, int index, t_mimi *shell);
int		ft_cd( char ***block, int index, t_mimi *shell);
int		ft_exit( char ***block, int index, t_mimi *shell);
int		ft_unset(char ***block, int index, t_mimi *shell);
int		ft_export(char ***block, int index, t_mimi *shell);
int		ft_solopwd(char ***block, int index);
int		ft_soloecho(char ***block, int index);
int		ft_soloenv(char ***block, int index, t_mimi *shell);
int		ft_solocd(char ***block, int index, t_mimi *shell);
int		ft_solounset(char ***block, int index, t_mimi *shell);
int		ft_soloexport(char ***block, int index, t_mimi *shell);

void	sig_int_in_parent(int sig);
void	sig_quit_in_child(int sig);

#endif
