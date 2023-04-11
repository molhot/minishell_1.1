/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 23:03:52 by kazuki            #+#    #+#             */
/*   Updated: 2023/04/02 23:13:23 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*searchpath_utils(char *path, char *value, const char *filename)
{
	char	*end;

	ft_bzero(path, PATH_MAX);
	end = ft_strchr(value, ':');
	if (end)
		ft_strlcpy(path, value, end - value + 1);
	else
		ft_strlcpy(path, value, PATH_MAX);
	ft_strlcat(path, "/", PATH_MAX);
	ft_strlcat(path, filename, PATH_MAX);
	return (end);
}

char	*searchpath(const char *cmd)
{
	char	*path;
	char	*value;
	char	*end;

	value = map_get(g_env, "PATH");
	if (!value)
		return (NULL);
	if (ft_strcmp(cmd, "") == 0)
		return (NULL);
	path = (char *)malloc(sizeof(char) * PATH_MAX);
	if (!path)
		fatal_error("malloc");
	if (ft_strlen(cmd) > PATH_MAX)
		return (NULL);
	while (value != NULL && *value != '\0')
	{
		end = searchpath_utils(path, value, cmd);
		if (access(path, X_OK) == 0)
			return (accessok_file(path));
		if (end == NULL)
			break ;
		value = end + 1;
	}
	free(path);
	return (NULL);
}

char	*accessok_file(char *path)
{
	char	*dup;

	dup = ft_strdup(path);
	free(path);
	if (dup == NULL)
	{
		free(dup);
		return (NULL);
	}
	return (dup);
}
