/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:38:42 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/12 14:28:36 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

// static void	ft_free_redirect(t_exc *last_tab, int i)
// {
// 	int	j;

// 	j = 0;
// 	if (last_tab[i].redirect && last_tab[i].redirect[j])
// 	{
// 		while (last_tab[i].redirect[j] != NULL)
// 		{
// 			free (last_tab[i].redirect[j]);
// 			j++;
// 		}
// 	}
// 	free(last_tab[i].redirect);
// }

// static void	ft_free_arg(t_exc *last_tab, int i)
// {
// 	int	j;

// 	j = 0;
// 	if (last_tab[i].arg && last_tab[i].arg[j])
// 	{
// 		while (last_tab[i].arg[j] != NULL)
// 		{
// 			free (last_tab[i].arg[j]);
// 			j++;
// 		}
// 	}
// 	free(last_tab[i].arg);
// }

// static void	ft_free_heredoc(t_exc *last_tab, int i)
// {
// 	int	j;

// 	j = 0;
// 	if (last_tab[i].heredoc && last_tab[i].heredoc[j])
// 	{
// 		while (last_tab[i].heredoc[j] != NULL)
// 		{
// 			free (last_tab[i].heredoc[j]);
// 			j++;
// 		}
// 	}
// 	free(last_tab[i].heredoc);
// }

/*
*pas le seul exit code --> recup les exit code d'execv
*/
void	ft_free_tab_exc(t_exc *last_tab, t_pars *tab)
{
	int	i;

	i = -1;
	if (last_tab)
	{
		while (tab && ++i <= tab->pipe)
		{
			if (last_tab[i].cmd)
				free(last_tab[i].cmd);
			if (last_tab[i].opt)
				free(last_tab[i].opt);
			if (last_tab[i].redirect)
				ft_free(last_tab->redirect, ft_tabsize(last_tab->redirect));
			if (last_tab[i].arg)
				ft_free(last_tab->arg, ft_tabsize(last_tab->arg));
			if (last_tab[i].heredoc)
				ft_free(last_tab->heredoc, ft_tabsize(last_tab->heredoc));
			// ft_free_redirect(last_tab, i);
			// ft_free_arg(last_tab, i);
			// ft_free_heredoc(last_tab, i);
		}
	}
}
