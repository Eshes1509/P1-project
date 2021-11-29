#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct carOwnerData {
    // values set by user
    char    name[50]; // Name of Cor Owner
    char    phoneNum[9]; // Phone number of CO
    char    Email[50]; // Email of CO
    int     age; // age of CO
    int     postCode; // postcode of CO
    int     price; // Price / h (dkk) of CO
    char    carName[50]; // Name of CO's car
    int     modelYear; // Model year of CO's car
    int     odometer; // kilometers driven by CO's car
    char    transmission; // CO's car's transmission | a = auto, b = manual
    // values set by program
    double  rating[]; // rating of CO
} carOwner;

typedef struct carRenterData {
    char    name[50]; // name of Car Renter
    char    phoneNum[9]; // Phone number of CR
    char    Email[50]; // Email of CR
    int     age; // Age of CR
    int     postCode; // Postcode of CR
    char    prefCarType; // CR's preffered car type | can be a,b or c, a most expensive, c least expensive
    char    prefTransmissionType; // CR's Preffered transmission type | can be a,b or c, a = auto, b = manual, c = both

    // values set by program
    double  rating[]; // rating of CR
} carRenter;

void getName (char name[]);
carOwner carOwnerData(char userName[]);
carRenter carRenterData(char userName[]);


int main(void) {
    carOwner *allOwners = (carOwner*) malloc(sizeof(carOwner) * 3);

    char fullName[50];
    char ans;

    FILE *output_file_pointer; // pointer to a file

    printf("Hello and welcome to our, please enter your full name: ");
    getName(fullName);

    printf("Hello %s!. First off, we would like to know whether you would want to rent a car or rent out a car\n", fullName);

    do {
        printf("'a': Rent a  car\n'b': Rent out a car\n");
        ans = getchar();
    } while(ans !='a' && ans != 'b');

    if (ans == 'a')  {
        //the custom datatype carRenter was defined earlier.

        carRenter tempCarRenter = carRenterData(fullName);
        output_file_pointer = fopen("renters.txt", "a");
        fprintf(output_file_pointer, "%s, %s, %s, %d, %d, %c, %c, %fl.\n", tempCarRenter.name, tempCarRenter.phoneNum, tempCarRenter.Email, tempCarRenter.age, tempCarRenter.postCode, tempCarRenter.prefCarType, tempCarRenter.prefTransmissionType, tempCarRenter.rating[0]);
        fclose(output_file_pointer);
        printf("Full name: %s\n"
               "Phone number: %s\n"
               "E-mail: %s\n"
               "Age: %d\n"
               "Postal code: %d\n"
               "Preffered price range: %c\n"
               "Gear type: %c\n"
               "Stars: %fl.\n", tempCarRenter.name, tempCarRenter.phoneNum, tempCarRenter.Email, tempCarRenter.age, tempCarRenter.postCode, tempCarRenter.prefCarType, tempCarRenter.prefTransmissionType, tempCarRenter.rating[0]);
    }

    else if (ans == 'b') {
        //the custom datatype carOwner was defined earlier.
        carOwner tempCarOwner = carOwnerData(fullName);
        output_file_pointer = fopen("owners.txt", "a");
        fprintf(output_file_pointer, "%s, %s, %s, %d, %d, %d, %s, %d, %d, %c, %fl.\n", tempCarOwner.name, tempCarOwner.phoneNum, tempCarOwner.Email, tempCarOwner.age, tempCarOwner.postCode, tempCarOwner.price, tempCarOwner.carName, tempCarOwner.modelYear, tempCarOwner.odometer, tempCarOwner.transmission, tempCarOwner.rating[0]);
        fclose(output_file_pointer);
        printf("Full name: %s\n"
               "Phone number: %s\n"
               "E-mail: %s\n"
               "Age: %d\n"
               "Postal code: %d\n"
               "Price/hour: %d\n"
               "Car name: %s\n"
               "Model year: %d\n"
               "Kilometers driven: %d\n"
               "Gear type: %c\n"
               "Stars: %fl.\n", tempCarOwner.name, tempCarOwner.phoneNum, tempCarOwner.Email, tempCarOwner.age, tempCarOwner.postCode, tempCarOwner.price, tempCarOwner.carName, tempCarOwner.modelYear, tempCarOwner.odometer, tempCarOwner.transmission, tempCarOwner.rating[0]);
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
    char temp;


    // Name
    strcpy(carOwner1.name,userName);

    // Phonenumber
    printf("hello %s. Please enter your phone number: ",carOwner1.name);
    scanf("%s", &carOwner1.phoneNum);

    // Email
    printf("Please enter your E-mail: ");
    scanf("%s", &carOwner1.Email);

    // Age
    printf("Please enter your age: ");
    scanf("%d", &carOwner1.age);

    // Postcode
    printf("Please enter the postal code for where car is placed: ");
    scanf("%d", &carOwner1.postCode);

    // Price of CO's car
    printf("Please enter the price per hour for your car ");
    scanf("%d", &carOwner1.price);

    // CO's car's name
    printf("Please enter the name of your car: ");
    scanf("%c",&temp);
    scanf("%[^\n]", carOwner1.carName);

    // Model year of CO's car
    printf("Please enter the model year of your car ");
    scanf("%d", &carOwner1.modelYear);

    // Kilometers driven by CO's car
    printf("Please enter the the amount of kilometers you car has driven: ");
    scanf("%d", &carOwner1.odometer);

    // CO's car's transmission
    printf("Is your car using automatic gearing or manual? (a = auto, b = manual): ");
    scanf("%c", &temp);
    scanf("%c", &carOwner1.transmission);

    return carOwner1;
}

//The function that fetches data for a car renter
carRenter carRenterData(char userName[]) {
    carRenter carRenter1;
    char temp; // Used in 'scanf("%c", &temp);' It clears the print buffer

    // Name
    strcpy(carRenter1.name,userName);

    // Phonenumber
    printf("hello %s. Please enter your phone number: ", carRenter1.name);
    scanf("%s", &carRenter1.phoneNum);

    // Email
    printf("Please enter your E-mail: ");
    scanf("%s", &carRenter1.Email);

    // Age
    printf("Please enter your age:");
    scanf("%d", &carRenter1.age);

    // Postcode
    printf("Please enter the postal code for where you would like rent a car: ");
    scanf("%d", &carRenter1.postCode);

    // Preffered car type
    printf("Please select a price range for which you want to rent a car (a = 0 for x kr, b = x+1 for y kr, c = y+1 for z kr): ");
    scanf("%c", &temp);
    scanf("%c", &carRenter1.prefCarType);

    // Preffered transmission type
    printf("Please enter preffered gear type: (a = automat, b = manuelt,  c = begge)): ");
    scanf("%c", &temp);
    scanf("%c", &carRenter1.prefTransmissionType);

    return carRenter1;
}

/* Idéer til programmet */
/* - Mulighed for at sortere biler efter pris,
når man har valgt hvilken type bil du gerne vil have og listen med dem er kommet frem */
