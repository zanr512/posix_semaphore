#include <string.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <mqueue.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char** argv){
	
	int opcija;
	char data[4096] = "";
	
	int oprimek_vrsta = -1;
	unsigned int priority = 1;
	
	for(int j = 1; j < argc; j++)
	{
		if(strncmp(argv[j], "-", 1) == 0)
		{
			j++;
		}
		else
		{
			strcat(data,argv[j]);
			strcat(data," ");
		}
	}
	
	printf("%s",data);
		
	int q = 0;
	while((opcija = getopt(argc, argv, "q:")) != -1)
	{
		switch(opcija)
		{
			case 'q':
				
				q = 1;
				break;
				
		}
	}
	
	if(q == 0)
	{
		printf("Podati je potrebno -q\n");
		return 0;
	}
	
	char *ime_vrste = argv[2];
	
	
	
	oprimek_vrsta = mq_open(ime_vrste, O_WRONLY);
        
        if(oprimek_vrsta == -1){
            perror("tezava pri odpiranju vrste");
            return -1;
        }
        
        if(strlen(data) == 0)
			strcpy(data,"3l3n7");
         if(mq_send(oprimek_vrsta, data, strlen(data), priority) == -1){                    
                perror("tezava pri posiljanju sporocila");
                return -1;
            }
        mq_close(oprimek_vrsta);
	
	
	
	
	
}
