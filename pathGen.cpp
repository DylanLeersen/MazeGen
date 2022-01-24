#include "maze.hpp"
extern int size;

enum direction{
up, down, left, right
};
bool error;
char maze[21][21];
void mazeToHashtag(){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            maze[i][j] = '#';
        }
    }
    return;
}

void printMaze(){
    for(int i = 0; i < size; i++){
        for(int j =0; j < size; j++){
            std::cout << maze[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}
bool checkNeighbours(int row, int col){
    int neighbourCount = 0;
    //check top
    for(int i = 0; i < 3; i++){
        if(maze[row - 1][col -1 + i] == ' '){
            neighbourCount += 1;
        }
    }
    //check sides
    //left
    if(maze[row][col - 1] == ' '){
        neighbourCount += 1;
    }
    //right
    if(maze[row][col + 1] == ' '){
        neighbourCount += 1;
    }
    //check bottom
    for(int i = 0; i < 3; i++){
        if(maze[row + 1][col - 1 + i] == ' '){
            neighbourCount += 1;
        }
    }

    
    return neighbourCount <= 2 ? true : false;
}

bool checkNeighbours(int row, int col, bool TurnTo1s){
    int neighbourCount = 0;
    //check top
    for(int i = 0; i < 3; i++){
        if(maze[row - 1][col -1 + i] == ' '){
            neighbourCount += 1;
        }
    }
    //check sides
    //left
    if(maze[row][col - 1] == ' '){
        neighbourCount += 1;
    }
    //right
    if(maze[row][col + 1] == ' '){
        neighbourCount += 1;
    }
    //check bottom
    for(int i = 0; i < 3; i++){
        if(maze[row + 1][col - 1 + i] == ' '){
            neighbourCount += 1;
        }
    }

    if(neighbourCount == 1){
            //change the spots where are techinacally are possble but if you chose more then one of them then it means they are no longer possble
            //we will use 1s to represent these

            //top
            for(int i = 0; i < 3; i++){
                if(maze[row - 1][col -1 + i] == '#'){
                    maze[row -1][col - 1 + i] = '1';
                }
            }
            //left
            if(maze[row][col - 1] == '#'){
                maze[row][col - 1] = '1';
            }
            //right
            if(maze[row][col + 1] == '#'){
                maze[row][col + 1] = '1';
            }
            //check bottom
            for(int i = 0; i < 3; i++){
                if(maze[row + 1][col - 1 + i] == '#'){
                    maze[row + 1][col - 1 + i] = '1';
                }
            }
            
        }
        return true;
}
void change1sToNs(int row, int col){
    
    for(int i = 0; i < 3; i++){
        if(maze[row - 1][col -1 + i] == '1'){
            maze[row -1][col - 1 + i] = 'N';
        }/*else if (maze[row - 1][col - 1 + i] == ' ' && !(maze[row][col] == '1')) {
            change1sToNs(row - 1, col - 1 + i);
        }*/
    }
    //left
    if(maze[row][col - 1] == '1'){
        maze[row][col - 1] = 'N';
    }/*else if(maze[row][col - 1] == ' ' && !(maze[row][col] == '1')){
        change1sToNs(row, col - 1);
    }*/
    //right
    if(maze[row][col + 1] == '1'){
        maze[row][col + 1] = 'N';
    }/*else if (maze[row][col + 1] == ' ' && !(maze[row][col] == '1') ) {
        change1sToNs(row, col + 1);
    }*/
    //check bottom
    for(int i = 0; i < 3; i++){
        if(maze[row + 1][col - 1 + i] == '1'){
            maze[row + 1][col - 1 + i] = 'N';
        }/*else if (maze[row + 1][col - 1 + i] == ' ' && !(maze[row][col] == '1')) {
            change1sToNs(row + 1, col - 1 + i);
        }*/
    }
}
void movePosTo(int toRow, int toCol, int & row, int & col){
    change1sToNs(toRow, toCol);
    // make sure this comes after change1stoNs because if it is not then it will cause a infinite loop if it comes first
    maze[toRow][toCol] = ' ';
    checkNeighbours(toRow, toCol, true);
    
    
    row = toRow;
    col = toCol;
    return;
}

bool winCheck(int & row, int & col, int endRow, int endCol){
    if(row - 1 == endRow && col == endCol){
        return true;
    }else if(row == endRow){
        if(col - 1 == endCol){
            return true;
        }else if(col + 1 == endCol){
            return true;
        }
    }
    return false;
    
}
void mEater(int row, int col, bool oneState){
    maze[row][col] = '#';
    //down
    if(maze[row + 1][col] == 'M' && checkNeighbours(row + 1, col)){
        mEater(row + 1, col, false);
    }
    //left
    if(maze[row][col - 1] == 'M' && checkNeighbours(row, col - 1)){
        mEater(row, col - 1, false);
    }
    //up
    if(maze[row - 1][col] == 'M' && checkNeighbours(row - 1, col)){
        mEater(row - 1, col, false);
    }
    //right
    if(maze[row][col + 1] == 'M' && checkNeighbours(row, col + 1)){
        mEater(row, col + 1, false);
    }


    // we can move onto the 1s with this but once we are in that state then we can not move onto another 1
    if(!oneState){
        //down
        if(maze[row + 1][col] == '1' && checkNeighbours(row + 1, col)){
        mEater(row + 1, col, true);
        }
        //left
        if(maze[row][col - 1] == '1' && checkNeighbours(row, col - 1)){
            mEater(row, col - 1, true);
        }
        //up
        if(maze[row - 1][col] == '1' && checkNeighbours(row - 1, col)){
            mEater(row - 1, col, true);
        }
        //right
        if(maze[row][col + 1] == '1' && checkNeighbours(row, col + 1)){
            mEater(row, col + 1, true);
        }
    }
    
    

    
    return;
}
void isPossible(int endRow, int endCol){
    // turn #s to Ms
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(maze[i][j] == '#'){
                maze[i][j] = 'M';
            }
        }
    }

    //call recursvie mEaters which will flood the map and eat all of the Ms they can get turning them into #s
    //left
    mEater(endRow, endCol - 1, false);
    //down
    mEater(endRow + 1, endCol, false);
    //right
    mEater(endRow, endCol + 1, false);
    //turn left over Ms into Ns so they will not be touched
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(maze[i][j] == 'M'){
                maze[i][j] = 'N';
            }
        }
    }
    
   return; 
}

