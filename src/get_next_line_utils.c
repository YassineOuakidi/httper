#include "../inc/get_next_line.h"
#include <stdio.h>

int found_new_line(s_list *list){
	size_t i = 0;
	if(!list) return 0;
	s_list *node = list;
	while(node){
		i = 0;
		while(node->str[i]){
			if(node->str[i]=='\n')return 1;
			i++;
		}
		node = node ->next;
	}
	return 0;
}

char *add_to_buffer(s_list *list){
	if(!list->str) return NULL;
	char *ans = malloc(BUFFER_SIZE + 1);
	
	size_t i = 0;
	while(list->str[i]){
		ans[i] = list->str[i];
		i++;
	}
	ans[i] = '\0';
	return ans;
}

size_t get_len(s_list **list) {
    if (!list || !*list) return 0; 
    s_list *node = *list;
    size_t ans = 0;

    while (node) {
        if (node->str) {
            size_t i = 0;
            while (node->str[i] && node->str[i] != '\n') {
                ans++;
                i++;
            }
            if (node->str[i] == '\n') {
                break;
            }
        }
        node = node->next;
    }
    return ans;
}


int get_endl_pos(char *str){
	if(!str) return 0;
	size_t i = 0;
	while(str[i]){
		if(str[i]=='\n') return i;
		i++;
	}
	return 0;
}

