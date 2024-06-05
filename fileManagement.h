
#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H
#include "UserData.h"
#include <vector>
#include <string>

using namespace std;

void saveUserData(vector<UserData>& users, string& filename);
vector<UserData> loadUserData(string& filename);

#endif 
