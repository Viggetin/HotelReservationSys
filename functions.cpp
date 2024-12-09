#include "header.h"

/*  Ohjelman logo 
*   Funktio yksinkertaisesti kutsuttaessa tekee Cout:in avulla ASCII logon 
*/
void print_logo()
{
    cout << "  ____              _    _____                             \n";
    cout << " |  _ \\            | |  |_   _|                            \n";
    cout << " | |_) | ___   ___ | | __ | |  _ __  _ __    ___ _   _ ___ \n";
    cout << " |  _ < / _ \\ / _ \\| |/ / | | | '_ \\| '_ \\  / __| | | / __|\n";
    cout << " | |_) | (_) | (_) |   < _| |_| | | | | | | \\__ \\ |_| \\__ \\ \n";
    cout << " |____/ \\___/ \\___/|_|\\_\\_____|_| |_|_| |_| |___/\\__, |___/\n";
    cout << "                                                  __/ |    \n";
    cout << "                                                 |___/     \n";
}
/*  Päävalikon vaihtoetojen tulostus
*   
*   Funktion idea on siis tulostaa ohjelman päävalikon vaihtoehdot terminaaliin käyttajan pyynnöstä ja ohjelman alussa.
*/
void displayMenu()
{
    cout << "\nWelcome to BookInn hotel reservation system\n";
    cout << "Please choose your action by entering menu number\n\n";
    cout << "1) Make a reservation\n";
    cout << "2) Check room status\n";
    cout << "3) Reservation search\n";
    cout << "4) Display menu\n";
    cout << "0) Exit\n";
}

/* Päävalikon komento funktio
*
* Funktion ideana on toimia ohjelman eri toimintojen kutsujana käyttäjän pyyntöjen mukaisesti. Se siis käsittelee annetun komennon, tarkistaa että se on validi komento, ja palauttaa käyttäjän valinnan. 
*
* Ohjelma toimii alustamalla ensin choice eli valintamuuttujan, joka käsittelee komento vaihtoehdot 0-4, sekä error-booleanin, jota käytetään virheiden tarkistamiseen.
* Silmukka pyörii niin kauan, kunnes syöte on validi. Jos käyttäjä syöttää muuta kuin luvun, cin.fail() palauttaa virheen, ja virhetila poistetaan kutsumalla cin.clear(), minkä jälkeen cin.ignore() tyhjentää syöttöpuskurin.
* Lisäksi valinnan ollessa alueen ulkopuolella (alle 0 tai yli 4) annetaan virheilmoitus, ja silmukka jatkuu. Kun syöte on kelvollinen, funktio palauttaa valinnan ja mahdollistaa ohjelman etenemisen käyttäjän antaman komennon perusteella.
*
* Käytin tätä pääsääntöisenä virheentarkistuksena. Se toimii myös funktioissa, jotka vain palauttavat käyttäjän päävalikkoon josta he joutuvat uudestaan valitsemaan toiminnon ja täyttämään tiedot oikein. 
*/

int ask_command() 
{
    int choice;
    bool error; // Virheen tila muuttujassa

    do {
        error = false;
        cout << "\n[Main Menu] Enter a command (0-4): ";
        cin >> choice;

        //käyttäjän syötteen tarkistaminen
        if (cin.fail()) 
        {
            cout << "Error. Please enter a valid number!\n";
            error = true;
            cin.clear();
            cin.ignore(80, '\n'); 
        } else if (choice < 0 || choice > 4) 
        {
            cout << "Invalid input. Please enter a number between 0 and 4.\n";
            error = true;
        }
    } while (error);

    return choice;
}

