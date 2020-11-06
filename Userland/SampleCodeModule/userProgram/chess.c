
#include <stdint.h>
#include <chess.h>
#include <stdc.h>

//PIECES
#define EMPTY 0
#define KING 1
#define QUEEN 2
#define KNIGHT 3
#define ROOK 4
#define BISHOP 5
#define PAWN 6

#define LEFT 10
#define RIGHT 20



#define MAX_POS 8
#define BLACK 15395564
#define WHITE 0

#define BACKGROUND_COLOR_1 9226804
#define BACKGROUND_COLOR_2 16475904
#define PIECE_SIZE 4
#define PIECE_RESOLUTION 16



//
#define PLAYER1 1
#define PLAYER2 2

#define MAXPLAYS 99

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

struct piece board[MAX_POS+1][MAX_POS+1];
struct log logs1[MAXPLAYS];
struct log logs2[MAXPLAYS];


int validKnightMov(struct piece p, int x, int y);
int validPawnMov(struct piece p, int x, int y);
void initBoard();
int isWinner();
void makeMov(int fromX,int fromY,int toX,int toY);
void updateView();
int isValidMovement(int x, int y,struct piece p);
int validPawnMov(struct piece p, int x, int y);
int validKingMov(struct piece p, int x, int y);
int noMoveKing(int team);
int noMoveRook(struct piece p, int side,int team);
int noPiecesBetween(int side,int team);
int dangerPlace(int x,int y);
int winner = 0, time1 = 0, time2 = 0, indexLogs1=0,indexLogs2=0;

int playchess(){
    initBoard();
    updateView(board);
    int turn = PLAYER1;
    while(!isWinner()){
        int fromX = 0,fromY = 0,toX = 7,toY =2;
        //board[fromX][fromY] = (struct piece){fromX,fromY,EMPTY,-1};
        // //initTimer();
        // //scanf("desde %d,%d hacia %d,%d\n",fromX,fromY,toX,toY);
        // if(1){
        //     if(turn == PLAYER1){
        //         logs1[indexLogs1++] = (struct log){board[fromX][fromY], toX,toY};
        //     }
        //     if(turn == PLAYER2){
        //         logs2[indexLogs2++] = (struct log){board[fromX][fromY], toX,toY};
        //     }
        makeMov(fromX,fromY,toX,toY);
        

        // }
        // if(turn == PLAYER1){
        //     //time1 = endTimer();
        //     turn = PLAYER2;
        // }else{
        //     //time2 = endTimer();
        //     turn = PLAYER1;
        // }
        updateView(board);
        // break;
    }
    return 0;
}
void makeMov(int fromX,int fromY,int toX,int toY){
        // int aux = BISHOP;
        // if(board[fromX][fromY].type == ROOK){
        //     aux = ROOK;
        // }else{
        //     aux = KNIGHT;
        // }
        board[toX][toY] = (struct piece) {toX,toY,board[fromX][fromY].type,board[fromX][fromY].team};
        board[fromX][fromY].type = EMPTY;
}

int isWinner(){
    // if(time1 - time2 > 60){
    //     return 3;
    // }
    // int flag = 0;
    // for(int i = 0; i <= MAX_POS;i++){
    //     for(int j = 0; j <= MAX_POS;j++){
    //         if(!&board[i][j] && board[i][j].type == KING && board[i][j].team == BLACK){
    //             flag =1;
    //         }
    //     }
    // }
    // if(flag == 0){
    //     winner = 1;
    //     return 1;
    // }else{
    //     flag = 0;
    //     for(int i = 0; i <= MAX_POS;i++){
    //         for(int j = 0; j <= MAX_POS;j++){
    //             if(!&board[i][j] && board[i][j].type == KING && board[i][j].team == WHITE){
    //                 flag =1;
    //             }
    //         }
    //     }
    // }
    // if(flag == 0){
    //     winner = 2;
    //     return 2;
    // }
    return 0;
}

void updateView(){
    int backgroundColor = BACKGROUND_COLOR_2;
    int aux_x = 0;
    int aux_y = 0;

    for (int i = 0; i < MAX_POS+1; i++){
        for (int j = 0; j < MAX_POS+1; j++){
            if(i%2 == 0){//si i es par
                if(j%2 == 0){
                    backgroundColor = BACKGROUND_COLOR_1;
                }else{
                    backgroundColor = BACKGROUND_COLOR_2;
                }
            }else if(j%2 == 0){
                backgroundColor = BACKGROUND_COLOR_2;
            }else{
                backgroundColor = BACKGROUND_COLOR_1;
            }
            Matrix16x16(aux_x, aux_y, charBitmap(board[i][j].type), PIECE_SIZE, board[i][j].team, backgroundColor);            aux_x += PIECE_SIZE*PIECE_RESOLUTION;
        }
        aux_x = 0;
        aux_y += PIECE_SIZE*PIECE_RESOLUTION;
    }

}

