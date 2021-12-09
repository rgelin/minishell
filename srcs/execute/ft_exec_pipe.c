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

int	ft_exec_bis(t_exc *exc, int nbr_pipe, char ***env)
{
	int	fds[2 * nbr_pipe];
	int	i;
	int	pid;
	int	status;

		for (int j = 0; j < nbr_pipe; j++)
			pipe(fds + j * 2);
	i = 0;
	// printf("nbr pipe === %d\n", nbr_pipe);
	while (i <= nbr_pipe * 2)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i != 0)
				dup2(fds[(i - 1) * 2], STDIN_FILENO);
			if (i < nbr_pipe)
				dup2(fds[i * 2 + 1], STDOUT_FILENO);
			for(int j = 0; j < nbr_pipe * 2; j++)
				close(fds[i]);
			execute(exc[i], env);
			exit(EXIT_SUCCESS);
		}
		waitpid(pid, &status, 0);
		i++;
	}
	for (int j = 0; j < nbr_pipe * 2; j++)
		close(fds[j]);
	return (status);
}