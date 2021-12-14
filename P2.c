//prog to send file from p1 to p2 process
#include <stdio.h> 
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h> 
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <semaphore.h>

int main()
{
    sem_t s1;
    int fd,i,len=0;
    char *shm_ptr;
    sem_init(&s1,1,1);
    unsigned char buff[100];

    fd=open("/home/ktubuntu/EOS/eos_lab_exam/dictionary.txt",O_RDWR ,S_IRUSR | S_IWUSR); 
    if (fd == -1)
    {
        perror("error-->Source not present \n");              //printf("%d",errno)-->errno 2
        printf("%d",errno);
    
    }  
    int shm_fd;
    shm_fd = shm_open("/dictionary",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
    if(shm_fd == -1)
    {
        perror("error msg \n");
    }
    ftruncate(shm_fd,sizeof(int));
    shm_ptr = (char *)mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,shm_fd,0);
    //read(fd,buff,sizeof(buff));
    
    
    
        sem_wait(&s1);
       for(i=0;*(shm_ptr+i)!='m';i++)
        {
            len++;
           // printf("%c",*(shm_ptr+i));
        }
        printf("%c",*(shm_ptr+i));
        sem_post(&s1);
        
    
    printf("length of string-->%d",len);
         shm_unlink("/dictionary");
    sem_destroy(&s1);
    return 0;

    



}