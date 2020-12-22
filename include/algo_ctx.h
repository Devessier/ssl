/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_ctx.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 17:40:57 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/22 12:36:58 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_CTX_H
# define ALGO_CTX_H
# include "ssl.h"

t_arg		*get_algo_arguments(t_algo algo);

t_algo_cmd	get_algo_usage(t_algo algo);

#endif
