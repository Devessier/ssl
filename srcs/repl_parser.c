/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:44:11 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/12 20:27:41 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "repl_parser.h"
#include "repl_parser_states.h"
#include "repl_parser_context.h"

void			repl_parser_init(t_repl_parser *parser)
{
	*parser = (t_repl_parser){
		.input_length = 0,
	};
	ft_bzero(parser->input, sizeof(parser->input));
	ft_bzero(parser->temporary, sizeof(parser->temporary));
	ft_bzero(parser->ouput, sizeof(parser->ouput));
}

static t_error	repl_parser_parse_new_state(t_repl_parser *parser
	, t_repl_parser_context *ctx)
{
	const char	c = parser->input[ctx->input_index];

	ctx->character = c;
	if (c == '"')
		ctx->state = repl_parser_parse_double_quote(ctx->state);
	else if (c == '\'')
		ctx->state = repl_parser_parse_single_quote(ctx->state);
	else if (ft_isspace(c))
		ctx->state = repl_parser_parse_whitespace(ctx->state);
	else if (c == '\0')
		ctx->state = repl_parser_parse_null(ctx->state);
	else if (ft_isprint(c))
		ctx->state = repl_parser_parse_printable(ctx->state);
	if (ctx->state == RP_IN_WORD_DOUBLE_QUOTED_NEW
		|| ctx->state == RP_IN_WORD_SINGLE_QUOTED_NEW)
	{
		ctx->state = ctx->state == RP_IN_WORD_DOUBLE_QUOTED_NEW
			? RP_IN_WORD_DOUBLE_QUOTED
			: RP_IN_WORD_SINGLE_QUOTED;
		ctx->input_index++;
		return (E_NEXT);
	}
	if (ctx->state == RP_ERROR)
		return (E_FAILURE);
	return (E_SUCCESS);
}

static void		repl_parser_parse_handle_new_state(t_repl_parser *parser
	, t_repl_parser_context *ctx)
{
	if (ctx->state == RP_IN_WORD
		|| ctx->state == RP_IN_WORD_DOUBLE_QUOTED
		|| ctx->state == RP_IN_WORD_SINGLE_QUOTED)
	{
		if (ctx->word_beginning == -1
			&& (ctx->state == RP_IN_WORD
				|| ctx->state == RP_IN_WORD_DOUBLE_QUOTED
				|| ctx->state == RP_IN_WORD_SINGLE_QUOTED))
			ctx->word_beginning = ctx->temporary_index;
		parser->temporary[ctx->temporary_index++] = ctx->character;
	}
	else if (ctx->state == RP_END_WORD)
	{
		parser->temporary[ctx->temporary_index++] = '\0';
		parser->ouput[ctx->words_count++] = parser->temporary
			+ ctx->word_beginning;
		ctx->word_beginning = -1;
	}
}

/*
** Split on whitespaces and handle quoting.
*/

ssize_t			repl_parser_parse(t_repl_parser *parser)
{
	t_repl_parser_context	ctx;
	t_error					status;

	repl_parser_context_init(&ctx);
	while (ctx.input_index < parser->input_length + 1)
	{
		if ((status = repl_parser_parse_new_state(
				parser, &ctx)) == E_NEXT)
			continue ;
		else if (status == E_FAILURE)
			return (-1);
		repl_parser_parse_handle_new_state(parser, &ctx);
		ctx.input_index++;
	}
	return (ctx.words_count);
}
