/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 16:20:11 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/08 18:00:18 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGS_H
# define ARGS_H

enum			e_arg_type
{
	ARG_END = 1,
	ARG_BOOLEAN,
	ARG_STRING
};

typedef enum	e_get_arg_value_r
{
	E_INVALID_STRING_VALUE = 1,
	E_INVALID_ARG_TYPE,
	OK
}				t_get_arg_value_r;

typedef struct	s_arg
{
	enum e_arg_type		type;
	char				name;
	void				*value;
	char				*description;
}				t_arg;

size_t			parse_args(const t_arg args[], int argc, const char **argv);

#endif
