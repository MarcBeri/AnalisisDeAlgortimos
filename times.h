/**
 *
 * Descripcion: Header file for time measurement functions 
 *
 * Fichero: times.h
 * Autor: Carlos Aguirre.
 * Version: 1.1
 * Fecha: 15-09-2019
 *
 */

#ifndef TIMES_H
#define TIMES_H

/* constants */

#ifndef ERR
  #define ERR -1
  #define OK (!(ERR))
#endif

#include "sorting.h"


typedef struct time_aa {
  int N;          
  int n_elems;   
  double time; 
  double average_ob; 
  int min_ob; 
  int max_ob; 
} TIME_AA, *PTIME_AA;


/* Functions */
short average_sorting_time(pfunc_sort method, int n_perms,int N, PTIME_AA ptime);
short generate_sorting_times(pfunc_sort method, char* file, int num_min, int num_max, int incr, int n_perms);
short save_time_table(char* file, PTIME_AA time, int n_times);

#endif
