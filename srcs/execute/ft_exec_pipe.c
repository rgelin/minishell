#include "../minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

extern int	g_exit_code;

int	exec_pipe(t_exc *exc, char ***env, int size)
{
	int		fd[2];
	// pid_t	pid;
	int		i;
	int		oldfd;
	int		status;
	(void)env;

	i = 0;
	oldfd = -1;
	// signal(SIGINT, &ft_sig_int);
	while (i <= size)
	{
		if (pipe(fd) == -1)
		{
			perror("error pipe");
			exit(EXIT_FAILURE);
		}
		g_global.fork_pid = fork();
		if (g_global.fork_pid == -1)
		{
			perror("error fork");
			exit(EXIT_FAILURE);
		}
		if (g_global.fork_pid == 0)
		{
			// signal(SIGINT, &ft_sigint_exec);
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
			
			exit(status);
		}
		// wait(&status);
			waitpid(g_global.fork_pid, &status, 0);
			if (WIFEXITED(status))
				status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				status = 128 + WTERMSIG(status);
		close(fd[1]);
		oldfd = fd[0];
		i++;
	}
	g_global.fork_pid = 0;
	ft_signal_msg(status);
	// printf("status: %d\n", status);
	return (status); 
}
