#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

void print_vector_vector_string(vector<vector<string>> lst){
    for (size_t i=0;i<lst.size();i++){
        for(size_t j=0;j<lst[0].size();j++){
            cout << lst[i][j] << " ";
        }
        cout << endl;
    }
}

vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}
