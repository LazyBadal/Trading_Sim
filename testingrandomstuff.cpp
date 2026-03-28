#include <iostream>
#include <random>
using namespace std;

int main() {
    int i=1;
    mt19937 gen(time(0));
    uniform_int_distribution<> dist(1, 50);
    while (i <= 40){
        i++;
        cout << dist(gen) << " ";
    }
}