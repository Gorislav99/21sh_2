/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assist_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 17:14:11 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/13 17:14:12 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void _commas(t_history_session *h_session, int key)
{

	if ((key == '\"' || key == '\'') && (h_session->comm.fd % 2 == 0))
	{
		++(h_session->comm.fd);
		h_session->comm.ch = key;
	}
	else if (key == h_session->comm.ch  && h_session->comm.fd % 2 != 0)
		++(h_session->comm.fd);
}

int	putchar_(int c)
{
	write(1, &c, 1);
	return (0);
}