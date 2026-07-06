#ifndef VIEWRESERVEROOM_H
#define VIEWRESERVEROOM_H

// Total rooms and prices
#define FLOORS 3
#define ROOMS_PER_FLOORS 10
#define MAX_ROOMS 200
#define MAX_BOOKINGS 100
#define RATE_SINGLE 50.00
#define RATE_DOUBLE 80.00
#define RATE_FAMILY 150.00

// status of rooms
#define AVAILABLE 0
#define RESERVED 1
#define OCCUPIED 2

#define Admin_Password "1234" //Admin Password

// room information
struct Room
{
    int numbers;     // room numbers
    int floors;      // floors numbers
    char type[15];   // room type
    int status;      // room status
    char guest[100]; // guest name when book
    char phone[20];  // guest phone number when book
    char email[100]; // guest email when book
    int nights;      // amount of nights
    float price;
};

// booking records
struct bookings
{
    int id;           // booking ID
    int room_numbers; // room booked by customer
    char guest[100];  // guest name when book
    char phone[20];   // guest phone number when book
    char email[100];  // guest email when book
    int nights;       // amount of nights
    char type[15];    // room type
    float bills;      // bills
};

// list of fuction used
// admin functions
void setup_hotel(struct Room rooms[], int *total);
void edit_room(struct Room room[], int total);
void admin_menu(struct Room room[], int total);

void init_rooms(struct Room rooms[], int *total);
void display_all_rooms(struct Room rooms[], int total);
void display_all_rooms_for_admin(struct Room rooms[], int total, char name[], char phone[], char email[]);
void book_room(struct Room rooms[], int total, char name[], char phone[], char email[]);
void display_available_room(struct Room rooms[], int total, char type[]);
int find_room(struct Room rooms[], int total, int number);
void check_in(struct Room rooms[], int total, char name[], char phone[], char email[]);
void check_out(struct Room rooms[], int total, char name[], char phone[], char email[]);
void view_booking(struct Room rooms[], int total);

// file functions
void save_rooms_to_file(struct Room rooms[], int total);
int load_rooms_from_file(struct Room rooms[], int *total);

#endif
