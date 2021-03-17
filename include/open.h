/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 12:49:31 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/17 01:45:52 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPEN_H
# define OPEN_H
# include "ssl.h"

int		open_read_file(t_context *ctx, char *file);
int		open_write_file(t_context *ctx, char *file);

#endif
