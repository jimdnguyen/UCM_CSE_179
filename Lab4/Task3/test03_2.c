//Example: test03.c

#define _MULTI_THREADED
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "check.h"
#include <unistd.h> //included this for sleep function


pthread_mutex_t       rwlock;

int active_readers = 0;
int active_writer = 0;
int pending_writers = 0;
pthread_cond_t readers_proceed;
pthread_cond_t writer_proceed;

int own_rlock(pthread_mutex_t *j){
  pthread_mutex_lock(j);
  while(pending_writers > 0 || active_writer < 0){ 
    pthread_cond_wait(&(readers_proceed),j);    
  }
  active_readers++;
  pthread_mutex_unlock(j);
}

int own_wlock(pthread_mutex_t *j){
  pthread_mutex_lock(j);
  pending_writers++;
  while(active_readers > 0 || active_writer == 1){
    pthread_cond_wait(&(writer_proceed),j); 
  }
  pending_writers--;
  active_writer = 1;
  pthread_mutex_unlock(j);
}

/*
int own_r_unlock(pthread_mutex_t *j){
  pthread_mutex_lock(j);
  active_readers--;
  if(active_readers == 0){
    pthread_cond_broadcast(&(readers_proceed));
  }
  pthread_mutex_unlock(j);
}

int own_w_unlock(pthread_mutex_t *j){
  pthread_mutex_lock(j);
  active_writer = 0;
  pthread_cond_broadcast(&(writer_proceed));
  pthread_mutex_unlock(j);
}

*/

int own_rw_unlock(pthread_mutex_t *j){ //merged the two unlocks together
    pthread_mutex_lock(j);

    if(active_readers > 0){
        active_readers--;
    }else if(active_writer > 0){
        active_writer = 0;
    }

    pthread_mutex_unlock(j); // having it here doesn't create a deadlock

    if(active_readers == 0){
        pthread_cond_broadcast(&(writer_proceed));
    }else if(active_writer == 0){
        pthread_cond_broadcast(&(readers_proceed));
    }
    
    //pthread_mutex_unlock(j); having the unlock here creates a deadlock

}

void *rdlockThread(void *arg)
{
  int rc;

  printf("Entered thread, getting read lock\n");
  rc = own_rlock(&rwlock);
  compResults("pthread_rwlock_rdlock()\n", rc);
  printf("got the rwlock read lock\n");

  sleep(5);

  printf("unlock the read lock\n");
  rc = own_rw_unlock(&rwlock);
  compResults("pthread_rwlock_unlock()\n", rc);
  printf("Secondary thread unlocked\n");
  return NULL;
}

void *wrlockThread(void *arg)
{
  int rc;

  printf("Entered thread, getting write lock\n");
  rc = own_wlock(&rwlock);
  compResults("pthread_rwlock_wrlock()\n", rc);

  printf("Got the rwlock write lock, now unlock\n");
  rc = own_rw_unlock(&rwlock);
  compResults("pthread_rwlock_unlock()\n", rc);
  printf("Secondary thread unlocked\n");
  return NULL;
}



int main(int argc, char **argv)
{
  int                   rc=0;
  pthread_t             thread, thread1,thread2,thread3;
  pthread_cond_init(&readers_proceed, NULL);
  pthread_cond_init(&writer_proceed, NULL);

  printf("Enter test case - %s\n", argv[0]);

  printf("Main, initialize the read write lock\n");
  rc = pthread_mutex_init(&rwlock, NULL);
  compResults("pthread_rwlock_init()\n", rc);

  printf("Main, grab a read lock\n");
  rc = own_rlock(&rwlock);
  compResults("pthread_rwlock_rdlock()\n",rc);

  printf("Main, grab the same read lock again\n");
  rc = own_rlock(&rwlock);
  compResults("pthread_rwlock_rdlock() second\n", rc);

  printf("Main, create the read lock thread\n");
  rc = pthread_create(&thread, NULL, rdlockThread, NULL);
  compResults("pthread_create\n", rc);

  printf("Main, create the read lock thread\n");
  rc = pthread_create(&thread2, NULL, rdlockThread, NULL);
  compResults("pthread_create\n", rc);

  printf("Main - unlock the first read lock\n");
  rc = own_rw_unlock(&rwlock);
  compResults("pthread_rwlock_unlock()\n", rc);

  printf("Main, create the write lock thread\n");
  rc = pthread_create(&thread1, NULL, wrlockThread, NULL);
  compResults("pthread_create\n", rc);

  printf("Main, create the write lock thread\n");
  rc = pthread_create(&thread3, NULL, wrlockThread, NULL);
  compResults("pthread_create\n", rc);

  sleep(5);

  printf("Main - unlock the second read lock\n");
  rc = own_rw_unlock(&rwlock);
  compResults("pthread_rwlock_unlock()\n", rc);

  printf("Main, wait for the threads\n");

  rc = pthread_join(thread, NULL);
  compResults("pthread_join\n", rc);

  rc = pthread_join(thread1, NULL);
  compResults("pthread_join\n", rc);

  rc = pthread_join(thread2, NULL);
  compResults("pthread_join\n", rc);

  rc = pthread_join(thread3, NULL);
  compResults("pthread_join\n", rc);

  rc = pthread_mutex_destroy(&rwlock);
  compResults("pthread_rwlock_destroy()\n", rc);

  pthread_cond_destroy(&readers_proceed);
  pthread_cond_destroy(&writer_proceed);

  printf("Main completed\n");
  return 0;
}