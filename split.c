/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmethira <pmethira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:57:28 by pmethira          #+#    #+#             */
/*   Updated: 2022/06/28 15:03:46 by pmethira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	wd_count(char const *s, char c)
{
	char	*str;
	char	**list;
	int		word;

	str = (char *)s;
	word = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		while (*str != c && *str)
			str++;
		if ((*str == 0 && *(str - 1) != c) || *str == c)
			word++;
	}
	return (word);
}

int	al_count(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i] != c && str[i])
	{
		i++;
	}
	return (i);
}

void	word_add(char *str, char c, char *list)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i])
	{
		list[i] = str[i];
		i++;
	}
	list[i] = 0;
}

void	reserve_word(char const *s, char c, char **list)
{
	char	*str;
	int		i;
	int		j;

	str = (char *)s;
	i = 0;
	j = 0;
	while (*str && j < wd_count(s, c))
	{
		while (*str == c)
			str++;
		i = al_count(str, c);
		list[j] = (char *)malloc(sizeof(char) * (i + 1));
		if (!list[j])
			return ;
		word_add(str, c, list[j]);
		while (*str != c && *str)
			str++;
		j++;
	}
	list[j] = 0 ;
}

char	**split(char const *s, char c)
{
	char	**list;
	int		word;

	word = wd_count(s, c);
	list = (char **)malloc(sizeof(char *) * (word + 1));
	if (!list)
		return (0);
	reserve_word(s, c, list);
	return (list);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				pre;
	long long int	ans;

	i = 0;
	pre = 1;
	ans = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			pre = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		ans = ans * 10 + (str[i] - '0');
		i++;
	}
	// if (ans < -2147483648 || ans > 2147483647)
	// 	error();
	return (pre * ans);
}

// int	main(void)
// {
// 	char	**str;
// 	char	*s = "   finix  prime note turtle   rabbit kim  prin methira jisoo sooyaa sophon tana    za x";

// 	str = split(s, ' ');
// 	for (int i = 0; str[i]; i++)
// 	{
// 		printf("word[%d] is -> %s\n", i, str[i]);
// 	}
// 	free(str);
// 	return (0);
// }
