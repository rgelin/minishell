#include "../srcs/minishell.h"

t_pars new_parsing(char *line)
{
	t_pars	tab;
	char	**tmp;
	int		i;
	int		heredoc;
	int		previous;
	int		cmd;
	int		redirection;

	i = 0;
	heredoc = 0;
	previous = 0;
	cmd = 0;
	redirection = 0;
	init_tab(&tab);
	tmp = ft_split_parsing(line, ' ');
	while (tmp[i] != NULL)
	{
		if (tmp[i][0] == '<' && tmp[i][1] == '<')
		{
			//fonction heredoc
			//heredoc = 1 si le << est collé au texte je vais devoir changer
			//le heredoc à 0 est bien mettre les lettres à rentré
			// et noté previous a 1
		}
		else if (*tmp && heredoc == 1)
		{
			//c'est ce qu on doit rentrer dans le heredoc
			//fonction heredoc
			//heredoc = 0
			//previous a 1
		}
		else if (*tmp[i] == '<'|| *tmp[i] == '>')
		{
			//fonction redirection
			//si heredoc est = 1 c'est une error ? a verif
			//redirection = 1
		}
		else if (*tmp && redirection == 1)
		{
			//mettre dans redirection puis mettre redirection = 0
		}
		else if (*tmp && (previous == 1 || cmd == 0 || heredoc == 0)) // a verifie pour la commande
		{
			//ca devient ma commande
			//cmd = 1
			//previous = 0
		}
		else if (*tmp && previous == 0 && cmd == 1)
		{
			//fonction argument ou option ?
			//si il y a un - c'est une option
			//sinon c'est un argument
		}
		i++;
	}
}
