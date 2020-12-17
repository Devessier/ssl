/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 13:05:46 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/17 16:31:42 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIGEST_H
# define DIGEST_H
# include "ssl.h"

typedef enum	e_digest_exec_origin
{
	DIGEST_EXEC_ORIGIN_STDIN = 1,
	DIGEST_EXEC_ORIGIN_STRING,
	DIGEST_EXEC_ORIGIN_FILE
}				t_digest_exec_origin;

extern t_arg	g_digest_arguments[];

#endif
