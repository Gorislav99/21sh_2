/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:11:01 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/02 16:11:11 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		print_ch(t_history_session *h_session, char key, int fl)
{
	char *temp;
	char *temp2;
	char buff[2];

	if (fl)
	{
		tputs(term->im, 1, putchar_);
		write(1, &key, 1);
		tputs(term->ei, 1, putchar_);
	}
	else
		write(1, "\n", 1);
	buff[0] = key;
	buff[1] = '\0';
	if (h_session->line)
	{
		temp = ft_strsub(h_session->line, 0, h_session->left);
		temp2 = ft_strjoin(temp, buff);
		free(temp);
		temp = ft_strjoin(temp2, (h_session->line) + (h_session->left));
		free(h_session->line);
		free(temp2);
		h_session->line = temp;
	}
	else
		h_session->line = ft_strdup(buff);
	(h_session->lenght)++;
	(h_session->left)++;
	h_session->victor->array[h_session->victor->curr_arr]++;
}

static void	cut_line(t_history_session *h_session)
{
	int temp;
	int	temp2;
	int	i;

	i = 0;
	temp = h_session->victor->curr_arr;
	temp2 = h_session->victor->curr_arr;
	while (++temp < h_session->victor->lenght)
	{
		tputs(term->do_, 1, putchar_);
		tputs(term->cd, 1, putchar_);
	}
	(h_session->victor->lenght - 1) == h_session->victor->curr_arr ? temp-- : 0;
	while (temp-- > temp2)
		tputs(term->up, 1, putchar_);
	ft_printf("%s", &h_session->line[h_session->left]);
	temp = h_session->victor->array[h_session->victor->lenght - 1];
	while (temp--)
		tputs(term->le, 1, putchar_);
	while (++temp2 < (h_session->victor->lenght - 1))
		tputs(term->up, 1, putchar_);
}

static void	add_line(t_history_session *h_session)
{
	int i;
	int temp;
	int	temp2;

	i = 0;
	temp = h_session->victor->curr_arr;
	temp2 = h_session->victor->curr_arr;
	while (temp++ < h_session->victor->lenght)
	{
		tputs(term->cd, 1, putchar_);
		tputs(term->do_, 1, putchar_);
	}
	while (--temp > temp2)
		tputs(term->up, 1, putchar_);
	i = 0;
	tputs(term->up, 1, putchar_);
	if (!(h_session->victor->curr_arr - 1))
		i -= h_session->lenght_hello;
	while (++i < h_session->victor->array[h_session->victor->curr_arr - 1])
		tputs(term->nd, 1, putchar_);
	ft_printf("%s", &h_session->line[h_session->left]);
	i = h_session->victor->array[h_session->victor->lenght - 1];
	if ((h_session->victor->lenght - 1) == h_session->victor->curr_arr)
		i += h_session->victor->array[h_session->victor->curr_arr - 1];
	while (i-- > 0)
		tputs(term->le, 1, putchar_);
	i = h_session->victor->lenght - h_session->victor->curr_arr;
	while (--i > 0)
		tputs(term->up, 1, putchar_);
	i = h_session->victor->array[h_session->victor->curr_arr - 1];
	if (!(h_session->victor->curr_arr - 1))
		i += h_session->lenght;
	while (--i > 0)
		tputs(term->nd, 1, putchar_);
	h_session->victor->array[h_session->victor->curr_arr - 1] +=
	h_session->victor->array[h_session->victor->curr_arr];
	h_session->victor->pop(&h_session->victor, h_session->victor->curr_arr);
}

void		backspace_ch(t_history_session *h_session)
{
	int		pos;
	char	*temp;
	char	*temp2;
	int		i;

	i = 0;
	if (h_session->lenght > 0 && h_session->left > 0)
	{
		if (h_session->line[h_session->left - 1] == '\n'
		&& (!h_session->victor->curr_arr || h_session->fl))
			return ;
		else if (h_session->line[h_session->left - 1] == '\n')
		{
			h_session->victor->array[h_session->victor->curr_arr]--;
			if (!h_session->victor->array[h_session->victor->curr_arr])
			{
				cut_line(h_session);
				h_session->victor->pop(&h_session->victor, h_session->victor->curr_arr);
				tputs(term->up, 1, putchar_);
				if (!h_session->victor->curr_arr)
					i -= h_session->lenght_hello;
				while (++i < h_session->victor->array[h_session->victor->curr_arr])
					tputs(term->nd, 1, putchar_);
			}
			else
				add_line(h_session);
		}
		else
		{
			if (h_session->line[h_session->left - 1] == h_session->comm.ch)
				--(h_session->comm.fd);
			tputs(term->le, 1, putchar_);
			tputs(term->dc, 1, putchar_);
			h_session->victor->array[h_session->victor->curr_arr]--;
		}
		temp = ft_strsub(h_session->line, 0, h_session->left - 1);
		temp2 = ft_strjoin(temp, (h_session->line) + (h_session->left));
		free(temp);
		free(h_session->line);
		h_session->line = temp2;
		--(h_session->lenght);
		--(h_session->left);
	}
}

void		left_ch(t_history_session *h_session)
{
	int i;

	i = 0;
	if (h_session->left > 0 && h_session->line[h_session->left - 1] != '\n')
	{
		tputs(term->le, 1, putchar_);
		(h_session->left)--;
	}
	else if (h_session->left > 0 &&
	h_session->line[h_session->left - 1] == '\n' && !h_session->fl)
	{
		tputs(term->up, 1, putchar_);
		h_session->victor->curr_arr--;
		if (!h_session->victor->curr_arr)
			i -= h_session->lenght_hello;
		while (++i < h_session->victor->array[h_session->victor->curr_arr])
			tputs(term->nd, 1, putchar_);
		(h_session->left)--;
	}
}

void		right_ch(t_history_session *h_session)
{
	int i;

	i = 0;
	if (h_session->left < h_session->lenght && h_session->line[h_session->left] != '\n')
	{
		tputs(term->nd, 1, putchar_);
		(h_session->left)++;
	}
	else if (h_session->left < h_session->lenght && h_session->line[h_session->left] == '\n' && !h_session->fl)
	{
		tputs(term->do_, 1, putchar_);
		h_session->victor->curr_arr++;
		(h_session->left)++;
	}
}
