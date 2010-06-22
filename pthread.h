/*
 *  This code was written by Ramiro Polla and placed in the Public Domain.
 */

#ifndef PTHREAD_H
#define PTHREAD_H

#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define _WIN32_WINNT 0x0600
#include <windows.h>
#include <process.h>

typedef int pthread_mutexattr_t;
typedef int pthread_condattr_t;
typedef int pthread_attr_t;
typedef CRITICAL_SECTION pthread_mutex_t;
typedef CONDITION_VARIABLE pthread_cond_t;
typedef HANDLE pthread_t;

#define PTHREAD_MUTEX_INITIALIZER {(void*)-1};

int pthread_create(pthread_t *restrict,
                   const pthread_attr_t *restrict,
                   void *(*start_routine)(void*), void *restrict);
int pthread_cond_signal(pthread_cond_t *);
int pthread_cond_wait(pthread_cond_t *restrict,
                      pthread_mutex_t *restrict);
int pthread_mutex_lock(pthread_mutex_t *);
int pthread_mutex_unlock(pthread_mutex_t *);
int pthread_join(pthread_t, void **);
int pthread_cond_broadcast(pthread_cond_t *);
int pthread_mutex_destroy(pthread_mutex_t *);
int pthread_cond_destroy(pthread_cond_t *);
int pthread_cond_init(pthread_cond_t *restrict,
                      const pthread_condattr_t *restrict);
int pthread_mutex_init(pthread_mutex_t *restrict,
                       const pthread_mutexattr_t *restrict);

int pthread_num_processors_np(void);

#endif
