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

typedef struct s_heredoc
{
	int	*tab_fd;
	int	index;
	int	nb_to_close;
}				t_heredoc;

typedef struct s_mimi
{
	int			y;
	int			x;
	int			z;
	int			s;
	int			run;
	int			end;
	int			ret;
	int			fin;
	int			tip;
	int			type;
	int			nb_hd;
	int			index;
	int			ferme;
	int			quote;
	int			size;
	void		*ptr;
	int			ret_line;
	t_list		*list;
	t_list		*envlist;
	char		*str;
	char		*args;
	char		*line;
	char		*command;
	const char	*file;
	int			flies;
	char		**tab;
	char		**env;
	char		instr[9];
	int			save_fd[3];
	t_heredoc	hd;
}				t_mimi;

extern int		g_ret;//globale

char	*ft_itoaa(int n);
char	*cut_from_posi(char *str, int e);
char	*cpy_from_two_posi(char *str, int s, int e);
int		str_c(char *str, char c);
char	*dollary(char *str, t_mimi *shell, int x);
char	*find_env(char *str, t_mimi *shell);
char	*ft_itoaa(int n);
int		ft_is_nb(char c);
int		ft_is_alpha(char c);
char	*cut_i(char *str, int x);
char	*joi(char *s1, char *s2);
char	*malicious(const char *str);
size_t	ft_strlenn(const char *s);
int		where_charly(char *str, int x, char c);
///////SRCS2/////
char	*cpy_from_two_pos(char *str, int s, int e);
char	*char_err(char *msg, int ret);
char	*cut_from_pos(char *str, int e);
char	*do_end(t_mimi *shell);
char	*do_pipe(t_mimi *shell, int x);
char	*nexty(t_mimi *shell, char *msg, int ret);
char	*ney(t_mimi *shell, char *msg, int ret, char c);
char	*nexy(t_mimi *shell, char *msg, int ret, char c);
char	*neyy(t_mimi *shell, char *msg, int ret, char c);
char	*do_red_next(t_mimi *shell, char *tmp, int x, char c);
char	*redir_vide(t_mimi *shell, char *tmp);
char	*do_red(t_mimi *shell, int x, char c);
char	*do_white(t_mimi *shell, int x);
t_list	*ft_lstnew(char *content);
char	*inside_kote_34(char *str, t_mimi *shell, int x, int c_pos);
char	*inside_kote_39(char *str, t_mimi *shell, int x, int c_pos);
char	*goty(t_mimi *shell, char *msg, int ret, char c);
char	*next_goats(t_mimi *shell, char *tmp, int x);
char	*goats(t_mimi *shell, int x);
char	*cut_in(char *str, int x);
char	*get_in(char *str, int x);
int		int_err(char *msg, int ret);
char	*join(char *s1, char *s2);
char	*johnny(char *s1, char *s2);
int		where_is_charly(char *str, int x, char c);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_listadd_back(t_list **alst, t_list *new);
t_list	*ft_listnew(char *content, int x);
void	*ft_memcpy(void *dst, const void *src, size_t size);
size_t	ft_memlen(void *s);
void	set_struct(t_mimi	*shell, char **envp);
int		main(int ac, char **av, char **envp);
int		ret_nb(int ret, char *msg, t_mimi *shell);
//static void	reset_stuff(t_mimi *shell);
//static void	set_stuff(t_mimi *shell, char **envp);
void	set_struct(t_mimi	*shell, char **envp);
char	**next_hd(t_mimi *shell, int x);
int		next_kote(char *str, char c, int x);
int		check_for_quotes(t_mimi *shell, char c);
int		mani(t_mimi *shell);
char	*repartiteur(t_mimi *shell, int x, char *str);
char	**malloc_char_et_et(int size);
char	*copy_char_et(char *str);
char	**error_copy_char_et_et(char **tmp, int size);
char	**copy_char_et_et(char **str);
void	free_list(t_mimi *shell);
void	show_list(t_mimi *shell);///////a virer

#endif