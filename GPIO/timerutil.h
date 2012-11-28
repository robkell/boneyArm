/**
 * @file    timerutil.h
 * @brief   
 *
 * This interface enables easy benchmarking on Linux. It returns
 * microseconds as unit, but does not in any way guarantee this precision in
 * the resulting numbers.
 *
 * The maximum timespan measurable (delta or total) depends on the number of
 * bits of an unsigned long on your system (X), and is 2^X us. With 32-bit
 * unsigned longs this means 2^32 us which is almost 72 minutes.
 *
 * @verbatim
 * ============================================================================
 * Copyright (c) Texas Instruments Inc 2005
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied or provided.
 * ============================================================================
 * @endverbatim
 */

#ifndef _TIMERUTIL_H
#define _TIMERUTIL_H

#include <sys/time.h>

/**
 * @brief Object that stores the state of the timer. Needs to be declared
 * by the application and passed to the timerutil API calls.
 */
typedef struct TimerUtilObjStruct {
    struct timeval original;
    struct timeval previous;
} TimerUtilObj;

/**
 * @brief Pointer to a timer state object.
 */
typedef TimerUtilObj *TimerUtilHandle;

/**
 * @brief Indicates that a timer util API call completed successfully.
 */
#define TIMERUTIL_FAILURE -1

/**
 * @brief Indicates that a timer util API call failed.
 */
#define TIMERUTIL_SUCCESS 0

/**
 * @brief Resets the state of the timer. Must be called before other timer
 * util API calls.
 * @param hTimer Handle of the timer to reset.
 * @return TIMERUTIL_SUCCESS for success and TIMERUTIL_FAILURE for failure.
 */
static inline int TimerUtil_reset(TimerUtilHandle hTimer)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL) == -1) {
        return TIMERUTIL_FAILURE;
    }

    hTimer->original = tv;
    hTimer->previous = tv;

    return TIMERUTIL_SUCCESS;
}

/**
 * @brief Calculates the delta in microseconds between now and the last time
 * delta was called (or when reset was called if that is more recent) on this
 * timer object.
 * @param hTimer Handle of the timer to calculate a delta on.
 * @param deltaPtr Pointer to where the resulting value will be stored if the
 * operation was successful.
 * @return TIMERUTIL_SUCCESS for success and TIMERUTIL_FAILURE for failure.
 */
static inline int TimerUtil_delta(TimerUtilHandle hTimer,
                                  unsigned long *deltaPtr)
{
    struct timeval tv;
    time_t         s;
    suseconds_t    us;

    if (gettimeofday(&tv, NULL) == -1) {
        return TIMERUTIL_FAILURE;
    }

    s = tv.tv_sec - hTimer->previous.tv_sec;
    us = tv.tv_usec - hTimer->previous.tv_usec;

    *deltaPtr = s * 1000000 + us;

    hTimer->previous = tv;

    return TIMERUTIL_SUCCESS;
}

/**
 * @brief Calculates the delta in microseconds between now and the last time
 * reset was called on this timer object.
 * @param hTimer Handle of the timer to calculate a delta on.
 * @param totalPtr Pointer to where the resulting value will be stored if the
 * operation was successful.
 * @return TIMERUTIL_SUCCESS for success and TIMERUTIL_FAILURE for failure.
 */
static inline int TimerUtil_total(TimerUtilHandle hTimer,
                                  unsigned long *totalPtr)
{
    struct timeval tv;
    time_t         s;
    suseconds_t    us;

    if (gettimeofday(&tv, NULL) == -1) {
        return TIMERUTIL_FAILURE;
    }

    s = tv.tv_sec - hTimer->original.tv_sec;
    us = tv.tv_usec - hTimer->original.tv_usec;

    *totalPtr = s * 1000000 + us;

    return TIMERUTIL_SUCCESS;
}

#endif // _TIMERUTIL_H
