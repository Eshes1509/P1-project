#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdbool.h>
#include "CarRentalFunctions.h"

int main(void) {
  int ans;
  srand(time(NULL));

  printf("1. Sign in\n2. Sign up as renter\n3. Sign up as owner\n6. Display car renter information\n7. Display car owner information\n9. Make a deal\n10. Rate a Deal\n");
  do{
    scanf("%d", &ans);  
  } while(ans < 1 && ans > 9);
  
  switch (ans)
  {
  case 1: 
    break;
  case 2: 
    carRenterData();
    break;
  case 3: 
    carOwnerData();
    break;
  case 4: 
    carRenterDisplay();
    break;
  case 5: 
    carOwnerDisplay();
    break;
  case 6:
    makeDeal();
    break;
  case 7:
    findTransaction();
    break;
    
  default:
    break;
  }
  fflush(stdin);
  return 0;
}


