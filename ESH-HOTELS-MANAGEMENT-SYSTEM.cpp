#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>


typedef struct admincredentials{
	int adminid;
	char password[20];
} adcre;

typedef struct payments{
	int guestid;
	float bill;
}pay;

typedef struct guestcredentials{
	int guestid;
	char guestname[100];
	int roomnumber;
	char roomtype[50];
	long long int guestphone;
} Guest;

typedef struct {
	int roomnumber;
	char roomtype[20];
	int roomavailable;
	float roomprice;
} Room;

void updatebill(int id, float bill);
void updateDataAfterCheckout(int guestid);
void storepaymentdata(int gID, float bill);
void updateguestfile(Guest guests[]);
void displayadminmenu();
void loginadmin();
void updateroomprice(int roomNumber, float newPrice);
void updateroomavailibility(int roomnumber, int roomavailable);
void guestinfo();
void updateroomstatus();
void displaylogin();
void roominfo();
void displayuserpanel();
void payment(int guestid);
void cleaningservice();
void orderfood(int id);
void checkout();
void roombooking();
void storeguestinfo(Guest guest);
void updateRoomFile(Room rooms[]);
int calculateNextGuestID();
int countLinesInFile(const char *filename);

int main(){
	printf("\n\n\n\t\t\t\t#######################################");
	printf("\n\n\n\t\t\t\t      Welcome To ESH Group Of Hotels");
	printf("\n\n\n\t\t\t\t#######################################");
	displaylogin();
}

void updateRoomFile(Room rooms[]) {
    FILE *fptr = fopen("Rooms.txt", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < 100; i++) {
        fprintf(fptr, "%d\t%s\t%d\t%.2f\n", rooms[i].roomnumber, rooms[i].roomtype, rooms[i].roomavailable, rooms[i].roomprice);
    }

    fclose(fptr);
}

void displaylogin(){
	int n1;
	do{
	printf("\n\nSelect an option:\n1. Admin Login\n2. User Login\n3. Exit\n=> ");
	scanf("%d", &n1);
	switch(n1){
		case 1:{
			loginadmin();
			break;
		}
		case 2:{
			printf("\n\nGood Evening Sir, \nWelcome to ESH Hotels. \nHow may I help you?");
			displayuserpanel();
			break;
		}
		case 3:{
			exit(0);
		}}
}
    while(n1!=3 || n1!=2 || n1!=3 );
    
	
}

void loginadmin(){ // Function to check admin credentials
	adcre admin1 = {242531, "2531hashir"};
	adcre admin2 = {242507, "shaheer2507"};
	adcre admin3 = {242542, "2542shaheer"};
	adcre admin4 = {242546, "esfaan2546"};
	
	int id;
	char pass[20];

	while (1) {
    printf("Enter admin id: ");
    scanf("%d", &id);
    printf("Enter password: ");
    scanf("%s", pass);

    if((id == admin1.adminid && strcmp(pass, admin1.password) == 0) ||
        (id == admin2.adminid && strcmp(pass, admin2.password) == 0) ||
        (id == admin3.adminid && strcmp(pass, admin3.password) == 0) ||
        (id == admin4.adminid && strcmp(pass, admin4.password) == 0)) {
        printf("\nLogin Successful\n");
        displayadminmenu();
        break;
    } else {
        printf("Alert!!! You have entered wrong userid or password\n");
    }
}

}

void displayadminmenu(){//TO display Admin Panel
	int tasknumber;
	printf("\nSelect an option: \n");
	printf("1. Change Room Price\n2. Update Room Avalibilty\n3. View Room Information\n4. View Guest Information\n5. Logout\n=> ");
	scanf("%d", &tasknumber);
	switch(tasknumber){
		case 1:{
			int roomnumber;
			float roomprice;
			
			printf("Enter room number: ");
			scanf("%d", &roomnumber);
			printf("Enter room price: ");
			scanf("%f", &roomprice);
			
			updateroomprice(roomnumber, roomprice);
			break;
		}
		case 2:{
			int roomnumber;
			int roomavailable;
			
			printf("Enter room number: ");
			scanf("%d", &roomnumber);
			printf("Enter availibility: ");
			scanf("%d", &roomavailable);
			
			updateroomavailibility(roomnumber, roomavailable);
			break;
		}
		case 3:{
			roominfo();
			break;
		}
		case 4:{
			guestinfo();
			break;
		}
		case 5:{
			displaylogin();
			break;
		}
	}
}

