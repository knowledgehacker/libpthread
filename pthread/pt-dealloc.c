/* Deallocate a thread structure.
   Copyright (C) 2000, 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

#include <assert.h>
#include <pthread.h>
#include <stdlib.h>

#include <pt-internal.h>

/* List of thread structures corresponding to free thread IDs.  */
extern struct __pthread *__pthread_free_threads;
extern pthread_mutex_t __pthread_free_threads_lock;


/* Deallocate the thread structure for PTHREAD.  */
void
__pthread_dealloc (struct __pthread *pthread)
{
  assert (pthread->state != PTHREAD_TERMINATED);

  /* Withdraw this thread from the thread ID lookup table.  */
  __pthread_setid (pthread->thread, NULL);

  /* Mark the thread as terminated.  We broadcast the condition
     here to prevent pthread_join from waiting for this thread to
     exit where it was never really started.  Such a call to
     pthread_join is completely bogus, but unfortunately allowed
     by the standards.  */
  __pthread_mutex_lock (&pthread->state_lock);
  if (pthread->state != PTHREAD_EXITED)
    pthread_cond_broadcast (&pthread->state_cond);
  __pthread_mutex_unlock (&pthread->state_lock);

  /* We do not actually deallocate the thread structure, but add it to
     a list of re-usable thread structures.  */
  pthread_mutex_lock (&__pthread_free_threads_lock);
  __pthread_enqueue (&__pthread_free_threads, pthread);
  pthread_mutex_unlock (&__pthread_free_threads_lock);

  /* Setting PTHREAD->STATE to PTHREAD_TERMINATED makes this TCB
     available for reuse.  After that point, we can no longer assume
     that PTHREAD is valid.

     Note that it is safe to not lock this update to PTHREAD->STATE:
     the only way that it can now be accessed is in __pthread_alloc,
     which reads this variable.  */
  pthread->state = PTHREAD_TERMINATED;
}
