#include "minishell.h"

int	exec_pipe(t_exc *exc, char ***env, int size)
{
	int		fd[2];
	pid_t	pid;
	int		i;
	int		oldfd;
	int		status;
	(void)env;

	i = 0;
	oldfd = STDIN_FILENO;
	while (i <= size)
	{
		if (pipe(fd) == -1)
		{
			perror("error pipe");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("error fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (size != 0)
			{
				dup2(oldfd, STDIN_FILENO);
				close(oldfd);
			}
			if (i <= size - 1)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			if (size != 0)
				close(fd[0]);
			status = execute(exc[i], env);
			exit(status);
		}
		waitpid(pid, &status, 0);
		close(fd[1]);
		oldfd = fd[0];
		i++;
	}
	return (status);
}
