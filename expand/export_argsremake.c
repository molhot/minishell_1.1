/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_argsremake.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 05:12:19 by mochitteiun       #+#    #+#             */
/*   Updated: 2023/03/12 05:12:19 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	sp_wd_ch(char c)
{
	if (c == '"' || c == '$' || c == '\\')
		return (true);
	return (false);
}

static void	export_argsremake_sp(\
size_t position, char **sub, char **dup, char *free_sub)
{
	size_t	last;

	last = ft_strlen(free_sub);
	if (position != last && **sub == '\\' \
	&& sp_wd_ch(*(*sub + 1)) == true)
	{
		append_char(&(*dup), **sub);
		(*sub)++;
	}
	else if (*sub != free_sub && *(*sub - 1) != '\\' \
	&& sp_wd_ch(**sub) == true)
		append_char(&(*dup), '\\');
	append_char(&(*dup), **sub);
	(*sub)++;
}

void	export_argsremake(t_token *token)
{
	char	*sub;
	char	*free_sub;
	char	*dup;
	size_t	position;

	position = 0;
	while (token != NULL)
	{
		dup = NULL;
		sub = token->word;
		if (sub != NULL && ft_strcmp(sub, "\0") == 0)
			dup = ft_strdup("");
		free_sub = sub;
		while (sub != NULL && *sub != '\0')
		{
			export_argsremake_sp(position, &sub, &dup, free_sub);
			position++;
		}
		token->word = dup;
		free(free_sub);
		token = token->next;
	}
}
