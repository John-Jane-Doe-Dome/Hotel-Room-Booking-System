#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "viewreserveroom.h"

/*
 this is the setup of the rooms
 each floors has 10 rooms
 the first 5 rooms will be single
 the next 3 rooms will be double
 the last 2 is fami
*/

void init_rooms(struct Room rooms[], int *total)
{
    int floors;
    int slot;
    *total = 0;

    // go through each floors
    for (floors = 1; floors <= FLOORS; floors++)
    {
        // go through each room in the floor
        for (slot = 1; slot <= ROOMS_PER_FLOORS; slot++)
        {
            rooms[*total].numbers = (floors * 100) + slot;
            rooms[*total].floors = floors;

            // rooms type
            // the . is for it to call the variables from the data structures
            if (slot <= 5)
            {
                strcpy(rooms[*total].type, "Single");
                rooms[*total].price = RATE_SINGLE;
            }
            else if (slot <= 8)
            {
                strcpy(rooms[*total].type, "Double");
                rooms[*total].price = RATE_DOUBLE;
            }
            else
            {
                strcpy(rooms[*total].type, "Family");
                rooms[*total].price = RATE_FAMILY;
            }
            rooms[*total].status = AVAILABLE;
            rooms[*total].guest[0] = '\0';
            rooms[*total].phone[0] = '\0';
            rooms[*total].email[0] = '\0';
            rooms[*total].nights = 0;

            (*total)++;
        }
    }
}

/*
    declaring the room status
*/

char *status_word(int status)
{
    if (status == AVAILABLE)
    {
        return "Available";
    }
    if (status == RESERVED)
    {
        return "Reserved";
    }
    if (status == OCCUPIED)
    {
        return "Occupied";
    }
    return "Unknown";
}

/*
    displaying all rooms in a simple table format
*/

void display_all_rooms(struct Room rooms[], int total)
{
    printf("---------------------------------------\n");
    printf("%-6s %-6s %-8s %-12s %-20s\n", "Room", "Floor", "Type", "Status", "Guest");
    printf("---------------------------------------\n");
    for (int i = 0; i < total; i++)
    {
        printf("%-6d %-6d %-8s %-12s",
               rooms[i].numbers,
               rooms[i].floors,
               rooms[i].type,
               status_word(rooms[i].status));
        // only shows a name if the room is occupied
        if (rooms[i].status == AVAILABLE)
        {
            printf("-\n");
        }
        else
        {
            printf("%s\n", rooms[i].guest);
        }
    }
    printf("---------------------------------------\n\n");
    printf("==============================\n");
}

//display all rooms and info for admin to see
void display_all_rooms_for_admin(struct Room rooms[], int total, char name[], char phone[], char email[], int nights)
{
    printf("-----------------------------------------------------------------------------------------------------------------------\n");
    printf("%-6s %-6s %-8s %-12s %-20s %-20s %-30s %-6s\n", "Room", "Floor", "Type", "Status", "Guest", "Phone", "Email", "Nights");
    printf("-----------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < total; i++)
    {
        printf("%-6d %-6d %-8s %-12s",
               rooms[i].numbers,
               rooms[i].floors,
               rooms[i].type,
               status_word(rooms[i].status));
        // only shows a name, phone number, and email if the room is occupied
        if (rooms[i].status == AVAILABLE)
        {
            printf("%-20s %-20s %-30s %-6d\n", "-", "-", "-", 0);
        }
        else
        {
            printf("%-20s %-20s %-30s %-6d\n", rooms[i].guest, rooms[i].phone, rooms[i].email, rooms[i].nights);
        }
    }
    printf("---------------------------------------\n\n");
    printf("==============================\n");
}

/*
    print information of the room that match the type,
    and are available to book
*/

void display_available_room(struct Room rooms[], int total, char type[])
{
    int found = 0;
    printf("Available %s rooms: \n", type);
    printf("-----------------------\n");

    for (int i = 0; i < total; i++)
    {
        // skips the room if its the wrong type
        if (strcmp(rooms[i].type, type) != 0)
            continue;

        // skips the room if its not available
        if (rooms[i].status != AVAILABLE)
            continue;

        printf("Room %d\n", rooms[i].numbers);
        found++;
    }
    if (found == 0)
        printf("No %s rooms currently available.\n", type);

    printf("-----------------------\n\n");
}

/*
    search for the room by its number
*/
int find_room(struct Room rooms[], int total, int numbers)
{
    for (int i = 0; i < total; i++)
    {
        if (rooms[i].numbers == numbers)
            return i; // finds it and return its position
    }
    return -1; // doesn't find anything
<<<<<<< HEAD
}
=======
<<<<<<< HEAD
}

