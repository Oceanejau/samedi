/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:23:17 by wmari             #+#    #+#             */
/*   Updated: 2023/01/30 22:48:06 by wmari            ###   ########.fr       */
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

#define MAIN 1
#define PARENT 2
#define CHILD 3
#define HD 4

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
int		is_redir(char ***block, int index, int n, t_mimi *shell);
char	*find_path(char *cmd, t_mimi *shell);
char	*find_cmd(char ***block, int index, t_mimi *shell);
void	skip_redir(char ***block, int index, int *n, t_mimi *shell);
char	**create_args(char ***block, int index, t_mimi *shell);
int		deal_with_redir(char ***block, int index, int n, t_mimi *shell);
int		outfile_dou_modif(char *file, int fd);
int		outfile_modif(char *file, int fd);
int		infile_modif(char *file, int fd);
int		exec_bin(char ***block, int index, t_mimi *shell, int *fd_btw_pipe);
int		execute_stuff(char ***block, int index,
			int *fd_btw_pipe, t_mimi *shell);
int		better_exec(char ***block, t_mimi *shell);
char	**ft_tabstradd(char **old, char *new_str);
char	***list_to_block(t_list *list);
int		exec_parent(int *pipefd, char ***block,
			int index, int *fd_btw_pipe);
int		preroutine(char ***block, int index, t_mimi *shell);
int		check_same_till_equals(const char *s1, const char *s2);
int		check_if_add(const char *s1, const char *s2);
char	**envlist_to_env(t_list *envlist);
void	make_envlist(t_mimi *shell);
void	free_envchar(t_mimi *shell);
int		free_args(char **args);
int		set_fd(int *savefd);
int		reset_fd(int *savefd);
int		free_fd(int *savefd);
void	free_list(t_mimi *shell);
void	free_env(t_mimi *shell);
void	free_tab(char **tab);
int		redir_or_not(char ***block, int index, int n, t_mimi *shell);
void	free_all_bin(char **str, t_mimi *shell, char ***block, char *cmd);
void	last_cmd(char ***block, int index, int *fd);

/*________BUILTIN__________*/
int		builtin_finder(char *name);
int		exec_builtin(char ***block, int index, t_mimi *shell, int *fd_btw_pipe);
int		exec_prebuiltin(char ***block, int index,
			int *fd_btw_pipe, t_mimi *shell);
int		exec_solobuiltin(char ***block, int index, t_mimi *shell, int *fd_btw_pipe);
int		ft_pwd( char ***block, int index, t_mimi *shell);
int		ft_echo( char ***block, int index, t_mimi *shell);
int		ft_env(char ***block, int index, t_mimi *shell);
int		ft_cd( char ***block, int index, t_mimi *shell);
int		ft_exit( char ***block, int index, t_mimi *shell, int *fd_btw_pipe);
int		ft_unset(char ***block, int index, t_mimi *shell);
int		ft_export(char ***block, int index, t_mimi *shell);
int		ft_solopwd(char ***block, int index);
int		ft_soloecho(char ***block, int index, t_mimi *shell);
int		ft_soloenv(char ***block, int index, t_mimi *shell);
int		ft_solocd(char ***block, int index, t_mimi *shell);
int		ft_solounset(char ***block, int index, t_mimi *shell);
int		ft_soloexport(char ***block, int index, t_mimi *shell);
void 	echo_comp(char ***block, int index, int i, t_mimi *shell);
void	free_all_built(char ***block, t_mimi *shell, int *fd);
void	add_stuff_export(char *str, t_list *temp);

void	catch_signal(int mode);
int		write_in_hd(t_mimi *shell, int index, char *delim);
char	*get_delim(t_mimi *shell);
int		create_file(char *name, t_mimi *shell);
char	*get_name(int index);
int		heredoc_init(t_mimi *shell);
int		modif_list(t_mimi *shell, int index);
void	free_hd(t_mimi *shell);

#endif
