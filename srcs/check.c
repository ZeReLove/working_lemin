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

int     checking_data(t_data *str, t_room *room) //нет проверки на на дубликаты. Надо ли?
{
    if (str->amount_of_ants > 0 && str->start && str->end && index_for_rc == 1)
        return (1);
    else
        map_error(room, str);
    return (0);
}

void    checking_duplicates(t_room *room, char *room_name, t_data *str)
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

int     check_room(char **line, t_room *room, t_data *str)
{
    int i;
    int j;
    int count;

    i = 1;
    j = 0;
    count = 0;
    if (*line == NULL)
        map_error(room, str);
    if (line[0][0] == ' ' || line[0][0] == '\t')
        map_error(room, str);
    if (line[0][0] == 'L' || line[0][0] == '#')
        map_error(room, str);
    while (line[0][i] && line[0][i] != ' ')
        i++;
    while (line[0][i])
    {
        if (!((line[0][i] >= '0' && line[0][i] <= '9') || line[0][i] == ' '))
            map_error(room, str);
        if (line[0][i] == ' ')
            count++;
        i++;
    }
    if (count != 2)
        map_error(room, str);
    if (line[0][i - 1] == ' ')
        map_error(room, str);
    return (1);
}

int     check_ants(const int fd, char **line, t_room *room, t_data *str)
{
    int i;

    i = 0;
    if (!get_next_line(fd, line))
        map_error(room, str);
    printf("%s\n", *line);
    if ((line[0][0] == '#' && line[0][1] == '#') || (line[0][0] == '#' && line[0][1] != '#'))
    {
        if (ft_strequ(*line, "##start") || ft_strequ(*line, "##end"))
            map_error(room, str);
        else
            get_next_line(fd, line);
            
    }
    while (line[0][i])
    {
        if (!(line[0][i] >= '0' && line[0][i] <= '9'))
            map_error(room, str);
        i++;
    }
    return (1);
}
