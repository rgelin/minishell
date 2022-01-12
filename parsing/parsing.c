/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:21:29 by jlong             #+#    #+#             */
/*   Updated: 2022/01/12 12:22:01 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	init_quote(t_quote *quote)
{
	quote->simple_quote = 0;
	quote->double_quote = 0;
}

int	check_parsing(t_state *s)
{
	if (!check_quote(s->line, s->eof))
	{
		write(1, "Error quote\n", 12);
		ft_free_pars_error(s);
		return (0);
	}
	if (s->n_of_pipe >= 0)
		s->pipe = get_index(s->line, (s->n_of_pipe + 1), '|');
	return (1);
}

int	check_quote(char *line, int index)
{
	int		i;
	t_quote	quote;

	init_quote(&quote);
	i = -1;
	while (++i < index)
	{
		if (line[i] == '\'')
		{
			if (quote.simple_quote == 0 && quote.double_quote == 0)
				quote.simple_quote = 1;
			else
				quote.simple_quote = 0;
		}
		if (line[i] == '"')
		{
			if (quote.double_quote == 0 && quote.simple_quote == 0)
				quote.double_quote = 1;
			else
				quote.double_quote = 0;
		}		
	}
	if (quote.simple_quote == 0 && quote.double_quote == 0)
		return (1);
	return (0);
}

void	check_char(t_state *s)
{
	int	i;

	i = -1;
	while (s->line[++i] != '\0')
	{	
		if (s->line[i] == 124 && check_quote(s->line, i))
			s->n_of_pipe++;
	}
	s->eof = i;
}

t_pars	*parsing(t_state *s)
{
	t_pars	*tab;

	tab = NULL;
	check_char(s);
	if (check_parsing(s))
	{
		tab = split_line(s);
		tab->pipe = s->n_of_pipe;
		ft_free_pars_tab(s);
	}
	return (tab);
}
