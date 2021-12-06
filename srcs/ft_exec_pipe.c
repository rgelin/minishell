#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

extern int	g_exit_code;

void	ft_sigint_exec(int signal)
{
	(void)signal;
	printf("\n");
	printf("fork\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_code = 130;
}

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
	signal(SIGINT, &ft_sig_int);
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
			signal(SIGINT, &ft_sigint_exec);
			if (size != 0)
			{
				dup2(oldfd, STDIN_FILENO);
				if (oldfd != -1)
					close(oldfd);
			}
			close(fd[0]);
			if (i <= size - 1)
			{
				dup2(fd[1], STDOUT_FILENO);
			}
			close(fd[1]);
			status = execute(exc[i], env);
			// printf("exit code: %d\n", status);
			// exit(status);
			
			// exit(g_exit_code);
		}
		// wait(&status);
		else
		{
			waitpid(pid, &status, 0);
			//pas sur que ce soit tres legal tout ca
			//mais cependant c'est une macro et pas une fonction
			status = WEXITSTATUS(status);
			close(fd[1]);
			oldfd = fd[0];
		}
		i++;
	}
	// printf("status: %d\n", status);
	return (status); 
}
