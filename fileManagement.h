
#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H
#include "userData.h"
#include <vector>
#include <string>

using namespace std;

void saveUserData(const vector<UserData>& users, const string& filename);
vector<UserData> loadUserData(const string& filename);

#endif 
