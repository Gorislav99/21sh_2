/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 16:43:12 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/01 16:43:14 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef INPUT_H
#define INPUT_H 
// # define KEY_TAB 9
# define KEY_NL 10
# define KEY_ESC 27
# define KEY_BS 127
// # define KEY_DEL 1295
# define KEY_UP 1183
# define KEY_DOWN 1184
# define KEY_RIGHT 1185
# define KEY_LEFT 1186
# define KEY_SHIFT_UP 1341
# define KEY_SHIFT_DOWN 1342
# define KEY_END 1188
# define KEY_HOME 1190
# define KEY_SHIFT_LEFT 1344
# define KEY_SHIFT_RIGHT 1343
# define KEY_COPY_LEFT 1349
# define KEY_COPY_RIGHT 1351
# define KEY_PASTE 1297
# define KEY_CUT 1298
// # define KEY_CTRL_E 5
// # define KEY_CTRL_R 18
// # define KEY_CTRL_U 21
# include "../vector/vector.h"
# define GRID_LENGHT 3

typedef struct	s_term
{
	char		*le;
	char		*nd; // курсор на 1 символ влево
	char		*cd; // очистка до конца экрана
	char		*dc;
	char		*im;
	char		*ei;
	char		*so;
	char		*se;
	char		*up;
	char		*do_;

}				t_term;



typedef struct s_commas
{
	char	ch;
	int		fd;
}				t_commas;

typedef struct			s_history_session
{
	t_commas					comm;
	int							left;
	int							lenght;
	char						*line;
	int							number_hist;
	int							lenght_hello;
	int							fl;
	t_vector					*victor;
	struct s_history_session	*up;
	struct s_history_session	*down;

}						t_history_session;

t_term					*term;
int						g_dispersion;
char					*g_buffer;

int	putchar_(int c);
void	backspace_ch(t_history_session *h_session);
void	print_ch(t_history_session *h_session, char key, int fl);
void    left_ch(t_history_session *h_session);
void    right_ch(t_history_session *h_session);
t_history_session	*add_history(t_history_session *h_session, int lenght_hello);
void	key_history(t_history_session *h_session, int key);
void    navigation(t_history_session *h_session, int key);
void	navigation_words(t_history_session *h_session, int key);
void    cut_copy_paste(t_history_session *h_session, int key);
void 	_commas(t_history_session *h_session, int key);
void    save_buff(t_history_session *h_session);
void    key_paste(t_history_session *h_session);
void	key_cut(t_history_session *h_session, int temp);
char	*input(t_history_session **h_session, int lenght_hello);



#endif