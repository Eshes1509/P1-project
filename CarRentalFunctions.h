
typedef struct transactionData
{
  int transactionID;    // An ID number that is linked to every transaction
  int renterID;         // Individual ID number for the renter
  char renterName[50];  // Renters name
  char renterEmail[50]; // Renters email
  int ownerID;          // Individual ID number for the owner
  char ownerName[50];   // Owners name
  char ownerEmail[50];  // Owners email
  char carName[50];     // Name of the car
  bool ownerRated;      // Boolean data type on whether the owner has rated
  bool renterRated;     // Boolean data type on whether the renter has rated
} tranDet;

typedef struct carOwnerData
{
  // values set by user
  int ID;            // Car owners ID number
  char name[50];     // Name of Car Owner
  char phoneNum[9];  // Phone number of CO
  char Email[50];    // Email of CO
  int age;           // age of CO
  int postCode;      // postcode of CO
  int price;         // Price / h (dkk) of CO
  char carName[50];  // Name of CO's car
  char carType;      // Car owners type of car (a = city car/hatchback, b = sedan/station car, c = SUV/Van)
  int modelYear;     // Model year of CO's car
  int odometer;      // kilometers driven by CO's car
  char transmission; // CO's car's transmission | a = auto, b = manual
  char CarDescription[100];
  double rating;
  int ratingAmount;
  // values set by program
  // double  rating[]; // rating of CO
} carOwner;

typedef struct carRenterData
{
  int ID;                    // Car renters ID number
  char name[50];             // name of Car Renter
  char phoneNum[9];          // Phone number of CR
  char Email[50];            // Email of CR
  int age;                   // Age of CR
  int postCode;              // Postcode of CR
  char prefCarType;          // CR's preffered car type | (a = city car/hatchback, b = sedan/station car, c = SUV/Van)
  char prefTransmissionType; // CR's Preferred transmission type | can be a,b or c, a = auto, b = manual, c = both
  double rating;
  int ratingAmount;
  // values set by program
  // double  rating[]; // rating of CR
} carRenter;

// user logins
carRenter carRenter1;
carOwner carOwner1;
bool RenterLoggedIn = 0;
bool OwnerLoggedIn = 0;

void getName(char name[])
{
  char *fullName = (char *)malloc(50);
  /*Checks if memory allocation was sucessfull*/
  if (fullName == NULL)
  {
    printf("Memory allocation failed");
    exit(0);
  }
  // Is able to obtain a string including spaces
  gets(fullName);
  strcpy(name, fullName);
  free(fullName);
}

carRenter enterCarRenter(void)
{
  carRenter tempCarRenter;
  char name[50];

  tempCarRenter.ID = ((rand() % 1000000) + 100000);
  printf("Enter name: ");
  fgets(tempCarRenter.name, 50, stdin);
  getName(name);
  strcpy(tempCarRenter.name, name);
  printf("Enter phone number: ");
  scanf(" %s", &tempCarRenter.phoneNum);
  printf("Enter E-mail: ");
  scanf(" %s", &tempCarRenter.Email);
  printf("Enter age: ");
  scanf(" %d", &tempCarRenter.age);
  printf("Enter postcode: ");
  do
  {
    scanf("\n%d", &tempCarRenter.postCode);
  } while (tempCarRenter.postCode != 9000 && tempCarRenter.postCode != 9200 && tempCarRenter.postCode != 9210 && tempCarRenter.postCode != 9220);
  printf("Enter preferred type of car (a = city car/hatchback, b = sedan/station car, c = SUV/Van): ");
  scanf(" %c", &tempCarRenter.prefCarType);
  printf("Enter preferred transmission type (a = automatic, b = manual,  c = both)): ");
  scanf(" %c", &tempCarRenter.prefTransmissionType);
  tempCarRenter.rating = 0;
  tempCarRenter.ratingAmount = 0;
  return tempCarRenter;
}

// The function that fetches data for a car renter
carRenter carRenterData()
{
  FILE *fp;
  carRenter tempCarRenter;

  tempCarRenter = enterCarRenter();
  // open file for writing
  fp = fopen("renters.dat", "ab");
  if (fp == NULL)
  {
    fprintf(stderr, "\nError opened file\n");
    exit(1);
  }

  // write struct to file
  fwrite(&tempCarRenter, sizeof(tempCarRenter), 1, fp);
  if (fwrite != 0)
    printf("Account succesfully created !\n");
  else
    printf("Error writing to file !\n");

  // close file
  fclose(fp);
}

