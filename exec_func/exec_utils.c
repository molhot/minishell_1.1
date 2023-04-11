/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:59:30 by satushi           #+#    #+#             */
/*   Updated: 2023/04/07 17:51:36 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	count_tokens(t_token *args)
{
	size_t	count;
	t_token	*itr;

	count = 0;
	itr = args;
	while (itr != NULL)
	{
		count++;
		itr = itr->next;
	}
	return (count);
}

static char	*token_to_str(t_token *token)
{
	if (token->word == NULL)
		return (NULL);
	else
		return (ft_strdup(token->word));
}

char	**args_to_argv(t_token *args)
{
	size_t	len;
	char	**argv;
	size_t	i;

	len = count_tokens(args);
	i = 0;
	argv = malloc(sizeof(char *) * (len + 1));
	if (argv == NULL)
		fatal_error("malloc");
	while (i != len)
	{
		argv[i] = token_to_str(args);
		args = args->next;
		i++;
	}
	argv[len] = NULL;
	return (argv);
}

void	aray_free(char **argv)
{
	size_t	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
