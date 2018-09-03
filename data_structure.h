#include <string.h>
typedef struct holder
{
	char *cmd;
	char *option;
	char *search;
}holder;
void mem(holder *tmp)
	{
		tmp->cmd = (char *)malloc(50);
		tmp->option= (char *)malloc(50);
		tmp->search = (char *)malloc(50);
	}
	void cmd3(holder *tmp,char *cmd,char *option,char *search)
	{
		mem(tmp);
		strcpy(tmp->cmd,cmd);
		strcpy(tmp->option,option);
		strcpy(tmp->search,search);
	}
	void cmd2(holder *tmp,char *cmd,char *option)
	{
		mem(tmp);
		strcpy(tmp->cmd,cmd);
		strcpy(tmp->option,option);
		tmp->search= NULL;
	}
	void cmd1(holder *tmp,char *cmd)
	{
		mem(tmp);
		strcpy(tmp->cmd,cmd);
		tmp->option= NULL;
		tmp->search= NULL;

	}
	
holder codes[1000];
int current_node=-1;
int last_node = 0;
void add3(char *cmd,char *option,char *search)
{
	current_node++;
	holder element_1;
	cmd3(&element_1,cmd,option,search);
	codes[current_node] = element_1;
}
void add2(char *cmd,char *option)
{
	current_node++;
	holder element_1;
	cmd2(&element_1,cmd,option);
	codes[current_node] = element_1;
}
void add1(char *cmd)
{
	current_node++;
	holder element_1;
	cmd1(&element_1,cmd);
	codes[current_node] = element_1;
}
void update_last_node()
{
	last_node = current_node+1;
}
int max(int x, int y)
{
	return x>y?x:y;
}
void print_history(int x)
{
	if(x==-1)
	{
		x = current_node;
	
	x = max(0,current_node-x);
	printf("--------------------------------HISTORY-------------------------------\n");
	for(int j=current_node-1;j>=x;j--)
	{
		if(codes[j].cmd!=NULL)
		printf("%s ",codes[j].cmd);
		if(codes[j].option!=NULL)
		printf("%s ",codes[j].option);
		if(codes[j].search!=NULL)
		printf("%s ",codes[j].search);
	printf("\n");
	}
	}
	else
	{
		printf("%d\n",x);
		char *argv[4];
		//x = max(0,current_node-x);
		if(codes[x].cmd!=NULL)
		printf("%s ",codes[x].cmd);
		if(codes[x].option!=NULL)
		printf("%s ",codes[x].option);
		if(codes[x].search!=NULL)
		printf("%s ",codes[x].search);
		argv[0] = codes[x].cmd;
		argv[1] = codes[x].option;
		argv[2] = codes[x].search;
		argv[3] = NULL;
		execvp(*(argv+0), argv);
	}
}