carOwner enterCarOwner(void)
{
  carOwner tempCarOwner;
  char name[50];

  tempCarOwner.ID = ((rand() % 1000000) + 100000);
  printf("Enter name: ");
  fgets(tempCarOwner.name, 50, stdin);
  getName(name);
  strcpy(tempCarOwner.name, name);
  printf("Enter phone number: ");
  scanf("%s", &tempCarOwner.phoneNum);
  printf("Enter E-mail: ");
  scanf("%s", &tempCarOwner.Email);
  printf("Enter age: ");
  scanf("%d", &tempCarOwner.age);
  printf("Enter postcode: ");
  do
  {
    scanf("\n%d", &tempCarOwner.postCode);
  } while (tempCarOwner.postCode != 9000 && tempCarOwner.postCode != 9200 && tempCarOwner.postCode != 9210 && tempCarOwner.postCode != 9220);

  printf("Enter how much your car should cost per hour: ");
  scanf(" %d", &tempCarOwner.price);

  while (tempCarOwner.price > 100)
  {
    printf("\nEnter a maximum of 100 dkk: ");
    scanf(" %d", &tempCarOwner.price);
  }
  printf("Enter name of your car: ");
  fgets(tempCarOwner.carName, 50, stdin);
  getName(name);
  strcpy(tempCarOwner.carName, name);
  printf("Enter car type (a = city car/hatchback, b = sedan/station car, c = SUV/Van): ");
  do
  {
    printf("\na, b or c: ");
    tempCarOwner.carType = getchar();
  } while (tempCarOwner.carType != 'a' && tempCarOwner.carType != 'b' && tempCarOwner.carType != 'c');
  printf("Enter your car's model year: ");
  scanf("%d", &tempCarOwner.modelYear);
  printf("Enter your car's mileage: ");
  scanf("%d", &tempCarOwner.odometer);
  printf("Enter your car's transmission type (a = automatic, b = manual): ");
  fflush(stdin);
  scanf("%c", &tempCarOwner.transmission);
  printf("Enter small description of car (<100 characters): ");
  fgets(tempCarOwner.CarDescription, 50, stdin);
  getName(name);
  strcpy(tempCarOwner.CarDescription, name);
  tempCarOwner.rating = 0;
  tempCarOwner.ratingAmount = 0;

  return tempCarOwner;
}
// The function that fetches data for a car owner
carOwner carOwnerData()
{
  FILE *fp;
  carOwner tempCarOwner;
  tempCarOwner = enterCarOwner();
  // open file for writing
  fp = fopen("owners.dat", "ab");
  if (fp == NULL)
  {
    fprintf(stderr, "\nError opened file\n");
    exit(1);
  }

  // write struct to file
  fwrite(&tempCarOwner, sizeof(tempCarOwner), 1, fp);
  if (fwrite != 0)
    printf("Account succesfully created !\n");
  else
    printf("Error writing to file !\n");

  // close file
  fclose(fp);
}

int userSelect(char Email[])
{
  FILE *fp, *fp1;
  carRenter tempCarRenter;
  carOwner tempCarOwner;
  int found = 0;

  // Open renters.dat for reading
  fp = fopen("renters.dat", "rb");
  if (fp == NULL)
  {
    fprintf(stderr, "\nError opening file\n");
    exit(1);
  }
  // Open owners.dat for reading
  fp1 = fopen("owners.dat", "rb");
  if (fp1 == NULL)
  {
    fprintf(stderr, "\nError opening file\n");
    exit(1);
  }
  // read file contents till end of file
  while (1)
  {
    fread(&tempCarRenter, sizeof(tempCarRenter), 1, fp);
    if (feof(fp))
    {
      break;
    }
    if (!strcmp(tempCarRenter.Email, Email))
    {
      found = 1;
      RenterLoggedIn = 1;
      carRenter1 = tempCarRenter;
      fclose(fp);
      fclose(fp1);
      return 1;
    }
  }
  while (1)
  {
    fread(&tempCarOwner, sizeof(tempCarOwner), 1, fp1);
    if (feof(fp1))
    {
      break;
    }
    if (!strcmp(tempCarOwner.Email, Email))
    {
      found = 1;
      OwnerLoggedIn = 1;
      carOwner1 = tempCarOwner;
      fclose(fp);
      fclose(fp1);
      return 0;
    }
  }
  if (found == 0)
  {
    printf("Sorry no record found\n");
  }
  // close file
  fclose(fp);
  fclose(fp1);
  return -1;
}

