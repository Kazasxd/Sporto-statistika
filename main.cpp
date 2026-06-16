#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Zaidejas {
    string vardas;
    string pavarde;
    string sportas;
    int amzius;
    double taskuVidurkis;
    int rungtynes;
};

void nuskaitytiIsFailo(const string& failoVardas, vector<Zaidejas>& zaidejai);
void isaugotiIFaila(const string& failoVardas, const vector<Zaidejas>& zaidejai);
void atvaizduotiMenu();
void atvaizduotiVisusZaidejus(const vector<Zaidejas>& zaidejai);
void atvaizduotiVienaZaideja(const Zaidejas& z);
void pridetiZaideja(vector<Zaidejas>& zaidejai);
void redaguotiZaideja(vector<Zaidejas>& zaidejai);
void salintiZaideja(vector<Zaidejas>& zaidejai);
void ieskotiPagalPavarde(const vector<Zaidejas>& zaidejai);
void rikiuotiPagalTaskus(vector<Zaidejas>& zaidejai);
void komandosStatistika(const vector<Zaidejas>& zaidejai);
void geriausiasRezultatas(const vector<Zaidejas>& zaidejai);

int main() {
    vector<Zaidejas> zaidejai;
    string pradinisFailas = "zaidejai.txt";
    string rezultatuFailas = "issaugoti.txt";

    nuskaitytiIsFailo(pradinisFailas, zaidejai);

    int pasirinkimas;
    do {
        atvaizduotiMenu();
        cout << "Iveskite pasirinkima: ";
        cin >> pasirinkimas;
        cin.ignore();

        switch(pasirinkimas) {
            case 1:
                atvaizduotiVisusZaidejus(zaidejai);
                break;
            case 2:
                pridetiZaideja(zaidejai);
                isaugotiIFaila("issaugoti.txt", zaidejai);
                cout << "Duomenys issaugoti!\n";
                break;
            case 3:
                redaguotiZaideja(zaidejai);
                isaugotiIFaila("issaugoti.txt", zaidejai);
                break;
            case 4:
                salintiZaideja(zaidejai);
                isaugotiIFaila("issaugoti.txt", zaidejai);
                break;
            case 5:
                ieskotiPagalPavarde(zaidejai);
                break;
            case 6:
                rikiuotiPagalTaskus(zaidejai);
                atvaizduotiVisusZaidejus(zaidejai);
                break;
            case 7:
                komandosStatistika(zaidejai);
                break;
            case 8:
                geriausiasRezultatas(zaidejai);
                break;
            case 0:
                cout << "Programa baigia darba. Visi pakeitimai issaugoti.\n";
                isaugotiIFaila("issaugoti.txt", zaidejai);
                break;
            default:
                cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
        }
    } while(pasirinkimas != 0);

    return 0;
}

void nuskaitytiIsFailo(const string& failoVardas, vector<Zaidejas>& zaidejai) {
    ifstream failas(failoVardas);
    if (!failas.is_open()) {
        cerr << "Klaida: nepavyko atidaryti failo " << failoVardas << endl;
        return;
    }

    string eilute;
    while (getline(failas, eilute)) {
        stringstream ss(eilute);
        Zaidejas z;
        string vardasPavarde;

        getline(ss, vardasPavarde, ';');
        stringstream vp(vardasPavarde);
        vp >> z.vardas >> z.pavarde;

        getline(ss, z.sportas, ';');

        string temp;
        getline(ss, temp, ';');
        z.amzius = stoi(temp);

        getline(ss, temp, ';');
        z.taskuVidurkis = stod(temp);

        getline(ss, temp);
        z.rungtynes = stoi(temp);

        zaidejai.push_back(z);
    }

    failas.close();
    cout << "Nuskaityta " << zaidejai.size() << " zaideju.\n";
}

