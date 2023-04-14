/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 01:39:08 by satushi           #+#    #+#             */
/*   Updated: 2023/04/14 20:49:18 by kazuki           ###   ########.fr       */
/*   Updated: 2023/04/14 12:31:19 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	generate_child(t_node *node, char *path, char **argv, char **environ)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	prepare_pipe_child(node);
	if (path == NULL)
		exit(0);
	if (redirect_reconect(node->command) == 1)
		exit(1);
	if (is_builtin(node->command->args->word))
		exit(do_builtin(node->command->args->word, node->command));
	else
	{
		if (path[0] == '/' || path[0] == '.')
			execve(path, argv, ready_nextenviron());
		else
		{
			if (searchpath(path) == NULL)
				exit(127);
			else
				execve(searchpath(path), argv, environ);
		}
		printf("commad not found :x\n");
		exit(127);
	}
}

void	check_executable(t_node *node, char *cmd)
{
	t_redirect	*redirect;
	char		*checked_path;

	redirect = *(node->command->redirect);
	while (redirect != NULL)
	{
		if (redirect->redirectfile == -1 || redirect->ambigous == true)
			return (redirectfile_check(redirect));
		redirect = redirect->next;
	}
	checked_path = searchpath(cmd);
	if (is_builtin(cmd) == false && cmd[0] != '/' && cmd[0] != '.' \
	&& checked_path == NULL && ft_strcmp("exit", cmd) != 0)
	{
		printf("minishell: %s: command not found :x\n", cmd);
		g_env->err_status = 127;
	}
	free(checked_path);
}

static void	exec_command(pid_t pid, t_node *node, char **argv, char **environ)
{
	if (pid == 0 && argv[0] != NULL)
	{
		check_executable(node, argv[0]);
		generate_child(node, argv[0], argv, environ);
	}
	else if (pid == 0 && argv[0] == NULL)
	{
		redirectfile_check_noexe(*(node->command->redirect));
		generate_child(node, NULL, argv, environ);
	}
}

pid_t	exec_command_line(t_node *node)
{
	extern char	**environ;
	pid_t		pid;
	char		**argv;

	argv = args_to_argv(node->command->args);
	if (!argv)
		fatal_error("malloc");
	prepare_pipe(node);
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	exec_command(pid, node, argv, environ);
	prepare_pipe_parent(node);
	aray_free(argv);
	if (node->next)
		return (exec_command_line(node->next));
	return (pid);
}

void	exec(t_node *node)
{
	pid_t	last_pid;

	if (node == NULL)
		last_pid = -1;
	else
	{
		ready_redirection_file(node);
		if (g_env->readline_interrupted)
		{
			g_env->readline_interrupted = false;
			g_env->err_status = 1;
			rl_event_hook = NULL;
			return ;
		}
		last_pid = exec_command_line(node);
	}
	wait_pipeline(last_pid);
}
