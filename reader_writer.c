#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[33m"
#define RESET "\x1B[0m"

sem_t x,y;
pthread_t tid;
pthread_t writerthreads[100],readerthreads[100];
int readercount = 0;

void *reader(void* param)
{
    sem_wait(&x);
    readercount++;
    if(readercount==1)
        sem_wait(&y);
    sem_post(&x);
    printf(GRN "%d reader is inside\n" RESET,readercount);
    usleep(3);
    sem_wait(&x);
    readercount--;
    if(readercount==0)
    {
        sem_post(&y);
    }
    sem_post(&x);
    printf(GRN "%d Reader is leaving\n" RESET,readercount+1);
    return NULL;
}

void *writer(void* param)
{
    printf(RED "Writer is trying to enter\n" RESET);
    sem_wait(&y);
    printf(RED "Writer has entered\n" RESET);
    sem_post(&y);
    printf(RED "Writer is leaving\n" RESET);
    return NULL;
}

int main()
{
    int n2,i;
    printf("Enter the number of readers:");
    scanf("%d",&n2);
    printf("\n");
    int n1[n2];
    sem_init(&x,0,1);
    sem_init(&y,0,1);
    for(i=0;i<n2;i++)
    {
        pthread_create(&writerthreads[i],NULL,reader,NULL);
        pthread_create(&readerthreads[i],NULL,writer,NULL);
    }
    for(i=0;i<n2;i++)
    {
        pthread_join(writerthreads[i],NULL);
        pthread_join(readerthreads[i],NULL);
    }

}
