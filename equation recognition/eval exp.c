/* In this file an evaluator evaluateExpressions is definined that can evaluate
 * arithmetical expressions generated by the following BNF grammar:
 *
 * <expression>  ::= <term> { '+'  <term> | '-' <term> }
 *
 * <term>     ::= <number> | <identifier> | '(' <expression> ')'
 *
 * Input for the evaluator is the token list constructed by the scanner (in scanner.c).
 * For the evaluation of a token list the method of recursive descent is used.
 * It relies on the use of three functions for the recognition and evaluation of
 * terms, factors and expressions, respectively.
 * These three functions are defined with mutual recursion, corresponding with the
 * structure of the BNF grammar.
 */

#include <stdio.h>  /* getchar, printf */
#include <stdlib.h> /* NULL */

#include "scanner.h"
#include "recognizeExp.h"
#include "evalExp.h"
//#include "recognizeExp.c"


/* ValueOfNumbers is the total of the nat numbers on one side of the equations
 * ValueOfFactors is the total factor of the variable on one side
 */

int valueNumber(List *lp, double *wp) {
  if (*lp != NULL && (*lp)->tt == Number) {
    *wp = ((*lp)->t).number;
    *lp = (*lp)->next;
    return 1;
  }
  return 0;
}

/* The functions valueFactor, valueTerm and valueExpression are extensions of
 * acceptFactor, acceptTerm en acceptExpression. The second parameter
 * is a pointer: after successful execution it refers to the value
 * of the initial segment of the token list that is recognized as a factor, term
 * or expression, respectively.
 */


 /* valueTerm 
  * V, N, NV
  * V, N(V) = 1, Factor
  * N, N = N, Number
  * NV, N(V) = N, Factor 
  */


double valueEquation(List *lp){
  int N = 0, F = 0; // Left side of the = will be number, right side will be factor
  long double S;
  while (!acceptCharacter(lp, '=')){ // while not = sign yet
    if (acceptCharacter(lp, '-')){ 
      if((*lp)->tt == Number){
        int num = (*lp)->t.number;
        *lp = (*lp)->next;
        if(acceptIdentifier(lp)){
          if(acceptCharacter(lp, '^')){
            if ((*lp)->t.number == 0){
              N -= num;
            } else {
              F += num;
            }
            *lp = (*lp)->next;
          } else {
            F += num;
          }
        } else {
          N -= num;
        }
      } else{
        *lp = (*lp)->next;
        if(acceptCharacter(lp, '^')){
          if ((*lp)->t.number == 0){
            N -= 1;
          } else {
            F += 1;
          }
          *lp = (*lp)->next;
        } else {
          F += 1;
        }
      }
    } else {
      if ((*lp)->tt == Number){
        int num = (*lp)->t.number;
        *lp = (*lp)->next;
        if (acceptIdentifier(lp)){
          if(acceptCharacter(lp, '^')){
            if ((*lp)->t.number == 0){
              N += num;
            } else {
              F -= num;
            }
            *lp = (*lp)->next;
          } else {
            F -= num;
          }
        } else{
          N += num;
        }
      } else {
        if (acceptCharacter(lp, '+')){
          continue;
        } else {
          *lp = (*lp)->next;
          if(acceptCharacter(lp, '^')){
            if ((*lp)->t.number == 0){
              N += 1;
            } else {
              F -= 1;
            }
            *lp = (*lp)->next;
          } else {
            F -= 1;
          }
        }
      }  
    }
  }   
  while (*lp != NULL){
    if (acceptCharacter(lp, '-')){ 
      if((*lp)->tt == Number){
        int num = (*lp)->t.number;
        *lp = (*lp)->next;
        if(acceptIdentifier(lp)){
          if(acceptCharacter(lp, '^')){
            if ((*lp)->t.number == 0){
              N += num;
            } else {
              F -= num;
            }
            *lp = (*lp)->next;
          } else {
            F -= num;
          }
        } else {
          N += num;
        }
      } else{
        *lp = (*lp)->next;
        if(acceptCharacter(lp, '^')){
          if ((*lp)->t.number == 0){
            N += 1;
          } else {
            F -= 1;
          }
          *lp = (*lp)->next;
        } else {
          F -= 1;
        }
      }
    } else {
      if ((*lp)->tt == Number){
        int num = (*lp)->t.number;
        *lp = (*lp)->next;
        if (acceptIdentifier(lp)){
          if(acceptCharacter(lp, '^')){
            if ((*lp)->t.number == 0){
              N -= num;
            } else {
              F += num;
            }
            *lp = (*lp)->next;
          } else {
            F += num;
          }
        } else{
          N -= num;
        }
      } else {
        if (acceptCharacter(lp, '+')){
          continue;
        } else {
          *lp = (*lp)->next;
          if(acceptCharacter(lp, '^')){
            if ((*lp)->t.number == 0){
              N -= 1;
            } else {
              F += 1;
            }
            *lp = (*lp)->next;
          } else {
            F += 1;
          }
        }
      }  
    }
  }
  // This part does the final math and returns S if it is valid, otherwise it returns NULL
  if (F == 0) {
    return 0.1878; //shoutout to Aegir
  } else {
    S = (double)N / F;
    return S;
  }
  
}

/* The function evaluateExpressions performs a dialogue with the user, which
 * demonstrates the recognizer and the evaluator.
 */

void evaluateExpressions() {
  char *ar;
  List tl, tl1;
  int degrees;
  int variables;
  printf("give an equation: ");
  ar = readInput();

  while (ar[0] != '!') {
    tl = tokenList(ar);
    tl1 = tl;
    variables =countVariables(tl);
    printList(tl1);
    degrees = countDegree(tl1);
    if (acceptEquation(&tl1) && tl1 == NULL ) {
      if (variables == 1){
        printf("this is an equation in 1 variable of degree %d\n",degrees);
        if (degrees == 1){
            tl1 = tl;
            long double solution = valueEquation(&tl1);
            if(solution != 0.1878) {
              if(-0.0005 < solution && solution <= 0) {
                printf("solution: 0.000\n");
              } else {     
              printf("solution: %.3Lf\n", solution);
              }
            } else {
              printf("not solvable\n");
            }
        }
      } else {
        printf("this is an equation, but not in 1 variable\n");
      }
    } else {
      printf("this is not an equation\n");
    }
    free(ar);
    freeTokenList(tl);
    printf("\ngive an equation: ");
    ar = readInput();
  }
  free(ar);
  printf("good bye\n");
}