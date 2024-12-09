
#include "header.h"
/*  Pääohjelma
*
*    Pääohjelma pyörittää koko ohjelman päävalikkoa. Se alkaa ensimmäisenä kutsumalla initRooms-funktiota, joka asettaa ohjelman huoneet.
*    Ohjelma jatkaa printtaamalla ohjelman logon ja päävalikon käyttäjälle näkyviin. Sen jälkeen käyttäjän valinnan mukaisesti ohjelma kutsuu komentoa vastaavan toiminnon.
*    Käyttäjän syöte tarkistetaan erikseen omassa funktiossa eli ask_command:issa. Ohjelma lopettaa toimintansa jos käyttäjä syöttää numero 0:n päävalikossa.
*/
int main()
{   
    srand(time(0));
    
    room rooms[MAX_ROOMS];
    int totalRooms = initRooms(rooms);

    int choice;

    // Tulostetaan logo
    print_logo();
    // valikon tulostaminen
    displayMenu();
    do {
        choice = ask_command(); // Päävalikon komennon kysyminen ja syötetarkistus

        switch (choice) {
            case 1:
                reservation(rooms, totalRooms); // varauksen teko
                break;
            case 2:
                checkHotelStatus(rooms, totalRooms); // Hotellin huoneiden tilojen tarkistus
                break;
            case 3:
                reservationSearch(rooms, totalRooms); // varauksien haku
                break;
            case 4:
                displayMenu(); // valikon näyttö uudestaan 
                break;
            case 0:
                cout << "Thank you for using the BookInn system. Goodbye!\n"; // ohjelman lopetus
                return 0;
        }
    } while (true);

    return 0;
}
