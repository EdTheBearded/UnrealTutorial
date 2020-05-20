#include <iostream>
#include <ctime>

void PrintIntro(const int Difficulty, const int CodeSum, const int CodeProd) {

    std::cout << "\nThis is HQ, our cybersecurity team investigated the bomb's level " << Difficulty << std::endl;
    std::cout << "binaries and discovered the code consists of 3 digits, which:\n";
    std::cout << "Sum up to: " << CodeSum << std::endl;
    std::cout << "Multiplied are equal to: " << CodeProd << std::endl;
    std::cout << "\nIts now up to you, HQ out.\n";
    std::cout << "\nInsert code > ";

}

bool PlayGameWithDifficulty(int Difficulty) {

    const int CodeA{rand() % Difficulty + Difficulty};
    const int CodeB{rand() % Difficulty + Difficulty};
    const int CodeC{rand() % Difficulty + Difficulty};

    const int CodeSum{CodeA + CodeB + CodeC};
    const int CodeProd{CodeA * CodeB * CodeC};
    PrintIntro(Difficulty, CodeSum, CodeProd);

    int GuessA{};
    int GuessB{};
    int GuessC{};

    std::cin >> GuessA >> GuessB >> GuessC;
    const int GuessSum = GuessA + GuessB + GuessC;
    const int GuessProd = GuessA * GuessB * GuessC;

    if (GuessProd == CodeProd && GuessSum == CodeSum) {
        return true;
    }
    else {
        std::cout << "And that, kids, is why there is a giant crater here...\n";
        std::cout << "GAME OVER\n";

        return false;
    }

}

int main() {
    
    srand(time(NULL));
    int LevelDifficulty{1};
    const int MaxLevelDifficulty{2};

    std::cout << "\n\nYou're a field agent who has encountered a bomb! HQ can't defuse it remotely\n";
    std::cout << "but they did check the bomb's controller binaries and are helping you over comms..\n\n";

    while(LevelDifficulty <= MaxLevelDifficulty){
        if (!PlayGameWithDifficulty(LevelDifficulty)){
            return 0;
        }
        std::cin.clear();
        std::cin.ignore();
        if (++LevelDifficulty <= MaxLevelDifficulty) {
            std::cout << "Great work! It seems like this stage was defused!!!\n";
        }

    }

    std::cout << "Nice job out there Agent! You got me sweating bullets, not gonna lie...\n";
    std::cout << "But I've never doubted you would make it!\n";

    return 0;
}