void updateroomprice(int roomNumber, float newPrice) {
    Room rooms[100];
    int found = 0;

    FILE *roomfile = fopen("Rooms.txt", "r");
    if (roomfile == NULL) {
        printf("Error: Could not open Rooms.txt\n");
        displayadminmenu();
    }

    for (int i = 0; i < 100 ; i++) {
        fscanf(roomfile, "%d %s %d %f", &rooms[i].roomnumber, rooms[i].roomtype, (int*)&rooms[i].roomavailable, &rooms[i].roomprice);
    }

    fclose(roomfile);

    for (int i = 0; i < 100; i++) {
        if (rooms[i].roomnumber == roomNumber) {
            rooms[i].roomprice = newPrice;
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Room number %d not found.\n", roomNumber);
        displayadminmenu();
    }

	updateRoomFile(rooms);

    printf("Room price updated successfully.\n");
    displayadminmenu();
}


void updateroomavailibility(int roomnumber, int roomavailable){
	int found = 0;
	Room rooms[100];
	
	FILE *frooms = fopen("Rooms.txt", "r");
	if(frooms == NULL){
		printf("Could not find the file");
		displayadminmenu();
	}
	
	for(int i=0 ; i<100 ; i++){
		fscanf(frooms, "%d %s %d %f", &rooms[i].roomnumber, rooms[i].roomtype, &rooms[i].roomavailable, &rooms[i].roomprice);
	}
	
	fclose(frooms);
	
	for(int i=0 ; i<100 ; i++){
		if(rooms[i].roomnumber == roomnumber){
			rooms[i].roomavailable = roomavailable;
			found =1;
			break;
		}
	}
	
	if(!found){
		printf("Room Number %d not found", roomnumber);
		displayadminmenu();
	}
	
	updateRoomFile(rooms);
    printf("Room availability updated successfully.\n");
    
    return;
}

void roominfo(){
	FILE *fptr = fopen("Rooms.txt", "r");
	if(fptr == NULL){
		printf("Could not find file!");
		displayadminmenu();
	}
	
	char ch;
	ch = fgetc(fptr);
	
	while( ch != EOF){
		printf("%c", ch);
		ch = fgetc(fptr);
	}
	
	fclose(fptr);
	displayadminmenu();
}

//Function to view specific guest info by guest id
void guestinfo(){
	const char *fptr = "Guests.txt";
	
	int enteredID;
	printf("\nEnter the guest ID: ");
	scanf("%d", &enteredID);
	
	int totallines = countLinesInFile(fptr);
	if(totallines == 0){
		printf("\nNo guests avaiable");
	}
	
	FILE *guestfile = fopen("Guests.txt", "r");
	if(guestfile == NULL){
		printf("\nFile do not exist");
		return;
	}
	
	Guest guests[totallines];
	
	for(int i=0 ; i<totallines ; i++){
		fscanf(guestfile, "%d %s %lld %d %s",
			&guests[i].guestid,
			guests[i].guestname,
			&guests[i].guestphone,
			&guests[i].roomnumber,
			guests[i].roomtype
		);
	}
	
	for(int i=0 ; i<totallines; i++){
		if(guests[i].guestid == enteredID){
			printf("\nInformation of Guest: %d\n", guests[i].guestid);
			printf("Guest ID: %d\nName: %s\nPhone Number: %lld\nRoom Number: %d\nRoomType: %s\n", 
				guests[i].guestid,
				guests[i].guestname,
				guests[i].guestphone,
				guests[i].roomnumber,
				guests[i].roomtype
			);
			break;
		}
	}
	fclose(guestfile);
	
	displayadminmenu();
}


void displayuserpanel(){
	int guesttask;
	printf("\n\nSelect a task\n1. Book a room\n2. Check Out\n3. Order Food\n4. Exit\n=> ");
	scanf("%d", &guesttask);
	
	switch(guesttask){
		case 1:{
			roombooking();
			break;
		}
		case 2:{
			checkout();
			break;
		}
		case 3:{
			int id;
			printf("\nEnter your id: ");
			scanf("%d", &id);
			orderfood(id);
			break;
		}
		case 4:{
			displaylogin();
			break;
		}
	}
}

// Function to handle room booking and guest info storage
void roombooking() {
    int bookingtype;

    printf("\n\nSelect room type: \n1.PG : 5000\n2.Single : 10000\n3.Double : 25000\n4.Suite : 50000\n => ");
    scanf("%d", &bookingtype);

    FILE *fptr = fopen("Rooms.txt", "r");
    if (fptr == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Room rooms[100];
    for (int i = 0; i < 100; i++) {
        fscanf(fptr, "%d %s %d %f", &rooms[i].roomnumber, rooms[i].roomtype, &rooms[i].roomavailable, &rooms[i].roomprice);
    }
    
    for (int i = 0; i < 100; i++) {
        // Check availability based on the selected room type
        if ((bookingtype == 1 && strcmp(rooms[i].roomtype, "PG") == 0) ||
            (bookingtype == 2 && strcmp(rooms[i].roomtype, "Single") == 0) ||
            (bookingtype == 3 && strcmp(rooms[i].roomtype, "Double") == 0) ||
            (bookingtype == 4 && strcmp(rooms[i].roomtype, "Suite") == 0)) {
            if (rooms[i].roomavailable == 0) {

                rooms[i].roomavailable = 1;  // Mark the room as booked

                // Create and populate guest structure
                Guest guest;
                guest.guestid = rooms[i].roomnumber;
                printf("Enter guest name: ");
                scanf("%s", guest.guestname);
                printf("Enter guest phone number (11 digits): ");
                scanf("%lld", &guest.guestphone);
                guest.roomnumber = rooms[i].roomnumber;
                strcpy(guest.roomtype, rooms[i].roomtype);

                storeguestinfo(guest);
                storepaymentdata(guest.guestid, rooms[i].roomprice);

                printf("\nYour room has been booked! Proceed to room number %d\n", rooms[i].roomnumber);
				printf("\nHere is your Guest ID: %d", guest.guestid);
                updateRoomFile(rooms);
                break;
            } else {
            	continue;
            }
        }
    }
	
    fclose(fptr);
    
    displayuserpanel();
}

// Function to store guest info in the file
void storeguestinfo(Guest guest) {
    FILE *fptr = fopen("Guests.txt", "a");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(fptr, "%d\t%s\t%lld\t%d\t%s\n",
            guest.guestid, guest.guestname, guest.guestphone, guest.roomnumber, guest.roomtype);
	
    fclose(fptr);
}

//Function to checkout
void checkout() {
    const char *fptr = "Guests.txt";

    int totallines = countLinesInFile(fptr);
    if (totallines == 0) {
        printf("\nNo guests available.\n");
        displayuserpanel();
        return;
    }

    // Reading Data from Guest File
    FILE *guestfile = fopen(fptr, "r");
    if (guestfile == NULL) {
        printf("File does not exist.\n");
        return;
    }

    Guest guests[totallines];
    for (int i = 0; i < totallines; i++) {
        fscanf(guestfile, "%d %s %lld %d %s",
            &guests[i].guestid,
            guests[i].guestname,
            &guests[i].guestphone,
            &guests[i].roomnumber,
            guests[i].roomtype
        );
    }
    fclose(guestfile);

    // Checkout process
    int checkoutID, guestFound = 0;
    printf("Enter Guest ID to proceed: ");
    scanf("%d", &checkoutID);

    guestfile = fopen(fptr, "w");
    if (guestfile == NULL) {
        perror("Error opening file for writing");
        return;
    }

    for (int i = 0; i < totallines; i++) {
        if (guests[i].guestid == checkoutID) {
            printf("\nCheckouting...\n");
            updateroomavailibility(guests[i].roomnumber, 0);
            guestFound = 1;
        } else {
            fprintf(guestfile, "%d\t%s\t%lld\t%d\t%s\n",
                guests[i].guestid,
                guests[i].guestname,
                guests[i].guestphone,
                guests[i].roomnumber,
                guests[i].roomtype
            );
        }
    }
    fclose(guestfile);

    if (!guestFound) {
        printf("Guest with ID %d not found.\n", checkoutID);
    } else {
        payment(checkoutID);
    }

    displayuserpanel();
}


// Function to count the number of lines in the files
int countLinesInFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }

    int lines = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }

    fclose(file);
    return lines;
}

