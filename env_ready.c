/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ready.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:39:39 by user              #+#    #+#             */
/*   Updated: 2023/04/20 01:09:06 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*conbinate_keyvalue(t_item *head)
{
	char	*env_remake;
	char	*name;
	char	*value;

	env_remake = NULL;
	name = head->name;
	value = head->value;
	while (*name != '\0')
		append_char(&env_remake, *name++);
	append_char(&env_remake, '=');
	if (value != NULL)
		while (*value != '\0')
			append_char(&env_remake, *value++);
	return (env_remake);
}

char	**ready_nextenviron(void)
{
	t_item	*head;
	char	**n_env;
	size_t	position;

	head = g_env->item_head;
	position = 0;
	while (head != NULL)
	{
		position++;
		head = head->next;
	}
	n_env = (char **)malloc(sizeof(char *) * (position + 1));
	head = g_env->item_head;
	position = 0;
	while (head != NULL)
	{
		if (head->value != NULL)
		{
			n_env[position] = conbinate_keyvalue(head);
			position++;
		}
		head = head->next;
	}
	n_env[position] = NULL;
	return (n_env);
}

char	*get_name(char *name_and_value)
{
	size_t	len;
	size_t	j;
	char	*name;

	len = 0;
	while (name_and_value[len] != '\0')
	{
		if (name_and_value[len] == '=')
			break ;
		len++;
	}
	name = malloc(sizeof(char) * (len + 1));
	if (!name)
		fatal_error("malloc");
	j = 0;
	while (len)
	{
		name[j] = name_and_value[j];
		j++;
		len--;
	}
	name[j] = '\0';
	return (name);
}

void	env_init(void)
{
	size_t		i;
	char		*name;
	char		*value;
	char		cwd[256];
	extern char	**environ;

	i = 0;
	g_env = malloc(sizeof(t_map));
	g_env->err_status = 0;
	g_env->item_head = NULL;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		fatal_error("getcwd");
	g_env->ms_pwd = ft_strdup(cwd);
	while (environ[i] != NULL)
	{
		name = get_name(environ[i]);
		value = getenv(name);
		map_set(&g_env, name, value);
		free(name);
		i++;
	}
	map_set(&g_env, "PWD", getcwd(cwd, sizeof(cwd)));
	map_set(&g_env, "OLDPWD", NULL);
}
