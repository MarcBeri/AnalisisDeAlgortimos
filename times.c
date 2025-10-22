/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "permutations.h"
#include "times.h"
#include "sorting.h"


/***************************************************/
/* Function: average_sorting_time Date:            */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short average_sorting_time(pfunc_sort metodo, 
                              int n_perms,
                              int N, 
                              PTIME_AA ptime)
{
  clock_t start_t, end_t;
  double total_t;
  int i, total_ob = 0, max_ob, min_ob, ob;
  int** perms=NULL;

  if(n_perms <=0 || !ptime || N<=0 || !metodo){
    return ERR;
  }

  perms = generate_permutations(n_perms,N);

  if(perms == NULL){
    free(perms);
    return ERR;
  }

  max_ob = INT_MIN;
  min_ob = INT_MAX; /*Los inicializamos de manera que cualquier 
                     numero siguiente se convierta en el max/min.*/

  start_t = clock();

  for(i = 0 ; i < n_perms ; i++){
    ob = metodo(perms[i],0,N-1);
    if(ob<min_ob){ 
      min_ob = ob;
    }
    if(ob>max_ob){
      max_ob = ob;
    }
    total_ob += ob;
  }

  end_t = clock();

  total_t = (double)(end_t - start_t) / n_perms;

  for(i = 0 ; i < n_perms ; i++){
    free(perms[i]);
  } 

  free(perms);

  ptime->N = N;
  ptime->n_elems = n_perms;
  ptime->time = total_t;
  ptime->average_ob = (double)(total_ob/n_perms);
  ptime->min_ob = min_ob;
  ptime->max_ob = max_ob;

  return OK;
}

/***************************************************/
/* Function: generate_sorting_times Date:          */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char* file, 
                                int num_min, int num_max, 
                                int incr, int n_perms)
{
  TIME_AA *time = NULL;
  int i, tam, aux;

  if(!method || !file || num_min <= 0 || num_max <= 0 || incr <= 0 || n_perms <= 0){
    return ERR;
  }

  aux = (num_max - num_min) / incr + 1;

  time=(TIME_AA*)malloc((aux)*sizeof(TIME_AA));

  if(time==NULL){
    return ERR;
  }
  
  for(i = 0, tam = num_min; i < aux; i++, tam += incr){
    if(average_sorting_time(method, n_perms, tam, &time[i]) == ERR){
      free(time);
      return ERR;
    }
  }

  if(save_time_table(file, time, aux) == ERR){
    free(time);
    return ERR;
  }

  free(time);
  return OK;
}

/***************************************************/
/* Function: save_time_table Date:                 */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short save_time_table(char* file, PTIME_AA ptime, int n_times)
{
  int i;
  FILE *f = NULL;

  if(!file || !ptime || n_times <= 0){
    return ERR;
  }
  
  f = fopen(file,"w");
  if(f == NULL){
   return ERR;
  }

  for(i=0; i < n_times; i++){
    fprintf(f," %d | %f | %f | %d | %d\n", ptime[i].N, ptime[i].time, 
            ptime[i].average_ob, ptime[i].max_ob, ptime[i].min_ob);
  }

  fclose(f);
  return OK;
}
