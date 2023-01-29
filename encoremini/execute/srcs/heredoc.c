#include "../../includes/execute.h"

void	end_heredoc(char **contents, t_mimi *shell, char **s, int *i)
{
	write(shell->hd.tab_fd[*i], *contents, ft_strlen(*contents));
/*	if (!s && g_exit_ret != 424242)
		print_error_heredoc(exec, *i);*/
	if (*s)
		free(*s);
}

char	*add_line(char *contents, char *s)
{
	char *swp;

	swp = contents;
	contents = ft_strjoin(swp, s);
	free(swp);
	if (!contents)
		return (NULL);
	swp = contents;
	contents = ft_strjoin(swp, "\n");
	free(swp);
	return (contents);
}


int	print_on_file(char **contents, int *i, t_mimi *shell)
{
	char	*s;

	s = readline("> ");
	if (!s || !strcmp(s, shell->hd.tab_exit_code[*i]))
		return (end_heredoc(contents, shell, &s, i), 2);
	else
	{
		s = ft_heredoc_expand(s, shell->env);
		if (!s)
		{
			free_string(*contents);
			return (print_error("!malloc 1 heredoc()"));
		}
		*contents = add_line(*contents, s);
		if (!*contents)
		{
			free(s);
			return (print_error("!malloc 2 heredoc()"));
		}
	}
	if (s)
		free(s);
	return (OK);
}

int	load_heredoc(int i, t_mimi *shell)
{
	int		start;
	char	*contents;

	contents = malloc(sizeof(char) * 1);
	if (!contents)
	{
		ft_putstr_fd("malloc fail, load_heredoc()", STDERR_FILENO);
		return (ERROR);
	}
	contents[0] = 0;
	start = 0;
	while (!start || strcmp(contents, shell->hd.tab_exit_code[i]))
	{
		start = print_on_file(&contents, &i, shell);
		if (start == 1)
			return (ERROR);
		else if (start == 2)
			break ;
	}
	free(contents);
	return (OK);
}


int	heredoc(t_mimi *shell, int i)
{
	int	hold_fd;

	hold_fd = dup(STDIN_FILENO); // sauvegarde du stdin actuel
	//signal_catching_mode(HEREDOC);
	shell->hd.tab_fd[i] = create_file(gen_name(shell, i), shell);
	if (!shell->hd.tab_fd[i])
		return (ERROR);
	if (load_heredoc(i, shell) == 1)
		return (ERROR);
	//signal_catching_mode(INTERACTIVE);
	/*if (g_exit_ret == 424242) // Si il ya eu un Cntrl C
		free_heredoc(exec);*/
	dup2(hold_fd, STDIN_FILENO); 
	close(hold_fd);
	return (OK);
}

int	heredoc_init(t_mimi *shell)
{
	if (!shell->nb_hd)
		return (OK);
	shell->hd.tab_fd = (int *)malloc(sizeof(int) * shell->nb_hd); // tableau de fd...
	if (!shell->hd.tab_fd)
		return (ERROR);
	shell->hd.cpt = 0;
	while (shell->hd.cpt < shell->nb_hd) // && (!signal cntrl C)
		heredoc(shell, shell->hd.cpt++);
	return (OK);
}
