#include <iostream>
#include <memory>

struct  Noisy
{
    Noisy()  { std::cout << "Born" << '\n'; };
    ~Noisy() { std::cout << "Died" << '\n'; };
};


int main() {
    auto a = std::make_unique<std::string>("Hlo Guys, i will be sold to B!");
    auto b = std::move(a);
    auto c = std::make_shared<std::string>("Pizza!");
    auto d = std::make_unique<int>(1000);
    
    // In an small road

    auto aCLONE = std::move(d);

    // in the lunch room

    // lets share!

    auto aNO2 = c;

    // Interrogation Room

    if (a == nullptr){
        std::cout << "I became a nullptr when i sold the hostage to B." << '\n';
        std::cout << "but i now am a stack of cash! (int) " << '\n';

        std::cout << *aCLONE << '$' << '\n';
        std::cout << "Said by A......... C... L...O..N.E" << '\n';

        std::cout << "\033[3m ACLONE IS SHOT \033[0m" << '\n';
        std::cout << "Where is the real A!?!?" << '\n';

        std::cout << "A_No2 : hi!, i shared lunch with c" << '\n';
        std::cout << *aNO2 << '\n';
    }
    if (b != nullptr){
        std::cout << *b << '\n';

        std::cout << "Said by hostage under B" << '\n';
    }
    if (c != nullptr){
        std::cout << "I am not a null ptr because i share!";
        std::cout << *c;

    }
    if (d == nullptr){
        std::cout << "D is sad because he lost his money!" << '\n';
    }

    std::cout << '\n' << "Moral of the story, what is done cannot be undone. You have to chose what you want to end up being at the start" << '\n';
    std::cout << '\n' << "Also share or you will end up with nothing for yourself!";
}