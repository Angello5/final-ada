#include "arbolB.h"
#include "fileManagement.h"
#include "cuckooHashing.h"
#include <boost/random.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution>
#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

int main(){
    boost::random::mt19937 gen(time(0));

    Btree tree(10);
    cuckooHashing cuckoo(100003);

    for(int i = 0;i<1000;i++){
        string dni=generateRandomDNI(gen);
        shared_ptr<UserData> UserData = make_shared<UserData>();
        UserData->dni = dni;
        userData->nombreCompleto = "Nombre_" + to_string(i);
        userData->nacionalidad = "Nacionalidad_" + to_string(i);
        userData->birthPlace = "Lugar de Nacimiento_" + to_string(i);
        userData->direccion = "Direccion_" + to_string(i);
        userData->telefono = "Telefono_" + to_string(i);
        userData->email = "Email_" + to_string(i);
        userData->estadoCivil = "EstadoCivil_" + to_string(i);

        if(!cuckoo.search(dni)){
            cuckoo.insert(dni);
            tree.insert(dni,UserData);
        }
    }

    //guarda datos
    vector<UserData> users;
    saveUserData(users,"user_data.txt");

    //carga datos
    users = loadUserData("user_data.txt")
}