#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#define BILLION  1000000000L;

void *countA(void *arg)
{
   long long int a=0,count=0 ;
   long long int range=656862281;
   
   struct timespec start, end;
   struct sched_param type;
   type.sched_priority = 0;
   pthread_setschedparam(pthread_self(),SCHED_OTHER,&type);
   clock_gettime( CLOCK_REALTIME, &start);
   for(a=0 ; a<=range ; a++){
       count++;
       }
   clock_gettime( CLOCK_REALTIME, &end);
   double accum = ( end.tv_sec - start.tv_sec )
          +(double) ( end.tv_nsec - start.tv_nsec )
            / (double)BILLION;

   printf("count for countA : %lld\n",count);
   printf("Time taken : %lf\n",accum);
}

void *countB(void *arg)
{
   int a=0,count=0 ;
   long long int range=656862281;
    struct timespec begin, stop;
   struct sched_param prior;

   prior.sched_priority = 1;
   pthread_setschedparam(pthread_self(),SCHED_RR,&prior);
   clock_gettime( CLOCK_REALTIME, &begin);
   for(a=0 ; a<=range ; a++){
       count++;
       }
   clock_gettime( CLOCK_REALTIME, &stop);
   double accum = ( stop.tv_sec - begin.tv_sec )
          + (double)( stop.tv_nsec - begin.tv_nsec )
            / (double)BILLION;

   printf("count for countB :, %lld\n",count);
   printf("Time taken :, %lf\n",accum);

}

int main()
{ 
   pthread_t Thr_A , Thr_B , Thr_C ;

   int priority_array[]={11,14,8};
   
   for(int i=0; i<=8 ; i++){
   pthread_create(&Thr_A , NULL,countA , priority_array);
   pthread_create(&Thr_B, NULL, countB, priority_array);
   }
   pthread_join(Thr_A, NULL);
   pthread_join(Thr_B, NULL);


   pthread_exit(NULL);

   

return 0;
}