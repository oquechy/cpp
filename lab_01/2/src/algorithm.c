#include "io.h"

int max(int a, int b) {
  logDebug('j');
  return (a > b ? a : b); 
}

int doComputation(int a, int b) {
  int c = max(3, 4);    
  logDebug('d');
  return c;
}