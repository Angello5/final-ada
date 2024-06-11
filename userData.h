#ifndef USERDATA_H
#define USERDATA_H
#include <string>
#include <memory>
#include <cstdint>

using namespace std;

struct UserData
{
    uint64_t dni;
    string nombreCompleto;
    string nacionalidad;
    string birthPlace;
    string direccion;
    string telefono;
    string email;
    string estadoCivil;

};


#endif 