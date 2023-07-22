#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t bowl;
sem_t forkStore[5];

void philosopherIsThinking(int num);
void philosopherIsEating(int num);
void philosopherHasEnteredTheTable(int num);
void philosopherPickedUpHisNextIndexFork(int num);
void philosopherPickedUpHisCurrentIndexFork(int num);
void philosopherHasFinishedEating(int num);
void philosopherPutDownHisNextIndexFork(int num);
void philosopherPutDownHisCurrentIndexFork(int num);
void philosopherIsGoingtoPickUpHisNextIndexFork(int num);
void philosopherIsGoingtoPickUpHisCurrentIndexFork(int num);
void philosopherIsGoingtoPutDownHisNextIndexFork(int num);
void philosopherIsGoingtoPutDownHisCurrentIndexFork(int num);
void philosopherIsGoingtoPickUpHisBowl(int num);
void philosopherIsGoingtoPutDownHisBowl(int num);
void philosopherPickedUpHisBowl(int num);
void philosopherPutDownHisBowl(int num);

void * philosopher(void * num)
{
	int phil=*(int *)num;
    while(1){
        philosopherIsThinking(phil);
        philosopherIsGoingtoPickUpHisBowl(phil);
        sem_wait(&bowl);
        philosopherPickedUpHisBowl(phil);
        philosopherIsGoingtoPickUpHisCurrentIndexFork(phil);
        sem_wait(&forkStore[phil]);
        philosopherPickedUpHisCurrentIndexFork(phil);
        philosopherIsGoingtoPickUpHisNextIndexFork(phil);
        sem_wait(&forkStore[(phil+1)%5]);
        philosopherPickedUpHisNextIndexFork(phil);
        philosopherIsEating(phil);
        philosopherHasFinishedEating(phil);
        philosopherIsGoingtoPutDownHisNextIndexFork(phil);
        sem_post(&forkStore[(phil+1)%5]);
        philosopherPutDownHisNextIndexFork(phil);
        philosopherIsGoingtoPutDownHisCurrentIndexFork(phil);
        sem_post(&forkStore[phil]);
        philosopherPutDownHisCurrentIndexFork(phil);
        philosopherIsGoingtoPutDownHisBowl(phil);
        sem_post(&bowl);
        philosopherPutDownHisBowl(phil);
    }
}

int main()
{
    int i;
	int a[5];
	pthread_t threadIDStore[5];

    sem_init(&bowl,0,4);

	i = 0;
	while (i < 5){
		sem_init(&forkStore[i],0,1);
		i++;
	}
	
	i = 0;
	while (i < 5){
		a[i] = i;
		pthread_create(&threadIDStore[i],NULL,philosopher,(void *)&a[i]);
		i++;
	}

	i = 0;
	while (i < 5){
		pthread_join(threadIDStore[i],NULL);
		i++;
	}
}


void philosopherIsThinking(int num){
	printf("\nPhilosopher %d is thinking",num);
}
void philosopherIsEating(int num){
	printf("\nPhilosopher %d is eating",num);
	sleep(2);
}
void philosopherHasEnteredTheTable(int num){
	printf("\nPhilosopher %d has entered table",num);
}
void philosopherPickedUpHisNextIndexFork(int num){
	printf("\nPhilosopher %d picked up his Next Index fork",num);
}
void philosopherPickedUpHisCurrentIndexFork(int num){
	printf("\nPhilosopher %d picked up his Current Index fork",num);
}

void philosopherHasFinishedEating(int num){
	printf("\nPhilosopher %d has finished eating",num);
}

void philosopherPutDownHisNextIndexFork(int num){
	printf("\nPhilosopher %d put down his Next Index fork",num);
}

void philosopherPutDownHisCurrentIndexFork(int num){
	printf("\nPhilosopher %d put down his Current Index fork",num);
}

void philosopherIsGoingtoPickUpHisNextIndexFork(int num){
	printf("\nPhilosopher %d is going to pick up his Next Index fork",num);
}

void philosopherIsGoingtoPickUpHisCurrentIndexFork(int num){
	printf("\nPhilosopher %d is going to pick up his Current Index fork",num);
}

void philosopherIsGoingtoPutDownHisNextIndexFork(int num){
	printf("\nPhilosopher %d is going to put down his Next Index fork",num);
}

void philosopherIsGoingtoPutDownHisCurrentIndexFork(int num){
	printf("\nPhilosopher %d is going to put down his Current Index fork",num);
}

void philosopherIsGoingtoPickUpHisBowl(int num){
    printf("\nPhilosopher %d is going to pick up his bowl",num);
}
void philosopherIsGoingtoPutDownHisBowl(int num){
    printf("\nPhilosopher %d is going to put down his bowl",num);
}
void philosopherPickedUpHisBowl(int num){
    printf("\nPhilosopher %d picked up his bowl",num);
}

void philosopherPutDownHisBowl(int num){
    printf("\nPhilosopher %d put down his bowl",num);
}