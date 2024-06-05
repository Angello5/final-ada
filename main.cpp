#include "arbolB.h"
#include "fileManagement.h"
#include "cuckooHashing.h"
#include <boost/random.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

string generateRandomDNI(boost::random::mt19937& gen){
    boost::random::uniform_int_distribution<> dist(10000000, 99999999); // Rango para DNIs de 8 dígitos
    int random_dni = dist(gen);
    return to_string(random_dni);
}

int main(){
    boost::random::mt19937 gen(time(0));

    vector<string> nombres ={"Carlos","Angello","Marcelo","Federico","Valeska","Emmanuel",
    "Samuel","Namir","Ysabel","Renzo","Erick","Esteban","Julia","Brenda","Ariana","Manuela",
    "Estefano","Araceli","Gabriel","Victor","Angel","Valentina","Valeria","Italo","Sofia","Amber",
    "Peter","Kevin","Gwen","Miguel","Daniela","Daniel","Tomas"};

    Btree tree(10);
    cuckooHashing cuckoo(100003);

    for(int i = 0;i<1000;i++){
        string dni=generateRandomDNI(gen);
        shared_ptr<UserData> userData = make_shared<UserData>();
        userData->dni = dni;
        userData->nombreCompleto = nombres[i % nombres.size()] + "_" + to_string(i);
        userData->nacionalidad = "Nacionalidad_" + to_string(i);
        userData->birthPlace = "Lugar de Nacimiento_" + to_string(i);
        userData->direccion = "Direccion_" + to_string(i);
        userData->telefono = "Telefono_" + to_string(i);
        userData->email = "Email_" + to_string(i);
        userData->estadoCivil = "EstadoCivil_" + to_string(i);

        if(!cuckoo.search(dni)){
            cuckoo.insert(dni);
            tree.insert(dni,userData);
        }
    }

    //guarda datos
    vector<UserData> users;
    saveUserData(users,"user_data.txt");

    //carga datos
    users = loadUserData("user_data.txt");
}