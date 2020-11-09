
#include <stdint.h>
#include <chess.h>
#include <stdc.h>

#define GOBACK 99999999
#define PAUSE 99999999

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
#define BLACK 0
#define WHITE 15395564


#define BACKGROUND_COLOR_1 9226804
#define BACKGROUND_COLOR_2 16475904
#define PIECE_SIZE 4
#define PIECE_RESOLUTION 16

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
int validRookMov(struct piece p, int x, int y);
int validBishopMov(struct piece p,int x,int y);
int validKingMov(struct piece p,int x,int y);
void initBoard();
int isWinner();
void makeMov(int fromX,int fromY,int toX,int toY);
// void updateView();
int isValidMovement(int x, int y,struct piece p);
int validPawnMov(struct piece p, int x, int y);
int validKingMov(struct piece p, int x, int y);
int noMoveKing(int team);
int noMoveRook(struct piece p, int side);
int noPiecesBetween(int side,int team);
int dangerPlace(int x,int y,int team);
int winner = 0, time1 = 0, time2 = 0, indexLogs1=0,indexLogs2=0,rotation=0;

int playchess(){
    
    initBoard();

    consoleSize(1016, 600, 500, 10);
    updateView();
   

    int turn = PLAYER1;
    print("Ingrese jugada con el formato\n: letraNum->letraNum\n");
    print("Oprima 'r' para girar el tablero\n");
    print("Empieza el equipo blanco\n");
    char buff;
    while(!isWinner()){
        char playString[100];
        int i =0;
        print("$ ");
       while(buff != '\n'){
            if(getchar(&buff) == 1){
                if(buff == 'r'){
                    if(rotation == 1){
                        updateView();
                        rotation =0;
                    }else{
                        rotate();
                        rotation = 1;
                    }
                }else{ 
                    putchar(buff);
                    playString[i++] = buff;
                }
            }
            if(buff == GOBACK){
                return 0;
            }
            if(buff == PAUSE){
                // clearDisplay(0);
                // StartShell();
                // consoleSize(1016, 600, 500, 10);
            }
       }
        playString[i] = 0;
        buff = 0;

        char fromX = playString[0] -'A',fromY = playString[1]-'1',toX = playString[4]-'A' ,toY = playString[5]-'1' ;
        if(fromX < 0 || fromX >7||fromY < 0 || fromY >7||toX <0 || toX >7||toY < 0 || toY >7){
            print("Mal formato\n");
        }else if(turn == PLAYER1 && board[fromX][fromY].team == BLACK){
            print("Es el turno de las blancas\n");
        }else if(turn == PLAYER2 && board[fromX][fromY].team == WHITE){
            print("Es el turno de las negras\n");
        }else{
            // int day = getDay();
            // int time = getTime();
            if(isValidMovement(toX,toY,board[fromX][fromY])){
                if(turn == PLAYER1){
                    logs1[indexLogs1++] = (struct log){board[fromX][fromY], toX,toY};
                }
                if(turn == PLAYER2){
                    logs2[indexLogs2++] = (struct log){board[fromX][fromY], toX,toY};
                }
                makeMov(fromX,fromY,toX,toY);

                if(turn == PLAYER1){
                    // if(getDay() == day){
                    //     time1 += getTime()- time;
                    // }else{
                    //     time1 += getTime() + (24*60*60)- time;
                    // }
                    
                    print("Tiempo blancas:  %d\n",time1);
                    turn = PLAYER2;
                }else{
                    // if(getDay() == day){
                    //     time2 += getTime()- time;
                    // }else{
                    //     time2 += getTime() + (24*60*60)- time;
                    // }
                    
                    print("Tiempo negras:  %d\n",time2);
                    turn = PLAYER1;
                }
                if(rotation == 0){
                    updateView();
                }else{
                    rotate();
                }
            }else{
                print("Movimiento Invalido\n");
            }
        }
    }
    if(winner == 1){
        print("Ganaron blancas\n");
    }else if(winner == 2){
        print("Ganaron negras\n");
    }else{
        print("Diferncia entre tiempo1 y tiempo2 mayor a 60\n");
    }
     return 0;
}

void rotate(){
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
            Matrix16x16(aux_x, aux_y, charBitmap(board[j][i].type), PIECE_SIZE, board[j][i].team, backgroundColor);            aux_x += PIECE_SIZE*PIECE_RESOLUTION;
        }
        aux_x = 0;
        aux_y += PIECE_SIZE*PIECE_RESOLUTION;
    }
}