void payment(int guestid) {
    FILE *fpay = fopen("Payment.txt", "r");
    if (fpay == NULL) {
        printf("\nError: Unable to open Payment.txt\n");
        return;
    }

    int index = countLinesInFile("Payment.txt");
    if (index <= 0) {
        printf("\nNo payment data available.\n");
        fclose(fpay);
        return;
    }

    pay payments[index];
    for (int i = 0; i < index; i++) {
        fscanf(fpay, "%d %f", &payments[i].guestid, &payments[i].bill);
    }

    fclose(fpay);

    // Search for the guest ID and display the bill
    int guestFound = 0;
    for (int i = 0; i < index; i++) {
        if (payments[i].guestid == guestid) {
            printf("\n\nMake your payment.\n");
            printf("Your total bill is: %.2f\n", payments[i].bill);
            guestFound = 1;
            break;
        }
    }

    if (!guestFound) {
        printf("\nGuest ID %d not found.\n", guestid);
        return;
    }

    // Proceed with checkout
    updateDataAfterCheckout(guestid);
    printf("\nYou have been checked out successfully.\n");
}


void updateDataAfterCheckout(int guestid){
	FILE *fpay = fopen("Payment.txt", "r");
	int index = countLinesInFile("Payment.txt");
	
	pay payments[index];
	
	for(int i=0; i<index ;i++){
		fscanf(fpay, "%d %f", &payments[i].guestid, &payments[i].bill);
	}
	
	fclose(fpay);
	
	fpay = fopen("Payment.txt", "w");
	
	for(int i=0; i<index ;i++){
		if(payments[i].guestid != guestid){
			fprintf(fpay, "%d\t%.2f\n", payments[i].guestid, payments[i].bill);
		}
	}
	
	fclose(fpay);
}

