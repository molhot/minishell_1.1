/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 23:22:25 by user              #+#    #+#             */
/*   Updated: 2023/04/03 10:50:14 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_expand_ok(t_redirect *redirect)
{
	const char	*file_path;

	file_path = redirect->file_path;
	if (ft_strchr(file_path, '\'') || ft_strchr(file_path, '\"'))
	{
		if (redirect->type == HEREDOC)
			redirect->expand_ok = false;
	}
	else
		redirect->expand_ok = true;
}

bool	parse_redirect(t_redirect **redirect, t_token **tok)
{
	const char	*tok_word;
	const char	*tok_next_word;

	*redirect = malloc(sizeof(t_redirect));
	tok_word = (*tok)->word;
	tok_next_word = (*tok)->next->word;
	if (ft_strcmp(tok_word, ">") == 0 && ft_strcmp(tok_next_word, ">") == 0)
	{
		(*redirect)->type = APPEND;
		*tok = (*tok)->next;
	}
	else if (ft_strcmp(tok_word, "<") == 0 && ft_strcmp(tok_next_word, \
				"<") == 0)
	{
		(*redirect)->type = HEREDOC;
		*tok = (*tok)->next;
	}
	else if (ft_strcmp(tok_word, "<") == 0)
		(*redirect)->type = IN;
	else
		(*redirect)->type = OUT;
	if ((*tok)->next->kind == TK_WORD)
		(*redirect)->file_path = ft_strdup((*tok)->next->word);
	check_expand_ok(*redirect);
	return (true);
}

void	free_redirect(t_redirect *redirect)
{
	t_redirect	*next;

	if (redirect == NULL)
		return ;
	next = redirect->next;
	if (redirect->file_path != NULL)
		free(redirect->file_path);
	free(redirect);
	free_redirect(next);
}

void	ready_redirect_in_out(t_node *node, bool *flag, bool f_content)
{
	if (f_content == true)
		node->command->redirect = \
			(t_redirect **)malloc(sizeof(t_redirect *) * 1);
	node->command->in_fd[0] = STDIN_FILENO;
	node->command->in_fd[1] = -1;
	node->command->out_fd[0] = -1;
	node->command->out_fd[1] = STDOUT_FILENO;
	*flag = true;
}
