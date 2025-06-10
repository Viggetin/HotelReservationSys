# BookInn – Hotel Reservation System

**BookInn** is a C++ command-line hotel reservation system that allows users to manage room bookings. The system supports room initialization, making reservations, searching for existing bookings, and viewing current room status.

## Project Structure

- `main.cpp` – Entry point of the application and main menu logic.
- `functions.cpp` – Core functions for reservation handling and system logic.
- `header.h` – Defines the `room` structure and function declarations.
- `Makefile` – Automates the compilation process.

## Features

- **Room Initialization**
  - Randomly creates between 40–300 rooms.
  - First half are 1-person rooms, second half are 2-person rooms.

- **Reservation System**
  - Allows users to reserve a room by selecting a room number, entering name, and number of nights (1–30).
  - Calculates total cost based on room type.
  - Assigns a unique reservation number (10000–99999).

- **Reservation Search**
  - Search for a booking by occupant name or reservation number.

- **Hotel Status View**
  - Lists all rooms, showing whether each is available or reserved.
  - Displays capacity and price per night.

- **Input Validation**
  - Ensures robust and user-friendly input handling.
  - Rejects invalid room numbers, names, or night counts.

## How to Build and Run

### Using the Makefile
- make        # Compiles the program into 'test.exe'
- ./test.exe  # Runs the program
-  make clean  # Removes object files and the executable

### Manual compilation
- g++ main.cpp functions.cpp -o test.exe
- ./test.exe

## Technical Details

- Uses `struct room` to store all data related to each room.
- `rand()` and `time(0)` used for generating room count and reservation numbers.
- **Room prices:**
  - 1-person room: **€100/night**
  - 2-person room: **€150/night**
- All data is stored in memory during runtime (**no file persistence**).

---

## Limitations

-  No persistent data storage (all data is lost after program exit).
-  No concurrent user support (single-session console application).
-  Reservation search is **case-sensitive**.
