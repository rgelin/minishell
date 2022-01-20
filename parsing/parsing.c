/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:21:29 by jlong             #+#    #+#             */
/*   Updated: 2022/01/20 10:06:08 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	init_quote(t_quote *quote)
{
	quote->simple_quote = 0;
	quote->double_quote = 0;
}

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
		if (tmp[i] && ft_strncmp(tmp[i], ">>", 2) && tmp[i + 1] == NULL)
			error = 1;
		else if  (tmp[i] && ft_strncmp(tmp[i], "<<", 2) && tmp[i + 1] == NULL)
			error = 1;
		else if  (tmp[i] && ft_strncmp(tmp[i], "<", 1) && tmp[i + 1] == NULL)
			error = 1;
		else if  (tmp[i] && ft_strncmp(tmp[i], ">", 1) && tmp[i + 1] == NULL)
			error = 1;
		if (error == 1)
			break ;
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
		if (tmp[i] && ft_strncmp(tmp[i], ">>>", 2))
			error = 1;
		if (tmp[i] && ft_strncmp(tmp[i], "<<<", 2))
			error = 1;
		if (tmp[i] && ft_strncmp(tmp[i], "||", 1))
			error = 1;
		if (error == 1)
			break ;
	}
	ft_free(tmp, ft_tabsize(tmp));
	if (error == 1)
		return (0);
	return (1);
}
//verifier les return 0
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
	if (s->n_of_pipe == -1)
	{
		ft_putendl_fd("Error syntax", 2);
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
		if (s->line[i] == '|' && s->line[i + 1] == '|')
		{
			s->n_of_pipe = -1;
			return ;
		}
		if (s->line[i] == '|' && check_quote(s->line, i))
			s->n_of_pipe++;
	}
	s->eof = i;
}

t_pars	*parsing(t_state *s, char **env)
{
	t_pars	*tab;

	tab = NULL;
	check_char(s);
	if (check_parsing(s))
	{
		tab = split_line(s, env);
		tab->pipe = s->n_of_pipe;
	}
	ft_free(s->cm, s->n_of_pipe + 1);
	ft_free_pars_tab(s);
	return (tab);
}
