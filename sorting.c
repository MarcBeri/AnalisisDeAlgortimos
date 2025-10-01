/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */


#include "sorting.h"

/***************************************************/
/* Function: InsertSort    Date:                   */
/* Your comment                                    */
/***************************************************/
int InsertSort(int* array, int ip, int iu)
{
  int i, j, aux, count = 0;

  for (i = ip + 1; i < iu; i++) {
    count++;
    aux = array[i];
    j = i - 1;
    while (j >= ip && array[j] > aux) {
      array[j + 1] = array[j];
      j--;
      count++;
    }
    array[j + 1] = aux;
  }

  return count;
}



/***************************************************/
/* Function: SelectSort    Date:                   */
/* Your comment                                    */
/***************************************************/
int BubbleSort(int* array, int ip, int iu)
{
  int count = 0;
  int i, j, aux;
  for(i = ip ; i < iu ; i++){
    for(j = ip+1 ; j < iu-i ; j++){
      if(array[j-1] > array[j]){
        aux = array[j-1];
        array[j-1] = array[j];
        array[j] = aux;
      }
    }
  }
  return count;
}






