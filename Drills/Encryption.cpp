#include <iostream>

char key = 'A';

void XorCiper(std::string*  Textptr, char Key){

    for (size_t i = 0; i < (*Textptr).size(); i++){
        (*Textptr)[i] ^= Key;
    }
};

int main() {
    std::string Text = "Something secret!";
    auto *Ptr = &Text;

    std::cout << Text << '\n';
    XorCiper(Ptr, key);
    std::cout << Text << '\n';
    
    XorCiper(Ptr, key);
    std::cout << Text;
}