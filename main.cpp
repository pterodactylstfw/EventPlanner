#include <iostream>
#include "Event.h"
#include "EventManager.h"

std::chrono::year_month_day transformaDataCustom(const std::string &data_str) {
    std::stringstream data_ss(data_str);
    std::string day_str, month_str, year_str;

    std::getline(data_ss, day_str, '/');
    std::getline(data_ss, month_str, '/');
    std::getline(data_ss, year_str);

    return std::chrono::year_month_day{
        std::chrono::year{std::stoi(year_str)},
        std::chrono::month{static_cast<unsigned int>(std::stoul(month_str))},
        std::chrono::day{static_cast<unsigned int>(std::stoul(day_str))}
    };
}

std::chrono::hh_mm_ss<std::chrono::seconds> transformaOraCustom(const std::string &ora_str) {
    std::stringstream ora_ss(ora_str);
    std::string h_str, min_str, sec_str = "00";

    std::getline(ora_ss, h_str, ':');
    std::getline(ora_ss, min_str);


    return std::chrono::hh_mm_ss<std::chrono::seconds>{
        std::chrono::hours{std::stoi(h_str)} +
        std::chrono::minutes{std::stoi(min_str)} +
        std::chrono::seconds{std::stoi(sec_str)}
    };
}


int main() {
    EventManager planner;
    while (true) {
        std::cout << "Introduceti optiunea dorita:" << std::endl;
        std::cout << '\t' << "1. Adaugare eveniment" << std::endl;
        std::cout << '\t' << "2. Stergere eveniment" << std::endl;
        std::cout << '\t' << "3. Editare eveniment" << std::endl;
        std::cout << '\t' << "4. Afisare evenimente" << std::endl;
        std::cout << '\t' << "5. Cautare evenimente dupa ID" << std::endl;
        std::cout << '\t' << "6. Cautare evenimente dupa titlu" << std::endl;
        std::cout << '\t' << "7. Notifica despre urmatoarele evenimente" << std::endl;
        std::cout << '\t' << "8. Salveaza in fisier evenimentele" << std::endl;
        std::cout << '\t' << "9. Incarca din fisier evenimentele" << std::endl;
        std::cout << '\t' << "10. Iesire" << std::endl;

        unsigned int optiune;
        do
            std::cin >> optiune;
        while (optiune > 10 || optiune < 1);

        std::cin.ignore();

        switch (optiune) {
            case 1: {
                std::string titlu, descriere, data, ora, locatie;

                std::cout << "Titlu eveniment: ";
                std::getline(std::cin, titlu);

                std::cout << "Descriere eveniment " << titlu << ": ";
                std::getline(std::cin, descriere);

                std::cout << "Data eveniment (Format: ZZ/LL/AAAA):";
                std::cin >> data;
                std::cin.ignore();

                std::cout << "Ora eveniment (Format hh:mm::ss):";
                std::cin >> ora;
                std::cin.ignore();

                std::cout << "Locatie eveniment: ";
                std::getline(std::cin, locatie);

                std::chrono::hh_mm_ss<std::chrono::seconds> oraCustom = transformaOraCustom(ora);
                std::chrono::year_month_day dataCustom = transformaDataCustom(data);

                // Obține un ID unic
                unsigned int currentID = planner.getNextID();

                planner.addEvent(Event(currentID, titlu, descriere, dataCustom, oraCustom, locatie));
                break;
            }

            case 2: {
                unsigned int ID;
                std::cout << "Introduceti ID-ul evenimentului dorit a fi sters: ";
                std::cin >> ID;
                if (planner.findEventByID(ID) != nullptr)
                    planner.deleteEvent(ID);
                break;
            }

            case 3: {
                // Editare eveniment
                unsigned int ID;
                std::cout << "Introduceti ID-ul evenimentului de editat: ";
                std::cin >> ID;
                std::cin.ignore();
                Event *ev = planner.findEventByID(ID);
                if (ev == nullptr) {
                    std::cout << "Nu exista eveniment cu acest ID!" << std::endl;
                    break;
                }
                std::string titlu, descriere, data, ora, locatie;
                std::cout << "Titlu nou: ";
                std::getline(std::cin, titlu);
                std::cout << "Descriere noua: ";
                std::getline(std::cin, descriere);
                std::cout << "Data noua (Format: ZZ/LL/AAAA): ";
                std::cin >> data;
                std::cin.ignore();
                std::cout << "Ora noua (Format: hh:mm): ";
                std::cin >> ora;
                std::cin.ignore();
                std::cout << "Locatie noua: ";
                std::cin >> locatie;
                std::cin.ignore();
                auto dataNoua = transformaDataCustom(data);
                auto oraNoua = transformaOraCustom(ora);
                Event nouEv(ID, titlu, descriere, dataNoua, oraNoua, locatie);
                if (planner.editEvent(ID, nouEv))
                    std::cout << "Eveniment editat cu succes!\n";
                else
                    std::cout << "Eroare la editarea evenimentului!\n";
                break;
            }

            case 4: {
                planner.showEvents();
                break;
            }

            case 5: {
                // Cautare eveniment dupa ID
                unsigned int ID;
                std::cout << "Introduceti ID-ul cautat: ";
                std::cin >> ID;
                if (planner.findEventByID(ID))
                    planner.findEventByID(ID)->print();
                else
                    std::cout << "Nu exista eveniment cu acest ID!\n";
                break;
            }

            case 6: {
                // Cautare evenimente dupa titlu
                std::string titlu;
                std::cout << "Introduceti titlul: ";
                std::getline(std::cin, titlu); // citește linia completă (cu spații)
                auto rezultate = planner.findEventsByTitle(titlu);
                if (rezultate.empty())
                    std::cout << "Nu exista evenimente cu acest titlu!\n";
                else
                    for (const auto &ev: rezultate) {
                        ev.print();
                        std::cout << "-----" << std::endl;
                    }
                break;
            }

            case 7: {
                // Notifica despre urmatoarele evenimente
                planner.notifyUpcomingEvents();
                break;
            }

            case 8: {
                // Salveaza evenimentele in fisier
                std::string filename;
                std::cout << "Introduceti numele fisierului pentru salvare: ";
                std::cin >> filename;
                planner.saveToFile(filename);
                std::cout << "Salvare terminata!" << std::endl;
                break;
            }

            case 9: {
                // Incarca evenimentele din fisier
                std::string filename;
                std::cout << "Introduceti numele fisierului pentru incarcare: ";
                std::cin >> filename;
                planner.loadFromFile(filename);
                std::cout << "Incarcare terminata!" << std::endl;
                break;
            }

            default:
                return 0;;
        }

    }


return 0;

}