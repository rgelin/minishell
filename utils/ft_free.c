/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:38:42 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/12 14:36:28 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

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
				ft_free(last_tab->redirect, ft_tabsize(last_tab->redirect) - 1);
			if (last_tab[i].arg)
				ft_free(last_tab->arg, ft_tabsize(last_tab->arg) - 1);
			if (last_tab[i].heredoc)
				ft_free(last_tab->heredoc, ft_tabsize(last_tab->heredoc) - 1);
		}
	}
}
