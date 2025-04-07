#include <iostream>
using namespace std;

int main() {
int height = 5;
for (int row = 1; row <= height; row++) {
    for (int space = 0; space < height - row; space++) {
        std::cout << " ";
    }
    for (int star = 0; star < row; star++) {
        std::cout << "*";
    }
    std::cout << std::endl;
break;
}


}