// int getTime(){
//     return getSeconds()+getMinutes()*60+getHours()*60*60;
// }

void makeMov(int fromX,int fromY,int toX,int toY){
        struct piece aux = board[fromX][fromY];
        board[toX][toY] = aux;
        board[toX][toY].x = toX;
        board[toX][toY].y = toY;
        board[fromX][fromY].type = EMPTY;
        board[fromX][fromY].team = 3;
}

int isWinner(){
    if(time1 - time2 > 60){
        return 3;
    }
    int flag = 0;
    for(int i = 0; i <= MAX_POS;i++){
        for(int j = 0; j <= MAX_POS;j++){
            if( board[i][j].type == KING && board[i][j].team == BLACK){
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
                if(board[i][j].type == KING && board[i][j].team == WHITE){
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
            }else
                backgroundColor = BACKGROUND_COLOR_1;
            if(i == MAX_POS || j ==  MAX_POS){
                backgroundColor = BLACK;    
            }
            Matrix16x16(aux_x, aux_y, charBitmap(board[i][j].type), PIECE_SIZE, board[i][j].team, backgroundColor);           
            aux_x += PIECE_SIZE*(PIECE_RESOLUTION+1);
        }
        aux_x = 0;
        aux_y += PIECE_SIZE*(PIECE_RESOLUTION);
    }

}

void initBoard(){

    for (int i = 0; i < MAX_POS; i++)
        board[8][i] = (struct piece) {i,8,i+7,WHITE};  
    for (int i = 0; i < MAX_POS; i++)
        board[i][8] = (struct piece) {i,i+14,i+15,WHITE};  
    for(int i = 2; i < 6; i++)
        for (int j = 0; j < MAX_POS; j++)
        board[i][j] = (struct piece) {i,j,EMPTY,3};  

    board[0][0] = (struct piece) {0,0,ROOK,WHITE};
    board[0][1] = (struct piece) {0,1,KNIGHT,WHITE};
    board[0][2] = (struct piece) {0,2,BISHOP,WHITE};
    board[0][3] = (struct piece) {0,3,QUEEN,WHITE};
    board[0][4] = (struct piece) {0,4,KING,WHITE};
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
    board[7][1] = (struct piece) {7,1,KNIGHT,BLACK};
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
    board[8][8] = (struct piece) {8,8,23,WHITE};

}

int isValidMovement(int x, int y,struct piece p){
    if(x >= MAX_POS && y >= MAX_POS)
        return 0;
    switch (p.type){
        case KING:
            return validKingMov(p,x,y);  
        case QUEEN:
            return validRookMov(p,x,y) || validBishopMov(p,x,y);
        case PAWN:
            return validPawnMov(p,x,y);
        case KNIGHT:
            return validKnightMov(p,x,y);
        case ROOK:
            return validRookMov(p,x,y);
        case BISHOP:
            return validBishopMov(p,x,y);
    }
    return 0;
}

int validPawnMov(struct piece p, int x, int y){
    if(p.team == WHITE){
        if(board[x][y].type == EMPTY  && y == p.y){
            if(x == p.x+1 )
                return 1;
            if(p.x == 1 && x == p.x + 2)
                return 1;
        }else{
            if((y == p.y+1 || y == p.y-1) && x == p.x+1 &&board[x][y].type != EMPTY && board[x][y].team == BLACK)
                return 1;
        }
    }else{
        if(board[x][y].type == EMPTY  && y == p.y){
            if(x == p.x-1 )
                return 1;
            if(p.x == 6 && x == p.x - 2)
                return 1;
        }else{
            if((y == p.y+1 || y == p.y-1) && x == p.x-1 &&board[x][y].type != EMPTY && board[x][y].team == WHITE)
                return 1;
        }
    }
    return 0;
}

int validKingMov(struct piece p, int x, int y){
    int enroqueType;
    if(p.team == WHITE && x == 0 && p.y == 4 && p.x == 0 && y == 6){
        enroqueType = RIGHT;
        if(noMoveKing(WHITE) && noMoveRook(p,enroqueType) && noPiecesBetween(enroqueType,WHITE)){
            for(int i = p.x ; i <= x;i++){
                if(dangerPlace(i,y,p.team)){
                    print("falla en i=%d,y=%d\n",i,y);
                    return 0;
                }
            }
            board[0][5]=board[0][7]; 
            board[0][5].y = 5;
            board[0][7].type = EMPTY;
            board[0][7].team = 3;
            return 1;
        }
    }else if(p.team == WHITE && p.y == 4 && p.x == 0 && x == 0 && y == 2){
        enroqueType = LEFT;
        if(noMoveKing(WHITE) && noMoveRook(p,enroqueType) && noPiecesBetween(enroqueType,WHITE)){
            for(int i = p.x ; i >= x;i--){
                if(dangerPlace(i,y,p.team)){
                    print("falla en i=%d,y=%dAAA\n",i,y);
                    return 0;
                }
            }
            board[0][3]=board[0][0]; 
            board[0][3].y = 3;
            board[0][0].type = EMPTY;
            board[0][0].team = 3;
            return 1;
        }
    }else  if(p.team == BLACK && x == 7 && p.y == 4 && p.x == 7 && y == 6){
         enroqueType = RIGHT;
        if(noMoveKing(BLACK) && noMoveRook(p,enroqueType) && noPiecesBetween(enroqueType,BLACK)){
            for(int i = p.x ; i <= x;i++){
                if(dangerPlace(i,y,p.team)){
                    print("falla en i=%d,y=%dAAA\n",i,y);
                    return 0;
                }
            }
            board[7][5]=board[7][7]; 
            board[7][5].y = 5;
            board[7][7].type = EMPTY;
            board[7][7].team = 3;
            return 1;
        }
    }else if(p.team == BLACK  && p.y == 4 && p.x == 7 && x == 7 && y == 2){
        enroqueType = LEFT;
        if(noMoveKing(BLACK) && noMoveRook(p,enroqueType) && noPiecesBetween(enroqueType,BLACK)){
            for(int i = p.x ; i >= x;i--){
                if(dangerPlace(i,y,p.team)){
                    print("falla en i=%d,y=%dAAA\n",i,y);
                    return 0;
                }
            }
            board[7][3]=board[7][0]; 
            board[7][3].y = 3;
            board[7][0].type = EMPTY;
            board[7][0].team = 3;
            return 1;
        }
    }
    return ((p.x+1 == x && p.y+1 == y) ||
            (p.x+1 == x && p.y == y) ||
            (p.x-1 == x && p.y == y) ||
            (p.y+1 == y && p.x == x) ||
            (p.y-1 == y && p.x == x) ||
            (p.x-1 == x && p.y+1 == y) ||
            (p.x-1 == x && p.y-1 == y) ||
            (p.x+1 == x && p.y-1 == y) ||
            (p.y+1 == y && p.x+1 == x) ||
            (p.y-1 == y && p.x+1 == x) ||
            (p.y-1 == y && p.x-1 == x) ||
            (p.y+1 == y && p.x-1 == x))&& 
            (board[x][y].type == EMPTY|| p.team != board[x][y].team);
}

int noMoveKing(int team){
    if(team == WHITE){
        for(int i = 0;i<=indexLogs1;i++){
            if(logs1[i].p.type == KING)
                return 0;
        }
        print("No move king\n");
        return 1;
    }else{
        for(int i = 0;i<=indexLogs2;i++){
            if(logs2[i].p.type == KING)
                return 0;
        }
        print("No move king\n");
        return 1;
    }
    return 0;
}

int noMoveRook(struct piece p, int side){
    int team = p.team;
    if(team == WHITE&& side == RIGHT){
        for(int i = 0;i<=indexLogs1;i++){
            if(logs1[i].p.type == ROOK  && logs1[i].p.y == 7)
                return 0;
        }
        print("No move rook\n");
        return 1;
    }else if(team == WHITE && side == LEFT){
        for(int i = 0;i<=indexLogs1;i++){
            if(logs1[i].p.type == ROOK  && logs1[i].p.y == 0)
                return 0;
        }
        print("No move rook\n");
        return 1;
    }else if(team == BLACK && side == LEFT){
        for(int i = 0;i<=indexLogs2;i++){
            if(logs2[i].p.type == ROOK  && logs2[i].p.y == 0)
                return 0;
        }
        print("No move rook\n");
        return 1;
    }else{
        for(int i = 0;i<=indexLogs2;i++){
            if(logs2[i].p.type == ROOK  && logs2[i].p.y == 7)
                return 0;
        }
        print("No move rook\n");
        return 1;
    }
    return 0;
}

int noPiecesBetween(int side,int team){
    if(side == LEFT && team == WHITE){
        if(board[0][0].type == ROOK && board[0][4].type == KING){
            for (int i = 1; i <= 3; i++){
                print("board[%d][0].type:%d\n",i,board[i][0].type);
                if(board[0][i].type != EMPTY){
                    return 0;
                }
            }
            print("No pieces between\n");
            return 1;
        }
        return 0;
    }else if(side == RIGHT && team == WHITE){
        if(board[0][7].type == ROOK && board[0][4].type == KING){
            for (int i = 5; i <= 6; i++){
                print("board[%d][0].type:%d\n",i,board[i][0].type);
                if(board[0][i].type != EMPTY){
                    return 0;
                }
            }
            print("No pieces between\n");
            return 1;
        }
        return 0;
    }else  if(side == LEFT && team == BLACK){
        if(board[7][0].type == ROOK && board[7][4].type == KING){
            for (int i = 1; i <= 3; i++){
                print("board[%d][7].type:%d\n",i,board[i][0].type);
                if(board[7][i].type != EMPTY){
                    return 0;
                }
            }
            print("No pieces between\n");
            return 1;
        }
        return 0;
    }else{
        if(board[7][7].type == ROOK && board[7][4].type == KING){
            for (int i = 5; i <= 6; i++){
                print("board[%d][7].type:%d\n",i,board[i][0].type);
                if(board[7][i].type != EMPTY){
                    return 0;
                }
            }
            print("No pieces between\n");
            return 1;
        }
        return 0;
    }
    return 0;
}

int dangerPlace(int x,int y,int team){
    for (int i = 0; i < MAX_POS; i++){
        for (int j = 0; j < MAX_POS; j++){
            if(board[i][j].team != team && isValidMovement(x,y,board[i][j])){
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
            (board[x][y].type == EMPTY|| p.team != board[x][y].team);
}

int validRookMov(struct piece p, int x, int y){
    if(p.x == x){
        if(p.y > y){
            for(int j = p.y-1; j > y;j--){
                print("%d,%d\n",x,j);
                if(board[x][j].type != EMPTY){
                    return 0;
                }
            }
            return  board[x][y].type == EMPTY||board[x][y].team != p.team;
        }else{
            for(int j = p.y+1; j < y;j++){
                print("%d,%d\n",x,j);
                if(board[x][j].type != EMPTY){
                    return 0;
                }
            }
            return  board[x][y].type == EMPTY||board[x][y].team != p.team;
        }
    }else if(p.y == y){
        if(p.x > x){
            for(int j = p.x-1; j > x;j--){
                print("%d,%d\n",j,y);
                if(board[j][y].type != EMPTY){
                    return 0;
                }
            }
            return  board[x][y].type == EMPTY||board[x][y].team != p.team;
        }else{
            for(int j = p.x+1; j < x;j++){
                print("%d,%d\n",j,y);
                if(board[j][y].type != EMPTY){
                    return 0;
                }
            }
            return  board[x][y].type == EMPTY||board[x][y].team != p.team;
        }
    }else{
        return 0;
    }
}

int validBishopMov(struct piece p,int x,int y){
    if(p.x > x && p.y > y && p.x - x == p.y - y){
        int j = p.y-1;
        for(int i = p.x-1; i > x && j > y;i--){
                print("board[i=%d][j=%d].type:%d\n",i,j,board[i][j].type);
                if(board[i][j].type != EMPTY){
                    return 0;
                }
            j--;
        }
        return  board[x][y].type == EMPTY ||(board[x][y].team != p.team);
    }else if(p.x < x && p.y > y  && x - p.x == p.y - y){
        int j = p.y-1;
        for(int i = p.x+1; i < x && j > y;i++){
                print("board[i=%d][j=%d].type:%d\n",i,j,board[i][j].type);
                if(board[i][j].type != EMPTY){
                    return 0;
                }
            j--;
        }
        return  board[x][y].type == EMPTY ||(board[x][y].team != p.team);
    }else if(p.x < x && p.y < y  && x - p.x == y - p.y){
        int j = p.y+1;
        for(int i = p.x+1; i < x && j < y;i++){
                print("board[i=%d][j=%d].type:%d\n",i,j,board[i][j].type);
                if(board[i][j].type != EMPTY){
                    return 0;
                }
            j++;
        }
        return  board[x][y].type == EMPTY ||(board[x][y].team != p.team);
    }else if(p.x > x && p.y < y  && p.x - x == y - p.y){
        int j = p.y+1;
        for(int i = p.x-1; i > x && j < y;i--){
                print("board[i=%d][j=%d].type:%d\n",i,j,board[i][j].type);
                if(board[i][j].type != EMPTY){
                    return 0;
                }
            j--;
        }
        return  board[x][y].type == EMPTY ||(board[x][y].team != p.team);
    }
    return  0;    
}