/*
  George Vamvakousis
  csd4112
*/
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdlib.h>
#define numOfCustomers 12

/*
   to change the number of customers you have to change the define on line 4
   to whatever you want to check(integer && >0)
*/

sem_t empty, full, sm;
int data;
pthread_t ptid;
pthread_t ctids[numOfCustomers];

void *
Chef ()
{
  int produced;
  printf ("Chef arrives to his restaurant\n---------\n");
  for (produced = 0; produced < numOfCustomers; produced++)
    {
      sem_wait (&empty);
      printf ("[Chef on facebook]\n---------\n");
      sem_wait (&sm);
      data = produced;
      sem_post (&sm);
      sem_post (&full);
      printf
	("Customer %d came to restaurant\nChef realises that a customer is waiting\n",
	 data);
    }
}

int kappa = 0;

void *
Customer (void *no)
{
  int *thread = (int *) no;
  sem_wait (&full);
  printf ("Customer %d orders\nCustomer %d waits to get served\n", data,
	  data);
  sem_wait (&sm);
  sem_post (&sm);
  printf ("Customer %d served\n---------\n", data);
  sem_post (&empty);

}

void killSemaphores(){
  sem_destroy(&empty);
  sem_destroy(&full);
  sem_destroy(&sm);
}

int
main ()
{

  int customers[numOfCustomers];
  int *pointToCustomers[numOfCustomers];

  for (int i = 0; i < numOfCustomers; i++)
    customers[i] = i;
  for (int i = 0; i < numOfCustomers; i++)
    pointToCustomers[i] = &customers[i];

  sem_init (&empty, 1, 1);
  sem_init (&full, 1, 0);
  sem_init (&sm, 1, 1);
  pthread_create (&ptid, NULL, Chef, NULL);

  int sleep_time;
  for (int i = 1; i <= numOfCustomers; i++){
    pthread_create (&ctids[i], NULL, Customer, (void *) pointToCustomers[i]);
    if(i%3 == 0 && i!=1 && i!=numOfCustomers-1){   /*  mini break every 3 customers for 1-5 seconds  */
        sleep_time = rand() % 5;
        sleep(sleep_time);
    }
  }

  pthread_join (ptid, NULL);

  for (int i = 0; i < numOfCustomers; i++)
    pthread_join (ctids[i], NULL);

  if(numOfCustomers==0)printf("Yo boy is chilling\n");
  printf("Chef closes his restaurant\n");
  killSemaphores();
  return 0;
}
