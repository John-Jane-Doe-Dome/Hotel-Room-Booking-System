#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "viewreserveroom.h"


// admin function
// FIX: total is now int * so setup_hotel's update to the room count
// actually propagates back to main() instead of being lost when this
// function returns (it was previously passed by value).
void admin_menu(struct Room rooms[], int *total)
{
    int choice;

    do
    {
        printf("\n------------ADMIN MENU------------\n");
        printf("1. View rooms\n2. Set up hotel\n3. Edit room (room number/type/price)\n4. Exit the program\n");
        printf("------------------------------------\n");
        printf("Please pick an action (1-4): ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice)
        {
        case 1:
            //display rooms and customer information for the admin
            display_all_rooms_for_admin(rooms, *total);
            break;
        case 2:
            // admin set up new hotel
            setup_hotel(rooms, total);
            break;
        case 3:
            // admin edit a room information (room number/type/price)
            edit_room(rooms, *total);
            break;
        case 4:
            // exit the entire program
            printf("\nExiting the program, thank you for visiting!\n");
            exit(0);
        default:
            printf("Invalid choice.\n");
            break;
        }
    } while (choice != 4);
}

void save_rooms_to_file(struct Room rooms[], int total)
{ // save the room information to rooms.txt
    FILE *file = fopen("rooms.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }
    for (int i = 0; i < total; i++)
    {
        // FIX: guest names are allowed to contain spaces (see
        // ValidateName in register.c), but this file is parsed back
        // with fscanf's %s, which treats whitespace as a field
        // separator. A name like "Saroeun Sothy" would get split
        // across the guest/phone/email columns on load, corrupting
        // every field after it. Escape spaces as underscores before
        // writing so each guest name stays a single %s token; loading
        // reverses this. '_' is safe because ValidateName never
        // allows it in a real name.
        char guest_escaped[100];
        if (strlen(rooms[i].guest) > 0)
        {
            size_t j;
            for (j = 0; rooms[i].guest[j] != '\0'; j++)
                guest_escaped[j] = (rooms[i].guest[j] == ' ') ? '_' : rooms[i].guest[j];
            guest_escaped[j] = '\0';
        }
        else
        {
            strcpy(guest_escaped, "-");
        }

        fprintf(file, "%d %d %s %d %.2f %s %s %s %d\n",
                rooms[i].numbers,
                rooms[i].floors,
                rooms[i].type,
                rooms[i].status,
                rooms[i].price,
                guest_escaped,
                strlen(rooms[i].phone) > 0 ? rooms[i].phone : "-",
                strlen(rooms[i].email) > 0 ? rooms[i].email : "-",
                rooms[i].nights);
    }
    fclose(file);
}

int load_rooms_from_file(struct Room rooms[], int *total)
{ // load the last saved room information from rooms.txt
    FILE *fp = fopen("rooms.txt", "r");
    if (fp == NULL) {
        *total = 0;
        return 0;
    }

    *total = 0;
    while (*total < MAX_ROOMS && fscanf(fp, "%d %d %14s %d %f %99s %19s %99s %d",
                &rooms[*total].numbers,
                &rooms[*total].floors,
                rooms[*total].type,
                &rooms[*total].status,
                &rooms[*total].price,
                rooms[*total].guest,
                rooms[*total].phone,
                rooms[*total].email,
                &rooms[*total].nights) == 9)
    {
        if (strcmp(rooms[*total].guest, "-") == 0)
        {
            rooms[*total].guest[0] = '\0';
        }
        else
        {
            // FIX: reverse the space->underscore escaping done in
            // save_rooms_to_file so the guest name displays correctly.
            for (int k = 0; rooms[*total].guest[k] != '\0'; k++)
            {
                if (rooms[*total].guest[k] == '_')
                    rooms[*total].guest[k] = ' ';
            }
        }
        if (strcmp(rooms[*total].phone, "-") == 0) rooms[*total].phone[0] = '\0';
        if (strcmp(rooms[*total].email, "-") == 0) rooms[*total].email[0] = '\0';
        (*total)++;
    }
    fclose(fp);
    return 1;
}

//admin set up the hotel at once:
//- input the number of floors
//- input how many single rooms, double rooms, and family rooms per floor and price for each type
void setup_hotel(struct Room rooms[], int *total)
{
    int numfloors, singleCount, doubleCount, familyCount, totalRoom;
    float singlePrice, doublePrice, familyPrice;
    printf("---------------HOTEL SETUP----------------\n");
    printf("Enter the number of floors: ");
    scanf("%d", &numfloors);
    while (getchar() != '\n');

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

    if (singlePrice <= 0 || doublePrice <= 0 || familyPrice <= 0)
    {
        printf("Error: Price must be greater than zero/Number of rooms cannot be negative.\n");
        return;
    }

    if (singleCount < 0 || doubleCount < 0 || familyCount < 0 || numfloors < 1)
    {
        printf("Error: Floors must be at least 1 and room counts cannot be negative.\n");
        return;
    }

    int roomPerfloor = singleCount + doubleCount + familyCount; // Calculate rooms per floor
    totalRoom = roomPerfloor * numfloors; // Calculate total rooms

    if (totalRoom < 1) {
        printf("Error: Total number of rooms per floor must be at least 1.\n");
        return;
    }
    if (totalRoom > MAX_ROOMS) {
        printf("Error: Total number of rooms per floor exceeds the maximum limit.\n");
        return;
    }

    /* Generate the new hotel */
    int floors;
    int slot;
    int index = 0;
    for (floors = 1; floors <= numfloors; floors++)
    {
        // go through each room in the floor
        for (slot = 1; slot <= roomPerfloor; slot++)
        {
            rooms[index].numbers = (floors * 100) + slot;
            rooms[index].floors = floors;

            // rooms type
            // the . is for it to call the variables from the data structures
            if (slot <= singleCount)
            {
                strcpy(rooms[index].type, "Single");
                rooms[index].price = singlePrice;
            }
            else if (slot <= singleCount + doubleCount)
            {
                strcpy(rooms[index].type, "Double");
                rooms[index].price = doublePrice;
            }
            else
            {
                strcpy(rooms[index].type, "Family");
                rooms[index].price = familyPrice;
            }
            rooms[index].status = AVAILABLE;
            rooms[index].guest[0] = '\0';
            rooms[index].phone[0] = '\0';
            rooms[index].email[0] = '\0';
            rooms[index].nights = 0;

            index++;
        }
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

    idx = find_room(rooms, total, roomNum);   /* reuse existing search function */

    if (idx == -1)
    {
        printf("Room number %d not found.\n", roomNum);
        return;
    }

    printf("Current room: %d, Current type: %s, Current price: %.2f\n", rooms[idx].numbers, rooms[idx].type, rooms[idx].price);

    printf("Enter the new room number (Re-enter the room number if you don't want to change it): ");
    scanf("%d", &rooms[idx].numbers);
    while (getchar() != '\n');

    // FIX: replaced goto with a proper do/while loop that re-prompts
    // for the type on invalid input (goto only re-ran the validation
    // check, not the scanf, but here we scan inside the loop body).
    do
    {
        printf("Enter the new room type (Re-enter the room type if you don't want to change it, with proper capitalization): ");
        scanf("%14s", rooms[idx].type);
        while (getchar() != '\n');

        if (strcasecmp(rooms[idx].type, "single") != 0 &&
            strcasecmp(rooms[idx].type, "double") != 0 &&
            strcasecmp(rooms[idx].type, "family") != 0)
        {
            printf("Invalid room type. Please enter Single, Double, or Family.\n");
        }
        else
        {
            break;
        }
    } while (1);

    printf("Enter the new price (Re-enter the price if you don't want to change it): ");
    scanf("%f", &rooms[idx].price);
    while (getchar() != '\n');

    save_rooms_to_file(rooms, total);
    printf("Room %d updated successfully.\n", rooms[idx].numbers);
}