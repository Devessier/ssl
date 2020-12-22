/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 11:20:21 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/22 15:28:44 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_H
# define SSL_H
# include <stdbool.h>

struct s_context;

typedef struct		s_digest_context
{
	bool		print;
	bool		quiet;
	bool		reverse;
	char		*string;
}					t_digest_context;

typedef union		u_algo_context
{
	t_digest_context	digest;
}					t_algo_context;

enum				e_arg_type
{
	ARG_END = 1,

	ARG_BOOLEAN,
	ARG_STRING
};

typedef struct		s_arg
{
	enum e_arg_type		type;
	char				*name;
	void				*value;
	char				*description;

	void				(*exec_after)(struct s_context* ctx);
}					t_arg;

typedef enum		e_algo
{
	ALGO_INVALID = 0,

	ALGO_MD5,
	ALGO_SHA256
}					t_algo;

t_algo				algo_name_to_algo(const char *algo_name);

typedef struct		s_context
{
	t_algo			algo;
	char			*algo_name;
	void			(*cmd)(struct s_context *ctx);
	void			(*usage)(struct s_context *ctx);

	t_arg			*args;
	char			**remaining_args;
	t_algo_context	algo_ctx;
}					t_context;

void				init_cmd(t_context *ctx, t_algo algo);

typedef void		(*t_algo_cmd)(t_context *ctx);

typedef enum		e_algo_type
{
	ALGO_TYPE_NONE = 1,

	ALGO_STANDARD,
	ALGO_DIGEST,
	ALGO_CIPHER
}					t_algo_type;

typedef struct		s_algo_desc
{
	t_algo			algorithm;
	char			*name;
	t_algo_type		type;
	t_arg			*arguments;
}					t_algo_desc;

typedef enum		e_error
{
	E_SUCCESS = 0,

	E_INVALID_ARG_STRING_VALUE,
	E_INVALID_ARG_TYPE,
	E_INVALID_ARG
}					t_error;

extern t_algo_desc	g_algorithms[];

#endif
