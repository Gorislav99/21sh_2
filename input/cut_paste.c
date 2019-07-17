/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_paste.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:19:31 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/16 14:19:32 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	write_vector(t_history_session *h_session)
{
	int i;
	int j;

	h_session->victor->del(&(h_session->victor));
	h_session->victor = init_vector();
	i = 0;
	j = 0;
	h_session->lenght = 0;
	while (h_session->line[i])
	{
		if (h_session->line[i] == '\n')
		{
			h_session->victor->push_back(&(h_session->victor), j);
			j = 0;
		}
		i++;
		++j;
		h_session->lenght++;
	}
	h_session->victor->push_back(&(h_session->victor), j);
}

static void	check_qoute(t_history_session *h_session, char *ln)
{
	int i;

	i = 0;
	while (ln && ln[i])
	{
		(ln[i] == '\"' || ln[i] == '\'') ? _commas(h_session, ln[i]) : 0;
		++i;
	}
}

void		key_paste(t_history_session *h_session)
{
	int		temp;
	char	*temp_str;
	char	*temp_str2;
	int		i;

	if (!h_session->line)
	{
		h_session->line = ft_strdup(g_buffer);
		h_session->lenght = ft_strlen(g_buffer);
		h_session->victor->array[0] = h_session->lenght;
	}
	else
	{
		temp_str = ft_strjoin(g_buffer, &(h_session->line[h_session->left]));
		cut_str(&(h_session->line), h_session->left, h_session->lenght);
		temp_str2 = h_session->line;
		h_session->line = ft_strjoin(h_session->line, temp_str);
		free(temp_str2);
		free(temp_str);
		write_vector(h_session);
	}
	tputs(term->im, 1, putchar_);
	tputs(term->cd, 1, putchar_);
	ft_printf("%s", &(h_session->line[h_session->left]));
	h_session->left += ft_strlen(g_buffer);
	temp = h_session->lenght;
	while (temp > h_session->left)
	{
		if (h_session->line[temp - 1] == '\n')
		{
			h_session->victor->curr_arr--;
			tputs(term->up, 1, putchar_);
			i = 0;
			while (++i < h_session->victor->array[h_session->victor->curr_arr])
				tputs(term->nd, 1, putchar_);
		}
		else
			tputs(term->le, 1, putchar_);
		temp--;
	}
	check_qoute(h_session, g_buffer);
	tputs(term->ei, 1, putchar_);
}

void		keep_left(t_history_session *h_session)
{
	int i;

	i = h_session->left - 1;
	tputs(term->cd, 1, putchar_);
	while (i >= 0 && h_session->line[i] && h_session->line[i] != '\n')
	{
		tputs(term->le, 1, putchar_);
		--i;
	}
	tputs(term->cd, 1, putchar_);
	while (h_session->victor->curr_arr)
	{
		tputs(term->up, 1, putchar_);
		i = 0;
		h_session->victor->curr_arr--;
		while (!h_session->victor->curr_arr && ++i < h_session->lenght_hello)
			tputs(term->nd, 1, putchar_);
		tputs(term->cd, 1, putchar_);
	}
}

void		key_cut(t_history_session *h_session, int disp)
{
	int i;
	int temp;

	tputs(term->im, 1, putchar_);
	h_session->comm.fd = 0;
	if (disp < 0)
	{
		cut_str(&(h_session->line), h_session->left, h_session->left + -1 * disp);
		write_vector(h_session);
		check_qoute(h_session, h_session->line);
		tputs(term->cd, 1, putchar_);
		ft_printf("%s", &h_session->line[h_session->left]);
	}
	else if (disp > 0)
	{
		keep_left(h_session);
		cut_str(&(h_session->line), h_session->left - disp, h_session->left);
		write_vector(h_session);
		check_qoute(h_session, h_session->line);
		ft_printf("%s", h_session->line);
		h_session->left -= disp;
	}
	temp = h_session->lenght;
	while (temp > h_session->left)
	{
		if (h_session->line[temp - 1] == '\n')
		{
			h_session->victor->curr_arr--;
			tputs(term->up, 1 , putchar_);
			i = !h_session->victor->curr_arr ? -h_session->lenght_hello : 0;
			while (++i < h_session->victor->array[h_session->victor->curr_arr])
				tputs(term->nd, 1, putchar_);	
		}
		else
			tputs(term->le, 1, putchar_);
		temp--;
	}
	g_dispersion = 0;
	tputs(term->ei, 1, putchar_);
}
