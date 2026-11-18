#include <stdio.h>
#include <string.h>

#define MAX 100

// Vehicle Type
enum VehicleType {
    CAR = 1,
    BIKE = 2
};

// Rental Status
enum RentalStatus {
    AVAILABLE = 1,
    RENTED = 2
};

// Union
union VehicleDetails {
    int seats;
    int engineCapacity;
};

// Structure
struct Vehicle {
    int id;
    char name[50];
    char brand[50];
    enum VehicleType type;
    enum RentalStatus status;
    union VehicleDetails details;
};

struct Vehicle v[MAX];
int count = 0;

// Search Vehicle
int search(int id) {
    for (int i = 0; i < count; i++) {
        if (v[i].id == id)
            return i;
    }
    return -1;
}

// Add Vehicle
void addVehicle() {
    if (count >= MAX) {
        printf("Vehicle limit reached!\n");
        return;
    }

    int id;
    printf("Enter Vehicle ID: ");
    scanf("%d", &id);

    if (search(id) != -1) {
        printf("Vehicle ID already exists!\n");
        return;
    }

    v[count].id = id;

    printf("Enter Vehicle Name: ");
    scanf("%49s", v[count].name);

    printf("Enter Brand: ");
    scanf("%49s", v[count].brand);

    printf("1. Car\n2. Bike\n");
    printf("Select Vehicle Type: ");
    scanf("%d", (int *)&v[count].type);

    if (v[count].type == CAR) {
        printf("Enter Number of Seats: ");
        scanf("%d", &v[count].details.seats);
    }
    else if (v[count].type == BIKE) {
        printf("Enter Engine Capacity: ");
        scanf("%d", &v[count].details.engineCapacity);
    }
    else {
        printf("Invalid Vehicle Type!\n");
        return;
    }

    v[count].status = AVAILABLE;
    count++;

    printf("\nVehicle Added Successfully!\n");
}

// Display All Vehicles
void displayVehicles() {
    if (count == 0) {
        printf("No Vehicles Found!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("\nVehicle ID: %d", v[i].id);
        printf("\nName: %s", v[i].name);
        printf("\nBrand: %s", v[i].brand);

        if (v[i].type == CAR)
            printf("\nType: Car\nSeats: %d",
                   v[i].details.seats);
        else
            printf("\nType: Bike\nEngine Capacity: %d CC",
                   v[i].details.engineCapacity);

        printf("\nStatus: %s\n",
               v[i].status == AVAILABLE ? "Available" : "Rented");
    }
}

// Search Vehicle
void searchVehicle() {
    int id;
    printf("Enter Vehicle ID: ");
    scanf("%d", &id);

    int i = search(id);

    if (i == -1) {
        printf("Vehicle Not Found!\n");
    }
    else {
        printf("\nVehicle Found!\n");
        printf("Name: %s\n", v[i].name);
        printf("Brand: %s\n", v[i].brand);
        printf("Status: %s\n",
               v[i].status == AVAILABLE ? "Available" : "Rented");
    }
}

// Rent Vehicle
void rentVehicle() {
    int id;
    printf("Enter Vehicle ID: ");
    scanf("%d", &id);

    int i = search(id);

    if (i == -1)
        printf("Vehicle Not Found!\n");
    else if (v[i].status == RENTED)
        printf("Vehicle Already Rented!\n");
    else {
        v[i].status = RENTED;
        printf("Vehicle Rented Successfully!\n");
    }
}

// Return Vehicle
void returnVehicle() {
    int id;
    printf("Enter Vehicle ID: ");
    scanf("%d", &id);

    int i = search(id);

    if (i == -1)
        printf("Vehicle Not Found!\n");
    else if (v[i].status == AVAILABLE)
        printf("Vehicle Already Available!\n");
    else {
        v[i].status = AVAILABLE;
        printf("Vehicle Returned Successfully!\n");
    }
}

// Display Available Vehicles
void availableVehicles() {
    int found = 0;

    for (int i = 0; i < count; i++) {
        if (v[i].status == AVAILABLE) {
            printf("\nID: %d", v[i].id);
            printf("\nName: %s", v[i].name);
            printf("\nBrand: %s\n", v[i].brand);
            found = 1;
        }
    }

    if (!found)
        printf("No Available Vehicles!\n");
}

// Main Function
int main() {
    int choice;

    do {
        printf("\n===== VEHICLE RENTAL MANAGEMENT SYSTEM =====\n");
        printf("\n1. Add Vehicle");
        printf("\n2. Display All Vehicles");
        printf("\n3. Search Vehicle");
        printf("\n4. Rent Vehicle");
        printf("\n5. Return Vehicle");
        printf("\n6. Display Available Vehicles");
        printf("\n7. Exit");

        printf("\n\nEnter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addVehicle();
                break;

            case 2:
                displayVehicles();
                break;

            case 3:
                searchVehicle();
                break;

            case 4:
                rentVehicle();
                break;

            case 5:
                returnVehicle();
                break;

            case 6:
                availableVehicles();
                break;

            case 7:
                printf("Thank You!\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    } while (choice != 7);

    return 0;
}