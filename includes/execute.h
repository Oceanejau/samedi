/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:23:17 by wmari             #+#    #+#             */
/*   Updated: 2023/02/08 16:44:37 by wmari            ###   ########.fr       */
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

# define MAIN 1
# define PARENT 2
# define CHILD 3
# define HD 4

enum	e_redir
{
	NOT_REDIR,
	INFILE,
	D_INFILE,
	OUTFILE,
	D_OUTFILE,
};

/*____________________EXEC_STUFF__________________*/
int		execute(t_mimi	*shell, char ***block);
void	wait_children(char ***block);
void	catch_signal(int mode);
int		is_it_txt(char ***block, int index, int ind2, t_mimi *shell);
char	*find_cmd(t_mimi *shell, int index);
int		exec_bin(char ***block, int index, int *fbp, t_mimi *shell);
int		exec_child(char ***block, int index, int *fbp, t_mimi *shell);
int		do_stuff_child(char ***block, int index, int *fbp, int *pipefd);
int		do_stuff_parent(int	*pipefd, char ***block, int index, int *fbp);
char	**create_args(char ***block, int index, t_mimi *shell);
int		execute_stuff(char ***block, int index, int *fbp, t_mimi *shell);
char	*find_path(char *cmd, t_mimi *shell, int n);
int		nb_cmd(char ***block);
int		nb_args(char **tab);
void	make_envlist(t_mimi *shell);
int		check_same_till_equals(const char *s1, const char *s2);
int		check_if_add(const char *s1, const char *s2);
char	**envlist_to_env(t_list *envlist);
void	free_envchar(t_mimi *shell);
char	***list_to_block(t_list *list);
int		infile_modif(char *file);
int		outfile_dou_modif(char *file);
int		outfile_modif(char *file);
int		set_fd(int *savefd);
int		reset_fd(int *savefd);
int		redir_stuff(t_mimi *shell, int index);
int		create_file_redir(t_mimi *shell, int index);
int		exec_empty(char ***block, int index, int *fbp, t_mimi *shell);
int		count_pipe(t_mimi *shell);

/*____________________BUILTIN_STUFF__________________*/
int		builtin_finder(char *name);
int		exec_built(char ***block, int index, t_mimi *shell, int *fd_btw_pipe);
int		exec_builtin(char ***block, int index, int *fbp, t_mimi *shell);
int		ft_cd(char ***block, int index, t_mimi *shell, int *fbp);
int		free_alloc_cd(char ***block, t_mimi *shell, char *save, char **args);
int		ft_echo(char ***block, int index, t_mimi *shell, int *fbp);
int		ft_env(char ***block, int index, t_mimi *shell, int *fbp);
int		ft_exit(char ***block, int index, t_mimi *shell, int *fbp);
int		ft_export(char ***block, int index, t_mimi *shell, int *fbp);
int		ft_pwd(char ***block, int index, t_mimi *shell, int *fbp);
int		ft_unset(char ***block, int index, t_mimi *shell, int *fbp);

/*________________FREE_STUFF______________________*/
void	free_block(char ***block);
void	free_tab(char **tab);
int		return_error_pipe(char ***block, int *fbp, t_mimi *shell);
int		return_error_fork(char ***block, int *fbp, t_mimi *shell);
int		return_error_redir(char ***block, int *fbp, t_mimi *shell, int *pipefd);
int		return_error(char ***block, int *fbp, t_mimi *shell);
int		free_sfd(int *savefd);
void	free_list(t_mimi *shell);
void	free_env(t_mimi *shell);
void	free_listrec(t_list *list);

/*___________HEREDOC_STUFF_______________________*/
char	*get_name(int index);
int		create_file(char *name, t_mimi *shell);
char	*get_delim(t_mimi *shell);
int		write_in_hd(t_mimi *shell, int index, char *delim);
void	free_hd(t_mimi *shell);
int		modif_list(t_mimi *shell, int index);
int		heredoc_init(t_mimi *shell);

#endif