void isaugotiIFaila(const string& failoVardas, const vector<Zaidejas>& zaidejai) {
    ofstream failas(failoVardas);
    if (!failas.is_open()) {
        cerr << "Klaida: nepavyko irasyti i faila " << failoVardas << endl;
        return;
    }

    for (const auto& z : zaidejai) {
        failas << z.vardas << " " << z.pavarde << ";"
               << z.sportas << ";"
               << z.amzius << ";"
               << z.taskuVidurkis << ";"
               << z.rungtynes << endl;
    }

    failas.close();
}

void atvaizduotiMenu() {
    cout << "\n========== SPORTO ZAIDEJU STATISTIKA ==========\n";
    cout << "1. Perziureti visus zaidejus\n";
    cout << "2. Prideti nauja zaideja\n";
    cout << "3. Redaguoti zaidejo duomenis\n";
    cout << "4. Pasalinti zaideja\n";
    cout << "5. Ieskoti zaidejo pagal pavarde\n";
    cout << "6. Rikiuoti zaidejus pagal tasku vidurki\n";
    cout << "7. Komandos statistika\n";
    cout << "8. Rasti geriausia rezultatyvu zaideja\n";
    cout << "0. Isjungti programa\n";
    cout << "===============================================\n";
}

void atvaizduotiVienaZaideja(const Zaidejas& z) {
    cout << left << setw(20) << (z.vardas + " " + z.pavarde)
         << setw(15) << z.sportas
         << setw(8) << z.amzius
         << setw(15) << z.taskuVidurkis
         << setw(10) << z.rungtynes << endl;
}

void atvaizduotiVisusZaidejus(const vector<Zaidejas>& zaidejai) {
    if (zaidejai.empty()) {
        cout << "Nera zaideju duomenu.\n";
        return;
    }

    cout << "\nVardas Pavarde        Sportas       Amzius  Tasku_Vidurkis  Rungtynes\n";
    cout << "------------------------------------------------------------------------\n";
    for (const auto& z : zaidejai) {
        atvaizduotiVienaZaideja(z);
    }
    cout << "------------------------------------------------------------------------\n";
    cout << "Is viso zaideju: " << zaidejai.size() << endl;
}

void pridetiZaideja(vector<Zaidejas>& zaidejai) {
    Zaidejas naujas;

    cout << "Iveskite zaidejo varda: ";
    getline(cin, naujas.vardas);
    cout << "Iveskite zaidejo pavarde: ";
    getline(cin, naujas.pavarde);
    cout << "Iveskite sporto saka (Krepsinis/Futbolas/Tenisas): ";
    getline(cin, naujas.sportas);
    cout << "Iveskite amziu: ";
    cin >> naujas.amzius;
    cout << "Iveskite tasku vidurki: ";
    cin >> naujas.taskuVidurkis;
    cout << "Iveskite suzaistu rungtyniu skaiciu: ";
    cin >> naujas.rungtynes;
    cin.ignore();

    zaidejai.push_back(naujas);
    cout << "Zaidejas sekmingai pridetas!\n";
}

void redaguotiZaideja(vector<Zaidejas>& zaidejai) {
    string pavarde;
    cout << "Iveskite zaidejo pavarde, kuri norite redaguoti: ";
    getline(cin, pavarde);

    for (auto& z : zaidejai) {
        if (z.pavarde == pavarde) {
            cout << "Rastas zaidejas:\n";
            atvaizduotiVienaZaideja(z);

            cout << "Iveskite naujus duomenis:\n";
            cout << "Naujas vardas (" << z.vardas << "): ";
            string input;
            getline(cin, input);
            if (!input.empty()) z.vardas = input;

            cout << "Nauja pavarde (" << z.pavarde << "): ";
            getline(cin, input);
            if (!input.empty()) z.pavarde = input;

            cout << "Nauja sporto saka (" << z.sportas << "): ";
            getline(cin, input);
            if (!input.empty()) z.sportas = input;

            cout << "Naujas amzius (" << z.amzius << "): ";
            getline(cin, input);
            if (!input.empty()) z.amzius = stoi(input);

            cout << "Naujas tasku vidurkis (" << z.taskuVidurkis << "): ";
            getline(cin, input);
            if (!input.empty()) z.taskuVidurkis = stod(input);

            cout << "Naujas rungtyniu skaicius (" << z.rungtynes << "): ";
            getline(cin, input);
            if (!input.empty()) z.rungtynes = stoi(input);

            cout << "Duomenys atnaujinti!\n";
            return;
        }
    }
    cout << "Zaidejas su pavarde " << pavarde << " nerastas.\n";
}