carRenter carRenterDisplay(void)
{

  printf("Name: %s\nPhone number: %s\nEmail: %s\nAge: %d\nPostcode: %d\nPreferred car type: %c\nPreferred transmission type: %c\nRating: %0.2lf (%d Ratings)\n",
         carRenter1.name, carRenter1.phoneNum, carRenter1.Email, carRenter1.age, carRenter1.postCode, carRenter1.prefCarType, carRenter1.prefTransmissionType, carRenter1.rating, carRenter1.ratingAmount);
}

carOwner carOwnerDisplay(void)
{

  printf("Name: %s\nPhone number: %s\nEmail: %s\nAge: %d\nPostcode: %d\nCar price: %d dkk per hour\nCar name: %s\nModel year: %d\nKilometers driven: %d\nTransmission type: %c\nDescription: %s\nRating: %0.2lf (%d ratings)",
         carOwner1.name, carOwner1.phoneNum, carOwner1.Email, carOwner1.age, carOwner1.postCode, carOwner1.price, carOwner1.carName, carOwner1.modelYear, carOwner1.odometer, carOwner1.transmission, carOwner1.CarDescription, carOwner1.rating, carOwner1.ratingAmount);
}

carRenter carRenterEdit(void)
{
  FILE *fp, *fp1;
  carRenter tempCarRenter;
  int found = 0;
  fp = fopen("renters.dat", "rb");
  fp1 = fopen("temp.dat", "wb");
  while (1)
  {
    fread(&tempCarRenter, sizeof(tempCarRenter), 1, fp);
    if (feof(fp))
    {
      break;
    }
    if (!strcmp(tempCarRenter.Email, carRenter1.Email))
    {
      found = 1;
      tempCarRenter = enterCarRenter();
      fwrite(&tempCarRenter, sizeof(tempCarRenter), 1, fp1);
    }
    else
    {
      fwrite(&tempCarRenter, sizeof(tempCarRenter), 1, fp1);
    }
  }
  fclose(fp);
  fclose(fp1);
  if (found == 0)
  {
    printf("Sorry, no record found");
  }
  else
  {
    fp = fopen("renters.dat", "wb");
    fp1 = fopen("temp.dat", "rb");
    while (1)
    {
      fread(&tempCarRenter, sizeof(tempCarRenter), 1, fp1);
      if (feof(fp1))
      {
        break;
      }
      fwrite(&tempCarRenter, sizeof(tempCarRenter), 1, fp);
    }
  }
  fclose(fp);
  fclose(fp1);
}

carOwner carOwnerEdit(void)
{
  FILE *fp, *fp1;
  carOwner tempCarOwner;
  int found = 0;
  fp = fopen("owners.dat", "rb");
  fp1 = fopen("temp.dat", "wb");
  while (1)
  {
    fread(&tempCarOwner, sizeof(tempCarOwner), 1, fp);
    if (feof(fp))
    {
      break;
    }
    if (!strcmp(tempCarOwner.Email, carOwner1.Email))
    {
      found = 1;
      tempCarOwner = enterCarOwner();
      fwrite(&tempCarOwner, sizeof(tempCarOwner), 1, fp1);
    }
    else
    {
      fwrite(&tempCarOwner, sizeof(tempCarOwner), 1, fp1);
    }
  }
  fclose(fp);
  fclose(fp1);
  if (found == 0)
  {
    printf("Sorry, no record found");
  }
  else
  {
    fp = fopen("owners.dat", "wb");
    fp1 = fopen("temp.dat", "rb");
    while (1)
    {
      fread(&tempCarOwner, sizeof(tempCarOwner), 1, fp1);
      if (feof(fp1))
      {
        break;
      }
      fwrite(&tempCarOwner, sizeof(tempCarOwner), 1, fp);
    }
  }
  fclose(fp);
  fclose(fp1);
}

