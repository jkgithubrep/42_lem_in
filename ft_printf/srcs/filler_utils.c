/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:48:08 by apion             #+#    #+#             */
/*   Updated: 2019/03/20 20:50:37 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		fill_char(char *str, char c, int size)
{
	int	i;

	i = 0;
	while (i < size)
		*(str + i++) = c;
	return (i);
}
