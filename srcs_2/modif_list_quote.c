#include "minishell.h"

int modif_list_quote(t_mimi *shell)
{
    t_list	*new;

	new = shell->list;
//	printf("========showlist main========\n");
	while (new != NULL)
	{
  //      printf("str = -%s- type = %d\n", new->str, new->type);
        if (new->type == 3)
        {
            free(new->str);
            ///////option malloc '\0'/////////

            new->str = (char *)malloc(sizeof(char) * 1);
            if (!new->str)
                return (-1);// free toute la liste
            new->str[0] = '\0';
            
            /////fin de l'option malloc '\0'/////

            ///////option NULL//////
          //  new->str = NULL;
            ///////fin option NULL///////
        }
		new = new->next;
	}
	//printf("==========fin list===========\n");
    return (0);
}