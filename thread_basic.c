#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void* myturn(void * arg){
	for(int i=0; i<5; i++){
		sleep(8);
		printf("My turn\n");
	}
}
void yourturn(){
	for(int i=0; i<8; i++){
		sleep(1);
		printf("Your Turn\n");
	}
}

int main(){
	pthread_t newthread;
	pthread_create(&newthread, NULL, myturn, NULL);
	yourturn();
	pthread_join(newthread, NULL);
}
