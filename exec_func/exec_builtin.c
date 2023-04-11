/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:46:37 by user              #+#    #+#             */
/*   Updated: 2023/04/04 22:12:22 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	do_builtin(char *line, t_command *command)
{
	if (ft_strcmp(command->args->word, "env") == 0)
		ms_env(command);
	else if (ft_strncmp(command->args->word, "export", 6) == 0)
		ms_export(line, command);
	else if (ft_strncmp(command->args->word, "pwd", 3) == 0)
		ms_pwd(command);
	else if (ft_strncmp(command->args->word, "cd", 2) == 0)
		ms_cd(command);
	else if (ft_strncmp(command->args->word, "exit", 4) == 0)
		ms_exit(line, command);
	else if (ft_strncmp(command->args->word, "unset", 5) == 0)
		ms_unset(line, command);
	else if (ft_strncmp(command->args->word, "echo", 4) == 0)
		ms_echo(line, command);
	return (g_env->err_status);
}
