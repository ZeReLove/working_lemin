#include "lem_in.h"

t_plist		*algorithm(t_room *start, t_room *finish, t_room *arr)
{
	t_path	*path;
	t_plist	*plist;
	int		index;
	t_plist	*first;

	plist = NULL;
	index = 0;
	path = NULL;
	first = NULL;
	while (cutting_path(start, finish, first, &index))
	{
		while (width_search(start, finish, &path, 1))
		{
			clean_values(arr);
			plist = make_path_list(plist, path);
			if (index == 0)
			{
				first = plist;
				index = 1;
			}
		}
	}
	return (first);
}

int			cutting_path(t_room *start, t_room *finish, t_plist *first,
							int *index)
{
	t_plist	*tmp;
	t_path	*new;

	new = NULL;
	tmp = first;
	if (first)
	{
		unblock_rooms(tmp);
		block_direction(tmp, start);
		while (tmp->next)
			tmp = tmp->next;
		if (!width_search(start, finish, &new, 1))
			return (0);
		make_path_list(tmp, new);
		if (!both_directions(tmp->next, start))
		{
			free_path(first);
			return (0);
		}
		unblock_direction(first, start);
		if (!width_search(start, finish, NULL, 0))
		{
			free_path(first);
			return (0);
		}
		free_pathlist((first)->path, first);
		*index = 0;
	}
	return (1);
}

int			both_directions(t_plist *plist, t_room *start)
{
	t_path	*tmp;
	t_room	*tmp2;
	t_plist	*tmp3;
	int		count;

	tmp3 = plist;
	count = 0;
	tmp2 = start;
	while (tmp3)
	{
		tmp = tmp3->path;
		while (tmp)
		{
			if (find_room3(tmp, tmp2))
				count++;
			if (count == 10)
				return (1);
			tmp2 = tmp->room;
			tmp = tmp->next;
		}
		tmp3 = tmp3->next;
	}
	if (count)
		return (1);
	return (0);
}

int			width_search(t_room *start, t_room *finish, t_path **path,
							int index)
{
	int		val;
	t_nlist	*current;

	current = finish->neighb;
	start->value = 0;
	if (!give_values(&start, finish, 1))
		return (0);
	if (!index)
		return (1);
	*path = make_path(NULL, finish, 0);
	val = finish->value;
	while (val != 1)
	{
		while (current->room->value != val - 1)
			current = current->next;
		*path = make_path(*path, current->room, 1);
		current = current->room->neighb;
		val--;
	}
	return (1);
}

int			give_values(t_room **start, t_room *finish, int cur_val)
	{
		t_room	**queue;
		t_norm	norm;
		t_nlist	*tmp;
	
		tmp = (*start)->neighb;
		queue = give_values3(&norm, start);
		while (queue[norm.j] != NULL)
		{
			queue[(norm.j)++] = NULL;
			while (tmp)
			{
				if (tmp->room->value == NOT_GIVEN && tmp->room->status == OPENED &&
					tmp->status == OPENED)
				{
					queue[norm.i] = tmp->room;
					queue[(norm.i)++]->value = cur_val;
					if (check_finish(finish, queue[norm.i - 1]))
						return (give_values4(queue));
				}
				tmp = tmp->next;
			}
			give_values2(&norm, queue, &tmp, &cur_val);
		}
		free(queue);
		return (0);
	}
	
	t_room		**give_values3(t_norm *norm, t_room **start)
	{
		t_room	**queue;
	
		norm->i = 0;
		norm->j = 0;
		norm->block = 1;
		queue = make_queue();
		queue[(norm->i)++] = *start;
		return (queue);
	}
	
	int			give_values4(t_room **queue)
	{
		free(queue);
		return (1);
	}
	
	void		give_values2(t_norm *norm, t_room **queue, t_nlist **tmp,
					int *cur_val)
	{
		if (norm->j == norm->block || norm->block == 1)
			(*cur_val)++;
		if (norm->j == norm->block)
			norm->block = norm->i;
		if (queue[norm->j])
			*tmp = queue[norm->j]->neighb;
	}