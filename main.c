#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdbool.h>
#include "CarRentalFunctions.h"

int main(void) {
  int       answer = 0;
  int       isRenter = -1;
  char      Email[50];
  carOwner  arrCars[10];

  srand(time(NULL));

  printf("1. Sign in\n2. Sign up\n");

  do{
    scanf("%d", &answer);  
  } while(answer < 1 && answer > 2);

  if(answer == 1){

    do{
      printf("Please enter your email: ");
      scanf("%s", &Email); 

      isRenter = userSelect(Email); 
    } while(isRenter < 0);
    
    if(isRenter == 1){
      printf("Welcome back %s!\n", carRenter1.name);
      while(1){
        printf("\n1. Rent a car\n2. View your profile\n3. Edit your profile\n4. Exit\n");
        do{
          scanf("%d", &answer);  
        } while(answer < 1 && answer > 4);
  
        switch (answer) {
          case 1:
            carSelect(arrCars);
            break;
          
          case 2:
            carRenterDisplay();
            break;
  
          case 3:
            carRenterEdit();
            break;

          case 4:
            return EXIT_SUCCESS;

          default:
            break;
        }
      }
    }
    else if(isRenter == 0) {
      printf("Welcome back %s!\n", carOwner1.name);

      while(1){
        printf("\n1. View your car rental history\n2. View your profile\n3. Edit your profile\n4. Rate your latest Rental\n5. Exit\n");
        do{
          scanf("%d", &answer);  
        } while(answer < 1 && answer > 5);
  
        switch (answer) {
          case 1:
            show_rentals();
            break;
          
          case 2:
            carOwnerDisplay();
            break;
  
          case 3:
            carOwnerEdit();
            break;
          
          case 4:
            findTransaction();
            break;

          case 5:
            return EXIT_SUCCESS;

          default:
            break;
        }
      }
    }
  }
  else if(answer == 2){
    printf("1. Sign up as renter\n2. Sign up as owner\n");
    do{
      scanf("%d", &answer);  
    } while(answer < 1 && answer > 2);      

    if(answer == 1){
      carRenterData();
    }
    else if(answer == 2){
      carOwnerData();
    }
  }
  return 0;
}