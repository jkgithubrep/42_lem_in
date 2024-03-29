/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 11:56:52 by jkettani          #+#    #+#             */
/*   Updated: 2019/06/11 13:56:27 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_ants.h"
#include "env.h"
#include "path.h"
#include "ft_printf.h"
#include "options.h"

static void	print_ant_move_and_update_nodes(t_path *path, t_env *env, int *ret)
{
	if (*ret)
		ft_putchar(' ');
	else
		*ret = 1;
	ft_printf("L%d-%s", path->current->ant, path->current->next->name);
	if (path->current->next == env->end)
		++(env->end->ant);
	else
	{
		path->current->next->ant = path->current->ant;
		if (path->current == path->front)
			path->front = path->current->next;
	}
	path->current->ant = 0;
	if (path->current->from != env->start)
		path->current = path->current->from;
}

static int	print_moves_of_ants_already_in_anthill(t_env *env)
{
	int		i;
	int		ret;
	int		paths_covered;

	paths_covered = 0;
	ret = 0;
	while (paths_covered < env->nb_paths)
	{
		i = -1;
		while (++i < env->nb_paths)
		{
			if (!env->paths_array[i]->path_printed)
			{
				if (env->paths_array[i]->current->ant)
					print_ant_move_and_update_nodes(env->paths_array[i], env,
							&ret);
				else
				{
					env->paths_array[i]->path_printed = 1;
					++paths_covered;
				}
			}
		}
	}
	return (ret);
}

static void	print_moves_of_ants_entering_anthill(t_env *env, int *last_ant,
				int ants_printed)
{
	int		i;
	t_path	*path;

	i = 0;
	while (i < env->nb_paths)
	{
		path = env->paths_array[i];
		if ((path->back->from == env->start) && (*last_ant <= env->nb_ants))
		{
			if (i && (env->nb_ants - *last_ant + 1 + i) < path->nb_ants_stream)
				break ;
			if (i || ants_printed)
				ft_putchar(' ');
			ft_printf("L%d-%s", *last_ant, path->current->name);
			path->current->ant = *last_ant;
			++(*last_ant);
		}
		else
		{
			if (path->back->next != env->end)
				path->back = path->back->next;
		}
		++i;
	}
}

static void	print_line_of_ants_moves(t_env *env, int *last_ant)
{
	int		i;
	int		ants_printed;

	ants_printed = print_moves_of_ants_already_in_anthill(env);
	print_moves_of_ants_entering_anthill(env, last_ant, ants_printed);
	ft_putchar('\n');
	i = 0;
	while (i < env->nb_paths)
	{
		env->paths_array[i]->path_printed = 0;
		env->paths_array[i]->current = env->paths_array[i]->front;
		++i;
	}
}

void		print_all_lines_of_ants_moves(t_env *env)
{
	int		last_ant;
	int		j;

	last_ant = 1;
	j = 0;
	while (env->end->ant < env->nb_ants)
	{
		print_line_of_ants_moves(env, &last_ant);
		++j;
	}
	if (env->options & OP_DEBUG)
		ft_printf("\nNb of lines: %d\n", j);
}
