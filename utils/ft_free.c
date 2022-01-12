/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:38:42 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/12 15:15:11 by jlong            ###   ########.fr       */
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
