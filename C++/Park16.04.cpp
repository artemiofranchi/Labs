#include <iostream>
using namespace std;

char gc(){
    char c;
    cin >> c;
    return c;
}

void C(){
    if (gc() != 'c'){
        cout << "error!!" << '\n';
        exit(0);
    }
    cout << "returning c" << '\n';
}

void AB(){
    char sym = gc();
    if (sym == 'c'){
        cout << "returning c" << '\n';
        C();
    }
    else if (sym == 'a'){
        cout << "returning a" << '\n';
    }
    else{
        cout << "error!" << '\n';
        exit(0);
    }
}


void S(){
    if (gc() != 'a'){
        cout << "error!!!" << '\n';
        exit(0);
    }
    cout << "returning a" << '\n';
    AB();

}

int main(){
    S();
    if (gc() != '\n'){
        cout << "error!!!!";
    }
}

