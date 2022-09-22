#include "../parser_utils.h"

char *ft_free_strjoin(char *dst, const char *src)
{
	int i;
	char *ret;

	if(!dst || !src)
		return NULL;
	ret = malloc(sizeof(char) * (ft_strlen(dst) + ft_strlen(src) + 1));
	if(!ret)
		return NULL;
	i = -1;
	while(dst[++i])
	 ret[i] = dst[i];
	while(*src)
		ret[i++] = *src++;
	ret[i] = '\0';
	free(dst);
	return ret;
}