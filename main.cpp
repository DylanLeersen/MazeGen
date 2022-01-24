#include "maze.hpp"
int size = 10;
void createDeadEnds(){
    return;
}
int main(){
    //set maze size
    std::cout << "Size: "; std::cin >> size;
    //Genorate maze path
    genMaze();
    createDeadEnds();
    return 0;
}