/* Hotellin huoneiden alustaminen
*   
*   Tämän funktion ideana on toimia tehtävänannon mukaisella tavalla eli alustaa satunnaisesti huoneiden lukumäärä 40–300 huoneiston välillä.
*   Se myös alustaa itse rooms-struktin rakenteen ja alustavat tiedot tyhjille huoneille. 
*
*   Funktio alkaa satunnaisesti rand()-funktion avulla määrittämään hotellin huoneiden määrän väliltä 40–300.
*   Sen jälkeen funktio jatkaa for-loopilla asettamalla kaikki rooms-struktin huoneiden perustiedot huoneiden arvotun lukumäärän avulla.
*   
*   - roomNum: Huoneet numeroidaan niiden lukumäärän mukaisesti.
*   - isReserved: Huoneiden varaustilanne asetetaan vapaaksi eli false arvoksi, kunnes varauksen tekemisen jälkeen arvo muutetaan true arvoksi.
*   - capacity: Huoneet on jaettu kahteen erilaiseen kapasiteettiluokkaan, eli 1hh ja 2hh. Ehtolauseessa asetetaan kaikki hotellin ensimmäisen puoliskon huoneet 1hh ja loput 2hh.
*   - pricePerNight: Huoneiden hinta on ennestään määritelty tehtävänannossa; 1hh = 100 eur ja 2hh = 150 eur. Tämän mukaisesti ehtolauseella edellisen vaiheen mukaisesti asetetaan oikeat hinnat oikean huonetyypin mukaisesti.
*   - reservationNum: Huoneen varausnumero, joka asetetaan vasta huoneen varauksen yhteydessä.
*   - nights: Öiden varattu lukumäärä, jolle huone on varattu.
*   - totalCost: Huoneen varaukseen laskettu loppusumma varattujen öiden perusteella.
*
*   Funktio palauttaa hotellin huoneiden lukumäärän.
*/
int initRooms(room rooms[])
{
    int totalRooms = rand() % 261 + 40; // Satunnainen luku välillä 40–300

    for (int i = 0; i < totalRooms; i++)
{
    rooms[i].roomNum = i + 1;
    rooms[i].isReserved = false;
    rooms[i].occupantName = "";
    
    // Kapasiteetin asetus: ensimmäinen puolikas 1hh, loput 2hh
    if (i < totalRooms / 2) {
        rooms[i].capacity = 1;
    } else {
        rooms[i].capacity = 2;
    }

    // Hinnan asetus kapasiteetin mukaan
    if (rooms[i].capacity == 1) {
        rooms[i].pricePerNight = 100.0; // Yhden hengen huone
    } else {
        rooms[i].pricePerNight = 150.0; // Kahden hengen huone
    }

    rooms[i].reservationNum = 0;
    rooms[i].nights = 0;
    rooms[i].totalCost = 0.0;
}

    return totalRooms;
}

/*  Huoneen varaus funktio
*   
*   Reservation-funktion pääsääntöisenä ideana on mahdollistaa huoneiden varaaminen suoraan, jonka myötä varmistetaan, että ei varata jo varattua huonetta. Varattujen öiden määrä on rajoitettu maksimissaan 30 päivään.
*   Myös varauksen onnistuttua ilman syöttövirheitä se laskee lopullisen loppuhinnan ja tallentaa tiedot struktiin. 
*
*   Funktio aloittaa toimintansa asettamalla tarvittavat muuttujat, jotka tallennetaan käyttäjän syötteen mukaisesti. Ensimmäisenä esitetään eri huonetyyppien numeroinnit eli ensimmäinen puolisko on 1hh ja loput ovat 2hh.
*   Funktio jatkaa tästä kysymällä käyttäjältä, minkä huonenumeron hän haluaa varata, jonka perusteella määrittyy myös huonetyyppi. Syöttö tarkistetaan, onko syötetyt numerot huoneiden lukumäärän välillä ja myös onko kyseinen huone jo valmiiksi varattu.
*   Seuraavaksi käyttäjältä pyydetään syöttämään varaajan nimi. Ennen syötteen pyyntöä syötepuskuri tyhjennetään, koska edellisestä numero-syötteestä jää "\n"-rivinvaihtomerkki. 
*   getline toimii siten, että se lukee syötetyn tekstin rivinvaihtoon saakka, eli se lopettaisi heti, jos syötepuskuri ei ole tyhjennetty. Ohjelma jatkaa kysymällä hotelliyöiden määrää.
*   Lopulta lasketaan varattujen öiden perusteella lopullinen summa ja luodaan varaukselle uniikki varausnumero. Tiedot tallennetaan niihin kuuluville struktin sijainneille ja syötetyt tiedot esitetään tarkistuksen vuoksi lopussa.
*   
*/

