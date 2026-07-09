#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "viewreserveroom.h"

// incase the user enter will all lower case or upper case letter
void fix_type(char type[])
{
    for (int i = 0; type[i] != '\0'; i++)
    {
        type[i] = tolower((unsigned char)type[i]);
    }

    type[0] = toupper((unsigned char)type[0]);
}

// gets the prices from the header files
float get_rate(char type[])
{
    if (strcmp(type, "Single") == 0)
        return RATE_SINGLE;
    if (strcmp(type, "Double") == 0)
        return RATE_DOUBLE;
    if (strcmp(type, "Family") == 0)
        return RATE_FAMILY;

    return 0;
}

/*allows the customer to be able to book the room*/

void book_room(struct Room rooms[], int total, char name[], char phone[], char email[])
{
    char type[15];
    int numbers;
    int nights;
    int position;

    // ask the user what type of room do they want
    printf("Enter a room type(Single / Double / Family): ");
    scanf("%14s", type); // FIX: width limit to prevent overflowing type[15]
    while (getchar() != '\n')
        ;

    // fix the user input
    fix_type(type);

    // validates the room type
    if (strcmp(type, "Single") != 0 &&
        strcmp(type, "Double") != 0 &&
        strcmp(type, "Family") != 0)
    {
        printf("Invalid room type. Please enter Single, Double, or Family.\n");
        printf("==============================\n");
        return;
    }

    // display all the available rooms
    display_available_room(rooms, total, type);

    // ask which room does the user wants
    printf("Enter a room number: ");
    scanf("%d", &numbers);
    while (getchar() != '\n')
        ;

    // find the room in the array
    position = find_room(rooms, total, numbers);

    // check if the room actually exist
    if (position == -1)
    {
        printf("Room %d does not exist.\n", numbers);
        printf("==============================\n");
        return;
    }

    // validates wether the room is the type of room that the customer asked for
    if (strcmp(rooms[position].type, type) != 0)
    {
        printf("Room %d is not a room in the %s category.\n", numbers, type);
        printf("==============================\n");
        return;
    }

    // check whether the room they picked is available or not
    if (rooms[position].status != AVAILABLE)
    {
        printf("Room %d is not available for booking.\n", numbers);
        printf("==============================\n");
        return;
    }

    // FIX: previously used "goto loop_start" to validate nights, but the
    // scanf was outside the label, so an invalid entry (e.g. 0, -5, 31)
    // would loop back to the same check forever without ever asking
    // again - an infinite print loop with no way to recover. Now the
    // prompt and scanf are both inside a do/while loop that repeats
    // until a valid value (1-30) is entered.
    do
    {
        printf("Enter the amount of nights you are staying for(1-30): ");
        scanf("%d", &nights);
        while (getchar() != '\n')
            ;

        if (nights < 1 || nights > 30)
        {
            printf("Please enter the correct amount of nights(1-30).\n");
            printf("==============================\n");
        }
    } while (nights < 1 || nights > 30);

    // saves the information
    rooms[position].status = RESERVED;
    strcpy(rooms[position].guest, name);
    strcpy(rooms[position].phone, phone);
    strcpy(rooms[position].email, email);
    rooms[position].nights = nights;

    // persist the updated room data to file
    save_rooms_to_file(rooms, total);

    // print the confirmation of the bookings
    printf("==============================\n");
    printf("   Booking Confirmed!\n");
    printf("==============================\n");
    printf("Guest: %s\n", name);
    printf("Tel: %s\n", phone);
    printf("Email: %s\n", email);
    printf("Floor: %d\n", rooms[position].floors);
    printf("Room: %d (%s)\n", rooms[position].numbers, rooms[position].type);
    printf("Night: %d\n", nights);
    printf("Rate: %.2f\n", rooms[position].price);
    printf("Total: %.2f\n", rooms[position].price * nights);
    printf("==============================\n\n");
}