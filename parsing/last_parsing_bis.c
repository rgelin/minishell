/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_parsing_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 13:30:52 by jlong             #+#    #+#             */
/*   Updated: 2022/01/18 08:23:51 by jlong            ###   ########.fr       */
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
int	check_all_string_bis(char	*line, char **env, char c, int index)
{
	t_tmp	tmp;
	int		i;
	int		size;

	size = 0;
	init_tmp(&tmp);
	i = index + 1;
	while (line[i] != c)
		i++;
	tmp.n = i;
	tmp.nl = ft_substr(line, 0, index);
	tmp.tmp = ft_substr(line, index, tmp.n - index);
	tmp.rest = ft_substr(line, tmp.n, (ft_strlen(line) - i));
	tmp.var = ft_arg_bis(tmp.tmp, env);
	tmp.new_line = ft_strjoin_double_free(tmp.nl, tmp.var);
	size = ft_strlen(tmp.new_line);
	tmp.new_line = ft_strjoin_double_free(tmp.new_line, tmp.rest);
	free(line);
	free(tmp.var);
	free(tmp.rest);
	line = NULL;
	line = tmp.new_line;
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
		{
			if (double_quote == 0)
			{
				simple_quote = 1;
				//fonction qui va reprendre l'indice de début et qui va regarder
				//jusque quand l'autre ' est puis le substr ect...
				// i = -1
				i = check_all_string_bis(line, env, '\'', i);
			}
		}
		if (line[i] == '\"')
		{
			if (simple_quote == 0)
			{
				double_quote = 1;
				//Pareil que avec double quote mais qui va changer les $
				//i = -1
				i = check_all_string_bis(line, env, '\"', i);
			}
		}
		i++;
	}
	tmp.new_line = line;
	free(line);
	line = NULL;
	return (tmp.new_line);
}
