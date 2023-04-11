/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:24:47 by user              #+#    #+#             */
/*   Updated: 2023/04/04 22:15:06 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	exportwd_check(char *arg)
{
	if (!('a' <= *arg && *arg <= 'z'))
		if (!('A' <= *arg && *arg <= 'Z'))
			if (*arg != '_')
				return (false);
	arg++;
	while (*arg != '\0' && *arg != '=')
	{
		if ((!ft_isalnum(*arg) && *arg != '_') || \
		is_special_word_character(*arg) == true)
			return (false);
		arg++;
	}
	return (true);
}

static bool	error_unset(char *sub)
{
	printf("-minishell: %s: not correct argment!! booboo:X\n", sub);
	return (true);
}

static void	errorstatus_set(bool flag)
{
	if (flag == true)
		g_env->err_status = 1;
	else
		g_env->err_status = 0;
}

void	ms_unset(char *line, t_command *command)
{
	char	**commands;
	size_t	position;
	bool	not_correctarg;

	(void)line;
	not_correctarg = false;
	commands = command_to_array(command);
	if (!commands)
		fatal_error("malloc");
	if (commands[1] == NULL)
	{
		free_commands(commands);
		return ;
	}
	position = 0;
	while (commands[position] != NULL)
	{
		if (exportwd_check(commands[position]) == false)
			not_correctarg = error_unset(commands[position]);
		else
			map_unset(&g_env, commands[position]);
		position++;
	}
	errorstatus_set(not_correctarg);
	free_commands(commands);
}