void makeDeal(carOwner tempCarOwner)
{

  FILE *fp;
  tranDet tempTrans;

  // ID's
  tempTrans.transactionID = ((rand() % 1000000) + 100000);
  tempTrans.renterID = carRenter1.ID;
  tempTrans.ownerID = tempCarOwner.ID;

  tempTrans.renterRated = 0;
  tempTrans.ownerRated = 0;
  // emails
  strcpy(tempTrans.renterEmail, carRenter1.Email);
  strcpy(tempTrans.ownerEmail, tempCarOwner.Email);
  // names
  strcpy(tempTrans.renterName, carRenter1.name);
  strcpy(tempTrans.ownerName, tempCarOwner.name);
  strcpy(tempTrans.carName, tempCarOwner.carName);

  // open file
  fp = fopen("transactions.dat", "ab");

  if (fp == NULL)
  {
    fprintf(stderr, "\nError opened file\n");
    exit(1);
  }

  fwrite(&tempTrans, sizeof(tempTrans), 1, fp);

  if (fwrite != 0)
  {
    printf("Transaction completed\n");
  }

  else
  {
    printf("Error writing to file !\n");
  }

  // close file
  fclose(fp);
}

int compare_type_and_price(const void *v1, const void *v2)
{
  const carOwner *p1 = (carOwner *)v1;
  const carOwner *p2 = (carOwner *)v2;
  if (p1->carType < p2->carType)
  {
    return -1;
  }
  else if (p1->carType > p2->carType)
  {
    return 1;
  }
  else if (p1->price < p2->price)
    return -1;
  else if (p1->price > p2->price)
    return 1;
  else
    return 0;
}

void editTransaction(int transID)
{

  FILE *fp;
  FILE *fp1;
  long int pos;
  tranDet tempTrans;

  if (RenterLoggedIn == 1)
  {

    fp = fopen("transactions.dat", "rb+");
    fp1 = fopen("temp.dat", "wb");

    while (1)
    {
      fread(&tempTrans, sizeof(tempTrans), 1, fp);

      if (feof(fp))
      {
        break;
      }

      if (!strcmp(tempTrans.renterEmail, carRenter1.Email))
      {
        pos = ftell(fp);
        tempTrans.renterRated = 1;

        fwrite(&tempTrans, sizeof(tempTrans), 1, fp1);
      }
    }

    // closing files and opening in reversed modes
    fclose(fp);
    fclose(fp1);
    fp1 = fopen("temp.dat", "rb");
    fp = fopen("transactions.dat", "rb+");
    fseek(fp, (pos - sizeof(tempTrans)), SEEK_SET);

    fread(&tempTrans, sizeof(tempTrans), 1, fp1);

    fwrite(&tempTrans, sizeof(tempTrans), 1, fp);

    fclose(fp);
    fclose(fp1);
  }

  if (OwnerLoggedIn == 1)
  {
    fp = fopen("transactions.dat", "rb+");
    fp1 = fopen("temp.dat", "wb");

    while (1)
    {
      fread(&tempTrans, sizeof(tempTrans), 1, fp);

      if (feof(fp))
      {
        break;
      }

      if (!strcmp(tempTrans.ownerEmail, carOwner1.Email))
      {
        pos = ftell(fp);
        tempTrans.ownerRated = 1;

        fwrite(&tempTrans, sizeof(tempTrans), 1, fp1);
      }
    }

    // closing files and opening in reversed modes
    fclose(fp);
    fclose(fp1);
    fp1 = fopen("temp.dat", "rb");
    fp = fopen("transactions.dat", "rb+");
    fseek(fp, (pos - sizeof(tempTrans)), SEEK_SET);

    fread(&tempTrans, sizeof(tempTrans), 1, fp1);

    fwrite(&tempTrans, sizeof(tempTrans), 1, fp);

    fclose(fp);
    fclose(fp1);
  }
}