void storepaymentdata(int guestid, float price){
	FILE *fpay = fopen("Payment.txt", "a");
	
	fprintf(fpay, "%d %.2f\n", guestid, price);
	
	fclose(fpay);
}

//Function to update bill after food ordering
void updatebill(int id, float bill){
	FILE *fpay = fopen("Payment.txt", "r+");
	if(fpay == NULL){
		printf("\nError opening Payment.txt");
		return;
	}
	
	int index = countLinesInFile("Payment.txt");
	pay payments[index];
	int count = 0, guestfound = 0;
	
	for(int i=0 ; i<index ;i++){
		fscanf(fpay, "%d %f", &payments[i].guestid, &payments[i].bill);
	}
	
	for(int i=0 ; i<index ; i++){
		if(payments[i].guestid == id){
			payments[i].bill += bill;
			guestfound =1;
		}
	}
	
	if(!guestfound){
		printf("Guest %d not found", id);
		fclose(fpay);
	}
	fclose(fpay);
	
	fpay = fopen("Payment.txt", "w");
	if (fpay == NULL) {
        printf("\nError opening Payment.txt for writing");
        return;
    }
	
	for(int i=0 ; i<index ; i++){
		fprintf(fpay, "%d\t%.2f\n", payments[i].guestid, payments[i].bill);
	}
	
	fclose(fpay);
	if(guestfound == 1){
	printf("\n\nHere is your order Sir. Thank You!");
	printf("\nHave a nice meal.");
	}
}


//Function to order food
void orderfood(int id){
	int fooditem, quantity;
	printf("Here is Our Menu Sir: \n\n1. Birayni: 850\n2. Shawarma: 500\n3. Pulao: 700\n4. Fries: 150\n5. Pizza Fries: 600\n6. Pizza: 1250 (S)\n7. Chicken Burger: 1100\n8. Beef Burger: 1300\n9. Buffalo Burger: 1200\n10. Exit\n=> ");
	scanf("%d", &fooditem);
	
	printf("\nEnter Quantity: ");
	scanf("%d", &quantity);
	
	switch(fooditem){
		case 1:{
			updatebill(id, quantity*850.0);
			break;
		}
		case 2:{
			updatebill(id, quantity*500.0);
			break;
		}
		case 3:{
			updatebill(id, quantity*700.0);
			break;
		}
		case 4:{
			updatebill(id, quantity*150.0);
			break;
		}
		case 5:{
			updatebill(id, quantity*600.0);
			break;
		}
		case 6:{
			updatebill(id, quantity*1250.0);
			break;
		}
		case 7:{
			updatebill(id, quantity*1100.0);
			break;
		}
		case 8:{
			updatebill(id, quantity*1300.0);
			break;
		}
		case 9:{
			updatebill(id, quantity*1200.0);
			break;
		}
		case 10:{
			break;
		}
		default:{
			printf("\nInvalid Input!\n");
			break;
		}
	}
	displayuserpanel();
}