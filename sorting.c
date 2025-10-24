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


#include <stdlib.h>
#include "sorting.h"

/***************************************************/
/* Function: InsertSort    Date:                   */
/* Your comment                                    */
/***************************************************/
int InsertSort(int* array, int ip, int iu)
{
  int i, j, aux, count = 0;

  for (i = ip + 1; i <= iu; i++) {
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
  int flag = ERR;
  int count = 0;
  int i, j, aux;
  for(i = ip ; i < iu ; i++){
    flag = ERR;
    for(j = ip+1 ; j <= iu-i ; j++){
      if(array[j-1] > array[j]){
        count++;
        aux = array[j-1];
        array[j-1] = array[j];
        array[j] = aux;
        flag = OK;
      }
    }
    if(flag == OK){
      return count;
    }
  }
  return count;
}

int MergeSort(int* tabla, int ip, int iu)
{
  int mid = 0, ob_1 = 0, ob_2 = 0, ob_3 = 0, ob_total = 0;

  if(!tabla || ip < 0 || iu < 0 || ip > iu){
    return ERR;
  }

  if(ip == iu){
    return 0;   /*No tiene nada que ordenar*/
  }

  mid = (ip + iu) / 2;

  ob_1 += MergeSort(tabla, ip, mid);
  ob_2 += MergeSort(tabla, mid + 1, iu);
  ob_3 += Merge(tabla, ip, iu, mid);
  if(ob_1 == ERR || ob_2 == ERR || ob_3 == ERR){
    return ERR;
  }
  ob_total = ob_1 + ob_2 + ob_3;

  return ob_total;
}

int Merge(int* tabla, int ip, int iu, int imedio)
{
  int* aux = NULL;
  int len = 0, i = 0, j = 0, k = 0, count = 0;
  
  if(!tabla || ip < 0 || iu < 0 || imedio > iu){
    return ERR;
  }

  len = iu - ip + 1;
  aux = (int*)malloc(len*sizeof(int));
  if(aux == NULL){
    return ERR;
  }

  i = ip;
  j = imedio + 1;
  while(j <= iu && i <= imedio){
    if(tabla[i] >= tabla[j]){
      count++;
      aux[k] = tabla[j];
      j++;
    }else{
      count++;
      aux[k] = tabla[i];
      i++;
    }
    k++;
  }

  while(i <= imedio){
    aux[k] = tabla[i];
    i++;
    k++;
  }

  while(j <= iu){
    aux[k] = tabla[j];
    j++;
    k++;
  }

  for(i = ip ; i <= iu ; i++){
    tabla[i] = aux[i-ip];
  }

  free(aux);

  return count;
}

int QuickSort(int* tabla, int ip, int iu){
  int M = 0, ob_1 = 0, ob_2 = 0, ob_3 = 0, ob_total = 0;

  if(!tabla || ip < 0 || iu < 0 || iu < ip){
    return ERR;
  }

  if(ip == iu){
    return OK;
  }

  ob_1 += partition(tabla, ip, iu, &M);

  if(ip < M - 1){
    ob_2 += QuickSort(tabla, ip, M - 1);
  }
  if(M + 1 < iu){
    ob_3 += QuickSort(tabla, M + 1, iu);
  }

  if(ob_1 == ERR || ob_2 == ERR || ob_3 == ERR){
    return ERR;
  }

  ob_total = ob_1 + ob_2 + ob_3;

  return ob_total;
}

int partition(int* tabla, int ip, int iu, int *pos){
  int piv, aux, i, count = 0;

   count += median(tabla, ip, iu, pos);
  if((*pos) == ERR){
    return ERR;
  }

  piv = tabla[(*pos)];
  tabla[(*pos)] = tabla[ip];
  tabla[ip] = piv;
  (*pos) = ip;

  for(i = ip + 1 ; i <= iu ; i++){
    count++;
    if(tabla[i] < piv){
      (*pos)++;
      aux = tabla[i];
      tabla[i] = tabla[(*pos)];
      tabla[(*pos)] = aux;
    }
  }

  tabla[ip] = tabla[(*pos)];
  tabla[(*pos)] = piv;

  return count;
}

int median(int *tabla, int ip, int iu,int *pos){
  if(!tabla || ip < 0 || iu < 0 || !pos || ip > iu){
    return ERR;
  }
  *pos = ip;
  return 1;
}

int median_avg(int *tabla, int ip, int iu, int *pos){
  if(!tabla || ip < 0 || iu < 0 || !pos || ip > iu){
    return ERR;
  }
  *pos = ((iu + ip) / 2);
  return 1;
}

int median_stat(int *tabla, int ip, int iu, int *pos){
  int mid;
  if(!tabla || ip < 0 || iu < 0 || !pos || ip > iu){
    return ERR;
  }
  mid = (iu + ip) / 2;
  if(tabla[ip] < tabla[mid] && tabla[mid] < tabla[iu]){
    *pos = mid;
  }else if(tabla[ip] > tabla[mid] && tabla[ip] < tabla[iu]){
    *pos = ip;
  }else {
    *pos = iu;
  }
  return 3;
}