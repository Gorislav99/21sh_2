/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_buff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 18:03:59 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/14 18:04:00 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_left_assist(t_history_session *h_session, int temp, int i)
{
	while (i != h_session->left && h_session->line[i] != '\n')
	{
		--i;
		tputs(term->le, 1, putchar_);
	}
	if (h_session->line[i] == '\n')
	{
		while (temp > h_session->victor->curr_arr)
		{
			tputs(term->up, 1, putchar_);
			i -= h_session->victor->array[--temp];
		}
		i -= !h_session->victor->curr_arr ? h_session->lenght_hello : 0;
		while (++i < h_session->left)
			tputs(term->nd, 1, putchar_);
	}
}

void	clean_left(t_history_session *h_session)
{
	int i;
	int tmp;
	int temp;

	i = h_session->left;
	temp = h_session->victor->curr_arr;
	while (g_dispersion < 0)
	{
		if (h_session->line[i] == '\n')
		{
			tmp = !temp ? -h_session->lenght_hello : 0;
			while (tmp++ < h_session->victor->array[temp])
				tputs(term->le, 1, putchar_);
			tputs(term->do_, 1, putchar_);
			temp++;
		}
		else
		{
			tputs(term->dc, 1, putchar_);
			write(1, &(h_session->line[i]), 1);
		}
		++i;
		g_dispersion++;
	}
	clean_left_assist(h_session, temp, i);
}

void	clean_right_assist(t_history_session *h_session, int temp, int i)
{
	int tmp;

	tmp = 0;
	while (i > 0 && h_session->line[i] != '\n')
	{
		--i;
		tputs(term->le, 1, putchar_);
	}
	while (!temp && tmp++ < h_session->lenght_hello)
		tputs(term->le, 1, putchar_);
	while (temp < h_session->victor->curr_arr)
	{
		tputs(term->do_, 1, putchar_);
		i += h_session->victor->array[temp++];
	}
	tmp = 0;
	while (!temp && tmp++ < h_session->lenght_hello)
		tputs(term->nd, 1, putchar_);
	while (++i < h_session->left)
		tputs(term->nd, 1, putchar_);
}

void	clean_right(t_history_session *h_session)
{
	int i;
	int tmp;
	int temp;

	i = h_session->left;
	temp = h_session->victor->curr_arr;
	while (g_dispersion > 0)
	{
		if (h_session->line[i - 1] == '\n')
		{
			tputs(term->up, 1, putchar_);
			temp--;
			tmp = !temp ? -h_session->lenght_hello : 0;
			while (++tmp < h_session->victor->array[temp])
				tputs(term->nd, 1, putchar_);
		}
		else
		{
			tputs(term->le, 1, putchar_);
			tputs(term->dc, 1, putchar_);
			write(1, &(h_session->line[i - 1]), 1);
			tputs(term->le, 1, putchar_);
		}
		i--;
		g_dispersion--;
	}
	clean_right_assist(h_session, temp, i);
}

void	save_buff(t_history_session *h_session)
{
	free(g_buffer);
	tputs(term->im, 1, putchar_);
	if (g_dispersion < 0)
	{
		g_buffer = ft_strsub(h_session->line,
		h_session->left, -1 * g_dispersion);
		clean_left(h_session);
	}
	else
	{
		g_buffer = ft_strsub(h_session->line,
		h_session->left - g_dispersion, g_dispersion);
		clean_right(h_session);
	}
	tputs(term->ei, 1, putchar_);
}
