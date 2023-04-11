/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:18:23 by user              #+#    #+#             */
/*   Updated: 2023/04/03 01:44:22 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_environment_variables(char *path);
static void	change_directory(char *path);

static void	show_manual(char **commands)
{
	free_commands(commands);
	ft_putendl_fd("cd with only a relative or absolute path", 2);
	g_env->err_status = 1;
	return ;
}

void	ms_cd(t_command *command)
{
	char	**commands;

	commands = command_to_array(command);
	if (!commands)
		fatal_error("malloc");
	if (commands[1] == NULL || commands[2] != NULL || ft_strchr(commands[1],
			'~'))
		return (show_manual(commands));
	change_directory(commands[1]);
	free_commands(commands);
}

static void	change_directory(char *path)
{
	char	buf[PATH_MAX];

	if (chdir(path) < 0)
	{
		perror("chdir");
		return ;
	}
	else
	{
		if (getcwd(buf, sizeof(buf)) == NULL)
			ft_putendl_fd("cd: error retrieving current directory: \
		getcwd: cannot access parent directories: No such file or directory\n", \
							2);
		else
		{
			update_environment_variables(buf);
		}
		g_env->err_status = 0;
	}
}

static void	update_environment_variables(char *path)
{
	map_set(&g_env, "OLDPWD", g_env->ms_pwd);
	free(g_env->ms_pwd);
	g_env->ms_pwd = ft_strdup(path);
	map_set(&g_env, "PWD", g_env->ms_pwd);
}
