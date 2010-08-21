/*
 *  This code was written by Ramiro Polla and placed in the Public Domain.
 */

#include "pthread.h"

int pthread_create(pthread_t *__restrict__ thread,
                   const pthread_attr_t *__restrict__ attr,
                   void *(*start_routine)(void*), void *__restrict__ arg)
{
    unsigned tid;
    *thread = (pthread_t) _beginthreadex(NULL, 0, (void*) start_routine,
                                         arg, 0, &tid);
    return 0;
}

int pthread_cond_signal(pthread_cond_t *cond)
{
    WakeConditionVariable(cond);
    return 0;
}

int pthread_cond_wait(pthread_cond_t *__restrict__ cond,
                      pthread_mutex_t *__restrict__ mutex)
{
    int ret;
    ret = SleepConditionVariableCS(cond, mutex, INFINITE);
    return -(!ret);
}

int pthread_mutex_lock(pthread_mutex_t *mutex)
{
    if (__builtin_expect(*((short *)mutex) == -1, 0))
        InitializeCriticalSection(mutex);
    EnterCriticalSection(mutex);
    return 0;
}

int pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    LeaveCriticalSection(mutex);
    return 0;
}

int pthread_join(pthread_t thread, void **value_ptr)
{
    int ret;
    ret = WaitForSingleObject(thread, INFINITE);
    if (ret && value_ptr)
        GetExitCodeThread(thread, (void*) value_ptr);
    return -(!!ret);
}

int pthread_cond_broadcast(pthread_cond_t *cond)
{
    WakeAllConditionVariable(cond);
    return 0;
}

int pthread_mutex_destroy(pthread_mutex_t *mutex)
{
    int ret;
    ret = CloseHandle(mutex);
    return -(!ret);
}

int pthread_cond_destroy(pthread_cond_t *cond)
{
    return 0;
}

int pthread_cond_init(pthread_cond_t *__restrict__ cond,
                      const pthread_condattr_t *__restrict__ condattr)
{
    InitializeConditionVariable(cond);
    return 0;
}

int pthread_mutex_init(pthread_mutex_t *__restrict__ mutex,
                       const pthread_mutexattr_t *__restrict__ mutexattr)
{
    InitializeCriticalSection(mutex);
    return 0;
}

int pthread_num_processors_np(void)
{
    DWORD_PTR p, s;
    int n = 0;

    if (GetProcessAffinityMask(GetCurrentProcess(), &p, &s))
        for (; p; p >>= 1)
            n += p&1;

    return n ? n : 1;
}