void initBoard(){
    for (int i = 0; i < MAX_POS; i++)
        board[8][i] = (struct piece) {i,8,i+7,WHITE};  
    for (int i = 0; i < MAX_POS; i++)
        board[i][8] = (struct piece) {i,i+14,i+15,WHITE};  
    for(int i = 2; i < 6; i++)
    for (int j = 0; j < MAX_POS; j++)
     board[i][j] = (struct piece) {i,j,EMPTY,WHITE};  

    board[0][0] = (struct piece) {0,0,ROOK,WHITE};
    board[0][1] = (struct piece) {0,1,KNIGHT,WHITE};
    board[0][2] = (struct piece) {0,2,BISHOP,WHITE};
    board[0][3] = (struct piece) {0,3,KING,WHITE};
    board[0][4] = (struct piece) {0,4,QUEEN,WHITE};
    board[0][5] = (struct piece) {0,5,BISHOP,WHITE};
    board[0][6] = (struct piece) {0,6,KNIGHT,WHITE};
    board[0][7] = (struct piece) {0,7,ROOK,WHITE};
    board[1][0] = (struct piece) {1,0,PAWN,WHITE};
    board[1][1] = (struct piece) {1,1,PAWN,WHITE};
    board[1][2] = (struct piece) {1,2,PAWN,WHITE};
    board[1][3] = (struct piece) {1,3,PAWN,WHITE};
    board[1][4] = (struct piece) {1,4,PAWN,WHITE};
    board[1][5] = (struct piece) {1,5,PAWN,WHITE};
    board[1][6] = (struct piece) {1,6,PAWN,WHITE};
    board[1][7] = (struct piece) {1,7,PAWN,WHITE};

    board[7][0] = (struct piece) {7,0,ROOK,BLACK};
    board[7][1] = (struct piece) {7,0,KNIGHT,BLACK};
    board[7][2] = (struct piece) {7,2,BISHOP,BLACK};
    board[7][3] = (struct piece) {7,3,QUEEN,BLACK};
    board[7][4] = (struct piece) {7,4,KING,BLACK};
    board[7][5] = (struct piece) {7,5,BISHOP,BLACK};
    board[7][6] = (struct piece) {7,6,KNIGHT,BLACK};
    board[7][7] = (struct piece) {7,7,ROOK,BLACK};
    board[6][0] = (struct piece) {6,0,PAWN,BLACK};
    board[6][1] = (struct piece) {6,1,PAWN,BLACK};
    board[6][2] = (struct piece) {6,2,PAWN,BLACK};
    board[6][3] = (struct piece) {6,3,PAWN,BLACK};
    board[6][4] = (struct piece) {6,4,PAWN,BLACK};
    board[6][5] = (struct piece) {6,5,PAWN,BLACK};
    board[6][6] = (struct piece) {6,6,PAWN,BLACK};
    board[6][7] = (struct piece) {6,7,PAWN,BLACK};



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
            return board[x][y].type ==  EMPTY ||(board[x][y].team != p.team);
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
                return  board[x][y].type == EMPTY||(board[x][y].team != p.team);
            }else if(p.y == y){
                for(int j = p.x-1; j <= y;j++){
                    if(!&board[j][y]){
                        return 0;
                    }
                }
                return  board[x][y].type == EMPTY ||(board[x][y].team != p.team);
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
                return  board[x][y].type == EMPTY ||(board[x][y].team != p.team);
            };
    }
    return 0;
}

int validPawnMov(struct piece p, int x, int y){
    return (p.y == 1 && p.team == WHITE && p.y <= y-2 && p.x == x && board[x][y].type == EMPTY) ||
            (p.y == 6 && p.team == BLACK && p.y >= y+2 && p.x == x) ||
            (p.team == BLACK && p.y == y-1 && p.x == x && board[x][y].type == EMPTY) ||
            (p.team == WHITE && p.y == y+1 && p.x == x && board[x][y].type == EMPTY) ||
            (p.team == WHITE && p.y == y+1 && p.x == x+1 && (board[x][y].type == EMPTY|| p.team != board[x][y].team)) ||
            (p.team == WHITE && p.y == y+1 && p.x == x-1 && (board[x][y].type == EMPTY|| p.team != board[x][y].team)) ||
            (p.team == BLACK && p.y == y-1 && p.x == x+1 && (board[x][y].type == EMPTY|| p.team != board[x][y].team)) ||
            (p.team == BLACK && p.y == y-1 && p.x == x-1 && (board[x][y].type == EMPTY|| p.team != board[x][y].team));

}

