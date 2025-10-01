/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Carlos Aguirre
 * Version: 1.1
 * Fecha: 21-09-2019
 *
 */


#include "permutations.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

/***************************************************/
/* Function: random_num Date:   19-09-2025         */
/* Authors:     Mario Rodriguez Barragan           */
/*              Marcos Beriguete Gomez             */
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int inf: lower limit                            */
/* int sup: upper limit                            */
/* Output:                                         */
/* int: random number                              */
/***************************************************/
int random_num(int inf, int sup)
{
  int random = 0;

  if(inf > sup || inf < 0 || sup < 0){
    printf("Hay algún error en los datos introducidos.");
    return ERR;
  }

  random = inf + (((sup - inf + 1) * rand()) / (RAND_MAX + 1));

  return random;
}

/*return rand()/(RAND_MAX+1.)*(sup-inf+1)+inf;*/

/***************************************************/
/* Function: generate_perm Date:                   */
/* Authors:   Mario Rodriguez Barragan             */
/*            Marcos Beriguete Gomez               */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                                          */
/* int n: number of elements in the permutation    */
/* Output:                                         */
/* int *: pointer to integer array                 */
/* that contains the permitation                   */
/* or NULL in case of error                        */
/***************************************************/

int* genera_perm(int N){
  int i, j, aux;
  int *perm = NULL;

  if(N <= 0)
    return NULL;

  perm = (int*)malloc(N*sizeof(int));
  if(!(perm)){
    return NULL;
  }

  for(i = 0 ; i < N ; i++){
    perm[i] = i+1;
  }

  for(i = 0 ; i < N ; i++){
    j = random_num(0, N - 1);
    aux = perm[i];
    perm[i] = perm[j];
    perm[j] = aux;
  }

  return perm;
}

/***************************************************/
/* Function: generate_permutations Date:           */
/* Authors:    Mario Rodriguez Barragan            */
/*             Marcos Beriguete Gomez              */
/* Function that generates n_perms random          */
/* permutations with N elements                    */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements in each permutation   */
/* Output:                                         */
/* int**: Array of pointers to integer that point  */
/* to each of the permutations                     */
/* NULL en case of error                           */
/***************************************************/

int** generate_permutations(int n_perms, int N)
{
  int **perms;
  int i,j;

  if(N <= 0 || n_perms <= 0)
    return NULL;

  perms = (int**)malloc(n_perms*sizeof(int*));
  if(perms == NULL){
    free(perms);
    return NULL;
  }

  for(i=0;i<n_perms;i++){
    perms[i] = genera_perm(N);

    if(perms[i]==NULL){
      for(j=0;j<=i;j++){
        free(perms[j]);
      }
      free(perms);
      return NULL;
    }
  }

  return perms;
}
