/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:52:27 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/02 15:52:28 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void _debb(t_history_session **h_session);


int		ft_readkey(int fd)
{
	int		ret;
	char	*b;
	int		res;
	int		i;

	b = ft_strnew(6);
	res = -1;
	if (b != NULL)
	{
		if ((ret = read(fd, &b[0], 6)) > 0)
		{
			res = b[0];
			if (b[0] == KEY_ESC && ret > 1)
			{
				i = 0;
				while (b[++i] != '\0')
					res += b[i];
				res += 1000;
			}
		}
		free(b);
	}
	return (res);
}

void	key_func(t_history_session *h_session, int key)
{

	if (key == KEY_BS)
		backspace_ch(h_session);
	else if (key == KEY_LEFT)
		left_ch(h_session);
	else if (key == KEY_RIGHT)
		right_ch(h_session);
	else if (key < 255 && key >= 32)
		print_ch(h_session, key, 1);
	else if (key == KEY_SHIFT_UP || key == KEY_SHIFT_DOWN || key == KEY_HOME || key == KEY_END)
		navigation(h_session, key);
	else if (key == KEY_SHIFT_LEFT || key == KEY_SHIFT_RIGHT)
		navigation_words(h_session, key);


}

int		_enter(t_history_session *h_session, int key)
{
	int	*temp;
	int	i;
	int sum;

	i = 0;
	sum = 0;
	if (h_session->comm.fd % 2 == 0)
	{
		if (h_session->line && h_session->line[0] == '\0')
		{
			free(h_session->line);
			h_session->line = NULL;
		}
		write(1, "\n", 1);
		return (1);
	}
	while (h_session->victor->curr_arr < h_session->victor->lenght - 1)
	{
		h_session->victor->curr_arr++;
		tputs(term->do_, 1, putchar_);
	}
	h_session->victor->push_back(&(h_session->victor), 0);
	h_session->left = h_session->lenght;
	print_ch(h_session, key, 0);
	(h_session)->fl = 1;
	ft_printf("%s", "dquote> ");
	return (0);
}



char	*input(t_history_session **h_session, int lenght_hello)
{
	int		key;
	int		temp;

	temp = 1;
	*h_session = add_history(*h_session, lenght_hello);
	while (21)
	{
		key = ft_readkey(0);

		// ft_printf("%i\n", key);
		(key == '\"' || key == '\'') ? _commas(*h_session, key) : 0;
		if (key == KEY_COPY_LEFT || key == KEY_COPY_RIGHT)
		{
			temp = 0;
			cut_copy_paste(*h_session,key);
		}
		else if (!temp)
		{
			temp = !g_dispersion ? 1 : g_dispersion;
			if (key == KEY_CUT && g_dispersion)
				key_cut(*h_session, temp);
			else if (g_dispersion)
				save_buff(*h_session);
		}
		if (key == KEY_PASTE)
			cut_copy_paste(*h_session,key); 
		if (key == KEY_NL && _enter(*h_session, key))
			break ;
		if ((key == KEY_UP || key == KEY_DOWN) && !(*h_session)->fl)
			key_history(*h_session, key);
		else
			(*h_session)->number_hist = 0;
		key_func(*h_session, key);
	}
	_debb(h_session);
	(*h_session)->victor->curr_arr =(*h_session)->victor->lenght - 1;
	(*h_session)->left =(*h_session)->lenght;
	(*h_session)->fl = 0;
	return ((*h_session)->lenght == 0 ? ft_strdup("\0") : ft_strdup((*h_session)->line));
}



























void _debb(t_history_session **h_session)
{
	int i;
	i = 0;
	ft_printf("--------------------------------------\n");
	ft_printf("(*h_session)->left = %i\n", (*h_session)->left);
	ft_printf("(*h_session)->victor->lenght = %i\n", (*h_session)->victor->lenght);
	ft_printf("(*h_session)->victor->curr_arr = %i\n", (*h_session)->victor->curr_arr);
	ft_printf("(*h_session)->lenght = %i\n", (*h_session)->lenght);
	ft_printf("(*h_session)->dispersion = %i\n", g_dispersion);
	ft_printf("buffer = %s\n", g_buffer);

	ft_printf("--------------------------------------\nvector:\n");
	while (i < (*h_session)->victor->lenght)
		ft_printf("%i\n", (*h_session)->victor->array[i++]);
	ft_printf("--------------------------------------\n");
}