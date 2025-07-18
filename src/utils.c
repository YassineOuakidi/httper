

#include "../inc/http.h"


void free_mat(char **mat)
{
	if(!mat)
		return ;
	size_t		i = 0;
	while(mat[i])
	{
		free(mat[i]);
		i++;
	}
	free(mat);
	return;
}

void free_req(struct request req)
{
	if(req.url)
		free(req.url);
	if(req.content_type)
		free(req.content_type);
	if(req.body)
		free(req.body);
	if(req.query_string)
		free(req.query_string);
	if(req.host)
		free(req.host);
	if(req.cookie)
		free(req.cookie);
	size_t 		i = 0;
	while(req.data[i].key)
	{
		free(req.data[i].key);
		if(req.data[i].value)
			free(req.data[i].value);
		i++;
	}
}
