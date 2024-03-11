// Q3) Implement a function able to calculate and return the average, maximum and minimum value of
// an array with “n” positions. This function must also return a copy of the input array containing 
// only the even numbers of the original array, as well as the new array size. Implement this logic 
// using the C language and share this code through a public repository on GitHub.

#include <stdio.h>
#include <stdlib.h>


int main(){
  int N_size_array[100];
  int Even_array[100];
  int i = 0;
  int Even_count = 0;
  float Positions;
  int Max;
  int Min;
  float Sum = 0;
  float Average;

  printf("Please, Digit the number of elements: ");
  scanf("%f", &Positions);

  for(i=0; i < Positions; i++) {
    //---------------------------------Recieve array values
    printf("Please, Digit the %d* of array: ", i+1);
    scanf("%d", &N_size_array[i]);

    //---------------------------------First Max and Min
    if (i == 0)
    {
        Max = N_size_array[i];
        Min = N_size_array[i];
    }
    
    //---------------------------------Max and Min identification
    if (i != 0 && N_size_array[i] > Max)
    {
        Max = N_size_array[i];
    }
    if (i != 0 && N_size_array[i] < Min)
    {
        Min = N_size_array[i];
    }

    //---------------------------------Even nunbers detection
    if ((N_size_array[i] % 2) == 0)
    {
        Even_array[Even_count] = N_size_array[i];
        Even_count++;
    }
    Sum = Sum + N_size_array[i];
  }

  Average = Sum / Positions;
  printf("\nThe original array is:");
  for(i=0; i < Positions; i++){
    printf(" %d", N_size_array[i]);
  }
  printf("\nThe even array is:");
  for(i=0; i < Even_count; i++){
    printf(" %d", Even_array[i]);
  }
  printf("\nThe sum of array value is: %f", Sum);
  printf("\nThe average of array value is: %f", Average);
  printf("\nMax value of array: %d", Max);
  printf("\nMin value of array: %d\n", Min);
  return 0;
}