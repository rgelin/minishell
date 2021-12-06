#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

int	exec_pipe(t_exc *exc, char ***env, int size)
{
	int		fd[2];
	pid_t	pid;
	int		i;
	int		oldfd;
	int		status;
	(void)env;

	i = 0;
	oldfd = -1;
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
				if (oldfd != -1)
					close(oldfd);
				close(fd[0]);
			}
			if (i <= size - 1)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			execute(exc[i], env);
		}
		waitpid(pid, &status, 0);
		close(fd[1]);
		oldfd = fd[0];
		i++;
	}
	return (status);
}
