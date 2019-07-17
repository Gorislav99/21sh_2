/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 15:53:13 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/09 15:53:14 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	key_shift_up(t_history_session *h_session)
{
	int i;

	i = h_session->left;
	while (h_session->left > 0 && h_session->line[h_session->left - 1] != '\n')
	{
		tputs(term->le, 1, putchar_);
		--h_session->left;
	}
	h_session->victor->curr_arr--;
	tputs(term->up, 1, putchar_);
	i = i - h_session->left;
	if (i > (h_session->victor->array[h_session->victor->curr_arr] - 1))
		i = h_session->victor->array[h_session->victor->curr_arr] - 1;
	h_session->left = h_session->left -
	(h_session->victor->array[h_session->victor->curr_arr] - i);
	if (!h_session->victor->curr_arr)
		h_session->left--;
	if (!h_session->victor->curr_arr)
		i += h_session->lenght_hello;
	else
		++i;
	while (--i > 0)
		tputs(term->nd, 1, putchar_);
}

void	key_shift_down(t_history_session *h_session)
{
	int i;
	int j;

	i = h_session->left;
	j = 0;
	while (h_session->left > 0 && h_session->line[h_session->left - 1] != '\n')
	{
		tputs(term->le, 1, putchar_);
		--h_session->left;
	}
	if (!h_session->victor->curr_arr)
	{
		h_session->left++;
		while (++j < h_session->lenght_hello)
			tputs(term->le, 1, putchar_);
		++i;
	}
	tputs(term->do_, 1, putchar_);
	i = i - h_session->left;
	h_session->left += h_session->victor->array[h_session->victor->curr_arr];
	h_session->victor->curr_arr++;
	if (i > (h_session->victor->array[h_session->victor->curr_arr] - 1))
		i = h_session->victor->array[h_session->victor->curr_arr];
	else
		++i;
	while (--i > 0)
	{
		h_session->left++;
		tputs(term->nd, 1, putchar_);
	}
}

void	key_hom(t_history_session *h_session)
{
	int i;

	i = 0;
	while (h_session->left > 0 && h_session->line[h_session->left - 1] != '\n')
	{
		h_session->left--;
		tputs(term->le, 1, putchar_);
	}
	if (h_session->fl || h_session->left == 0)
		return ;
	while (h_session->victor->curr_arr > 0)
	{
		h_session->victor->curr_arr--;
		tputs(term->up, 1, putchar_);
	}
	while (++i < h_session->lenght_hello)
		tputs(term->nd, 1, putchar_);
	h_session->left = 0;
}

void	key_en(t_history_session *h_session)
{
	int i;

	i = 0;
	while (h_session->left > 0 && h_session->line[h_session->left - 1] != '\n')
	{
		h_session->left--;
		tputs(term->le, 1, putchar_);
	}
	if (h_session->fl)
	{
		while (h_session->left < h_session->lenght)
		{
			h_session->left++;
			tputs(term->nd, 1, putchar_);
		}
		return ;
	}
	if (h_session->left == 0 && h_session->victor->lenght > 1)
		while (++i < h_session->lenght_hello)
			tputs(term->le, 1, putchar_);
	else if (h_session->victor->lenght == 1)
		tputs(term->nd, 1, putchar_);
	while (h_session->victor->curr_arr < (h_session->victor->lenght - 1))
	{
		h_session->victor->curr_arr++;
		tputs(term->do_, 1, putchar_);
	}
	i = 0;
	while (++i < h_session->victor->array[h_session->victor->curr_arr])
		tputs(term->nd, 1, putchar_);
	h_session->left = h_session->lenght;
}

void	navigation(t_history_session *h_session, int key)
{
	if (key == KEY_SHIFT_UP || key == KEY_SHIFT_DOWN)
	{
		if (h_session->victor->lenght == 1 || h_session->fl)
			return ;
		if (key == KEY_SHIFT_UP && h_session->victor->curr_arr > 0)
			key_shift_up(h_session);
		else if (key == KEY_SHIFT_DOWN &&
		h_session->victor->curr_arr < (h_session->victor->lenght - 1))
			key_shift_down(h_session);
	}
	else if (key == KEY_HOME || key == KEY_END)
	{
		if (key == KEY_HOME && h_session->left > 0)
			key_hom(h_session);
		else if (key == KEY_END && h_session->left < h_session->lenght)
			key_en(h_session);
	}
}
