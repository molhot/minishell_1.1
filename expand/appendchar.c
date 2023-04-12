/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   appendchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 01:03:13 by satushi           #+#    #+#             */
/*   Updated: 2023/04/12 13:54:39 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_char(char **s, char c)
{
	size_t	size;
	char	*new;

	size = 2;
	if (*s)
		size += ft_strlen(*s);
	new = malloc(size);
	if (new == NULL)
		fatal_error("malloc");
	if (*s)
		ft_strlcpy(new, *s, size);
	new[size - 2] = c;
	new[size - 1] = '\0';
	if (*s)
		free(*s);
	*s = new;
}

void	append_single(char **args, char **new)
{
	bool	no_insert;

	no_insert = true;
	while (**args != '\'')
	{
		no_insert = false;
		append_char(&(*new), **args);
		(*args)++;
	}
	(*args)++;
	if (no_insert == true)
		append_char(&(*new), '\0');
}

static bool	slush_char_ch(char c)
{
	if (c == '$' || c == '"' || c == '\\')
		return (true);
	return (false);
}

void	append_double(char **args, char **new)
{
	bool	no_insert;

	no_insert = true;
	while (**args != '\"')
	{
		no_insert = false;
		if (**args == '\\' && slush_char_ch(*(*args + 1)) == true)
			b_slush_append(&(*args), &(*new));
		else if (**args == '$' && *(*args + 1) == '?')
			expand_dolleeques(&(*new), &(*args), *args);
		else if (**args == '$' && *(*args + 1) != '\"')
			expand_doller_dq(&(*new), &(*args), *args);
		else
		{
			append_char(&(*new), **args);
			(*args)++;
		}
	}
	(*args)++;
	if (no_insert == true)
		append_char(&(*new), '\0');
}

void	quote_append(char **args, char **new_word)
{
	char	*tmp;

	(*args)++;
	tmp = *args;
	if (*(tmp - 1) == '\'')
		append_single(&(*args), &(*new_word));
	else if (*(tmp - 1) == '\"')
		append_double(&(*args), &(*new_word));
}
