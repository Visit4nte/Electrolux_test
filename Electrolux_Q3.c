// Q3) Implement a function able to calculate and return the average, maximum and minimum value of
// an array with “n” positions. This function must also return a copy of the input array containing 
// only the even numbers of the original array, as well as the new array size. Implement this logic 
// using the C language and share this code through a public repository on GitHub.

#include <stdio.h>
#include <stdlib.h>

float *arrayCalc (int pos, int *R_array){
  int Even_array[100];
  int Max = R_array[0];
  int Min = R_array[0];
  int Even_count = 0;
  int i = 0;

  float Sum = 0;
  static float Answer_array[100];
  
  for (i =0; i < pos; i++)
  {
    if (R_array[i] > Max){
      Max = R_array[i];
    }
    if (R_array[i] < Min){
      Min = R_array[i];
    }
    if ((R_array[i] % 2) == 0)
    {
        Even_array[Even_count] = R_array[i];
        Even_count++;
    }
    Sum = Sum + R_array[i];
  }

  Answer_array[0] = Sum / pos;
  Answer_array[1] = Max;
  Answer_array[2] = Min;
  Answer_array[3] = Even_count;
  for (i = 0; i < Even_count; i++)
  {
   Answer_array[i+4] = Even_array[i];
    i++;
  }
  
  return Answer_array;
}

int main(){
  int N_size_array[100];
  float Positions;
  int i;
  float *Function_return;

  printf("Please, Digit the number of elements: ");
  scanf("%f", &Positions);

  for(i=0; i < Positions; i++) {
    printf("Please, Digit the %d* of array: ", i+1);
    scanf("%d", &N_size_array[i]);
  }

  Function_return = arrayCalc (Positions, N_size_array);

  printf("\nThe original array is:");
  for(i=0; i < Positions; i++){
    printf(" %d", N_size_array[i]);
  }
  printf("\nThe size of even array is: %.0f", Function_return[3]);
  printf("\nThe even array is:");
  for(i=0; i < Function_return[3]; i++){
    printf(" %.0f", Function_return[i+4]);
  }
  printf("\nThe average of array value is: %.3f", Function_return[0]);
  printf("\nMax value of array: %.0f", Function_return[1]);
  printf("\nMin value of array: %.0f\n", Function_return[2]);
  return 0;
}