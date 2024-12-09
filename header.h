#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>  // Nimien kasittelya varten --> getline
#include <cstdlib> // Satunnaislukuja varten -- rand()
#include <ctime>   // Ajastinpohjainen satunnaislukujen alustaminen --> time()
#include <limits> // Virhetarkistusta varten -> Cin.fail

using namespace std;

// Globaali vakio huoneiden maksimimaaralle
const int MAX_ROOMS = 300;

// Huone strukti
struct room
{
    int roomNum;          // Huonenumero
    bool isReserved;      // Onko huone varattu --> true / false
    string occupantName;  // Varaajan nimi
    int capacity;         // Huonekapasiteetti (1hh tai 2hh)
    int pricePerNight;    // Hinta per yö
    int reservationNum;   // Varausnumero
    int nights;           // Yöpymisajat
    int totalCost;        // Kokonais hinta yöpymisesta -> yö * hintaPerYö (riippuu huonetyypistä)
};

// Funktiot
void print_logo(); // Ohjelman logon printtaus
void displayMenu(); // Ohjelman pääalikon esitys komento 
int ask_command(); // Pääohjelman "komentorivi"
void reservation(room rooms[], int totalRooms); // varauksen teko funktio
int generate_reservation_number(); // Varausnumeron generointi
int initRooms(room rooms[]); // Ohjelman huoneiden alustaminen satunnaisella määrällä
void checkHotelStatus(const room rooms[], int totalRooms); // Kaikkien hotellihuoneiden tilan tarkistukseen listana
void reservationSearch(const room rooms[], int totalRooms); // Varauksien haku nimella tai varausnumerolla

#endif 
