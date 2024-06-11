#include "arbolB.h"
#include "fileManagement.h"
#include "cuckooHashing.h"
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <random>

using namespace std;


int main(){

    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<uint64_t> dist(1000000000000, 9999999999999);

    vector<string> nombres ={"Carlos","Angello","Marcelo","Federico","Valeska","Emmanuel",
    "Samuel","Namir","Ysabel","Renzo","Erick","Esteban","Julia","Brenda","Ariana","Manuela",
    "Estefano","Araceli","Gabriel","Victor","Angel","Valentina","Valeria","Italo","Sofia","Amber",
    "Peter","Kevin","Gwen","Miguel","Daniela","Daniel","Tomas"};

    Btree tree(3);
    cuckooHashing cuckoo(100003);

    vector<UserData> users;

    for(int i = 0;i<1000;i++){
        uint64_t dni = dist(gen);
        UserData userData;
        userData->dni = dni;
        userData->nombreCompleto = nombres[i % nombres.size()] + "_" + to_string(i);
        userData->nacionalidad = "Nacionalidad_" + to_string(i);
        userData->birthPlace = "Lugar de Nacimiento_" + to_string(i);
        userData->direccion = "Direccion_" + to_string(i);
        userData->telefono = "Telefono_" + to_string(i);
        userData->email = "Email_" + to_string(i);
        userData->estadoCivil = "EstadoCivil_" + to_string(i);

        users.push_back(userData);

        if(!cuckoo.search(dni)){
            cuckoo.insert(dni);
            tree.insert(dni,make_shared<UserData>(userData));
        }
    }

    //guarda datos
    string filename = "user_data.dat";
    saveUserData(users,filename);

   vector<UserData> loadedUsers = loadUserData(filename);

    for (const auto& user : loadedUsers) {
        cout << "DNI: " << user.dni << ", Nombre: " << user.nombreCompleto << endl;
    }

    return 0;
}