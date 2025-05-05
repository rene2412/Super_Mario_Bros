#include <iostream>
#include <string>
using namespace std;



int main() { 
string s = "hello world";

for (char c : s) {
	cout << &s << endl;
}

}
