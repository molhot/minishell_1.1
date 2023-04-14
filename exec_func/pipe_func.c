/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 01:16:50 by satushi           #+#    #+#             */
/*   Updated: 2023/04/14 09:27:28 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*static	void	cpy_pipe(int dst[2], int src[2])
{
	dst[0] = src[0];
	dst[1] = src[1];
}*/

void	prepare_pipe(t_node *node)
{
	int		*dst;
	int		*src;

	if (node->next == NULL)
		return ;
	if (pipe(node->command->out_fd) < 0)
		fatal_error("pipe");
	dst = node->next->command->in_fd;
	src = node->command->out_fd;
	dst[0] = src[0];
	dst[1] = src[1];
}

void	prepare_pipe_child(t_node *node)
{
	if (node->command->out_fd[0] != -1)
		close(node->command->out_fd[0]);
	dup2(node->command->in_fd[0], STDIN_FILENO);
	if (node->command->in_fd[0] != STDIN_FILENO)
		close(node->command->in_fd[0]);
	dup2(node->command->out_fd[1], STDOUT_FILENO);
	if (node->command->out_fd[1] != STDOUT_FILENO)
		close(node->command->out_fd[1]);
}

void	prepare_pipe_parent(t_node *node)
{
	if (node->command->in_fd[0] != STDIN_FILENO)
		close(node->command->in_fd[0]);
	if (node->next != NULL)
		close(node->command->out_fd[1]);
}

void	handle_last_result(int wstatus)
{
	if (WIFSIGNALED(wstatus))
	{
		if (WTERMSIG(wstatus) == SIGQUIT)
			ft_putendl_fd("Quit: 3", STDERR_FILENO);
		if (WTERMSIG(wstatus) == SIGINT)
			ft_putendl_fd("", STDERR_FILENO);
		g_env->err_status = WTERMSIG(wstatus) + 128;
	}
	else
		g_env->err_status = WEXITSTATUS(wstatus);
}

void	wait_pipeline(pid_t last_pid)
{
	int		wstatus;
	pid_t	wait_result;

	while (1)
	{
		wait_result = wait(&wstatus);
		if (wait_result == last_pid)
			handle_last_result(wstatus);
		else if (wait_result < 0)
		{
			if (errno == ECHILD)
				break ;
			else if (errno == EINTR)
				continue ;
			else
				fatal_error("wait");
		}
	}
}