void reservation(room rooms[], int totalRooms)
{

    int roomNumber, nights;
    string occupantName;
    cout << " Room reservation system \n\n";

    cout << "The amount of rooms is " << totalRooms << " \n";
    cout << "Rooms of the first half " << totalRooms/2 << " are 1 person rooms and last half from " << (totalRooms/2)+1 << " to "<< totalRooms << " are 2 person rooms \n\n";

    cout << "\nPlease enter Room number: ";
    cin >> roomNumber;

    // tarkistetaan onko huonenumero validi
    if (roomNumber < 1 || roomNumber > totalRooms)
    {
        cout << "\nInvalid room number! Please try again.\n";
        return;
    }

    // Tarkistetaan onko huone varattu jo
    if (rooms[roomNumber - 1].isReserved)
    {
        cout << "\nRoom " << roomNumber << " is already reserved. Please choose another room.\n";
        return;
    }

    // varauksen tekijän kysyminen
    cout << "\nPlease enter the occupant's name: ";
    cin.ignore(); 
    getline(cin, occupantName);

    // vietettävien öiden määrä
    cout << "\nEnter number of nights (1-30): ";
    cin >> nights;

    if (nights < 1 || nights > 30)
    {
        cout << "\nInvalid number of nights! Try again.\n";
        return;
    }

    // Varauksen kokonaishinnan laskeminen
    int totalCost = rooms[roomNumber - 1].pricePerNight * nights;

    // varausnumeron teko 
    int reservationNum = generate_reservation_number();

    // Huoneen tietojen + varauksen paivitys struktiin
    rooms[roomNumber - 1].isReserved = true;
    rooms[roomNumber - 1].occupantName = occupantName;
    rooms[roomNumber - 1].reservationNum = reservationNum;
    rooms[roomNumber - 1].nights = nights;
    rooms[roomNumber - 1].totalCost = totalCost;
    

    cout << "\nRoom " << roomNumber << " has been successfully reserved for " << occupantName << ".\n";
    cout << "\nTotal cost for " << nights << " nights: " << totalCost << " Euros.\n";
    cout << "\nYour reservation number is " << reservationNum << "\n";
}

/* Hotellin huoneiden tilan tarkistus
*
* Tämän funktion ideana on toimia ns. nykyisen huonekannan tilan tarkistamisessa listaamalla ne. 
* Funktio saa arvoina room-struktin kaikki huoneet ja myös satunnaisesti tehdyn huoneiden määrän arvokseen, jotta se listaa kaikki huoneet.
* Pääasiallisena tietona, mitä funktio palauttaa listattuna, on jokaisen huoneen varaustilanne tarkistamalla, onko varaus true tai false.
*
* Varauksen ollessa true, se palauttaa myös tietona, kuka on huoneen varaaja/asukas ja ilmoitetun majoittumisajan laskun loppusumman kanssa.
* Funktio myös palauttaa, onko huone 1hh vai 2hh ja mikä on huoneen hinta per yö.
*/
void checkHotelStatus(const room rooms[], int totalRooms)
{
    cout << "\nHotel rooms status:\n";
    for (int i = 0; i < totalRooms; i++)
    {
        
        if (rooms[i].isReserved)
        {
            cout << "Room " << rooms[i].roomNum << " (Reserved by " << rooms[i].occupantName << ") --> ";
            cout << "Total cost for " << rooms[i].nights << " nights: " << rooms[i].totalCost << " Euros.";
        }
        else
        {
            cout << "Room " << rooms[i].roomNum << " (Available)";
        }

        // Tulostetaan huoneen lisätiedot
        cout << ", Capacity: " << rooms[i].capacity;
        cout << ", Price: " << rooms[i].pricePerNight << " Euro per night.\n";
    }
}