//admin set up the hotel at once:
//- input the number of floors
//- input how many single rooms, double rooms, and family rooms per floor and price for each type
void setup_hotel(struct Room rooms[], int *total)
{
    int numfloors, singleCount, doubleCount, familyCount,totalRoom;
    float singlePrice, doublePrice, familyPrice;
    printf("---------------HOTEL SETUP----------------\n");
    printf("Enter the number of floors: ");
    scanf("%d", &numfloors);
    while (getchar() != '\n');

    // FIX #6: validate numfloors before it's used as a divisor below
    if (numfloors < 1)
    {
        printf("Error: Number of floors must be at least 1.\n");
        return;
    }

    printf("Enter the number of single rooms per floor: ");
    scanf("%d", &singleCount);
    while (getchar() != '\n');
    printf("Enter the price for single rooms: ");
    scanf("%f", &singlePrice);
    while (getchar() != '\n');

    printf("Enter the number of double rooms per floor: ");
    scanf("%d", &doubleCount);
    while (getchar() != '\n');
    printf("Enter the price for double rooms: ");
    scanf("%f", &doublePrice);
    while (getchar() != '\n');

    printf("Enter the number of family rooms per floor: ");
    scanf("%d", &familyCount);
    while (getchar() != '\n');
    printf("Enter the price for family rooms: ");
    scanf("%f", &familyPrice);
    while (getchar() != '\n');

    if (singleCount < 0 || doubleCount < 0 || familyCount < 0)
    {
        printf("Error: Number of rooms cannot be negative.\n");
        return;
    }

    if (singlePrice <= 0 || doublePrice <= 0 || familyPrice <= 0)
    {
        printf("Error: Price must be greater than zero.\n");
        return;
    }

    totalRoom = singleCount + doubleCount + familyCount;

    if (totalRoom < 1) {
        printf("Error: Total number of rooms per floor must be at least 1.\n");
        return;
    }
    if (totalRoom > MAX_ROOMS) {
        printf("Error: Total number of rooms per floor exceeds the maximum limit.\n");
        return;
    }

    int roomPerfloor = (totalRoom + numfloors - 1) / numfloors; // Calculate rooms per floor
    int index = 0;

    /* Generate Single rooms */
    for (int i = 0; i < singleCount; i++, index++) {
        int floor = (index / roomPerfloor) + 1;
        int slot = (index % roomPerfloor) + 1;
        rooms[index].numbers = (floor * 100) + slot;
        rooms[index].floors = floor;
        strcpy(rooms[index].type, "Single");
        rooms[index].price = singlePrice;
        rooms[index].status = AVAILABLE;
        rooms[index].guest[0] = '\0';
        rooms[index].phone[0] = '\0';
        rooms[index].email[0] = '\0';
        rooms[index].nights = 0;
    }

    /* Generate Double rooms */
    for (int i = 0; i < doubleCount; i++, index++) {
        int floor = (index / roomPerfloor) + 1;
        int slot = (index % roomPerfloor) + 1;
        rooms[index].numbers = (floor * 100) + slot;
        rooms[index].floors = floor;
        strcpy(rooms[index].type, "Double");
        rooms[index].price = doublePrice;
        rooms[index].status = AVAILABLE;
        rooms[index].guest[0] = '\0';
        rooms[index].phone[0] = '\0';
        rooms[index].email[0] = '\0';
        rooms[index].nights = 0;
    }

    /* Generate Family rooms */
    for (int i = 0; i < familyCount; i++, index++) {
        int floor = (index / roomPerfloor) + 1;
        int slot = (index % roomPerfloor) + 1;
        rooms[index].numbers = (floor * 100) + slot;
        rooms[index].floors = floor;
        strcpy(rooms[index].type, "Family");
        rooms[index].price = familyPrice;
        rooms[index].status = AVAILABLE;
        rooms[index].guest[0] = '\0';
        rooms[index].phone[0] = '\0';
        rooms[index].email[0] = '\0';
        rooms[index].nights = 0;
    }
    *total = totalRoom;

    save_rooms_to_file(rooms, *total);
    printf("Hotel setup completed successfully!\n");
}

