
#include "../srcs/minishell.h"

extern int	g_exit_code;

void	init_ptn(t_exc *tab)
{
	tab->cmd = NULL;
	tab->opt = NULL;
	tab->arg = NULL;
	tab->redirect = NULL;
}

char *option(char **options)
{
	char	*line;
	int		i;
	int		size;

	size = 0;
	i = 0;
	if (options[i] == NULL)
		return (NULL);
	while (options[i])
	{
		size = size + ft_strlen(options[i]);
		i++;
	}
	line = malloc(sizeof(line) * (size + 2));
	i = 0;
	line[0] = '-';
	line[1] = '\0';
	while (options[i])
	{
		line = ft_strcat(line, options[i]);
		free(options[i]);
		i++;
	}
	return (line);
}

t_exc *last_parsing(t_pars *tab)
{
	int		i;
	//int		j;
	t_exc	*last_tab;
	
	last_tab = NULL;
	last_tab = malloc(sizeof(t_exc) * (tab->pipe + 1));
	if (!last_tab)
	{
		//fonction qui free tout mon tab
		exit(EXIT_FAILURE);
	}
	i = 0;
	init_ptn(last_tab);
	while (i < tab->pipe + 1)
	{
		if (tab[i].command)
			last_tab[i].cmd = tab[i].command;
		if (tab[i].option)
			last_tab[i].opt = option(tab[i].option);
		if (tab[i].redirect)
			last_tab[i].redirect = tab[i].redirect;
		if (tab[i].arg)
			last_tab[i].arg = ft_arg(tab[i].arg);
		// printf("last_tab[%d]->command = %s\n", i, last_tab[i].cmd);
		// printf("last_tab[%d]->opt = %s\n", i, last_tab[i].opt);
		//j = 0;
		// if (last_tab[i].redirect[j] != NULL)
		// {
		// 	while(last_tab[i].redirect[j])
		// 	{
		// 		// printf("last_tab[%d]->redirect = %s\n", i, last_tab[i].redirect[j]);
		// 		j++;
		// 	}
		// }
		// j = 0;
		// if (tab[i].arg && last_tab[i].arg[j] != NULL)
		// {
		//  	while(last_tab[i].arg[j])
		//  	{
		//  		printf("last_tab[%d].arg = %s\n", i, last_tab[i].arg[j]);
		//  		j++;
		//  	}
		// }
		i++;
	}
	return (last_tab);
}
