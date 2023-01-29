#include "../../includes/execute.h"

int	print_error(char *s)
{
	ft_putstr_fd("ERROR: ", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
	//g_exit_ret = 127;
	return (ERROR);
}

int	create_file(char *filename, t_mimi *shell)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH, 0777);
	if (fd == -1)
        ft_putstr_fd("file creation failed", STDERR_FILENO);
	else
        shell->hd.cpt_close++;
	return (fd);
}

char	*gen_name(t_mimi *shell, int i, char **exit_code)
{
	char	*nb;

	nb = ft_itoa(i);
	if (!nb)
	{
        ft_putstr_fd("malloc fail, gen_name()", STDERR_FILENO);
		return (NULL);
	}
    exit_code = next_hd(i, shell);
	next_hd(i, shell) = ft_strjoin("hold/temp", nb);
	/*if (!exec->hd.tab_of_name_file[i])
		print_error("malloc failed 1");*/
	free(nb);
	//return (exec->hd.tab_of_name_file[i]);
}