/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_exec.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 16:42:38 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/17 16:46:04 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_EXEC_H
# define MD5_EXEC_H
# include "ssl.h"
# include "reader.h"
# include "digest.h"

void	md5_algo_exec(t_context *ctx, t_reader *reader, t_digest_exec_origin origin);

#endif
