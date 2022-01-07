#include "../srcs/minishell.h"

//error si on a des trucs comme <> ou >< ?
void	split_redirect(char **redirect, t_exc *tab, int m)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	tab->redirect = malloc(sizeof(char *) * (m + 1));
	if (!tab->redirect)
		exit(EXIT_FAILURE);
	while (redirect[i] != NULL)
	{
		if ((redirect[i][0] == '<' && redirect[i][1] != '<')
			|| (redirect[i][0] == '>' && redirect[i][1] != '<'))
		{
			tab->redirect[j] = ft_strdup(redirect[i]);
			j++;
		}
		i++;
	}
	tab->redirect[j] = NULL;
}
/*
void	split_heredoc(char **redirect, t_exc *tab, int n)
{
	int	i;

	i = 0;
	tab->heredoc = malloc(sizeof(char *) * (n + 1));
	if (!tab->heredoc)
		exit(EXIT_FAILURE);
	while (redirect[i] != NULL)
	{
		if (redirect[i][0] == '<' && redirect[i][1] == '<')
		{

		}
		i++;
	}	
}
*/
void	heredoc_or_redirect(char **redirect, t_exc *tab)
{
	int	i;
	int	n;
	int	m;

	i = 0;
	n = 0;
	m = 0;
	while (redirect[i])
	{
		if (redirect[i][0] == '<' && redirect[i][1] == '<')
			n++;
		else
			m++;
		i++;
	}
	split_redirect(redirect, tab, m);
}