void salintiZaideja(vector<Zaidejas>& zaidejai) {
    string pavarde;
    cout << "Iveskite zaidejo pavarde, kuri norite pasalinti: ";
    getline(cin, pavarde);

    auto it = remove_if(zaidejai.begin(), zaidejai.end(),
        [&pavarde](const Zaidejas& z) { return z.pavarde == pavarde; });

    if (it != zaidejai.end()) {
        zaidejai.erase(it, zaidejai.end());
        cout << "Zaidejas pasalintas!\n";
    } else {
        cout << "Zaidejas su pavarde " << pavarde << " nerastas.\n";
    }
}

void ieskotiPagalPavarde(const vector<Zaidejas>& zaidejai) {
    string pavarde;
    cout << "Iveskite paieskos pavarde: ";
    getline(cin, pavarde);

    bool rastas = false;
    for (const auto& z : zaidejai) {
        if (z.pavarde == pavarde) {
            if (!rastas) {
                cout << "\nVardas Pavarde        Sportas       Amzius  Tasku_Vidurkis  Rungtynes\n";
                cout << "------------------------------------------------------------------------\n";
                rastas = true;
            }
            atvaizduotiVienaZaideja(z);
        }
    }

    if (!rastas) {
        cout << "Zaidejas su pavarde " << pavarde << " nerastas.\n";
    }
}

void rikiuotiPagalTaskus(vector<Zaidejas>& zaidejai) {
    sort(zaidejai.begin(), zaidejai.end(),
        [](const Zaidejas& a, const Zaidejas& b) {
            return a.taskuVidurkis > b.taskuVidurkis;
        });
    cout << "Zaidejai surikiuoti pagal tasku vidurki!\n";
}

void komandosStatistika(const vector<Zaidejas>& zaidejai) {
    if (zaidejai.empty()) {
        cout << "Nera duomenu.\n";
        return;
    }

    vector<string> sportai = {"Krepsinis", "Futbolas", "Tenisas"};

    for (const string& sportas : sportai) {
        double sumaTasku = 0;
        int sumaRungtyniu = 0;
        int skaicius = 0;

        for (const auto& z : zaidejai) {
            if (z.sportas == sportas) {
                sumaTasku += z.taskuVidurkis;
                sumaRungtyniu += z.rungtynes;
                skaicius++;
            }
        }

        if (skaicius > 0) {
            cout << "\n=== " << sportas << " ===\n";
            cout << "Zaideju skaicius: " << skaicius << endl;
            cout << "Bendras tasku vidurkis: " << fixed << setprecision(2) << sumaTasku << endl;
            cout << "Vidutinis tasku vidurkis komandoje: " << sumaTasku / skaicius << endl;
            cout << "Viso suzaista rungtyniu: " << sumaRungtyniu << endl;
        }
    }
}

void geriausiasRezultatas(const vector<Zaidejas>& zaidejai) {
    if (zaidejai.empty()) {
        cout << "Nera duomenu.\n";
        return;
    }

    auto geriausias = max_element(zaidejai.begin(), zaidejai.end(),
        [](const Zaidejas& a, const Zaidejas& b) {
            return a.taskuVidurkis < b.taskuVidurkis;
        });

    cout << "\nGeriausias rezultatyvumo zaidejas:\n";
    cout << "Vardas Pavarde        Sportas         Amzius  TaskuVidurkis  Rungtynes\n";
    cout << "------------------------------------------------------------------------\n";
    atvaizduotiVienaZaideja(*geriausias);
}
