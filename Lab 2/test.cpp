#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int fmax=n;
    int smax=0;
    while(n!=0) {
        cin >> n;
        if(n==fmax){
             smax=n;
        }
        if(n>fmax){
            smax=fmax;
            fmax=n;
        }
        if(n < fmax && n>smax){
            smax=n;
        }
    }
    cout << smax << endl;
    return 0;
}