/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplecommand_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 20:32:36 by marvin            #+#    #+#             */
/*   Updated: 2023/02/26 20:32:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	re_token_in_null(t_token **token, t_token **re_token)
{
	(*re_token)->word = NULL;
	(*re_token)->kind = TK_WORD;
	if ((*token)->next != NULL)
	{
		(*re_token)->next = (t_token *)malloc(sizeof(t_token) * 1);
		(*re_token) = (*re_token)->next;
	}
	(*token) = (*token)->next;
}

static void	split_tokenword(t_token **token, t_token **re_token)
{
	char	*token_wd;
	char	*new_wd;

	token_wd = (*token)->word;
	new_wd = NULL;
	while (*token_wd == ' ' || *token_wd == '\t')
		token_wd++;
	while (*token_wd != '\0')
	{
		if (*token_wd == '\"' || *token_wd == '\'')
			remake_token_insplit(&token_wd, &new_wd);
		else if (*token_wd == '\\')
		{
			append_char(&new_wd, *token_wd++);
			append_char(&new_wd, *token_wd++);
		}
		else
			append_char(&new_wd, *token_wd++);
		if (*token_wd == ' ' || *token_wd == '\t' || *token_wd == '\0')
			remaking_blank(&new_wd, &token_wd, re_token);
	}
	(*token) = (*token)->next;
}

static void	re_token_make(t_token **retoken, t_token *token)
{
	(*retoken)->word = ft_strdup(token->word);
	(*retoken)->kind = token->kind;
	if (token->next != NULL)
	{
		(*retoken)->next = (t_token *)malloc(sizeof(t_token) * 1);
		(*retoken) = (*retoken)->next;
	}
}

static	bool	check_tokenwdblank(char *string)
{
	while (is_blank(*string))
		string++;
	while (*string != '\0')
	{
		if (is_blank(*string))
			return (true);
		if (*string == '\\')
			string = string + 2;
		else if ((*string == '\'' || *string == '\"') && *(string + 1) != '\0')
			check_inquote(*string, &string);
		else
			string++;
	}
	return (false);
}

void	remake_token(t_token *token, t_token *re_token)
{
	t_token	*head;

	head = token;
	while (token != NULL)
	{
		if (token->word == NULL && (token->next == NULL \
		|| token->next->kind == TK_OP))
			re_token_in_null(&token, &re_token);
		else if (token->word == NULL)
			token = token->next;
		else if (check_tokenwdblank(token->word))
			split_tokenword(&token, &re_token);
		else
		{
			re_token_make(&re_token, token);
			token = token->next;
		}
	}
	free_token(head);
	re_token->next = NULL;
}
