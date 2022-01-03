int isChecked (int board[8][8], int color) {
    for (int i = 0; i < 8; i++) {//i = row
        for (int k = 0; k < 8; k++) {//k = column
            int piece = board[i][k]; //signed (has color data) piece code
            if (piece * (color-0.5) > 0) {
                switch (abs(piece))
                {
                case 1://pawn
                    if (piece == abs(piece) && color == 1) {//white piece attacking, black getting checked
                        if (k == 7) {
                            if (board[i-1][k-1] == -6) return 1;
                        } else if (k == 0) {
                            if (board[i-1][k+1] == -6) return 1;
                        } else {
                            if (board[i-1][k-1] == -6 || board[i-1][k+1] == -6) return 1;
                        }
                    } else if (piece != abs(piece) && color == 0){//black piece attacking, white getting checked
                        if (k == 7) {
                            if (board[i+1][k-1] == 6) return 1;
                        } else if (k == 0) {
                            if (board[i+1][k+1] == 6) return 1;
                        } else {
                            if (board[i+1][k-1] == 6 || board[i+1][k+1] == 6) return 1;
                        }
                    }
                    break;
                case 2://rook
                    if (piece == abs(piece) && color == 1) {
                        for (int r = 1; r < 8-k; r++) {//starting at one for rook offset
                            if (board[i][r+k] == -6) return 1; //found a king before another piece, thus in check
                            if (board[i][r+k] != 0) break; //found a different piece other than king, blocking the check
                        }
                        //check if it works (i dont think so really)
                        for (int r = -1; r+k >= 0; r--) {
                            if (board[i][r+k] == -6) return 1;
                            if (board[i][r+k] != 0) break;
                        }
                        for (int r = 1; r < 8-i; r++) {
                            if (board[i+r][k] == -6) return 1;
                            if (board[i+r][k] != 0) break;
                        }
                        for (int r = -1; r+i >= 0; r--) {
                            if (board[i+r][k] == -6) return 1;
                            if (board[i+r][k] != 0) break;
                        }
                        break;
                    } else if (piece != abs(piece) && color == 0) {
                        for (int r = 1; r < 8-k; r++) {//starting at one for rook offset
                            if (board[i][r+k] == 6) return 1; //found a king before another piece, thus in check
                            if (board[i][r+k] != 0) break; //found a different piece other than king, blocking the check
                        }
                        //check if it works (i dont think so really)
                        for (int r = -1; r+k >= 0; r--) {
                            if (board[i][r+k] == 6) return 1;
                            if (board[i][r+k] != 0) break;
                        }
                        for (int r = 1; r < 8-i; r++) {
                            if (board[i+r][k] == 6) return 1;
                            if (board[i+r][k] != 0) break;
                        }
                        for (int r = -1; r+i >= 0; r--) {
                            if (board[i+r][k] == 6) return 1;
                            if (board[i+r][k] != 0) break;
                        }
                        break;
                    }
                case 3://bishop
                    if (piece == abs(piece) && color == 1) {

                    }
                default:
                    break;
                }
            }
        }
    }
    return 0;
}