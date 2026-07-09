#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "register.h"
#include "viewreserveroom.h"
// finds the room
void check_in(struct Room rooms[], int total, char name[], char phone[], char email[])
{
    int numbers;
    int position;
    printf("Enter the room number you have booked: ");
    scanf("%d", &numbers);
    while (getchar() != '\n')
        ;

    position = find_room(rooms, total, numbers);

    if (position == -1)
    {
        printf("Room %d does not exist.\n", numbers);
        printf("==============================\n");
        return;
    }

    // FIX: previously OCCUPIED and RESERVED were both accepted here,
    // meaning an already-checked-in guest could "check in" again and
    // get a misleading second "Check-in successful!" message with no
    // actual state change. Now OCCUPIED is explicitly rejected first.
    if (rooms[position].status == OCCUPIED)
    {
        printf("Room %d is already checked in.\n", numbers);
        printf("==============================\n");
        return;
    }

    if (rooms[position].status != RESERVED)
    {
        printf("Room %d has not been booked.\n", numbers);
        printf("==============================\n");
        return;
    }

    // verify that the person checking in matches the registered booking
    if (strcasecmp(name, rooms[position].guest) != 0 ||
        strcmp(phone, rooms[position].phone) != 0 ||
        strcasecmp(email, rooms[position].email) != 0)
    {
        printf("\nVerification failed. Your registered details do not match this booking.\n");
        printf("==============================\n");
        return;
    }

    rooms[position].status = OCCUPIED;

    // persist the updated room data to file
    save_rooms_to_file(rooms, total);

    // tell the user they have been successfully checked-in
    printf("==============================\n");
    printf("   Check-in successful!\n");
    printf("==============================\n");
    printf("Guest: %s\n", rooms[position].guest);
    printf("Tel: %s\n", rooms[position].phone);
    printf("Email: %s\n", rooms[position].email);
    printf("Floor: %d\n", rooms[position].floors);
    printf("Room: %d (%s)\n", rooms[position].numbers, rooms[position].type);
    printf("Night: %d\n", rooms[position].nights);
    printf("==============================\n");
    printf("Please enjoy your stay %s!\n\n", rooms[position].guest);
    printf("==============================\n");
}