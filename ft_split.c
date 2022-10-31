#include <stdio.h>
#include <stdlib.h>

static 	int	is_char(char c, char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static	size_t	count_outer(char *str, char *charset)
{
	size_t	len;
	size_t	i;
	
	if (!charset)
		return (0);
	len = 0;
	i = 0;
	while (str[i])
	{
		if (!is_char(str[i], charset))
		{
			len++;
			while (str[i] && !is_char(str[i], charset))
				i++;
		}
		else
			i++;	
	}
	return (len);
}

static size_t	count_inner(char *str, char *charset)
{
	size_t	i;
	
	i = 0;
	while (str[i] && !is_char(str[i], charset))
		i++;
	return (i);
}

static	char	*inner_alloc(char *str, char *charset)
{
	char	*res;
	size_t	i;
	
	res = (char *)malloc(sizeof(char) * (count_inner(str, charset) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (*str && !is_char(*str, charset))
	{
		res[i] = *str;
		i++;
		str++;
	}
	res[i] = '\0';
	return (res);
}

char	**ft_split(char *str, char *charset)
{
	char	**res;
	size_t	i;

	if (!str)
		return (NULL);
	res = (char **)malloc(sizeof(char *) * (count_outer(str, charset) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (!is_char(*str, charset))
		{
			res[i] = inner_alloc(str, charset);
			while (*str && !is_char(*str, charset))
				str++;
			i++;
		}
		else
			str++;
	}
	res[i] = 0;
	return (res);
}

int	main(void)
{
	char	str[50] = "1111111113113221111122233344445";
	char	set[50] = "444";
	char	*temp;
	char	**res = ft_split(str, set);
	size_t	len = count_outer(str, set);
	printf("Outer: %zu\n", len);
	for (size_t i = 0; i < len; i++)
	{
		temp = res[i];
		printf("Result: %s\n", temp);
		free(temp);
	}
	free(res);
	return (0);
}