void edit_room(struct Room rooms[], int total)
{
    int roomNum, idx;

    display_all_rooms(rooms, total);

    printf("Enter the room number to edit: ");
    scanf("%d", &roomNum);
    while (getchar() != '\n');

    idx = find_room(rooms, total, roomNum);   /* reuse your existing search function */

    if (idx == -1)
    {
        printf("Room number %d not found.\n", roomNum);
        return;
    }

    printf("Current floor: %d, Current price: %.2f\n", rooms[idx].floors, rooms[idx].price);

    printf("Enter new floor: ");
    scanf("%d", &rooms[idx].floors);
    while (getchar() != '\n');

    printf("Enter new price: ");
    scanf("%f", &rooms[idx].price);
    while (getchar() != '\n');

    save_rooms_to_file(rooms, total);
    printf("Room %d updated successfully.\n", rooms[idx].numbers);
}

// FIX #8: admin_menu now takes total by reference so changes made by
// setup_hotel (e.g. re-running hotel setup) propagate back to main().
void admin_menu(struct Room rooms[], int *total)
{
    int choice;

    do
    {
        printf("\n------------ADMIN MENU------------\n");
        printf("1. View rooms\n2. Set up hotel\n3. Edit room (floor/price)\n4. Exit to main menu\n");
        printf("------------------------------------\n");
        printf("Please pick an action (1-4): ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice)
        {
        case 1:
            display_all_rooms(rooms, *total);
            break;
        case 2:
            setup_hotel(rooms, total);
            break;
        case 3:
            edit_room(rooms, *total);
            break;
        case 4:
            printf("Exiting admin menu.\n");
            break;
        default:
            printf("Invalid choice.\n");
            break;
        }
    } while (choice != 4);
}

void save_rooms_to_file(struct Room rooms[], int total)
{
    FILE *file = fopen("rooms.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }
    for (int i = 0; i < total; i++)
    {
        fprintf(file, "%d %d %s %d %s %s %s %d %.2f\n",
                rooms[i].numbers,
                rooms[i].floors,
                rooms[i].type,
                rooms[i].status,
                strlen(rooms[i].guest) > 0 ? rooms[i].guest : "N/A",
                strlen(rooms[i].phone) > 0 ? rooms[i].phone : "N/A",
                strlen(rooms[i].email) > 0 ? rooms[i].email : "N/A",
                rooms[i].nights,
                rooms[i].price);
    }
    fclose(file);
}

int load_rooms_from_file(struct Room rooms[], int *total)
{
    // FIX #2: read from the same file that save_rooms_to_file() writes to
    FILE *fp = fopen("rooms.txt", "r");
    if (fp == NULL) {
        *total = 0;
        return 0;
    }

    *total = 0;
    // FIX #3: the scan format/argument order now matches exactly what
    // save_rooms_to_file() writes:
    // numbers floors type status guest phone email nights price
    while (*total < MAX_ROOMS && fscanf(fp, "%d %d %14s %d %99s %19s %99s %d %f",
                &rooms[*total].numbers,
                &rooms[*total].floors,
                rooms[*total].type,
                &rooms[*total].status,
                rooms[*total].guest,
                rooms[*total].phone,
                rooms[*total].email,
                &rooms[*total].nights,
                &rooms[*total].price) == 9)
    {
        // FIX (minor/style #3): save_rooms_to_file() writes "N/A" for empty
        // fields, so check for "N/A" here (previously checked for "-", which
        // never matched, leaving the literal text "N/A" in loaded records).
        if (strcmp(rooms[*total].guest, "N/A") == 0) rooms[*total].guest[0] = '\0';
        if (strcmp(rooms[*total].phone, "N/A") == 0) rooms[*total].phone[0] = '\0';
        if (strcmp(rooms[*total].email, "N/A") == 0) rooms[*total].email[0] = '\0';
        (*total)++;
    }
    fclose(fp);
    return 1;
=======
>>>>>>> Bot
}
>>>>>>> 840af7bc9ca6f0c292cf1cbe424375f388c4f22b
