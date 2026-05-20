# BookInn - Hotel Reservation System

**BookInn** is a C++ command-line hotel reservation system for managing room bookings. The system supports room initialization, making reservations, searching for existing bookings, and viewing the current room status.

## Project Structure

| File           | Description                                        |
|----------------|----------------------------------------------------|
| `main.cpp`     | Entry point and main menu logic                    |
| `functions.cpp`| Core functions for reservation handling            |
| `header.h`     | Defines the `room` structure and function declarations |
| `Makefile`     | Automates the compilation process                  |

## Features

**Room Initialization**
- Randomly creates between 40 and 300 rooms at startup.
- The first half are single-person rooms, the second half are double-person rooms.

**Reservation System**
- Reserve a room by selecting a room number, entering an occupant name, and specifying the number of nights (1-30).
- Total cost is calculated automatically based on room type.
- Each reservation is assigned a unique reservation number (10000-99999).

**Reservation Search**
- Look up an existing booking by occupant name or reservation number.

**Hotel Status View**
- Lists all rooms with their availability status, capacity, and price per night.

**Input Validation**
- Rejects invalid room numbers, names, and night counts.

## Building and Running

### Using the Makefile

```sh
make          # Compiles the program into 'test.exe'
./test.exe    # Runs the program
make clean    # Removes object files and the executable
```

### Manual Compilation

```sh
g++ main.cpp functions.cpp -o test.exe
./test.exe
```

## Technical Details

- Room data is stored in a `struct room` array held in memory for the duration of the session.
- Room count and reservation numbers are generated using `rand()` seeded with `time(0)`.
- Room prices: single-person room **100 EUR/night**, double-person room **150 EUR/night**.

## Limitations

- No persistent storage — all data is lost when the program exits.
- Single-session only; no concurrent user support.
- Reservation search is case-sensitive.
