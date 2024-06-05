#include "fileManagement.h"
#include <fstream>
#include <sstream>

using namespace std;

void saveUserData(vector<UserData>& users, string& filename){
    ofstream file(filename);
        for(auto& user : users){
            file<< user.dni<< "," <<user.nombreCompleto<<"," <<user.nacionalidad<<","
            <<user.birthPlace<<","<<user.direccion<< "," <<user.telefono<<"," <<user.email<<
            ","<<user.estadoCivil<<"\n";
        }
    file.close();
}

vector<UserData> loadUserData(string& filename){
    vector<UserData> users;
    ifstream file(filename);
    string line;
    while(getline(file,line));
    istringstream ss(line);
    UserData user;
    getline(ss,user.dni,',');
    getline(ss,user.nombreCompleto,',');
    getline(ss,user.nacionalidad,',');
    getline(ss,user.birthPlace,',');
    getline(ss,user.direccion,',');
    getline(ss,user.telefono,',');
    getline(ss,user.email,',');
    getline(ss,user.estadoCivil,',');
    users.push_back(user);
}
file.close();
return users;