/* Default mutex attributes.  Generic version.
   Copyright (C) 2000, 2002, 2008 Free Software Foundation, Inc.
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

#include <pthread.h>
#include <pt-internal.h>

const struct __pthread_mutexattr __pthread_default_mutexattr =
{
  prioceiling: 0,
  protocol: PTHREAD_PRIO_NONE,
  pshared: PTHREAD_PROCESS_PRIVATE,
  mutex_type: PTHREAD_MUTEX_DEFAULT
};

const struct __pthread_mutexattr __pthread_errorcheck_mutexattr =
{
  prioceiling: 0,
  protocol: PTHREAD_PRIO_NONE,
  pshared: PTHREAD_PROCESS_PRIVATE,
  mutex_type: PTHREAD_MUTEX_ERRORCHECK
};

const struct __pthread_mutexattr __pthread_recursive_mutexattr =
{
  prioceiling: 0,
  protocol: PTHREAD_PRIO_NONE,
  pshared: PTHREAD_PROCESS_PRIVATE,
  mutex_type: PTHREAD_MUTEX_RECURSIVE
};
