/*********************************************************************
 * Maxeler Technologies: Smith Waterman Demo                         *
 *                                                                   *
 * Version: 1.3                                                      *
 * Date:    30 July 2013                                             *
 *                                                                   *
 * Common library code source file                                   *
 *                                                                   *
 *********************************************************************/

#include "timing.h"

double gettime(){
  struct timeval tmp_time;
  gettimeofday(&tmp_time, NULL);
  return (tmp_time.tv_sec + (tmp_time.tv_usec*1.0e-6L));
}