// Function that enables a user to rate another, if they have had a deal with them
void userRating(char userEmail[], char ans, tranDet tempTrans)
{
  FILE *fp;
  FILE *fp1;
  carRenter tempCarRenter;
  carOwner tempCarOwner;
  int found = 0;
  double rate;
  long int pos;
  // If the person rating is a renter, the person that has to be rated is an owner, therefore open owner.dat

  // read file contents till end of file

  if (ans == 'a')
  {
    fp1 = fopen("temp.dat", "wb");
    fp = fopen("owners.dat", "rb+");

    if (fp == NULL)
    {
      fprintf(stderr, "\nError opening file\n");
      exit(1);
    }

    while (1)
    {
      fread(&tempCarOwner, sizeof(tempCarOwner), 1, fp);

      if (feof(fp))
      {
        break;
      }

      if (!strcmp(tempCarOwner.Email, userEmail))
      {

        found = 1;

        // saves the position of the pointer in the file, so that the position of the found user can be used later
        pos = ftell(fp);

        printf("You have made a deal with %s. What do you wish to rate this user?\n1: bad\n2: not good\n3: decent\n4: good\n5: very good\n", tempCarOwner.name);
        do
        {
          scanf("%lf", &rate);
        } while (rate < 1 && rate > 5);

        tempCarOwner.rating = ((tempCarOwner.rating * tempCarOwner.ratingAmount + rate) / ((double)tempCarOwner.ratingAmount + 1.00));
        tempCarOwner.ratingAmount++;

        fwrite(&tempCarOwner, sizeof(tempCarOwner), 1, fp1);
      }
    }
    fclose(fp);
    fclose(fp1);
  }

  if (ans == 'b')
  {
    fp1 = fopen("temp.dat", "wb");
    fp = fopen("renters.dat", "rb+");

    if (fp == NULL)
    {
      fprintf(stderr, "\nError opening file\n");
      exit(1);
    }

    while (1)
    {
      fread(&tempCarRenter, sizeof(tempCarRenter), 1, fp);

      if (feof(fp))
      {
        break;
      }

      if (!strcmp(tempCarRenter.Email, userEmail))
      {

        found = 1;

        // saves the position of the pointer in the file, so that the position of the found user can be used later
        pos = ftell(fp);

        printf("You have made a deal with %s. What do you wish to rate this user?\n1: bad\n2: not good\n3: decent\n4: good\n5: very good\n", tempCarRenter.name);
        do
        {
          scanf("%lf", &rate);
        } while (rate < 1 && rate > 5);

        tempCarRenter.rating = ((tempCarRenter.rating * tempCarRenter.ratingAmount + rate) / ((double)tempCarRenter.ratingAmount + 1.00));
        tempCarRenter.ratingAmount++;

        fwrite(&tempCarRenter, sizeof(tempCarRenter), 1, fp1);
      }
    }
    fclose(fp);
    fclose(fp1);
  }

  if (ans == 'a' && found == 1)
  {

    fp = fopen("owners.dat", "rb+");

    // moves the file pointer to the desired user
    fseek(fp, (pos - sizeof(tempCarOwner)), SEEK_SET);

    fp1 = fopen("temp.dat", "rb");

    fread(&tempCarOwner, sizeof(tempCarOwner), 1, fp1);

    fwrite(&tempCarOwner, sizeof(tempCarOwner), 1, fp);

    editTransaction(tempTrans.transactionID);

    fclose(fp);
    fclose(fp1);
  }

  else if (ans == 'b' && found == 1)
  {

    fp = fopen("renters.dat", "rb+");

    // moves the file pointer to the desired user
    fseek(fp, (pos - sizeof(tempCarRenter)), SEEK_SET);

    fp1 = fopen("temp.dat", "rb");

    fread(&tempCarRenter, sizeof(tempCarRenter), 1, fp1);

    fwrite(&tempCarRenter, sizeof(tempCarRenter), 1, fp);

    editTransaction(tempTrans.transactionID);

    fclose(fp);
    fclose(fp1);
  }

  else if (found == 0)
  {

    printf("No unrated user in your transaction!");
  }
}