bool does1Option(int row, int col){
    //up
    if(maze[row - 1][col] == '#'){
        return true;
    }
    //down
    if(maze[row + 1][col] == '#'){
        return true;
    }
    //left
    if(maze[row][col - 1] == '#'){
        return true;
    }
    //right
    if(maze[row][col + 1] == '#'){
        return true;
    }
    return false;
}
bool isUpPoss(int row, int col){
    if(row - 1 >= 0 && (maze[row - 1][col] == '#' || maze[row - 1][col] == '1') && checkNeighbours(row - 1, col) ){
            if(maze[row - 1][col] == '1' && !does1Option(row - 1, col)){
                return false;
            }
            return true;
        }else{
            return false;
        }
}

bool isDownPoss(int row, int col){
    if(row + 1 <= size - 1 && (maze[row + 1][col] == '#' || maze[row + 1][col] == '1') && !(col == 0) && !(col == size - 1) && checkNeighbours(row + 1, col)){
            if(maze[row + 1][col] == '1' && !does1Option(row  + 1, col)){
                return false;
            }
            return true;
        }else{
            return false;
        }
}
bool isLeftPoss(int row, int col){
    if(col - 1 >= 0 && (maze[row][col - 1] == '#' || maze[row][col - 1] == '1') && checkNeighbours(row, col - 1) ){
            if(maze[row][col - 1] == '1' && !does1Option(row, col - 1)){
                return false;
            }
            return true;
        }else{
            return false;
        }
}
bool isRightPoss(int row, int col){
    if(col + 1 <= size - 1 && (maze[row][col + 1] == '#' || maze[row][col + 1] == '1') && checkNeighbours(row, col + 1)){
            if(maze[row][col + 1] == '1' && !does1Option(row, col + 1)){
                return false;
            }
            return true;
        }else{
            return false;
        }
}
void checkPossible(int row, int col, bool & isUp, bool & isDown, bool & isLeft, bool  & isRight, int endRow, int endCol){
    isPossible(endRow, endCol);
    // is up possible
        if(isUpPoss(row, col)){
            isUp = true;
        }else {
            isUp = false;
        }
        // is Down possbile
        if(isDownPoss(row, col))
        {
            isDown = true;
        }else{
            isDown = false;
        }
        // is Left possbile
        if(isLeftPoss(row, col)){
            isLeft = true;
        }else{
            isLeft = false;
        }
        // is Right possbile
        if(isRightPoss(row, col)){
            isRight = true;
        }else{
            isRight = false;
        }
        
        if( (!isUp) && (!isDown) && (!isLeft) && (!isRight)){
            error = true;
        }
        return;
}

void genMaze(){
    error = false;
    srand(time(0));
    mazeToHashtag();
    //vars
        int row = size - 1 ,col = size/2;
        maze[row][col] = '0';
        int endRow = 0, endCol = 10;
        maze[endRow][endCol] = 'E';
        bool isUp;
        bool isDown;
        bool isLeft;
        bool isRight;
        bool ready;
    
    while(!winCheck(row, col, endRow, endCol)){
        if(error){
            srand(time(0));
            mazeToHashtag();
            row = size - 1; 
            col = size/2;
            maze[row][col] = '0';
            maze[endRow][endCol] = 'E';
            
            error = false;
        }
        checkPossible(row, col, isUp, isDown, isLeft, isRight, endRow, endCol);
        
        
        do{
            
            switch (rand()%4) {
                case 0:
                    if(isUp){
                        movePosTo(row - 1, col, row, col);
                        ready = true;
                    }else{
                        ready = false;
                    }
                    break;
                case 1:
                    if(isDown){
                        movePosTo(row + 1, col, row, col);
                        ready = true;
                    }else{
                        ready = false;
                    }
                    break;
                case 2:
                    if(isLeft){
                        movePosTo(row, col - 1, row, col);
                        ready = true;
                    }else{
                        ready = false;
                    }
                    break;
                case 3:
                    if(isRight){
                        movePosTo(row, col + 1, row, col);
                        ready = true;
                    }else{
                        ready = false;
                    }
                    break;
            }
            
            
        }while(!(ready) && !error);
        
        
    }

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(maze[i][j] != ' ' && maze[i][j] != 'E' && maze[i][j] != '0'){
                maze[i][j] = '#';
            }
        }
    }
    printMaze();
}
