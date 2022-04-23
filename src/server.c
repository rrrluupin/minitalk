/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlupin <rlupin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:29:32 by rlupin            #+#    #+#             */
/*   Updated: 2022/04/23 15:56:53 by rlupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	ft_rec_len_of_str(int *curr_bit, char **s, int *recived, int si)
{
	static int	real_len_val;

	real_len_val = 0;
	if (si == SIGUSR2)
		real_len_val += ft_recursive_power(2, *curr_bit);
	if (*curr_bit == 7)
	{
		*recived = 1;
		*s = ft_calloc(real_len_val + 1, sizeof(char));
		*curr_bit = 0;
		real_len_val = 0;
		return ;
	}
	(*curr_bit)++;
}

static void	ft_freeall_res_var(int *len_of_str, char **str, int *i)
{
	*len_of_str = 0;
	if (str)
	{
		ft_putendl_fd(*str, 1);
		free(*str);
		*str = 0;
	}
	*i = 0;
}

static void	ft_server_recive_information(int signal)
{
	static int	real_char_val = 0;
	static int	curr_bit = 0;
	static int	len_of_recived_str = 0;
	static char	*result = 0;
	static int	i = 0;

	if (!len_of_recived_str)
		ft_rec_len_of_str(&curr_bit, &result, &len_of_recived_str, signal);
	else
	{
		if (signal == SIGUSR2)
			real_char_val += ft_recursive_power(2, curr_bit);
		if (curr_bit == 7)
		{
			result[i++] = real_char_val;
			curr_bit = 0;
			if (real_char_val == 0)
				return (ft_freeall_res_var(&len_of_recived_str, &result, &i));
			real_char_val = 0;
			return ;
		}
		curr_bit++;
	}
}

int	main(void)
{
	int	id;

	id = (int)(getpid());
	ft_putnbr_fd(id, 1);
	ft_putchar_fd('\n', 1);
	signal(SIGUSR1, ft_server_recive_information);
	signal(SIGUSR2, ft_server_recive_information);
	while (1)
		usleep(WAIT_TIME);
}
