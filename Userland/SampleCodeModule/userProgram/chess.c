#include <stdint.h>

//PIECES
#define KING 1
#define QUEEN 2
#define KNIGHT 3
#define ROOK 4
#define BISHOP 5
#define PAWN 6
//

#define MAX_POS 8
#define WHITE 1
#define BLACK 2

//
#define PLAYER1 1
#define PLAYER2 2

#define MAXPLAYS 99
/*
struct piece {
    int x;
    int y;
    int type;
    int team;
};
struct log{
    struct piece p;
    int toX;
    int toY;
};
struct piece board[MAX_POS][MAX_POS] = {0};
struct log logs1[MAXPLAYS] = {0};
struct log logs2[MAXPLAYS] = {0};



//int validKnightMov(int fromX, int fromY, int toX, int toY);
int validPawnMov(struct piece p, int x, int y);
void initBoard();

int winner = 0, time1 = 0, time2 = 0, indexLogs1=0,indexLogs2=0;

int main(){
    initBoard();
    int turn = PLAYER1;
    while(!isWinner()){
        int fromX,fromY,toX,toY;
        initTimer();
        int enroque = scanf("desde %d,%d hacia %d,%d\n",fromX,fromY,toX,toY);
        if(enroque)
            tryEnroque(turn);
        else if(isValidMovement(toX,toY,board[fromX][fromY])){
            if(turn == PLAYER1){
                logs1[indexLogs1++] = (struct log){board[fromX][fromY], toX,toY};
            }
            if(turn == PLAYER2){
                logs2[indexLogs2++] = (struct log){board[fromX][fromY], toX,toY};
            }
            makeMov(fromX,fromY,toX,toY);
        }
        if(turn == PLAYER1){
            time1 = endTimer();
            turn = PLAYER2;
        }else{
            time2 = endTimer();
            turn = PLAYER1;
        }
        updateView(board);
    }
    return 0;
}

int makeMov(int fromX,int fromY,int toX,int toY){
        board[toX][toY] = board[fromX][fromY];
        void *c = 0;
        memcpy((board+fromX+fromY), c,1);
}

int isWinner(){
    if(time1 - time2 > 60){
        return 3;
    }
    int flag = 0;
    for(int i = 0; i <= MAX_POS;i++){
        for(int j = 0; j <= MAX_POS;j++){
            if(!&board[i][j] && board[i][j].type == KING && board[i][j].team == BLACK){
                flag =1;
            }
        }
    }
    if(flag == 0){
        winner = 1;
        return 1;
    }else{
        flag = 0;
        for(int i = 0; i <= MAX_POS;i++){
            for(int j = 0; j <= MAX_POS;j++){
                if(!&board[i][j] && board[i][j].type == KING && board[i][j].team == WHITE){
                    flag =1;
                }
            }
        }
    }
    if(flag == 0){
        winner = 2;
        return 2;
    }
    return 0;
}


void initBoard(){
    board[0][0] = (struct piece) {0,0,ROOK,WHITE};
    board[1][0] = (struct piece) {1,0,KNIGHT,WHITE};
    board[2][0] = (struct piece) {2,0,BISHOP,WHITE};
    board[3][0] = (struct piece) {3,0,QUEEN,WHITE};
    board[4][0] = (struct piece) {4,0,KING,WHITE};
    board[5][0] = (struct piece) {5,0,BISHOP,WHITE};
    board[6][0] = (struct piece) {6,0,KNIGHT,WHITE};
    board[7][0] = (struct piece) {7,0,ROOK,WHITE};

    board[0][7] = (struct piece) {0,7,ROOK,BLACK};
    board[1][7] = (struct piece) {1,7,KNIGHT,BLACK};
    board[2][7] = (struct piece) {2,7,BISHOP,BLACK};
    board[3][7] = (struct piece) {3,7,QUEEN,BLACK};
    board[4][7] = (struct piece) {4,7,KING,BLACK};
    board[5][7] = (struct piece) {5,7,BISHOP,BLACK};
    board[6][7] = (struct piece) {6,7,KNIGHT,BLACK};
    board[7][7] = (struct piece) {7,7,ROOK,BLACK};
}

int isValidMovement(int x, int y,struct piece p){
    if(x > MAX_POS && y > MAX_POS)
        return 0;
    
    switch (p.type){
        case KING:
            return p.y == (y+1) || p.x == (x+1);  
        case QUEEN:
            //Chequeo que este el camino libre
            for(int i = p.x; i <= x;i++){
                for(int j = p.y; j <= y;j++){
                    if(!&board[i][j]){
                        return 0;
                    }
                }
            }
            return &board[x][y] ||(board[x][y].team != p.team);
        case PAWN:
            return validPawnMov(p,x,y);
        case KNIGHT:
            return validKnightMov(p,x,y);
        case ROOK:
            if(p.x == x){
                for(int j = p.y-1; j <= y;j++){
                    if(!&board[x][j]){
                        return 0;
                    }
                }
                return  &board[x][y] == 0||(board[x][y].team != p.team);
            }else if(p.y == y){
                for(int j = p.x-1; j <= y;j++){
                    if(!&board[j][y]){
                        return 0;
                    }
                }
                return  &board[x][y] == 0 ||(board[x][y].team != p.team);
            }else{
                return 0;
            }
        case BISHOP:
            if(p.x - x == p.y - y){
                for(int i = p.x; i <= x;i++){
                    for(int j = p.y; j <= y;j++){
                        if(!&board[j][y]){
                            return 0;
                        }
                    }
                }
                return  &board[x][y] == 0 ||(board[x][y].team != p.team);
            };
    }
    return 0;
}

int validPawnMov(struct piece p, int x, int y){
    return (p.y == 1 && p.team == WHITE && p.y <= y-2 && p.x == x && &board[x][y] ==0) ||
            (p.y == 6 && p.team == BLACK && p.y >= y+2 && p.x == x) ||
            (p.team == BLACK && p.y == y-1 && p.x == x && &board[x][y] ==0) ||
            (p.team == WHITE && p.y == y+1 && p.x == x && &board[x][y] ==0) ||
            (p.team == WHITE && p.y == y+1 && p.x == x+1 && (&board[x][y] == 0|| p.team != board[x][y].team)) ||
            (p.team == WHITE && p.y == y+1 && p.x == x-1 && (&board[x][y] == 0|| p.team != board[x][y].team)) ||
            (p.team == BLACK && p.y == y-1 && p.x == x+1 && (&board[x][y] == 0|| p.team != board[x][y].team)) ||
            (p.team == BLACK && p.y == y-1 && p.x == x-1 && (&board[x][y] == 0|| p.team != board[x][y].team));

}


int validKnightMov(struct piece p, int x, int y){
    return ((p.x+2 == x && p.y+1 == y )||
            (p.x-2 == x && p.y+1 == y ) ||
            (p.x-2 == x && p.y-1 == y) ||
            (p.x+2 == x && p.y-1 == y) ||
            (p.y+2 == y && p.x+1 == x) ||
            (p.y-2 == y && p.x+1 == x) ||
            (p.y-2 == y && p.x-1 == x) ||
            (p.y+2 == y && p.x-1 == x))&& 
            (&board[x][y] == 0|| p.team != board[x][y].team);
}*/