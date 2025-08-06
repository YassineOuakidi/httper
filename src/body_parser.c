

#include "../inc/http.h"

static char hex_to_char(char a, char b)
{
	if (!isxdigit(a) || !isxdigit(b))
		return 0;

	char hex[3] = { a, b, '\0' };
	return (char)strtol(hex, NULL, 16);
}

char *decode(char *str)
{
	if (!str)
		return NULL;

	size_t len = strlen(str);

	char *decoded = malloc(len + 1);
	if (!decoded)
		return NULL;

	char *dst = decoded;

	for (size_t i = 0; i < len; i++)
	{
		if (str[i] == '%' && i+2 < len && isxdigit(str[i + 1]) && isxdigit(str[i + 2]))
		{
			*dst++ = hex_to_char(str[i + 1], str[i + 2]);
			i += 2;
		}
		else if (str[i] == '+')
		{
			*dst++ = ' ';
		}
		else
		{
			*dst++ = str[i];
		}
	}
	*dst = '\0';

	return decoded;
}

void process_urlencoded(struct request **req)
{
	size_t 		i;

	char **splited = ft_split((*req)->body , '&');
	
	i = 0;
	while(splited[i])
	{
		char **key_value = ft_split(splited[i] , '=');
		if (key_value && key_value[0] && key_value[1])
		{
			(*req)->data[i].key = decode(key_value[0]);
			(*req)->data[i].value = decode(key_value[1]);
		}
	
		free_mat(key_value);
		i++;
	}
	free_mat(splited);
}


char *rtrim(char *str)
{
	size_t len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == '\r' || str[len - 1] == '\n' || str[len - 1] == ' '))
		len--;

	char *new = malloc(len + 1);
	if (!new) return NULL;

	memcpy(new, str, len);
	new[len] = '\0';
	return new;
}

void process_formdata(struct request **req)
{
	char **splited = ft_split( (*req)->content_type , ';' );

	char **splited2 = ft_split(splited[1] , '=');

	char *boundary_tmp = ft_strdup(splited2[1]);

	char *boundary_tmp2 = ft_strjoin("--" , boundary_tmp);

	char *boundary = rtrim(boundary_tmp2);
	size_t boundary_len = ft_strlen(boundary);

	free_mat(splited);
	free_mat(splited2);
	free(boundary_tmp);
	free(boundary_tmp2);

	char **body_split = ft_split((*req)->body , '\n');
	
	size_t		order = 0;
	size_t 		i = 0;
	int in = 0;

	while(body_split[i])
	{
		char *trimed = rtrim(body_split[i]);
		
		if(strncmp(trimed , boundary , boundary_len) == 0)
		{
			if(in == 1)
				order ++;
			in = 1;
			i++;
		}
		else 
		{

			char **tmp = ft_split(trimed , '=');
			(*req)->data[order].key = decode(tmp[1]);
			i+=2;


			char *temp = rtrim(body_split[i]);
			while(strncmp(temp , boundary , boundary_len)!=0)
			{
				(*req)->data[order].value = ft_strjoin((*req)->data[order].value , temp);
				i++;
				free(temp);
				temp = rtrim(body_split[i]);
			}
			free(temp);
			free_mat(tmp);
		}
		free(trimed);

	}
	free_mat(body_split);

}


