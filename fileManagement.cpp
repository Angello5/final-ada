#include "fileManagement.h"
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void saveUserData(const vector<UserData>& users, const string& filename){
    ofstream file(filename);
        for(const auto& user : users){
           file.write(reinterpret_cast<const char*>(&user.dni), sizeof(user.dni));

           auto writeString = [&file](const string& str){
            size_t size = str.size();
            file.write(reinterpret_cast<const char*>(&size), sizeof(size));
            file.write(str.c_str(), size);
           };

            writeString(user.nombreCompleto);
            writeString(user.nacionalidad);
            writeString(user.birthPlace);
            writeString(user.direccion);
            writeString(user.telefono);
            writeString(user.email);
            writeString(user.estadoCivil);
        }
    file.close();
}

vector<UserData> loadUserData(const string& filename){
    vector<UserData> users;
    ifstream file(filename, ios::binary);

    while(file){
        UserData user;
        file.read(reinterpret_cast<char*>(user.dni), sizeo(user.dni));

        auto readString = [&file]() {
            size_t size;
            file.read(reinterpret_cast<char*>(&size), sizeof(size));
            std::string str(size, ' ');
            file.read(&str[0], size);
            return str;
        };
        
        user.nombreCompleto = readString();
        user.nacionalidad = readString();
        user.birthPlace = readString();
        user.direccion = readString();
        user.telefono = readString();
        user.email = readString();
        user.estadoCivil = readString();

        if(file) users.push_back(user);
    }
file.close();
return users;
}