/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:21:24 by user              #+#    #+#             */
/*   Updated: 2023/04/11 19:42:45 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	bool	commandch(char **commands)
{
	size_t	posi;

	posi = 0;
	while (commands[posi] != NULL)
		posi++;
	if (posi >= 3)
	{
		printf("exit\n");
		printf("too many argments\n");
		g_env->err_status = 1;
		return (false);
	}
	return (true);
}

static	bool	atolch(char *s1)
{
	if (*s1 == '+' || *s1 == '-')
		s1++;
	while (ft_isdigit(*s1) == 1)
		s1++;
	if (*s1 != '\0')
	{
		printf("exit\n");
		printf("not correct arg :X\n");
		return (false);
	}
	return (true);
}

static	void	show_error_exit(void)
{
	printf("exit\n");
	printf("minishell: exit: numeric argument required\n");
	exit(255);
}

void	ms_exit(char *line, t_command *command)
{
	char	**commands;

	(void)line;
	commands = command_to_array(command);
	if (commandch(commands) == false)
	{
		free_commands(commands);
		return ;
	}
	if (!commands)
		fatal_error("malloc");
	if (commands[1] == NULL)
	{
		printf("exit\n");
		exit(g_env->err_status);
	}
	if (!ms_atoi(commands[1]) || (ms_atoi(commands[1]) == -1 \
		&& ft_strlen(commands[1]) > 2))
		show_error_exit();
	if (atolch(commands[1]) == false)
		exit (255);
	printf("exit\n");
	exit(ms_atoi(commands[1]));
}