int validKingMov(struct piece p, int x, int y){
    int enroqueType;
    if(p.team == WHITE && y == 0 && p.x == 4 && p.y == 0 && x == 6){
        enroqueType = RIGHT;
        if(noMoveKing(WHITE) && noMoveRook(p,enroqueType,WHITE) && noPiecesBetween(enroqueType,WHITE)){
            for(int i = p.x ; i <= x;i++){
                if(dangerPlace(i,y)){
                    return 0;
                }
            }
            return 1;
        }
    }else if(p.team == WHITE && p.x == 4 && p.y == 0 && x == 2){
        enroqueType = LEFT;
        if(noMoveKing(WHITE) && noMoveRook(p,enroqueType,WHITE) && noPiecesBetween(enroqueType,WHITE)){
            for(int i = p.x ; i >= x;i--){
                if(dangerPlace(i,y)){
                    return 0;
                }
            }
            return 1;
        }
    }else  if(p.team == BLACK && p.x == 4 && p.y == 7 && x == 6){
         enroqueType = RIGHT;
        if(noMoveKing(BLACK) && noMoveRook(p,enroqueType,BLACK) && noPiecesBetween(enroqueType,BLACK)){
            for(int i = p.x ; i <= x;i++){
                if(dangerPlace(i,y)){
                    return 0;
                }
            }
            return 1;
        }
    }else if(p.team == BLACK && p.x == 4 && p.y == 7 && x == 2){
        enroqueType = LEFT;
        if(noMoveKing(BLACK) && noMoveRook(p,enroqueType,BLACK) && noPiecesBetween(enroqueType,BLACK)){
            for(int i = p.x ; i >= x;i--){
                if(dangerPlace(i,y)){
                    return 0;
                }
            }
            return 1;
        }
    }


    return ((p.x+2 == x && p.y+1 == y )||
            (p.x-2 == x && p.y+1 == y ) ||
            (p.x-2 == x && p.y-1 == y) ||
            (p.x+2 == x && p.y-1 == y) ||
            (p.y+2 == y && p.x+1 == x) ||
            (p.y-2 == y && p.x+1 == x) ||
            (p.y-2 == y && p.x-1 == x) ||
            (p.y+2 == y && p.x-1 == x))&& 
            (board[x][y].type == EMPTY|| p.team != board[x][y].team);
}

int noMoveKing(int team){
    if(team == WHITE){
        for(int i = 0;i<=indexLogs1;i++){
            if(logs1[i].p.type == KING)
                return 0;
        }
        return 1;
    }else{
        for(int i = 0;i<=indexLogs2;i++){
            if(logs2[i].p.type == KING)
                return 0;
        }
        return 1;
    }
    return 0;
}

int noMoveRook(struct piece p, int side,int team){
    if(team == WHITE&& side == RIGHT){
        for(int i = 0;i<=indexLogs1;i++){
            if(logs1[i].p.type == ROOK  && p.x != 7)
                return 0;
        }
        return 1;
    }else if(team == WHITE && side == LEFT){
        for(int i = 0;i<=indexLogs1;i++){
            if(logs1[i].p.type == ROOK  && p.x != 0)
                return 0;
        }
        return 1;
    }else if(team == BLACK && side == LEFT){
        for(int i = 0;i<=indexLogs2;i++){
            if(logs2[i].p.type == ROOK  && p.x != 0)
                return 0;
        }
        return 1;
    }else{
        for(int i = 0;i<=indexLogs2;i++){
            if(logs2[i].p.type == ROOK  && p.x != 0)
                return 0;
        }
        return 1;
    }
    return 0;
}

int noPiecesBetween(int side,int team){
    if(side == LEFT && team == WHITE){
        if(board[0][0].type == ROOK && board[0][4].type == KING){
            for (int i = 1; i >= 3; i--){
                if(board[i][0].type != EMPTY){
                    return 0;
                }
            }
            return 1;
        }
    }else if(side == RIGHT && team == WHITE){
        if(board[7][0].type == ROOK && board[0][4].type == KING){
            for (int i = 5; i <= 6; i++){
                if(board[i][0].type != EMPTY){
                    return 0;
                }
            }
            return 1;
        }
    }else  if(side == LEFT && team == BLACK){
        if(board[7][0].type == ROOK && board[7][4].type == KING){
            for (int i = 1; i >= 3; i--){
                if(board[i][7].type != EMPTY){
                    return 0;
                }
            }
            return 1;
        }
    }else{
        if(board[7][7].type == ROOK && board[7][4].type == KING){
            for (int i = 5; i <= 6; i++){
                if(board[i][7].type != EMPTY){
                    return 0;
                }
            }
            return 1;
        }
    }
    return 0;
}

int dangerPlace(int x,int y){
    for (int i = 0; i < MAX_POS; i++)
    {
        for (int j = 0; j < MAX_POS; j++)
        {
            if(isValidMovement(x,y,board[i][j])){
                return 1;
            }
        }
        
    }
    return 0;
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
}