﻿/*
   Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.










   The lines above are intentionally left blank
*/

#ifndef MYSQL_IDLE_H
#define MYSQL_IDLE_H

/**
  @file mysql/psi/mysql_idle.h
  Instrumentation helpers for idle waits.
*/

#include "mysql/psi/psi.h"

/**
  @defgroup Idle_instrumentation Idle Instrumentation
  @ingroup Instrumentation_interface
  @{
*/

/**
  @def MYSQL_START_IDLE_WAIT
  Instrumentation helper for table io_waits.
  This instrumentation marks the start of a wait event.
  @param LOCKER the locker
  @param STATE the locker state
  @sa MYSQL_END_IDLE_WAIT.
*/
#ifdef HAVE_PSI_IDLE_INTERFACE
  #define MYSQL_START_IDLE_WAIT(LOCKER, STATE) \
    LOCKER= inline_mysql_start_idle_wait(STATE, __FILE__, __LINE__)
#else
  #define MYSQL_START_IDLE_WAIT(LOCKER, STATE) \
    do {} while (0)
#endif

/**
  @def MYSQL_END_IDLE_WAIT
  Instrumentation helper for idle waits.
  This instrumentation marks the end of a wait event.
  @param LOCKER the locker
  @sa MYSQL_START_IDLE_WAIT.
*/
#ifdef HAVE_PSI_IDLE_INTERFACE
  #define MYSQL_END_IDLE_WAIT(LOCKER) \
    inline_mysql_end_idle_wait(LOCKER)
#else
  #define MYSQL_END_IDLE_WAIT(LOCKER) \
    do {} while (0)
#endif

#ifdef HAVE_PSI_IDLE_INTERFACE
/**
  Instrumentation calls for MYSQL_START_IDLE_WAIT.
  @sa MYSQL_END_IDLE_WAIT.
*/
static inline struct PSI_idle_locker *
inline_mysql_start_idle_wait(PSI_idle_locker_state *state,
                             const char *src_file, int src_line)
{
  struct PSI_idle_locker *locker;
  locker= PSI_IDLE_CALL(start_idle_wait)(state, src_file, src_line);
  return locker;
}

/**
  Instrumentation calls for MYSQL_END_IDLE_WAIT.
  @sa MYSQL_START_IDLE_WAIT.
*/
static inline void
inline_mysql_end_idle_wait(struct PSI_idle_locker *locker)
{
  if (likely(locker != NULL))
    PSI_IDLE_CALL(end_idle_wait)(locker);
}
#endif

/** @} (end of group Idle_instrumentation) */

#endif

