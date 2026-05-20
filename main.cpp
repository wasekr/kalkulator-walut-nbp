#include <iostream>
#include <algorithm> // std::transform
#include <nlohmann/json.hpp>

//by troche przyspieszyc kompilacje
// #include <CLI/CLI.hpp>
#include <CLI/App.hpp>
#include <CLI/Formatter.hpp>
#include <CLI/Config.hpp>

#include <httplib.h>

//by wyswietlal polskie znaki
#ifdef _WIN32
#include <windows.h>
#endif

using json = nlohmann::json;


double get_exchange_rate(std::string currency) {
    //zaminana na male litery
    std::transform(begin(currency), end(currency), begin(currency), ::tolower );

    if (currency == "pln") {
        return 1.0;
    }

    httplib::Client client ("http://api.nbp.pl");
    const std::string path = "/api/exchangerates/rates/a/" + currency + "/?format=json";

    if (auto res = client.Get(path)) {
        if (res->status == 200) {
            try {
                json j = json::parse(res->body);
                return j["rates"][0]["mid"];

            } catch (const std::exception& e) {
                std::cerr << "Blad przy probie odczytania kursu waluty: " << currency << "\n";
                std::cerr << "Szczegoly:" << e.what() << "\n";
                return -1.0;
            }

        }else if (res->status == 404) {
            std::cerr << "Blad - nie znaleziono takiej waluty: " << currency << "\n";
            return -1.0;
        }
    }

    std::cerr << "Brak polaczenia z internetem przy pobieraniu kursu z NBP" << "\n";
    return -1.0;
}

void display_list_of_abbreviations() {
    httplib::Client client ("http://api.nbp.pl");
    std::cout << "Pobieram liste skrotow dostepnych walut..." << "\n";

    std::string path = "/api/exchangerates/tables/a/?format=json";
    if (auto res = client.Get(path)) {
        if (res->status == 200) {
            try {
                json j = json::parse(res->body);
                std::cout << "__________DOSTEPNE SKROTY WALUT__________" << "\n";

                for (const auto& rate : j[0]["rates"]) {
                    std::string abbreviation = rate["code"];
                    std::string currency_name = rate["currency"];
                    std:: cout << abbreviation << "->" << currency_name << "\n";
                }

                std::cout << "_________________________________________" << "\n";


            }catch (const std::exception &e) {
                std::cerr << "Blad przy probie pobierania listy" << "\n";
                std::cerr << "Szczegoly:" << e.what() << "\n";
            }

        }else if (res->status == 404) {
            std::cerr << "Blad - nie znaleziono listy skrotow walut na serwerze NBP: " << "\n";
        }

    }else {
        std::cerr << "Brak polaczenia z internetem przy pobieraniu listy skrotow walut.\n";
    }
}

//argcount liczba slow wpisanych w terminalu argv to wektor(tablica) przechowujacy te slowa (wskaznik na wskaznik)
int main(int argc, char** argv) {

//by wyswietlal polskie znaki
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    //inicjalizacja menu - app describtion
    CLI::App app("Kalkulator walutowy wedlug kursow NBP");

    //przykladowy wzorzec skladni by bylo wiadomo jak uzywac
    app.footer("\nPrzyklad uzycia:\nna Windows: .\\projekt_kalkulator_walut.exe -k 100 -z usd -n pln\nna Linux (Ubuntu): ./projekt_kalkulator_walut -l");


    double value = 0.0;
    std::string currency_from = "";
    std::string currency_to = "";

    app.add_option("-k,--kwota", value, "Kwota do przeliczenia")->required();
    app.add_option("-z,--z-waluty", currency_from, "Waluta zrodlowa (pln, usd, eur, itd.)")->required();
    app.add_option("-n,--na-walute", currency_to, "Waluta docelowa (usd, eur, pln, itd.)")->required();

    //add_flag_callback tworzy flage, ktora dziala jak przycisk awaryjny, program nie spr czy podano --kwota tylko
    //wypisuje liste i robi exit(0) nie zwracajac bledu o braku podanych argumentow
    app.add_flag_callback("-l,--lista", []() {
        display_list_of_abbreviations();
        exit(0);
    },"Wyswietla liste jakie dostepne waluty maja skroty");


    //wrzuca surowe argc i argv do obiektu app chyba ze wpisano --help to wypisze instrukcje i zrobi exit
    CLI11_PARSE(app, argc, argv);

    std::cout << "Pobieram kursy walut ...." << "\n";

    double exchange_rate_from = get_exchange_rate(currency_from);
    if (exchange_rate_from < 0.0) {
        return 1;
    }

    double exchange_rate_to = get_exchange_rate(currency_to);
    if (exchange_rate_to < 0.0) {
        return 1;
    }

    double result = (value * exchange_rate_from) / exchange_rate_to;

    std::cout << "-----------------WYNIK-----------------" << "\n";
    std::cout << value << " w " << currency_from << " jest warte: " << result << " w " << currency_to << "\n";
    std::cout << "---------------------------------------" << "\n";

    return 0;
}