/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:07:04 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/13 00:12:47 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include "libft.h"
#include "ssl.h"
#include "repl.h"
#include "repl_parser.h"
#include "reader.h"

static void		repl_prompt(void)
{
	const char	prompt[] = "ft_ssl > ";

	write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);
}

static t_error	repl_fill_buffer(t_reader *rd
	, t_repl_parser *parser)
{
	ssize_t	ret;
	char	c;

	ret = reader_read(rd, &c, 1);
	if (ret < 0)
	{
		ft_putf_fd(STDERR_FILENO, "ft_ssl: repl: %s\n", strerror(errno));
		return (E_FAILURE);
	}
	if (ret == 0)
		return (E_EXIT);
	if (c == '\n')
		return (E_EXECUTE);
	parser->input[parser->input_length++] = c;
	return (E_SUCCESS);
}

static t_error	repl_exec(t_repl_parser *parser, ssize_t argc)
{
	if (parser->ouput[0] == NULL)
		return (E_SUCCESS);
	if (ft_strcmp(parser->ouput[0], "quit") == 0
		|| ft_strcmp(parser->ouput[0], "exit") == 0)
		return (E_NEXT);
	if (argc > 0)
		ssl_exec(argc, parser->ouput);
	return (E_SUCCESS);
}

static t_error	repl_loop_fill_buffer(t_reader *rd
	, t_repl_parser *parser)
{
	t_error			status;

	while (parser->input_length < REPL_BUFFER_SIZE)
		if ((status = repl_fill_buffer(rd, parser)) == E_EXECUTE)
			break ;
		else if (status == E_FAILURE)
			return (E_FAILURE);
		else if (status == E_EXIT)
			return (E_SUCCESS);
	return (E_EXECUTE);
}

t_error			repl(void)
{
	const t_reader	rd = create_reader_fd(STDIN_FILENO, "stdin", false);
	t_repl_parser	parser;
	ssize_t			argc;
	t_error			status;

	while (true)
	{
		repl_parser_init(&parser);
		repl_prompt();
		if ((status = repl_loop_fill_buffer(
				(t_reader *)&rd, &parser)) != E_EXECUTE)
			return (status);
		if ((argc = repl_parser_parse(&parser)) == -1)
		{
			ft_putf_fd(STDERR_FILENO
				, "ft_ssl: repl: syntax error: %s\n", parser.input);
			continue ;
		}
		if (repl_exec(&parser, argc) == E_NEXT)
			break ;
	}
	return (E_SUCCESS);
}
