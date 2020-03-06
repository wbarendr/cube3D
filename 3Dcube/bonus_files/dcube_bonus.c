/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dcube_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: wbarendr <wbarendr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/18 12:18:51 by wbarendr       #+#    #+#                */
/*   Updated: 2020/03/06 17:07:07 by wbarendr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "dcube_bonus.h"

char	*place_string(char *str, int *i)
{
	int		j;
	char	*str1;

	j = 0;
	str1 = malloc(map_length(str, *i) + 1);
	if (str == NULL)
		return (NULL);
	while (str[*i] != '\n' && str[*i] != '\0')
	{
		if (str[*i] != ' ')
		{
			str1[j] = str[*i];
			j++;
		}
		(*i)++;
	}
	str1[j] = 0;
	(*i)++;
	return (str1);
}

char	*make_array(t_map *f, int i)
{
	int r;
	int savei;

	savei = i;
	r = 0;
	f->map = malloc(sizeof(char *) * (f->rows + 1));
	if (f->map == NULL)
		return (free_willy(f, "malloc failed 4"));
	while (r < f->rows)
	{
		f->map[r] = place_string(f->str, &i);
		if (f->map[r] == NULL)
			return (free_map(f, r, "malloc failed 5"));
		r++;
	}
	f->map[f->rows] = 0;
	r = check_valid_arr(f);
	if (r == 0)
		return ("\nDONE\n");
	r = get_other_values(f, savei);
	if (r == -1)
		return ("something went TERRIBLY wrong!!\nInput data is not correct..");
	return ("\nAll INPUT DATA IS CORRECT\n");
}

char	*check_valid2(t_map *f, int i)
{
	while (f->str[i] != '\n' && f->str[i] != 0)
		i++;
	if (f->str[i] != 0)
	{
		if (f->str[i] == '\n' && f->str[i + 1] == '\n')
		{
			f->rows--;
			i++;
		}
		i++;
	}
	if (f->rows < 3)
		return (free_willy(f, "\ninvalid map\n"));
	if (f->str[i] == 0)
		return ("INVALID MAP");
	return (make_array(f, i));
}

char	*check_valid(t_map *f)
{
	int i;

	f->rows = 0;
	i = ft_strlen(f->str) - 1;
	if (f->str[i] == '\n')
		i--;
	while (f->str[i] != '\n' && i != 0)
	{
		if (!(f->str[i] == '1' || f->str[i] == ' '))
			return (free_willy(f, "Last line of map is wrong"));
		i--;
	}
	while (check_char(f->str[i], f) == 1 && (!(f->str[i] == '\n' &&
			f->str[i + 1] == '\n')) && i != 0)
		i--;
	return (check_valid2(f, i));
}

char	*read_file(t_map *f, int fd)
{
	char	*temp;
	int		amount;

	f->str = ft_calloc(1, 1);
	if (f->str == NULL)
		return ("malloc fail 1");
	temp = malloc(10 + 1);
	if (temp == NULL)
		return (free_willy(f, "malloc fail 2"));
	amount = 1;
	while (amount != 0)
	{
		amount = read(fd, temp, 10);
		if (amount == -1)
			return (free_fred(f, &temp, "Read Failed"));
		temp[amount] = 0;
		f->str = ft_strjoin(f, &temp);
		if (f->str == NULL)
			return (free_fred(f, &temp, "malloc fail 3"));
	}
	free(temp);
	return (check_valid(f));
}
