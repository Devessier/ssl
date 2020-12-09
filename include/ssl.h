/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 11:20:21 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/09 01:08:57 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_H
# define SSL_H

enum			e_arg_type
{
	ARG_END = 1,
	ARG_BOOLEAN,
	ARG_STRING
};

typedef struct	s_arg
{
	enum e_arg_type		type;
	char				name;
	void				*value;
	char				*description;
}				t_arg;


typedef enum	e_algo
{
	ALGO_MD5,
	ALGO_SHA256
}				t_algo;

typedef struct	s_algo_desc
{
	t_algo		algo;
	char		*name;
}				t_algo_desc;

char			*get_algo_name(t_algo algo);

typedef struct	s_context
{
	t_algo		algo;

	t_arg		*args;
}				t_context;

typedef enum	e_error
{
	E_SUCCESS					= 0,

	E_INVALID_ARG_STRING_VALUE	= 1,
	E_INVALID_ARG_TYPE			= 2,
	E_INVALID_ARG				= 3
}				t_error;

#endif
