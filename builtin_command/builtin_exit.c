/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:21:24 by user              #+#    #+#             */
/*   Updated: 2023/04/12 22:28:01 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	bool	atolch(char *s1)
{
	while (*s1 == ' ' || *s1 == '\t')
		s1++;
	if (*s1 == '+' || *s1 == '-')
		s1++;
	while (ft_isdigit(*s1) == 1)
		s1++;
	while (*s1 == ' ' || *s1 == '\t')
		s1++;
	if (*s1 != '\0')
	{
		printf("exit\n");
		printf("not correct arg :X\n");
		return (false);
	}
	return (true);
}

static	bool	commandch(char **commands)
{
	size_t	posi;

	posi = 0;
	while (commands[posi] != NULL)
	{
		if (posi == 1)
			if (atolch(commands[posi]) == false)
				exit (255);
		posi++;
	}
	if (posi >= 3)
	{
		printf("exit\n");
		printf("too many argments\n");
		g_env->err_status = 1;
		free_commands(commands);
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

static	char	*return_arg(char *nanka)
{
	char	*new;

	new = NULL;
	while (*nanka == ' ' || *nanka == '\t')
		nanka++;
	while (*nanka != ' ' && *nanka != '\t' && *nanka != '\0')
		append_char(&new, *nanka++);
	append_char(&new, '\0');
	return (new);
}

void	ms_exit(char *line, t_command *command)
{
	char	**commands;
	char	*arg;

	(void)line;
	commands = command_to_array(command);
	if (!commands)
		fatal_error("malloc");
	if (commandch(commands) == false)
		return ;
	if (commands[1] == NULL)
	{
		printf("exit\n");
		exit (g_env->err_status);
	}
	arg = return_arg(commands[1]);
	if (ft_strcmp(arg, "0") == 0 || ft_strcmp(arg, "+0") == 0 \
	|| ft_strcmp(arg, "-0") == 0)
	{
		g_env->err_status = 0;
		exit(g_env->err_status);
	}
	if (!ms_atoi(arg) || (ms_atoi(arg) == -1 && ft_strlen(arg) > 2))
		show_error_exit();
	printf("exit\n");
	exit(ms_atoi(commands[1]));
}
