/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_var_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:21:25 by jlong             #+#    #+#             */
/*   Updated: 2022/01/14 16:24:49 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

char	*insert_exit_code(char *line, int index)
{
	char	*code;
	char	*tmp_line;
	char	*rest;
	char	*new_line;

	code = ft_itoa(g_global.exit_code);
	tmp_line = ft_substr(line, 0, index);
	rest = ft_substr(line, index + 2, (ft_strlen(line) - index));
	new_line = ft_strjoin_double_free(tmp_line, code);
	new_line = ft_strjoin_double_free(new_line, rest);
	free(line);
	free(rest);
	free(code);
	line = NULL;
	return (new_line);
}

char	*insert_var_env(char *line, int index, char **env)
{
	t_tmp	tmp;

	init_tmp(&tmp);
	tmp.n = index;
	tmp.tmp = ft_substr(line, 0, index);
	tmp.new_line = NULL;
	while (line[tmp.n] != '\0')
	{
		if (line[tmp.n] == ' ' || line[tmp.n] == '\'' || line[tmp.n] == '\0')
			break ;
		tmp.n++;
		tmp.m++;
	}
	tmp.nl = ft_substr(line, index + 1, tmp.m - 1);
	tmp.var = our_getenv(ft_strtrim(tmp.nl, "$"), env);
	tmp.rest = ft_substr(line, index + tmp.m, (ft_strlen(line) - index));
	tmp.new_line = ft_strjoin_double_free(tmp.tmp, tmp.var);
	tmp.new_line = ft_strjoin_double_free(tmp.new_line, tmp.rest);
	free(line);
	free(tmp.rest);
	free(tmp.var);
	line = NULL;
	return (tmp.new_line);
}

char	*check_var_env_bis(char *line, char **env, char c, int i)
{
	char	*new_line;

	new_line = NULL;
	if (c == '?')
	{
		new_line = insert_exit_code(line, i);
		//line = new_line;
	}
	else
	{
		new_line = insert_var_env(line, i, env);
		//line = new_line;
	}
	return (new_line);
}

char	*check_var_env(char *line, char **env)
{
	int		i;
	char	*new_line;

	i = 0;
	new_line = NULL;
	while (line[i] != '\0')
	{
		if (line[i] == '$' && line[i + 1] == '?')
		{
			new_line = check_var_env_bis(line, env, '?', i);
			line = new_line;
			i = -1;
		}
		else if (line[i] == '$' && (line[i + 1] == '\0' || line[i + 1] == ' '))
			i++;
		else if (line[i] == '$' && line[i + 1] == '$')
			i++;
		else if (line[i] == '$')
		{
			new_line = check_var_env_bis(line, env, ' ', i);
			line = new_line;
			i = -1;
		}
		else
			new_line = line;
		i++;
	}
	return (new_line);
}

char	**ft_arg(char **arg, char **env)
{
	int	i;

	i = 0;
	while (arg && arg[i])
	{
		if (arg[i][0] == '\'')
		{
			arg[i] = ft_strtrim(arg[i], "\'");
		}
		else if (arg[i][0] == '\"')
		{
			arg[i] = ft_strtrim(arg[i], "\"");
			arg[i] = check_var_env(arg[i], env);
		}
		else
		{
			arg[i] = check_var_env(arg[i], env);
		}
		i++;
	}
	return (arg);
}
