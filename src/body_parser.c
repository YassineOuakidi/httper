

#include "../inc/http.h"


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
			(*req)->data[i].key = ft_strdup(key_value[0]);
			(*req)->data[i].value = ft_strdup(key_value[1]);
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
			(*req)->data[order].key = ft_strdup(tmp[1]);
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


void process_json(struct request **req)
{
	
}
