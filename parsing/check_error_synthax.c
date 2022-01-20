/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_synthax.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:42:52 by jlong             #+#    #+#             */
/*   Updated: 2022/01/20 13:18:44 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

int	check_error_synthax(t_state *s)
{
	char	**tmp;
	int		i;
	int		error;

	i = -1;
	error = 0;
	tmp = ft_split_parsing(s->line, ' ');
	while (tmp && tmp[++i] != NULL)
	{
		if (tmp[i] && !ft_strncmp(tmp[i], ">>", 2) && tmp[i + 1] == NULL)
			error = 1;
		else if (tmp[i] && !ft_strncmp(tmp[i], "<<", 2) && tmp[i + 1] == NULL)
			error = 1;
		else if (tmp[i] && !ft_strncmp(tmp[i], "<", 1) && tmp[i + 1] == NULL)
			error = 1;
		else if (tmp[i] && !ft_strncmp(tmp[i], ">", 1) && tmp[i + 1] == NULL)
			error = 1;
		else if (tmp[i] && !ft_strncmp(tmp[i], "|", 1) && tmp[i + 1] == NULL)
			error = 1;
	}
	ft_free(tmp, ft_tabsize(tmp));
	if (error == 1)
		return (0);
	return (1);
}

int	check_error_synthax_bis(t_state *s)
{
	char	**tmp;
	int		i;
	int		error;

	i = -1;
	error = 0;
	tmp = ft_split_parsing(s->line, ' ');
	while (tmp && tmp[++i] != NULL)
	{
		if (tmp[i] && !ft_strncmp(tmp[i], ">>>", 3))
			error = 1;
		if (tmp[i] && !ft_strncmp(tmp[i], "<<<", 3))
			error = 1;
		if (tmp[i] && !ft_strncmp(tmp[i], "||", 2))
			error = 1;
	}
	ft_free(tmp, ft_tabsize(tmp));
	if (error == 1)
		return (0);
	return (1);
}

int	check_error_synthax_bis_bis(t_state *s, char c)
{
	char	**tmp;
	int		i;
	int		error;

	i = -1;
	error = 0;
	(void)c;
	tmp = ft_split_parsing(s->line, ' ');
	while (tmp && tmp[++i] != NULL)
	{
		if (tmp[i] && !ft_strncmp(tmp[i], ">>", 2) && tmp[i + 1] == NULL)
			error = 1;
		else if (tmp[i] && !ft_strncmp(tmp[i], "<<", 2) && tmp[i + 1] == NULL)
			error = 1;
		else if (tmp[i] && !ft_strncmp(tmp[i], "<", 1) && tmp[i + 1] == NULL)
			error = 1;
		else if (tmp[i] && !ft_strncmp(tmp[i], ">", 1) && tmp[i + 1] == NULL)
			error = 1;
		else if (tmp[i] && !ft_strncmp(tmp[i], "|", 1) && tmp[i + 1] == NULL)
			error = 1;
	}
	ft_free(tmp, ft_tabsize(tmp));
	if (error == 1)
		return (0);
	return (1);
}

int	check_parsing(t_state *s)
{
	if (!check_quote(s->line, s->eof))
	{
		write(2, "Error quote\n", 12);
		return (0);
	}
	if ((!check_error_synthax_bis(s)) || (!check_error_synthax(s)))
	{
		ft_putendl_fd("Error syntax", 2);
		return (0);
	}
	if (s->n_of_pipe >= 0)
		s->pipe = get_index(s->line, (s->n_of_pipe + 1), '|');
	return (1);
}
