#include "get_next_line.h"

int	find_newline(const char **s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
		{
			*s = *s + i + 1;
			return (i);
		}
		i++;
	}
	return (-1);
}


char	*ft_strdup(const char *s)
{
	int		len;
	char	*dup;
	char	*ptr;

	len = ft_strlen(s);
	dup = (char *)malloc((len + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	ptr = dup;
	while (*s)
		*ptr++ = *s++;
	*ptr = '\0';
	return (dup);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	true_len;

	if (s == NULL)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start || len < 1)
		return (ft_strdup(""));
	true_len = len;
	if ((size_t)ft_strlen(s) - start < len)
		true_len = ft_strlen(s) - start;
	substr = malloc(sizeof(char) * (true_len + 1));
	if (!substr || !s)
		return (NULL);
	ft_strlcpy(substr, s + start, true_len + 1);
	return (substr);
}
