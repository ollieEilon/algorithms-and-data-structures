#include <stdio.h>
#include <stdlib.h>
#include "LibStack.h"

int main(int argc, char *argv[]) {
  int repeat, length, input;
  scanf("%d", &repeat); //input for number of repeats we have for the program 
  while (repeat > 0){ //loop that checks how many repeats we have left
    scanf("%d", &length); //holds the length of the signal input
    int count = 0;

    Stack stack = newStack(10000); //declare a stack called 'stack'
    for (int i = 0; i < length; i++){ //get length inputs 
      scanf("%d", &input);
      count++; //increment count to know which is the last relevant input
      //in case the value is greater than the top value in the stack 
      if (input > stack.top){ 
        while (stack.top != input){
          push(i, &stack);
        }
      } else { //in case the value is smaller than the top value in the stack 
        while (stack.top > input){
          printf("[%d,%d)@%d ", stack.array[stack.top-1], i , stack.top);
          pop(&stack);
        }
      }
    }
    //code below works on the remaining output
    while (!isEmptyStack(stack)){//keep going until the stack is empty
      printf("[%d,%d)@%d ", stack.array[stack.top-1], count, stack.top);
      pop(&stack);
    }
    printf("\n");
    freeStack(stack); //free the stack 
    repeat--; //update the value of repeat 
  }
  
  return 0;
}
