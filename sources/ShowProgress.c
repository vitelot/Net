#include <stdio.h>
void ShowProgress(float fraction, float total) {
  int percent = (int) (fraction/total*100);
  if(percent%5==0) {
    printf("   %d%%\r", percent);
    fflush(stdout);
  }
}