/* Varauksien haku
*   
*   Tämän funktion tarkoituksena on mahdollistaa tehtyjen varauksien hakeminen, joko varaajan nimen perusteella tai varausnumeron perusteella. 
*   Funktio palauttaa tiivistelmän varauksesta, kuten huoneen numeron, varaajan nimen, varattujen öiden määrän ja kokonaiskustannuksen.
*   
*   Funktio alkaa kysymällä käyttäjältä, millä parametrilla hän haluaa etsiä varausta. Vaihtoehtoina ovat joko haku nimellä tai varausnumerolla. 
*   Nimihakua varten käyttäjältä pyydetään nimi syötteenä, joka tallennetaan name-muuttujaan merkkijonona. Ennen syötteen ottamista syötepuskuri tyhjennetään cin.ignore:lla, jotta vältetään virhetilanteet.
*   Jokaisen rooms-struktin huoneen tiedot tarkistetaan annetun nimen perusteella.
*   
*   Varausnumerolla tehtävä haku toimii samankaltaisesti nimihakuun verrattuna, mutta se vertailee jokaisen huoneen varausnumeroa käyttäjän syöttämään varausnumeroon. Kun sopiva varausnumero löytyy, palautetaan vastaavat tiedot.
*   
*   Jos sopivaa varausta ei löydy kummallakaan hakutavalla, funktio ilmoittaa, ettei varausta löytynyt.
*/
void reservationSearch(const room rooms[], int totalRooms)
{
    cout << " Search reservations \n\n";
    
    cout << "Search by:\n 1) Name \n 2) Reservation number\n";
    cout << "Please enter your command: ";

    // valikon vaihtoehto
    int choice;
    cin >> choice;

    // Varauksen hakeminen nimellä
    if (choice == 1)
    {
        string name;
        cout << "Enter name: ";
        cin.ignore(); // puskurin tyhjennys "\n" varalta
        getline(cin, name);

        //tarkistetaan kaikki huoneet 
        for (int i = 0; i < totalRooms; i++)
        {   
            // Onko huone varattu ja täsmääkö haettu nimi
            if (rooms[i].isReserved && rooms[i].occupantName == name)
            {
                double totalCost = rooms[i].pricePerNight * rooms[i].nights;
                cout << "Room " << rooms[i].roomNum << " reserved by " << rooms[i].occupantName;
                cout << " for " << rooms[i].nights << " nights || Total cost: " << totalCost << " Euros.\n";
                return;
            }
        }
    }
    else if (choice == 2)
    {
        int resNum;
        cout << "Enter reservation number: ";
        cin >> resNum;

        //tarkistetaan kaikki huoneet 
        for (int i = 0; i < totalRooms; i++)
        {
            // Onko huone varattu ja täsmääkö haettu varausnumero
            if (rooms[i].isReserved && rooms[i].reservationNum == resNum)
            {
                double totalCost = rooms[i].pricePerNight * rooms[i].nights;
                cout << "Room " << rooms[i].roomNum << " reserved by " << rooms[i].occupantName;
                cout << " for " << rooms[i].nights << " nights || Total cost: " << totalCost << " Euros.\n";
                return;
            }
        }
    }
    cout << "No matching room found.\n";
}



/* Varausnumeron satunnaisgeneraattori
*
*  Tämän funktion ideana on suoranaisesti tehdä satunnainen numero lukujen 10000-99999 valilla miten tehtavanannossa ohjeistettiin
*  funktio kayttaa rand() satunnaisgeneraattoria joka on skaalattu modulo operaattorilla 10000-99999 valille.
*/
int generate_reservation_number()
{
    return rand() % 90000 + 10000;
}