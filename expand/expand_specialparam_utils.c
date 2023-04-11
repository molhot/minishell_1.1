/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_specialparam_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:49:24 by mochitteiun       #+#    #+#             */
/*   Updated: 2023/03/17 12:49:24 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	append_char_util(char **dst, char **rest)
{
	if (**rest == '\'')
		append_char(dst, '\\');
	append_char(dst, **rest);
	*rest = *rest + 1;
}

void	expand_doller_ten(char **dst, char **rest, char *p)
{
	char	*name;
	char	*value;

	name = ft_calloc(1, sizeof(char));
	if (name == NULL)
		fatal_error("calloc");
	p++;
	if (!ft_isalpha(*p) && *p != '_')
	{
		free(name);
		return (not_expnad(&(*dst), &(*rest), p));
	}
	append_char(&name,*p++);
	while (ft_isalpha(*p) != 0 || *p == '_' || ft_isdigit(*p) != 0)
		append_char(&name,*p++);
	value = map_get(g_env, name);
	free(name);
	if (value)
	{
		while (*value)
			append_char_util(&(*dst), &value);
	}
	*rest = p;
}
