/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 14:44:00 by mrolfe            #+#    #+#             */
/*   Updated: 2019/08/28 14:56:13 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		checking_data(t_data *str, t_room *room)
{
	if (str->amount_of_ants > 0 && str->start && str->end && index_for_rc == 1)
		return (1);
	else
		map_error(room, str);
	return (0);
}

void	checking_duplicates(t_room *room, char *room_name, t_data *str)
{
	int i;
	int res;

	i = 0;
	while (i < room_nb + 1)
	{
		res = ft_strequ(room[i].name, room_name);
		if (res)
			map_error(room, str);
		i++;
	}
}

// void	check(char *line, int fd, t_data *str, t_room *room, int *index)
// {
// 	int i;

// 	i = 2;
// 	if (line[0] == '#')
// 		check2(line, fd, str, room);
// 	else if (checking_dash(line))
// 	{
// 		ft_printf("%s\n", line);
// 		if (*index == 0)
// 			sorting_rooms(room, 0, room_nb - 1, str);
// 		*index = 1;
// 		room_connections(room, line, str);
// 		free(line);
// 		line = NULL;
// 	}
// 	else
// 	{
// 		check_room(&line, room, str);
// 		ft_printf("%s\n", line);
// 		other_rooms(line, room, str);
// 	}
// }

// void check2(char *line, int fd, t_data *str, t_room *room)
// {
// 		if (ft_strequ(line, "##start"))
// 			read_start(line, fd, str, room);
// 		else if (ft_strequ(line, "##end"))
// 			read_end(line, fd, str, room);
// 		else
// 		{
// 			ft_printf("%s\n", line);
// 			free(line);
// 			line = NULL;
// 			return ;
// 		}
// }

void     check(char *line, int fd, t_data *str, t_room *room, int *index) //норма
{
    int i;

    i = 2;
    if (line[0] == '#')
    {
        if (ft_strequ(line, "##start"))
            read_start(line, fd, str, room);
        else if (ft_strequ(line, "##end"))
            read_end(line, fd, str, room);
        else
        {
            printf("%s\n", line);
            free(line);
            line = NULL;
            return ;
        }
    }
    else if (checking_dash(line))
    {
        if (!str->end_room || !str->start_room) // made for pipes_before_room (why doesn't work?)
            map_error(room, str);
        printf("%s\n", line);
        if (*index == 0)
            sorting_rooms(room, 0, room_nb - 1, str);
        *index = 1;
        room_connections(room, line, str);
        free(line);
        line = NULL;
    }
    else
    {
        check_room(&line, room, str);
        printf("%s\n", line);
        other_rooms(line, room, str);
    }
}

int		check_room(char **line, t_room *room, t_data *str)
{
	int i;
	int j;
	int count;

	i = 1;
	j = 0;
	count = 0;
	check_room2(line, room, str);
	while (line[0][i] && line[0][i] != ' ')
		i++;
	while (line[0][i])
	{
		if (!((line[0][i] >= '0' && line[0][i] <= '9') || line[0][i] == ' '))
		{
			free(line);
			line = NULL;
			map_error(room, str);
		}
		if (line[0][i] == ' ')
			count++;
		i++;
	}
	check_room3(line, room, str, count);
	return (1);
}

void check_room2(char **line, t_room *room, t_data *str)
{
	if (*line == NULL)
	{
		free(line);
		line = NULL;
		map_error(room, str);
	}
	if (line[0][0] == ' ' || line[0][0] == '\t')
	{
		free(*line);
		line = NULL;
		map_error(room, str);
	}
	if (line[0][0] == 'L' || line[0][0] == '#')
	{
		free(*line);
		line = NULL;
		map_error(room, str);
	}
}

void check_room3(char **line, t_room *room, t_data *str, int count)
{
	if (count != 2)
	{
		free(*line);
		line = NULL;
		map_error(room, str);
	}
	if (line[0][i - 1] == ' ')
	{
		free(*line);
		line = NULL;
		map_error(room, str);
	}
}

int		check_ants(const int fd, char **line)
{
	int i;

	i = 0;
	if (!get_next_line(fd, line))
		return (0);
	ft_printf("%s\n", *line);
	if ((line[0][0] == '#' && line[0][1] == '#') || (line[0][0] == '#' &&
			line[0][1] != '#'))
	{
		if (ft_strequ(*line, "##start") || ft_strequ(*line, "##end"))
			return (0);
		else
		{
			free(*line);
			get_next_line(fd, line);
		}
	}
	while (line[0][i])
	{
		if (!(line[0][i] >= '0' && line[0][i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}
