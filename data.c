/*

THIS IS JUST AN EXAMPLE OF HOW WE COULD MAKE A DATABASE
All the code i dadded is in main(), starting from l45 and ending on l100
What my added code does:
1. Makes a user.txt file if there is none (i have included the users.txt with a dummy user for showing the reading capability of the program)
2. Writes into user.txt the values of carRenter2 (does not overrite anything, everytime you run data.c it will add another carRenter2 to users.txt)
3. Reads line one of user.txt until a ',' and then until the  next ','
4. Prints the name and phone number of the first user in the users.txt list

*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct carOwnerData {
    char    name[50];
    char    phoneNum[9];
    char    Email[50];
    char    carType[50];
    int     age;
    int     postalCode;
    double  rating[];
} carOwner;

typedef struct carRenterData {
    char    name[50];
    char    phoneNum[9];
    char    Email[50];
    char    prefCarType[50];
    int     age;
    int     postalCode;
    double  rating[];
} carRenter;

void getName (char name[]);
carOwner carOwnerData(char userName[]);
carRenter carRenterData(char userName[]);

int main(void) {
    carOwner *allOwners = (carOwner*) malloc(sizeof(carOwner) * 3);

    char fullName[50];
    char ans;
    // CHANGES BEGIN HERE
    FILE *output_file_pointer; // pointer to our user.txt file
    FILE *input_file_pointer;
    char rName[50]; // the name extracted from users.txt
    char rPhoneNum[9];
    /* These are not used yet
    char rEmail[50];
    char rPrefCarType[50];
    int rAge;
    int rPostalCode;
    double rRating[1];
    */

    int ch; // for getting chars out of users.txt
    int i = 0; // for the while loop
    /*
    carRenter carRenter2; // i make a carRenter for easy debugging
    strcpy(carRenter2.name, "Andrzej Dudko");
    strcpy(carRenter2.phoneNum, "12345678");
    strcpy(carRenter2.Email, "andrzej@gmail.com");
    strcpy(carRenter2.prefCarType, "A");
    carRenter2.age = 20;
    carRenter2.postalCode = 9000;
    carRenter2.rating[0] = 5;

    output_file_pointer = fopen("users.txt", "a"); // input_file_pointer is set to point at the file users.txt, and append it
    if (output_file_pointer != NULL) {
      // the line below prints carRenter2 to users.txt
      fprintf(output_file_pointer, "%s, %s, %s, %s, %d, %d, %f.\n", carRenter2.name, carRenter2.phoneNum, carRenter2.Email, carRenter2.prefCarType, carRenter2.age, carRenter2.postalCode, carRenter2.rating[0]);
      fclose(output_file_pointer);

    } else {
      printf("Could not open output file. Bye.");
      exit(EXIT_FAILURE);
    }
    */

    input_file_pointer = fopen("users.txt", "r");
    if (output_file_pointer != NULL) {
      while ((ch = fgetc(input_file_pointer)) != EOF && ch != ',') {
        rName[i] = ch;
        i++;
      }
      rName[i] = '\0'; // an end indicator for when its made to a string
      ch = fgetc(input_file_pointer);
      i = 0;
      while ((ch = fgetc(input_file_pointer)) != EOF && ch != ',') {
        rPhoneNum[i] = ch;
        i++;
      }
      rPhoneNum[i] = '\0';
      printf("The first username from users.txt is: %s\n", rName);
      printf("The first phone nr. from users.txt is: %s\n", rPhoneNum);


    } else {
      printf("Could not open input file. Bye.");
      exit(EXIT_FAILURE);
    }









    printf("Hej, og velkommen til vores app, lad os starte med dit fulde navn: ");
    getName(fullName);

    printf("Hej %s!. Det foerste der skal ske er, at du skal vaelge om du vil leje eller udleje en bil\n", fullName);

    do {
        printf("Oensker du at leje eller udleje en bil?\n'a': Lej en bil\n'b': Udlej en bil:\n");
        ans = getchar();
    } while(ans !='a' && ans != 'b');

    if (ans == 'a')  {
        //the custom datatype carRenter was defined earlier.

        carRenter tempCarRenter = carRenterData(fullName);
        output_file_pointer = fopen("users.txt", "a");
        fprintf(output_file_pointer, "%s, %s, %s, %s, %d, %d, %f.\n", tempCarRenter.name, tempCarRenter.phoneNum, tempCarRenter.Email, tempCarRenter.prefCarType, tempCarRenter.age, tempCarRenter.postalCode, tempCarRenter.rating[0]);
        fclose(output_file_pointer);
        printf("Fulde navn: %s\nAlder: %d\nPostnummer: %d\nE-mail: %s\nTelefonnummer: %s\nForetrukne biltype: %s\n", tempCarRenter.name,tempCarRenter.age,tempCarRenter.postalCode, tempCarRenter.Email, tempCarRenter.phoneNum, tempCarRenter.prefCarType);
    }

    else if (ans == 'b') {
        //the custom datatype carOwner was defined earlier.
        carOwner tempCarOwner = carOwnerData(fullName);
        printf("Fulde navn: %s\nAlder: %d\nPostnummer: %d\nE-mail: %s\nTelefonnummer: %s\nDin biltype: %s\n", tempCarOwner.name,tempCarOwner.age,tempCarOwner.postalCode, tempCarOwner.Email, tempCarOwner.phoneNum, tempCarOwner.carType);
    }

}
//The function that optains the name of the user. Use of dynamic memory allocation. Remember to free(); when done using it
void getName (char name[]) {

    char *fullName = (char*) malloc(50);

    /*Checks if memory allocation was sucessfull*/
    if (fullName == NULL) {
        printf("Memory allocation failed");
        exit(0);
    }

    //Is able to obtain a string including spaces
    gets(fullName);

    strcpy(name, fullName);

    free(fullName);
}

