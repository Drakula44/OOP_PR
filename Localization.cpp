#include "Localization.h"
// clang-format off
/* cSpell:disable */

unordered_map<enum Localization::local_enum, string> Localization::local_str = {
    {Localization::WELCOME_MESSAGE, "Dobrodosli u simulator mreze gradskog prevoza. Molim vas, odaberite opciju:"},
    {Localization::LOADING_DATA, "Ucitavanje podataka o mrezi gradskog prevoza"},
    {Localization::END_OF_PROGRAM, "Kraj rada"},

    {Localization::LOADING_STATIONS, "Molimo Vas, unesite putanju do fajla sa stajalistima ili kliknite ENTER za ucitavanje podrazumevanog fajla (ulazi/stajalista.txt)"},
    {Localization::FILE_LOADED_STATIONS_DEFAULT, "Ucitan je podrazumevni fajl sa stajalistima"},
    {Localization::FILE_LOADED_STATIONS_CUSTOM, "Ucitan je fajl {} sa stajalistima"},

    {Localization::LOADING_BUSES, "Molimo Vas, unesite putanju do fajla sa linijama gradskog prevoza ili kliknite ENTER za ucitavanje podrazumevanog fajla (ulazi/linije.txt)"},
    {Localization::FILE_LOADED_BUSES_DEFAULT, "Ucitan je podrazumevni fajl sa linijama"},
    {Localization::FILE_LOADED_BUSES_CUSTOM, "Ucitan je fajl {} sa linijama"},

    {Localization::NETWORK_LOADED_SUCCESS, "Mreza gradskog prevoza je uspesno ucitana."},
    {Localization::MAIN_MENU, " Molimo Vas, odaberite opciju:"},

    {Localization::SHOW_BUS_INFO, "Prikaz informacija o stajalistu"},
    {Localization::SHOW_STATION_INFO, "Prikaz informacija o linijama gradskog prevoza"},
    {Localization::GET_PATH, "Pronalazak putanje izmedju dva stajalista"},
    {Localization::GET_STRATEGY, "Odaberite strategiju za pronalazenje putanje"},

    {Localization::GET_BUS_INFO, "Molimo Vas, unesite oznaku linije cije informacije zelite da prikazete."},
    {Localization::BUS_INFO_GENERATED, "Generisan je fajl {} sa osnovnim informacija o liniji {}"},

    {Localization::GET_STATION_INFO, "Molimo Vas, unesite sifru stajalista cije informacije zelite da prikazete."},
    {Localization::BUS_STATION_GENERATED, "Generisan je fajl {} sa osnovnim informacija o stajalistu {}"},

    {Localization::GET_ROUTE_INFO, "Molimo Vas, unesite sifru stajalista iz kog zelite da krenete i sifru stajalista do kog zelite da dodjete."},
    {Localization::ROUTE_INFO_GENERATED, "Generisan je fajl {} sa informacijama o putanji izmedju stajalista {} i {}"},

    {Localization::GET_STRATEGY_INFO, "Molimo Vas, unesite strategiju za pronalazenje putanje."},
    {Localization::STRATEGY_INFO_SELECTED, "Odabrana je strategija {}"},

    {Localization::FILE_CANT_LOAD, "Nije moguce ucitati fajl {}"},
    {Localization::INVALID_INPUT, "Opcija nije validna. Molimo Vas, pokusajte ponovo."},
};