/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlupin <rlupin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:29:16 by rlupin            #+#    #+#             */
/*   Updated: 2022/04/23 15:56:31 by rlupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static int	ft_search_for_main_errors(int argc, char **argv)
{
	int	i;

	if (argc != 3)
		return (1);
	i = -1;
	while (argv[1][++i])
	{
		if (!ft_strchr("0123456789", argv[1][i]))
			return (1);
	}
	return (0);
}

static void	ft_send_char_in_bits(unsigned char c, int pid)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		if (c & 0x01)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		c = c >> 1;
		usleep(WAIT_TIME);
	}
}

static void	ft_send_len_of_str_in_bits(int len, int pid)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		if (len & 0x01)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		len = len >> 1;
		usleep(WAIT_TIME);
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	int		str_len;
	int		i;
	char	*string_to_send;

	if (ft_search_for_main_errors(argc, argv))
		return (-1);
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		return (-1);
	string_to_send = argv[2];
	str_len = ft_strlen(string_to_send);
	i = -1;
	ft_send_len_of_str_in_bits(str_len, pid);
	while (string_to_send[++i])
		ft_send_char_in_bits(string_to_send[i], pid);
	ft_send_char_in_bits(string_to_send[i], pid);
}
