/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_red.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 04:25:24 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/27 07:44:38 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*nexty(t_mimi *shell, char *msg, int ret)
{
	free(shell->line);
	shell->line = NULL;
	//return (NULL);
	return (char_err(msg, ret));
}

char	*nexy(t_mimi *shell, char *msg, int ret, char c)
{
	free(shell->line);
	shell->line = NULL;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	g_ret = ret;
	return (NULL);
}

char	*neyy(t_mimi *shell, char *msg, int ret, char c)
{
	free(shell->line);
	shell->line = NULL;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd(c, 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	g_ret = ret;
	return (NULL);
}

char	*do_red_next(t_mimi *shell, char *tmp, int x, char c)
{
	if (((shell->line[0] != '\0' && shell->line[1] == '\0' && (shell->line[0]
					!= '<' && c != '>')) || ((shell->line[0] == '>'
					|| shell->line[0] == '<') && (c == '>' || c == '<')
				&& shell->line[1] == '\0' && shell->line[0] == c)))
	{
		/*printf("minishell: syntax error near unexpected token `newline'\n");
		free(shell->line);
		shell->line = NULL;
		return (NULL);*/
		return (nexty(shell, "syntax error near unexpected token `newline'", 2));
	}
	else if (shell->line[0] != c)
	{
	/*	printf("minishell: syntax error near unexpected token `%c'\n",
			shell->line[0]);
		free(shell->line);
		shell->line = NULL;*/
		return (nexy(shell, "syntax error near unexpected token `", 2, c));
	}
	else if (shell->line[0] != '\0' && shell->line[0] == c && (shell->line[1]
			== '>' || shell->line[1] == '<') && (shell->line[2] == '>'
			|| shell->line[2] == '<'))
	{
		/*printf("minishell: syntax error near unexpected token `%c%c'\n",
			shell->line[1], shell->line[2]);
		free(shell->line);
		shell->line = NULL;*/
		return (neyy(shell, "syntax error near unexpected token `", 2, c));
	}
	else if (shell->line[0] != '\0' && shell->line[0] == c && (shell->line[1]
			== '>' || shell->line[1] == '<'))
	{
		/*printf("minishell: syntax error near unexpected token `%c'\n",
			shell->line[1]);
		free(shell->line);
		shell->line = NULL;*/
		return (nexy(shell, "syntax error near unexpected token `", 2, c));
	}
	else
	{
		tmp = johnny(tmp, get_in(shell->line, x));
		shell->line = cut_in(shell->line, x);
		if (tmp[0] == '<' && tmp[1] == '<')
			shell->nb_hd++;
//		printf("				DO_red tmp = -%s- -%s-\n", tmp, shell->line);
	}
	return (tmp);
}

char	*redir_vide(t_mimi *shell)
{
/*	printf("minishell: syntax error near unexpected token `newline'\n");
	//shell->ret = -1;
	free(shell->line);
	shell->line = NULL;
	//free_list(shell);*/
	return (nexty(shell, "syntax error near unexpected token `newline'", 2));
}

/*


ojauregu@e2r4p14:~$ cat >>>> truc 
bash: syntax error near unexpected token `>>'
ojauregu@e2r4p14:~$ <<<< truc 
bash: syntax error near unexpected token `<'

mimishell🐚 >><
entre, >, tmp = >, 2, ><
minishell: syntax error near unexpected token `<'
🐚mimishell🐚 ><>
entre, >, tmp = >, 2, <>
minishell: syntax error near unexpected token `<'


*/
char	*do_red(t_mimi *shell, int x, char c)
{
	char	*tmp;

//printf("DO_RED %d\n", x);
	if (x > 0)
	{
		tmp = get_in(shell->line, x);
		shell->line = cut_in(shell->line, x);
		shell->type = TXT;
	//	printf("the fuck %s, %c\n", tmp, c);
		return (tmp);
	}
	if (x == 0)
		x++;
	tmp = get_in(shell->line, x);
	shell->line = cut_in(shell->line, x);
	if (shell->line == NULL)
		return (redir_vide(shell));
	if (shell->line && (shell->line[0] == '<' || shell->line[0] == '>'))
	{
		shell->type = REDIR;
		tmp = do_red_next(shell, tmp, x, c);
	}
	shell->type = REDIR;
//	printf("TMP ++ %s, type = %d\n", tmp, shell->type);
	return (tmp);
}
