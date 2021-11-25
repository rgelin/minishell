#include "../srcs/minishell.h"

void	ft_perror(char *cmd, char *arg, char *err_msg, char *other_msg)
{
	// char	*str_err;

	// str_err = ft_strjoin("minishell: ", cmd);
	// str_err = ft_strjoin_free(str_err, cmd);
	// str_err = ft_strjoin_free(str_err, ": ");
	// if (arg)
	// {
	// 	str_err = ft_strjoin_free(str_err, arg);
	// 	str_err = ft_strjoin_free(str_err, ": ");
	// }
	// str_err = ft_strjoin_free(str_err, strerror(errnum));
	// write(2, str_err, ft_strlen(str_err));
	// free(str_err);
	// str_err = NULL;
	write(2, "minishell: ", 11);
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	if (err_msg)
		write(2, err_msg, ft_strlen(err_msg));
	if (other_msg)
		write(2, other_msg, ft_strlen(other_msg));
	write(2, "\n", 1);
}