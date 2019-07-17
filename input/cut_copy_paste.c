/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_copy_paste.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 18:43:40 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/12 18:43:41 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	key_copy_left(t_history_session *h_session)
{
	int i;

	i = 0;
	if (h_session->line[h_session->left - 1] == '\n' && !h_session->fl)
	{
		tputs(term->up, 1, putchar_);
		if (!(h_session->victor->curr_arr - 1))
		{
			i += h_session->victor->array[h_session->victor->curr_arr - 1] ? 0 : 1;
			while (i++ < h_session->lenght_hello)
				tputs(term->nd, 1, putchar_);
		}
		h_session->victor->curr_arr--;
		h_session->left--;
		g_dispersion--;
		i = 0;
		while (++i < h_session->victor->array[h_session->victor->curr_arr])
			tputs(term->nd, 1, putchar_);
	}
	if (!(h_session->left) || h_session->line[h_session->left - 1] == '\n')
		return ;
	tputs(term->im, 1, putchar_);
	tputs(term->le, 1, putchar_);
	tputs(term->dc, 1, putchar_);
	if (g_dispersion <= 0)
		write(1, "\e[45m", ft_strlen("\e[45m"));
	write(1, &(h_session->line[h_session->left - 1]), 1);
	if (g_dispersion <= 0)
		write(1, "\e[0m", ft_strlen("\e[0m"));
	tputs(term->le, 1, putchar_);
	h_session->left--;
	g_dispersion--;
	tputs(term->ei, 1, putchar_);
}

static void	key_copy_right(t_history_session *h_session)
{
	int i;

	i = 0;
	if (h_session->line[h_session->left] == '\n' && !h_session->fl)
	{
		tputs(term->do_, 1, putchar_);
		h_session->victor->curr_arr++;
		h_session->left++;
		g_dispersion++;
	}
	if (h_session->left == h_session->lenght || h_session->line[h_session->left] == '\n')
		return ;
	tputs(term->dc, 1, putchar_);
	tputs(term->im, 1, putchar_);
	if (g_dispersion >= 0)
		write(1, "\e[45m", ft_strlen("\e[45m"));
	write(1, &(h_session->line[h_session->left]), 1);
	if (g_dispersion >= 0)
		write(1, "\e[0m", ft_strlen("\e[0m"));
	h_session->left++;
	g_dispersion++;
	tputs(term->ei, 1, putchar_);
}

void		cut_copy_paste(t_history_session *h_session, int key)
{
	if (key == KEY_COPY_LEFT && h_session->lenght && h_session->left)
		key_copy_left(h_session);
	else if (key == KEY_COPY_RIGHT &&
	h_session->lenght && h_session->left < h_session->lenght)
		key_copy_right(h_session);
	else if (key == KEY_PASTE && g_buffer)
		key_paste(h_session);
}
