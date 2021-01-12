/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:44:11 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/12 20:16:58 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPL_PARSER_H
# define REPL_PARSER_H
# include <stdint.h>
# include "repl.h"

typedef	enum	e_repl_parser_state
{
	RP_EOL,
	RP_NEXT,
	RP_ERROR,

	RP_WHITESPACE,
	RP_END_WORD,

	RP_IN_WORD,
	RP_IN_WORD_DOUBLE_QUOTED,
	RP_IN_WORD_SINGLE_QUOTED,
	RP_IN_WORD_DOUBLE_QUOTED_NEW,
	RP_IN_WORD_SINGLE_QUOTED_NEW,
}				t_repl_parser_state;

typedef struct	s_repl_parser
{
	char				input[REPL_BUFFER_SIZE + 1];
	size_t				input_length;
	char				temporary[REPL_BUFFER_SIZE];
	char				*ouput[REPL_BUFFER_SIZE / sizeof(char **)];
}				t_repl_parser;

typedef struct	s_repl_parser_context
{
	t_repl_parser_state	state;
	size_t				input_index;
	size_t				temporary_index;
	ssize_t				word_beginning;
	size_t				words_count;
	char				character;
}				t_repl_parser_context;

void			repl_parser_init(t_repl_parser *parser);
ssize_t			repl_parser_parse(t_repl_parser *parser);

#endif
