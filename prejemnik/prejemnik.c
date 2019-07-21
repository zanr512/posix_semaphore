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
	unsigned int priority = 1;
	
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
	
	struct mq_attr lastnosti_vrste;
    int oprimek_vrsta = -1;
    char *ime_vrste = argv[2];
	
	lastnosti_vrste.mq_maxmsg = 1; // maksimalno stevilo sporocil v vrsti
    lastnosti_vrste.mq_msgsize = 30; // maksimalna dolzina posaneznega sporocila
    
    
    oprimek_vrsta = mq_open(ime_vrste, O_RDWR|O_CREAT|O_EXCL, 0660, &lastnosti_vrste);
    
    if(oprimek_vrsta == -1){
            perror("tezava pri ustvarjanju vrste");
            return -1;
        }
    
    mq_close(oprimek_vrsta);
    oprimek_vrsta = mq_open(ime_vrste, O_RDONLY);
    
    
    while(1)
    {
			
		//oprimek_vrsta = mq_open(ime_vrste, O_RDONLY);
		//
		if(oprimek_vrsta == -1){
			perror("tezava pri odpiranju vrste");
			return -1;
		}

		if(mq_getattr(oprimek_vrsta, &lastnosti_vrste) == -1){
			perror("tezava pri branju lasnosti vrste");
			return -1;
		}

		int maxmsg_len = lastnosti_vrste.mq_msgsize;
		int msg_len;
		char *msg = malloc(maxmsg_len+1);
		

		memset(msg, 0, maxmsg_len+1);

		msg_len = mq_receive(oprimek_vrsta, msg, maxmsg_len, &priority);
		
		if(strcmp(msg,"3l3n7") == 0)
		{
			break;
		}

		if(msg_len == -1){
			perror("tezava pri branju sporocila");
		}else{
			printf("%s",msg);
		}
		
		free(msg);
		//mq_close(oprimek_vrsta);
		
		printf("\n");
	}
	mq_close(oprimek_vrsta);
    mq_unlink(ime_vrste);
	return 0;
	

}
