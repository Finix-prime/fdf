/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmethira <pmethira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:01:39 by pmethira          #+#    #+#             */
/*   Updated: 2022/06/24 14:01:55 by pmethira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


static int	ft_is_sep(char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

static int	ft_strlen_cus(char *str, char sep)
{
	int	cnt;

	cnt = 0;
	while (!ft_is_sep(*str, sep) && *str)
	{
		cnt++;
		str++;
	}
	return (cnt);
}

static int	ft_arrcnt(char *str, char sep)
{
	int		cnt;
	char	*p_str;

	cnt = 0;
	p_str = str;
	while (ft_is_sep(*p_str, sep) && *p_str)
		p_str++;
	while (*p_str)
	{
		if (!ft_is_sep(*p_str, sep) && (ft_is_sep(*(p_str + 1), sep) \
			|| !*(p_str + 1)))
			cnt++;
		p_str++;
	}
	if (*str && *str != sep && cnt == 0 && sep == ' ')
		cnt++;
	return (cnt);
}

static int	ft_add_array(char **ret, char *ptr_s, int arr_cnt, char sep)
{
	int	cnt;

	cnt = 0;
	while (*ptr_s)
	{
		if (!ft_is_sep(*ptr_s, sep))
		{
			ret[cnt] = malloc(sizeof(char) * (ft_strlen_cus(ptr_s, sep) + 1));
			if (!ret[cnt])
			{
				cnt = 0;
				while (cnt < arr_cnt + 1)
					free(ret[cnt++]);
				free(ret);
				return (0);
			}
			ft_strlcpy(&ret[cnt++][0], ptr_s, (ft_strlen_cus(ptr_s, sep) + 1));
			ptr_s += ft_strlen(ret[cnt - 1]);
			if (*ptr_s == '\0')
				break ;
		}
		ptr_s++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		arr_cnt;
	char	**ret;
	char	*ptr_s;

	if (!s)
		return (NULL);
	ptr_s = (char *) s;
	arr_cnt = ft_arrcnt(ptr_s, c);
	ret = malloc(sizeof(char *) * (arr_cnt + 1));
	if (!ret)
		return (NULL);
	ret[arr_cnt] = NULL;
	if (ft_add_array(ret, ptr_s, arr_cnt, c))
		return (ret);
	return (NULL);
}
