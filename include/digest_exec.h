/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest_exec.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 12:52:19 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/24 12:52:59 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIGEST_EXEC_H
# define DIGEST_EXEC_H
# include "ssl.h"
# include "reader.h"
# include "digest.h"

void			digest_algo_exec(t_context *ctx
	, t_reader *reader, t_digest_exec_origin origin);

#endif
