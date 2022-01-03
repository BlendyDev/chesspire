//char isLegalMove () { //int board[8][8], int startPos[2], int endPos[2]
//	return 'x';
//}
int isLegalMove (int board[8][8], int startPos[2], int gotoPos[2], int turn) {//0 = not legal, 1 = legal, 2 = legal with special rules
    if (startPos[0] == -1 || startPos[1] == -1 || gotoPos[0] == -1 || gotoPos[1] == -1) return 0; //valid parameters checker
    if (startPos[0] == gotoPos[0] && startPos[1] == gotoPos[1]) return 0; //cannot move into itslef
    
    int movingPiece = board[7-startPos[1]][startPos[0]];
    if (movingPiece == 0) return 0; //shouldnt be possible, but just in case (cannot move air)
    if (movingPiece * (turn - 0.5) > 0) return 0; //cannot move piece from opposite team (also shouldnt be possible)
    int boardAfterMove[8][8];
    for (int i = 0; i < 8; i++) {
        for (int k = 0; k < 8; k++) {
            boardAfterMove[i][k] = board[i][k]; //uhhh memcpy too hard so lets just nest for loops!
        }
    }
    boardAfterMove[7-gotoPos[1]][gotoPos[0]] = boardAfterMove[7-startPos[1]][startPos[0]];
    boardAfterMove[7-startPos[1]][startPos[0]] = 0;
    if (isChecked(boardAfterMove, turn) != 0) return 0;
    return 1;
}
int getBoardAfterMove (int board[8][8], int startPos[2], int gotoPos[2], int turn, int x, int y) {//0 = not legal, 1 = legal, 2 = legal with special rules
    int boardAfterMove[8][8];
    for (int i = 0; i < 8; i++) {
        for (int k = 0; k < 8; k++) {
            boardAfterMove[i][k] = board[i][k];
        }
    }
    if (startPos[0] == -1 || startPos[1] == -1 || gotoPos[0] == -1 || gotoPos[1] == -1) return -1;
    boardAfterMove[7-gotoPos[1]][gotoPos[0]] = boardAfterMove[7-startPos[1]][startPos[0]];
    boardAfterMove[7-startPos[1]][startPos[0]] = 0;
    return boardAfterMove[x][y];
}
int returncheckvalue (int board[8][8], int startPos[2], int gotoPos[2], int turn) {//0 = not legal, 1 = legal, 2 = legal with special rules
    int movingPiece = board[7-startPos[1]][startPos[0]];
    int boardAfterMove[8][8];
    for (int i = 0; i < 8; i++) {
        for (int k = 0; k < 8; k++) {
            boardAfterMove[i][k] = board[i][k];
        }
    }
    if (startPos[0] == -1 || startPos[1] == -1 || gotoPos[0] == -1 || gotoPos[1] == -1) return -1;
    boardAfterMove[7-gotoPos[1]][gotoPos[0]] = boardAfterMove[7-startPos[1]][startPos[0]];
    boardAfterMove[7-startPos[1]][startPos[0]] = 0;
    return isChecked(boardAfterMove, turn);
}