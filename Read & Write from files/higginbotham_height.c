//Foster Higginbotham's File.
//This project will demonstrate the ability to write and apply C code that can read and write from files. 

#include <stdio.h>
#include <stdlib.h>

int menu_choice();
void enter_data();
void get_total();

int main(void) {

  /*
    We can start with our text file. If it does not exist, then we need to make it. Otherwise, just continue on.
  */

  FILE *file;
  if (!(fopen("heightData.txt", "r"))) {
    file = fopen("heightData.txt", "w");
    fclose(file);
  }

  /*
    From here, we can start with our menu. We put the code in an infinite loop by checking if 0 is equal to 0,
    which it is. The menu choices are based on the assignment.
  */

  do
  {
    int choice = menu_choice();

    if (choice == 1) {
      enter_data(file);
    }
    else if (choice == 2) {
      get_total(file);
    }
    else if (choice == -1 || choice == 0) {
      printf("Goodbye for now.\n");
      break;
    }
  } while (0 == 0);

  return 0;
}

/*
  This function prompts the user to enter his choice for the menu. This is separately done to make the main more organized.
  We can return the users choice if they enter a valid choice, if not, we are returned zero. Note this will return 0 if you enter
  a number not in bounds, or if you enter a string since atoi() will return 0.
  Atoi() will be used a lot since it fits what we are doing, making strings into integers. It is also good since it will
  automatically check if a string has been entered and return 0 if so.
*/

int menu_choice() {
  char input[12];
  int choice;

  printf("Welcome to the Athlete Height Tally Tool.\nWhat do you want to do?\n1 = Enter Height Data\n2 = Get Height Average(s)\n-1 = Quit\n\n");

  scanf("%s", input);
  choice = atoi(input);

  if (choice == 1 || choice == 2 || choice == -1) {
    return choice;
  }
  return 0;
}

/*
  This function serves to enter data into the file pointer passed to it. We enter a infinite for loop and can escape if we
  receive a -1 from our user, or a zero from our atoi(). We check for a valid sport requested, then open our file for appending.
  Note it is important to not open for writing since this will overwrite our file. From here, we can enter another infinite for
  loop to repeatedly enter values for that sport, and break if we reach a -1 from our user or a 0 from atoi().
*/

void enter_data(FILE *f) {
  int sport;
  char input[12];

  while (0 == 0) {
    printf("Writing Data...\nFor which sport do you want to save data?\n1 = Arm Wrestling\n2 = Ostrich Racing\n3 = Extreme Ironing\n-1 = Quit\n\n");

    scanf("%s", input);
    sport = atoi(input);

    if (sport == 1 || sport == 2 || sport == 3)
    {
      f = fopen("heightData.txt", "a");

      while (0 == 0)
      {
        printf("Enter a value (-1 = quit)\n\n");
        scanf("%s", input);
        int val = atoi(input);

        if (val == -1 || val == 0) {
          fclose(f);
          break;
        }

        else {
          fprintf(f, "%d %d\n", sport, val);
        }
      }
    }

    else if (sport == -1 || sport == 0)
    {
      return;
    }
  }
}

/*
  This function gets the averages based on the input from the user. We enter an infinite for loop asking for the sport requested.
  From there, we can open our file to read from and start reading input based on sport. We can accumulate the total and divide by
  our count to get our average to return to the user.
*/

void get_total(FILE *f) {
  int sport, local_sport, local_height;;
  char input[12];

  while (0 == 0) {
    printf("Reading Data...\nFor which sport do you want have the average?\n0 = All\n1 = Arm Wrestling\n2 = Ostrich Racing\n3 = Extreme Ironing\n-1 = Quit\n\n");

    scanf("%s", input);
    sport = atoi(input);

    f = fopen("heightData.txt", "r");

    if (sport == 0 || sport == 1 || sport == 2 || sport == 3)
    {
      int total = 0, count = 0;
      while(fgets(input, 128, f) != NULL)
      {
        sscanf(input, "%d %d", &local_sport, &local_height);
        if (sport == local_sport) {
          total += local_height;
          count++;
        }
        else if (sport == 0) {
          total += local_height;
          count++;
        }
      }
      printf("The average height is: %0.2f\n", (double) total/(double) count);
    }
    else
    {
      return;
    }
  }
}