//The function that fetches data for a car owner
carOwner carOwnerData(char userName[]) {
    carOwner carOwner1;

    strcpy(carOwner1.name,userName);

    printf("Hej %s, for at kommme godt i gang, skal vi have noget mere data om dig, venligst foelg instrukserne:\nLad os starte med din alder: ", carOwner1.name);
    scanf("%d",&carOwner1.age);
    //Postnummer
    printf("Indtast her postkoden for det omraade i Aalborg, som du oensker at udleje din bil i: ");
    scanf("%d", &carOwner1.postalCode);
    //Email
    printf("Der skal derudover bruges nogle personlige oplysninger omkring dig. Indtast nu din E-mail: ");
    scanf("%s",&carOwner1.Email);
    //Tlf.nr.
    printf("Indtast nu tlf.nr.: ");
    scanf("%s",&carOwner1.phoneNum);
    //Foretrukne bil type
    printf("Indtast hvilken type bil du ejer: "); /* Type A - dyre B - middel C - billige */
    scanf("%s",&carOwner1.carType);

    return carOwner1;
}

//The function that fetches data for a car renter
carRenter carRenterData(char userName[]) {
    carRenter carRenter1;

    //copies the username that was given earlier to the renter struct name
    strcpy(carRenter1.name,userName);

    //alder
    printf("Hej %s, for at kommme godt i gang, skal vi have noget mere data om dig, venligst foelg instrukserne:\nLad os starte med din alder: ", carRenter1.name);
    scanf("%d",&carRenter1.age);
    //Postnummer
    printf("Indtast her postkoden for det omraade i Aalborg, som du oensker at leje en bil i: ");
    scanf("%d", &carRenter1.postalCode);
    //Email
    printf("Der skal derudover bruges nogle personlige oplysninger omkring dig. Indtast nu din E-mail: ");
    scanf("%s",&carRenter1.Email);
    //Tlf.nr.
    printf("Indtast nu tlf.nr.: ");
    scanf("%s",&carRenter1.phoneNum);
    //Foretrukne bil type
    printf("Indtast nu den oenskede type bil, du oensker at leje: ");
    scanf("%s",&carRenter1.prefCarType);

    return carRenter1;
}

/* Idéer til programmet */
/* - Mulighed for at sortere biler efter pris,
når man har valgt hvilken type bil du gerne vil have og listen med dem er kommet frem */
