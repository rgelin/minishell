#include "../srcs/minishell.h"


/*
	arg == char ** avec plusieurs arg
	=> char * cmd
	=> char * opt
	=> faire un tab taille n pour arg
	=> size == cmd + opt + taille arg * taille char *
*/

static int	ft_size_cmd(t_exc cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (cmd.cmd)
		i++;
	if (cmd.opt)
		i++;
	while (cmd.arg[j++])
		i++;
	return (i + 1);
}

char	**create_cmd(t_exc command)
{
	char	**to_ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	to_ret = (char **)malloc(sizeof(char *) * ft_size_cmd(command));
	if (!to_ret)
		return (NULL);
	to_ret[ft_size_cmd(command)] = NULL;
	if (command.cmd)
		to_ret[i++] = command.cmd;
	if (command.opt)
		to_ret[i++] = command.opt;
	if (command.arg)
	{
		while (command.arg[j])
			to_ret[i++] = command.arg[j++];
	}
	to_ret[i] = NULL;
	return (to_ret);
}
