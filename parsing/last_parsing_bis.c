/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_parsing_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 13:30:52 by jlong             #+#    #+#             */
/*   Updated: 2022/01/18 13:13:55 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

char	*get_var_env_bis(char *tab_redirect, char **env, int i)
{
	t_tmp new;

	init_tmp(&new);
	new.tmp = ft_substr(tab_redirect, 0, i);
	new.rest = ft_substr(tab_redirect, i, (ft_strlen(tab_redirect) - i));
	new.var = ft_arg_bis(new.rest, env);
	new.new_line = ft_strjoin_double_free(new.tmp, new.var);
	free(tab_redirect);
	free(new.var);
	tab_redirect = NULL;
	return (new.new_line);
}
//index est l 'endroit où on a le symbole ' ou "
//je dois return la ou je me suis arrête dans la string
//genre le début que j'ai pas touché + taille de la nouvelle variable
int	check_all_string_bis(char	**line, char **env, char c, int index)
{
	t_tmp	tmp;
	int		i;
	int		size;

	size = 0;
	init_tmp(&tmp);
	i = index + 1;
	while ((*line)[i] != '\0')
	{
		if (c != 'N' && (*line)[i] == c)
			break ;
		if (c == 'N' && ((*line)[i] == '\'' || (*line)[i] == '\"'))
			break ;
		i++;
	}
	printf("line = %s\n", (*line));
	tmp.n = i + 1;
	tmp.nl = ft_substr((*line), 0, index);
	printf("tmp.nl = %s\n", tmp.nl);
	tmp.tmp = ft_substr((*line), index, i - index);
	printf("tmp.tmp = %s\n", tmp.tmp);
	tmp.rest = ft_substr((*line), i, (ft_strlen((*line)) - i));
	printf("tmp.rest = %s\n", tmp.rest);
	tmp.var = ft_arg_bis(tmp.tmp, env);
	tmp.new_line = ft_strjoin_double_free(tmp.nl, tmp.var);
	size = ft_strlen(tmp.new_line);
	tmp.new_line = ft_strjoin_double_free(tmp.new_line, tmp.rest);
	free((*line));
	if (tmp.var)
		free(tmp.var);
	if (tmp.rest)
		free(tmp.rest);
	(*line) = NULL;
	(*line) = tmp.new_line;
	return (size);
}

char	*check_all_string(char	*line, char **env)
{
	int		i;
	int		double_quote;
	int		simple_quote;
	t_tmp	tmp;

	init_tmp(&tmp);
	i = 0;
	double_quote = 0;
	simple_quote = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
			i = check_all_string_bis(&line, env, '\'', i);
		else if (line[i] == '\"')
			i = check_all_string_bis(&line, env, '\"', i);
		else if (line[i] == '$')
			i = check_all_string_bis(&line, env, 'N', i);
		i++;
	}
	tmp.new_line = ft_strdup(line);
	free(line);
	line = NULL;
	return (tmp.new_line);
}