// Function that finds transactions for a user
void findTransaction(void)
{

  carOwner dealOwner;
  carOwner tempOwner;
  carRenter dealRenter;
  carRenter tempRenter;
  FILE *fp;
  tranDet tempTrans;
  tranDet foundTrans;
  bool found;
  char ans;
  char ans2;

  if (RenterLoggedIn == 1)
  {
    ans = 'a';
  }

  else if (OwnerLoggedIn == 1)
  {
    ans = 'b';
  }

  fp = fopen("transactions.dat", "rb");

  if (fp == NULL)
  {
    fprintf(stderr, "\nError opening file\n");
    exit(1);
  }

  // read file contents till end of file
  while (1)
  {

    fread(&tempTrans, sizeof(tempTrans), 1, fp);

    if (feof(fp))
    {
      break;
    }

    if (ans == 'a' && (!strcmp(tempTrans.renterEmail, carRenter1.Email)) && tempTrans.renterRated == 0)
    {

      found = 1;
      foundTrans = tempTrans;
    }

    else if (ans == 'b' && (!strcmp(tempTrans.ownerEmail, carOwner1.Email)) && tempTrans.ownerRated == 0)
    {

      found = 1;
      foundTrans = tempTrans;
    }
  }

  if (found == 0)
  {
    printf("\nNo unrated deals found");
  }

  // close file
  fclose(fp);

  if (found == 1)
  {

    fflush(stdin);
    if (ans == 'a')
    {
      printf("\nYou have made a deal with the transaction details:\nID: %d\nCounter Part Name: %s\nCounter Part Email: %s\nCar name: %s\nDo you wish to rate this deal?\ny: yes\nn: no\n",
             foundTrans.transactionID, foundTrans.ownerName, foundTrans.ownerEmail, foundTrans.carName);
    }
    else if (ans == 'b')
    {
      printf("\nYou have made a deal with the transaction details:\nID: %d\nCounter Part Name: %s\nCounter Part Email: %s\nDo you wish to rate this deal?\ny: yes\nn: no\n",
             foundTrans.transactionID, foundTrans.renterName, foundTrans.renterEmail);
    }
    do
    {

      scanf("%c", &ans2);
      printf("\n");

      if (ans == 'a' && ans2 == 'y')
      {
        userRating(foundTrans.ownerEmail, ans, foundTrans);
      }

      else if (ans == 'b' && ans2 == 'y')
      {
        userRating(foundTrans.renterEmail, ans, foundTrans);
      }

      else if (ans2 == 'n')
      {
        exit(1);
      }

    } while (ans2 != 'y' && ans2 != 'n');
  }
}

void carSelect(carOwner arrCars[])
{
  FILE *fp;
  carOwner tempCarOwner;
  int i = 0, number_of_cars, choice, rent_car, number_of_hours;
  fp = fopen("owners.dat", "rb");
  if (fp == NULL)
  {
    fprintf(stderr, "\nError opening file\n");
    exit(1);
  }
  while (1)
  {
    fread(&tempCarOwner, sizeof(tempCarOwner), 1, fp);
    if (feof(fp))
    {
      number_of_cars = i;
      break;
    }

    arrCars[i] = tempCarOwner;
    i++;
  }
  qsort(arrCars, number_of_cars, sizeof(carOwner), compare_type_and_price);
  do
  {
    for (i = 0; i < number_of_cars; i++)
    {
      printf("\n%d.", i + 1);
      printf("\nPrice: %d\nCar name: %s\nCar type: %c\nModel year: %d\nOdometer: %d\nTransmission type: %c\nCar description: %s\nCar is located in: %d\n",
             arrCars[i].price, arrCars[i].carName, arrCars[i].carType, arrCars[i].modelYear, arrCars[i].odometer, arrCars[i].transmission, arrCars[i].CarDescription, arrCars[i].postCode);
    }
    printf("\nChoose which car you would like to rent: ");
    scanf(" %d", &choice);
    choice--;
    printf("\nPrice: %d\nCar name: %s\nCar type: %c\nModel year: %d\nOdometer: %d\nTransmission type: %c\nCar description: %s\nCar is located in: %d\n",
           arrCars[choice].price, arrCars[choice].carName, arrCars[choice].carType, arrCars[choice].modelYear, arrCars[choice].odometer, arrCars[choice].transmission, arrCars[choice].CarDescription, arrCars[choice].postCode);
    printf("\nWould you like to rent this car? (1 = Yes, 2 = No): ");
    scanf(" %d", &rent_car);

    if (rent_car == 1)
    {
      printf("\nHow many hours would you like to rent this car? ");
      scanf(" %d", &number_of_hours);
      printf("You successfully chose %s\n", arrCars[choice].carName);
      printf("It will cost you %d dkk to rent this car for %d hours\n", arrCars[choice].price * number_of_hours, number_of_hours);
      makeDeal(arrCars[choice]);
      findTransaction();
    }
  } while (rent_car != 1);

  fclose(fp);
}

void show_rentals(void)
{
  FILE *fp;
  tranDet tempTrans;
  int n = 1;

  fp = fopen("transactions.dat", "rb");

  printf("Here is your rental history: \n");

  while (1)
  {
    fread(&tempTrans, sizeof(tempTrans), 1, fp);
    if (feof(fp))
    {
      break;
    }
    if (!strcmp(carOwner1.Email, tempTrans.ownerEmail))
    {
      printf("%d.\n", n++);
      printf("Transaction ID: %d\nRenter's name: %s\nRenter's email: %s\n", tempTrans.transactionID, tempTrans.renterName, tempTrans.renterEmail);
    }
  }
}