/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:22:25 by user              #+#    #+#             */
/*   Updated: 2023/04/20 01:22:40 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	is_valid_export_arguments(char *arg)
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

void	replace_word(char *src)
{
	while (*src != '\0')
	{
		if (*src == '"')
			*src = '\"';
		if (*src == '\\')
			*src = '\\';
		src++;
	}
}

void	insert_env_variable(char *start, char *end, char *last)
{
	char	*key;
	char	*value;

	key = ft_strndup(start, end - start);
	if (last == end)
		value = ft_strdup("");
	else
		value = ft_strndup(end + 1, last - end - 1);
	map_set(&g_env, key, value);
	replace_word(key);
	replace_word(value);
	free(key);
	free(value);
}

void	check_export_arguments(char **command)
{
	char	*end;
	char	*equal;
	size_t	count;

	count = 1;
	while (command[count] != NULL)
	{
		if (!is_valid_export_arguments(command[count]))
			puts_errorstring_export(command[count]);
		else
		{
			equal = command[count];
			end = command[count] + ft_strlen(command[count]);
			while (*equal != '=' && *equal != '\0')
				equal++;
			if (equal == end)
			{
				if (map_get(g_env, command[count]) == NULL)
					map_set(&g_env, command[count], NULL);
			}
			else
				insert_env_variable(command[count], equal, end);
		}
		(count)++;
	}
}

static bool	export_nullcheck(char **commands)
{
	size_t	position;

	position = 1;
	while (commands[position] != NULL)
	{
		if (ft_strcmp(commands[position], "") != 0)
			return (false);
		position++;
	}
	return (true);
}

void	ms_export(char *line, t_command *command)
{
	char	**commands;

	(void)line;
	commands = command_to_array(command);
	if (!commands)
		fatal_error("malloc");
	if (commands[0] != NULL)
	{
		if (export_nullcheck(commands) == true)
		{
			free_commands(commands);
			g_env->err_status = 0;
			return (show_sortedmap());
		}
		check_export_arguments(commands);
	}
	free_commands(commands);
}
