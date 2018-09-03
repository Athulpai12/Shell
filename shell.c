#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include <sys/types.h>  
#include <sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<math.h>
#include<map>
using namespace std;
map<int,char *> mp;
map<char,float> weather;
int xyz = -1;
#include "data_structure.h"
const char * logname;
const char * home;
//char * pwd=(char *)malloc(10*sizeof(char));
char pwd[1024];
const char * user;
const char * shell;
int saved_inp;
int saved_out;
int saved_err;
int fd,fd2;
int goto_func = -1;
int got_des = -1;
char *got_char;
#include<fcntl.h>
#include<dirent.h>
#include <sys/types.h>
#include<string.h>
int prime(int i)
{
	if(i==2||i==3)
		return 1;
	if(i%2==0||i%3==0)
		return 0;
	for(int j=2;j<=sqrt(i);j++)
		if(i%j==0)
			return 0;
	return 1;
}
void listDir(char *name,char *keyword)
{
	DIR *dir;
	struct dirent *currDir;
	int occ=0;
	dir=opendir(name);
	while((currDir=readdir(dir))!=NULL)
	{
		if(currDir->d_type==DT_DIR)
		{
			char *path = (char *)malloc(1024 * sizeof(char));
			if(!strcmp(currDir->d_name,".") || !strcmp(currDir->d_name,"..") )
			{
				continue;
				
			}
			//printf("%s\n",currDir->d_name);
			//printf("%d\n",sizeof(path));
			snprintf(path,1024, "%s/%s", name, currDir->d_name);
			//printf("%s\n",path);
			listDir(path,keyword);
			
			
		}
		else if(currDir->d_type==DT_REG)
		{
			char *path1 = (char *)malloc(1024 * sizeof(char));
			int count=0;
			occ=0;
			
			//printf("File found : %s\n",currDir->d_name);
			snprintf(path1,1024, "%s/%s", name, currDir->d_name);
			
			
			FILE *fp;
			fp=fopen(path1,"r");
			char line[100];
			while (fgets(line, 100, fp) != NULL) 
			{
        			if (strstr(line, keyword) != NULL) 
        			{
            
            			//printf("found in file %s\n",currDir->d_name);
            			occ++;
        			}
    			}
    			if(occ > 0)
    			{
    				printf("found in file %s with number of occurences : %d\n",path1,occ);
    			}
    			fclose(fp);
			
		}
		
			
	}
	//printf("total number of occurences %d\n",occ);
	
	closedir(dir);
	
}
void restore_flags()
{
     dup2(saved_inp,0);
     dup2(saved_out,1);
     dup2(saved_err,2);
}
int func(int check)
{
               int fd;
               if(check==0)
               fd = open(got_char,O_CREAT|O_WRONLY|O_TRUNC,0644);
               else if(check==1)
               fd = open(got_char, O_CREAT|O_WRONLY |O_APPEND,0644);
              // printf("%d\n",fd);
               if(check<2)
               dup2(fd,1);
               else
               dup2(got_des,1);
}
char* envVariable(char *s)
{
	return getenv(s);
}
void init()
{
	logname=envVariable("LOGNAME");
	home=envVariable("HOME");
	shell=envVariable("SHELL");
	getcwd(pwd,sizeof(pwd));
	user=envVariable("USER");
     saved_inp = dup(0);
     saved_err = dup(2);
     saved_out = dup(1);
     weather['b'] = 27.5;
     weather['c'] = 32;
     weather['k'] = 22.5;
}
void  parse(char *line, char **argv)
{
	char *array[100];
	int k=0;int i;
     for(i=0;line[i]!='\0';)
     {
     	if(line[i]=='\0')
     		break;
     	while(line[i]!='\0'&&line[i]==' ')
     		i++;
     	if(line[i]=='\0')
     		break;
     	if(line[i]=='|')
     	{
              // printf("%d %s\n",k,array[0]);
     		if(k==1)
     		{
     			add1(array[0]);
     			free(array[0]);
     		}
     		else if(k==2)
     		{
     			add2(array[0],array[1]);
     			free(array[0]);
     			free(array[1]);
     		}
     		else if(k==3)
     		{
     			add3(array[0],array[1],array[2]);
     			free(array[0]);
     			free(array[1]);
     			free(array[2]);
     		}
     		k=0;
     		
     		i++;
     	}
          else if(line[i]=='>')
          {
               i++;
               int check =0,des;
               if(line[i]=='>')
               {
                    check= 1;
                    i++;
               }
               else if(line[i]=='&')
               {
                    check=3;
                    des = line[i+1]-'0';
                    i++;
               }
               //printf("entered %c\n",line[i]);
               while(line[i]!='\0'&&line[i]==' ')
                    i++;
               if(line[i]=='\0')
                    break;
               int j = i;
               while(line[i]!=' '&&line[i]!='\0')
                    i++;
               char *c = (char *)malloc(i-j+5);
               for(int k_=j;k_<i;k_++)
                    c[k_-j] = line[k_];
               c[i-j] = '\0';
               goto_func = check;
               got_des = des;
               got_char = c;
        //  printf("des %d check%d\n",des,check);
              
          }
          else if(line[i]=='<')
          {
               
               while(line[i]!='\0'&&line[i]==' ')
                    i++;
               if(line[i]=='\0')
                    break;
               int j = i;
               while(line[i]!=' '&&line[i]!='\0')
                    i++;
               char *c = (char *)malloc(i-j+5);
               for(int k_=j;k_<i;k_++)
                    c[k_-j] = line[k_];
               c[i-j] = '\0';
               fd2 = open(c,O_RDONLY);
               dup2(fd2,0);
          }
     	while(line[i]!='\0'&&line[i]==' ')
     		i++;
     	if(line[i]=='\0')
     		break;
     	int j = i;
     	while(line[i]!=' '&&line[i]!='\0')
     		i++;
     	char *c = (char *)malloc(i-j+5);
     	for(int k_=j;k_<i;k_++)
               c[k_-j] = line[k_];
          c[i-j] = '\0';
     	array[k] = c;
     	if(!strcmp(c,"alias"))
     	{
     		add1(array[0]);
     		//printf("kk\n");
     		free(array[0]);
     		while(line[i]!='\0'&&line[i]==' ')
     			i++;
               int j = i;
               while(line[i]!=' '&&line[i]!='\0'&&line[i]!='=')
                    i++;
               char *ch = (char *)malloc(i-j+5);
               for(int k_=j;k_<i;k_++)
                    ch[k_-j] = line[k_];
               ch[i-j] = '\0';
               int hsh =0;
               int pow =26;
               while(*ch!='\0')
               {
               		//printf("%c\n",*ch);
               		
      				hsh+=(*ch-'a'+1)*pow;
      				pow=pow*26;
      				//fputc(*ch, target);
      				ch++;
               }
               char *new_hsh = (char *)malloc(100);
               while(line[i]==' '||line[i]=='=')
                    i++;
                int h_l =0;
               while(line[i]!='\0')
               {
               	 new_hsh[h_l] = line[i];
               	 i++;
               	 h_l++;
               }
               new_hsh[h_l] = '\0';
               mp[hsh] = new_hsh;
               while(line[i]!='\0')
               	i++;
               k=-2;
              // printf("hshhv valll%s\n",mp[hsh]);
     	}
     	k++;

     } 
     if(line[i]=='\0')
          {
               
               if(k==1)
               {
                    add1(array[0]);
                    free(array[0]);
               }
               else if(k==2)
               {
                    add2(array[0],array[1]);
                    free(array[0]);
                    free(array[1]);
               }
               else if(k==3)
               {
                    add3(array[0],array[1],array[2]);
                    free(array[0]);
                    free(array[1]);
                    free(array[2]);
               }
               k=0;
               
               i++;
          }
          /*
     printf("%d\n",current_node);
          for(int j=last_node;j<=current_node;j++)
     {
          if(codes[j].option!=NULL)
          printf("%s %s\n",codes[j].option,codes[j].cmd);             
     }
     */
     
}
int get_value_hash(char *c)
{
	int pow =26;
	int ans =0;
	while(*c!='\0')
	{
		ans+=(*c-'a'+1)*pow;
		pow=pow*26;
		c++;
	}
	return ans;
}
void change_value_back()
{
	goto_func = -1;
	got_des =-1;
	got_char = NULL;
}
void swap_data()
{
     char ch; //*source_file = (char *)malloc(20), *target_file = (char *)malloc(20);;
   FILE *source, *target;
   source = fopen("r.txt", "r");
   target = fopen("g.txt", "w");
   while( ( ch = fgetc(source) ) != EOF )
      fputc(ch, target);
   fclose(source);
   fclose(target);
 
}
void  phase1(char *line, char **argv)
{
     while (*line != '\0') 
     {       
          while (*line == ' ' || *line == '\t' || *line == '\n' || *line=='/')
          {
               *line++ = '\0';     
          }
          *argv++ = line;          
          while (*line != '\0' && *line != ' ' && *line != '\t' && *line != '\n' && *line!='/')
          { 
               line++;             
          }
     }
     *argv = '\0';                 
}
void  execute(char **argv)
{
     pid_t  pid;
     int    status;
     for(int k=last_node;k<=current_node;k++)
          { 
               argv[0] = codes[k].cmd;
               argv[1] = codes[k].option;
               argv[2] = codes[k].search; 
              // printf("%s\n",argv[0]); 
               pid=fork();
              
               if (pid < 0) 
     {     
          printf("fork process failed\n");
          exit(1);
     }
     else if (pid == 0) 
     {   
               int tmp_fd,tmp_fd2,tmp_fd3;
            if(current_node==last_node)
            {
               if(goto_func!=-1)
                    func(goto_func);
                
            }
            else if(k==current_node)
            {
               tmp_fd2 = open("g.txt",O_RDONLY);
               dup2(tmp_fd2,0);
                if(goto_func!=-1)
                    func(goto_func);

            }
            else if(k==last_node)
            {
               tmp_fd = open("r.txt",O_WRONLY|O_TRUNC);
               dup2(tmp_fd,1);
            }
            else
            {
               tmp_fd = open("r.txt",O_WRONLY|O_TRUNC);
               dup2(tmp_fd,1);
               tmp_fd2 = open("g.txt",O_RDONLY);
               dup2(tmp_fd2,0);
            }
            //printf("%sp\n",*(argv+0));
           // printf("%s\n",mp[26]);
            xyz=get_value_hash(*(argv+0));
            if(!strcmp(*(argv+0),"alias"))
            {
            	//printf("ssss%d\n",xyz);
            	exit(0);
            }
            else if(mp.find(xyz)!=mp.end())
            {
            	
            	 char  *argv1[64]; 
            	// printf("%sp\n",mp[xyz]);
            	 char *line = mp[xyz];
            	 int i=0;
            	phase1(line,argv1);
     		 if (execvp(*(argv1+0), argv1) < 0) //*(argv+0)
          {    
               printf("exec process failed\n");
               exit(1);
          }
            }
            else if(!strcmp(*(argv+0),"history"))
            {
            	int x = -1;
            	//printf("%s\n",*(argv+0));
            	if(*(argv+1)!=NULL)
            		x = atoi(*(argv+1));
            	print_history(x);
            }
            else if(!strcmp(*(argv+0),"prime"))
            {
            	if(prime(atoi(*(argv+1))))
            		printf("Prime\n");
            	else
            		printf("not a Prime\n");
            }
            else if(!strcmp(*(argv+0),"sgown"))
            {
            	listDir("/home/athulpai/Music/folder",*(argv+1));
            }
            else if(!strcmp(*(argv+0),"weather"))
            {
            	char c = argv[1][0];
            	printf("%f",weather[c]);
            }
            else if(!strcmp(*(argv+0),"echo") && !strcmp(*(argv+1),"$USER"))
            {
               printf("%s",user);
               //exit(0) indicates successful program termination  while exit(1) indicates unsucessful termination.
            }
           else if(!strcmp(*(argv+0),"echo") && !strcmp(*(argv+1),"$LOGNAME"))
            {
               printf("%s",logname);
              // exit(0);
            }
            else if(!strcmp(*(argv+0),"echo") && !strcmp(*(argv+1),"$HOME"))
            {
               printf("%s",home);
              // exit(0);
            }
            else if(!strcmp(*(argv+0),"echo") && !strcmp(*(argv+1),"$SHELL"))
            {
               printf("%s",shell);
              // exit(0);
            }
            else if(!strcmp(*(argv+0),"cd"))
            {
              printf("in cd %s",*(argv+1));
               //if exit(0) is uncommented, cd wont work. If exit(0) is commented, exit will only work if entered twice
               chdir(*(argv+1));
               //exit(0);
            }
     
          else if (execvp(*argv, argv)<0) //*(argv+0)
          {    
          		restore_flags();
               printf("exec process failed\n");
               exit(1);
               break;
          }
          close(tmp_fd2);
          close(tmp_fd);
         
          exit(0);
          
     }
     else 
     {                                  
          while (wait(&status) != pid)       
               ;
            restore_flags();
         // printf("sortingeeeee\n");
          swap_data(); 
     }

          }
     
}

int  main()
{
     char  line[1024]; //input array            
     char  *argv[64]; //array of pointers to the command and flags            
     init();
     while (1) 
     {                   
          printf("Enter the command\n");     
          L1:gets(line);              
          //printf("\n");

          parse(line, argv);
          if (strcmp(codes[current_node].cmd, "exit") == 0) 
          { 

               //chdir(pwd);
               exit(0);  
          }         
          if(line[strlen(line)-1]=='\\')
               goto L1;
          
         execute(argv);
         restore_flags();  
         update_last_node(); 
         change_value_back();        
          printf("\n");
     }
     
}
