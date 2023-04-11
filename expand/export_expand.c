/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:43:24 by mochitteiun       #+#    #+#             */
/*   Updated: 2023/03/03 19:43:24 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	switch_doller_inexpandquote(char **new_word, char **args)
{
	if (**args == '$' && *(*args + 1) == '\0')
	{
		append_char(&(*new_word), **args);
		(*args)++;
	}
	else if (**args == '$' && (*(*args + 1) == '\'' || *(*args + 1) == '\"'))
		(*args)++;
	else if (**args == '$' && *(*args + 1) == '?')
		expand_dolleeques(&(*new_word), &(*args), *args);
	else if (**args == '$')
		expand_doller(&(*new_word), &(*args), *args);
}

static void	append_double_export(char **args, char **new)
{
	bool	fa;

	fa = true;
	while (**args != '\"')
	{
		fa = false;
		if (**args == '$' && *(*args + 1) != '\"')
			expand_doller_dq(&(*new), &(*args), *args);
		else
		{
			if (**args == '\\')
			{
				append_char(&(*new), **args);
				(*args)++;
			}
			append_char(&(*new), **args);
			(*args)++;
		}
	}
	if (fa == true)
		append_char(&(*new), '\0');
	(*args)++;
}

static char	*expand_args_expote(char *args, char *args_free)
{
	char	*new_word;

	new_word = NULL;
	while (*args != '\0')
	{
		if (*args == '\\')
		{
			args++;
			append_char(&new_word, *args++);
		}
		else if ((*args == '\'' || *args == '\"') && *(args + 1) != '\0')
		{
			args++;
			if (*(args - 1) == '\'')
				append_single(&args, &new_word);
			else if (*(args - 1) == '\"')
				append_double_export(&args, &new_word);
		}
		else if (*args == '$')
			switch_doller_inexpandquote(&new_word, &args);
		else
			append_char(&new_word, *args++);
	}
	free(args_free);
	return (new_word);
}

void	expand_export(t_token *token)
{
	while (token != NULL)
	{
		if (token->word != NULL)
			token->word = expand_args_expote(token->word, token->word);
		token = token->next;
	}
}
