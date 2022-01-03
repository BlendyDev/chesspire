#include <os.h>
#include <SDL/SDL_config.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <math.h>
#include "assets/white_pawn.h"
#include "assets/white_rook.h"
#include "assets/white_knight.h"
#include "assets/white_bishop.h"
#include "assets/white_queen.h"
#include "assets/white_king.h"
#include "assets/black_pawn.h"
#include "assets/black_rook.h"
#include "assets/black_knight.h"
#include "assets/black_bishop.h"
#include "assets/black_queen.h"
#include "assets/black_king.h"
#include "legalmove.h"
#include "check.h"

int board[8][8] = {               //0 -> none, 1 -> pawn, 2 -> rook, 3 -> knight, 4 -> bishop, 5 -> queen, 6 -> king, positives -> white, negatives -> black        
{-2,-3,-4,-5,-6,-4,-3,-2},
{-1, -1, -1, -1, -1, -1, -1, -1},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{1, 1, 1, 1, 1, 1, 1, 1},
{2, 3, 4, 5, 6, 4, 3, 2}};
bool finished = false;
SDL_Surface *screen;
nSDL_Font *font;
nSDL_Font *tinyfont;
int width = 320;
int height = 240;
int turn = 0; //0 = white, 1 = black
int selectedRow = -1;
int selectedColumn = -1;
int selectedSquare[2] = {-1, -1};
int gotoRow = -1;
int gotoColumn = -1;
SDL_Surface *BLACK_PAWN;
SDL_Surface *BLACK_ROOK;
SDL_Surface *BLACK_KNIGHT;
SDL_Surface *BLACK_BISHOP;
SDL_Surface *BLACK_QUEEN;
SDL_Surface *BLACK_KING;

SDL_Surface *WHITE_PAWN;
SDL_Surface *WHITE_ROOK;
SDL_Surface *WHITE_KNIGHT;
SDL_Surface *WHITE_BISHOP;
SDL_Surface *WHITE_QUEEN;
SDL_Surface *WHITE_KING;


void init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("error initializing SDL: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	screen = SDL_SetVideoMode(width, 240, has_colors ? 16 : 8, SDL_SWSURFACE);
	if (screen == NULL) {
		printf("error initializing display: %s\n", SDL_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	BLACK_PAWN = nSDL_LoadImage(image_black_pawn);
	SDL_SetColorKey(BLACK_PAWN, SDL_SRCCOLORKEY, SDL_MapRGB(BLACK_PAWN->format, 0xFF, 0x00, 0xFF));
	BLACK_ROOK = nSDL_LoadImage(image_black_rook);
	SDL_SetColorKey(BLACK_ROOK, SDL_SRCCOLORKEY, SDL_MapRGB(BLACK_ROOK->format, 0xFF, 0x00, 0xFF));
	BLACK_KNIGHT = nSDL_LoadImage(image_black_knight);
	SDL_SetColorKey(BLACK_KNIGHT, SDL_SRCCOLORKEY, SDL_MapRGB(BLACK_KNIGHT->format, 0xFF, 0x00, 0xFF));
	BLACK_BISHOP = nSDL_LoadImage(image_black_bishop);
	SDL_SetColorKey(BLACK_BISHOP, SDL_SRCCOLORKEY, SDL_MapRGB(BLACK_BISHOP->format, 0xFF, 0x00, 0xFF));
	BLACK_QUEEN = nSDL_LoadImage(image_black_queen);
	SDL_SetColorKey(BLACK_QUEEN, SDL_SRCCOLORKEY, SDL_MapRGB(BLACK_QUEEN->format, 0xFF, 0x00, 0xFF));
	BLACK_KING = nSDL_LoadImage(image_black_king);
	SDL_SetColorKey(BLACK_KING, SDL_SRCCOLORKEY, SDL_MapRGB(BLACK_KING->format, 0xFF, 0x00, 0xFF));

	WHITE_PAWN = nSDL_LoadImage(image_white_pawn);
	SDL_SetColorKey(WHITE_PAWN, SDL_SRCCOLORKEY, SDL_MapRGB(WHITE_PAWN->format, 0xFF, 0x00, 0xFF));
	WHITE_ROOK = nSDL_LoadImage(image_white_rook);
	SDL_SetColorKey(WHITE_ROOK, SDL_SRCCOLORKEY, SDL_MapRGB(WHITE_ROOK->format, 0xFF, 0x00, 0xFF));
	WHITE_KNIGHT = nSDL_LoadImage(image_white_knight);
	SDL_SetColorKey(WHITE_KNIGHT, SDL_SRCCOLORKEY, SDL_MapRGB(WHITE_KNIGHT->format, 0xFF, 0x00, 0xFF));
	WHITE_BISHOP = nSDL_LoadImage(image_white_bishop);
	SDL_SetColorKey(WHITE_BISHOP, SDL_SRCCOLORKEY, SDL_MapRGB(WHITE_BISHOP->format, 0xFF, 0x00, 0xFF));
	WHITE_QUEEN = nSDL_LoadImage(image_white_queen);
	SDL_SetColorKey(WHITE_QUEEN, SDL_SRCCOLORKEY, SDL_MapRGB(WHITE_QUEEN->format, 0xFF, 0x00, 0xFF));
	WHITE_KING = nSDL_LoadImage(image_white_king);
	SDL_SetColorKey(WHITE_KING, SDL_SRCCOLORKEY, SDL_MapRGB(WHITE_KING->format, 0xFF, 0x00, 0xFF));

	SDL_ShowCursor (SDL_ENABLE);
	tinyfont = nSDL_LoadFont(NSDL_FONT_TINYTYPE, 128, 128, 128); 
	font = nSDL_LoadFont(NSDL_FONT_VGA,	250, 250, 250);
	//SDL_Flip(screen);
	
	
	//SDL_Quit();
}
void draw() {
	char a[5];
	int gotoPos[2]={gotoColumn,gotoRow};
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 200));
	nSDL_DrawString(screen, tinyfont, width-60, height-10, "BlendyDev");
	nSDL_DrawString(screen, tinyfont, 10, height-10, itoa(isLegalMove(board, selectedSquare, gotoPos, turn), a, 10));
	nSDL_DrawString(screen, tinyfont, 10, height-30, itoa(returncheckvalue(board, selectedSquare, gotoPos, turn), a, 10));
	SDL_Rect border = {65, 7, 210, 210};
	SDL_FillRect(screen, &border, SDL_MapRGB(screen->format, 80, 40, 20));

	SDL_Rect whiteBG = {70, 12, 200, 200};
	SDL_FillRect(screen, &whiteBG, SDL_MapRGB(screen->format, 255, 200, 60));
	for (int i = 0; i<4; i++) {
		for (int k = 0; k<8; k++) {
			SDL_Rect blackBG = {70 + 50*i + 25*((k+1)%2), 12 + 25*k, 25, 25};
			SDL_FillRect(screen, &blackBG, SDL_MapRGB(screen->format, 200, 100, 50));
		}
	}

	for (int i = 0; i<8; ++i) {
		for (int k = 0; k<8; ++k) {
			int square = board[i][k];
			SDL_Rect piece;
			piece.x = k*25+70; 
			piece.y = i*25+13;
			piece.h = 25;
			piece.w = 25;
			
			switch(abs(square)) {
				case 1:
				if (square == abs(square)) {
					SDL_BlitSurface(WHITE_PAWN, NULL, screen, &piece);
				} else {
					SDL_BlitSurface(BLACK_PAWN, NULL, screen, &piece);
				}
				break;
				case 2:
				if (square == abs(square)) {
					SDL_BlitSurface(WHITE_ROOK, NULL, screen, &piece);
				} else {
					SDL_BlitSurface(BLACK_ROOK, NULL, screen, &piece);
				}
				break;
				case 3:
				if (square == abs(square)) {
					SDL_BlitSurface(WHITE_KNIGHT, NULL, screen, &piece);
				} else {
					SDL_BlitSurface(BLACK_KNIGHT, NULL, screen, &piece);
				}
				break;
				case 4:
				if (square == abs(square)) {
					SDL_BlitSurface(WHITE_BISHOP, NULL, screen, &piece);
				} else {
					SDL_BlitSurface(BLACK_BISHOP, NULL, screen, &piece);
				}
				break;
				case 5:
				if (square == abs(square)) {
					SDL_BlitSurface(WHITE_QUEEN, NULL, screen, &piece);
				} else {
					SDL_BlitSurface(BLACK_QUEEN, NULL, screen, &piece);
				}
				break;
				case 6:
				if (square == abs(square)) {
					SDL_BlitSurface(WHITE_KING, NULL, screen, &piece);
				} else {
					SDL_BlitSurface(BLACK_KING, NULL, screen, &piece);
				}
				break;
				default:
				break;
			}
			//debug text
			
			nSDL_DrawString(screen, tinyfont, piece.x, piece.y, itoa(getBoardAfterMove(board, selectedSquare, gotoPos, turn, i, k), a, 10));
			
		}
	}
	if (selectedRow != -1) {
		if (selectedColumn == -1) {
			for (int i = 0; i<8; i++) {
				outlineSquare(i, selectedRow, 2, 255, 40, 40);
			}
		} else {
			outlineSquare(selectedColumn, selectedRow, 2, 255, 40, 40);
		}
	} else if (selectedColumn != -1) {
		for (int i = 0; i<8; i++) {
			outlineSquare(selectedColumn, i, 2, 255, 40, 40);
		}
	} else if (selectedSquare[0] != -1) {
		if (gotoRow != -1) {
				if (gotoColumn == -1) {
					for (int i = 0; i<8; i++) {
						outlineSquare(i, gotoRow, 2, 40, 130, 255);
					}
				} else {
					outlineSquare(gotoColumn, gotoRow, 2, 40, 130, 255);
				}
			} else if (gotoColumn != -1){
				for (int i = 0; i<8; i++) {
					outlineSquare(gotoColumn, i, 2, 40, 130, 255);
				}
			}
		outlineSquare(selectedSquare[0], selectedSquare[1], 2, 40, 255, 40);
	}
}
int main(void) {
	init();
	while (!finished)
	{
		SDL_Event event;
		draw();
		SDL_Flip(screen);
		SDL_WaitEvent(&event); 
		if (event.type == SDL_KEYDOWN)
		{
			onKeyDown(event.key.keysym.sym);
		}
		
	}
	nSDL_FreeFont(font);
	nSDL_FreeFont(tinyfont);
	SDL_FreeSurface(screen);
	SDL_FreeSurface(WHITE_PAWN);
	SDL_FreeSurface(WHITE_ROOK);
	SDL_FreeSurface(WHITE_KNIGHT);
	SDL_FreeSurface(WHITE_BISHOP);
	SDL_FreeSurface(WHITE_QUEEN);
	SDL_FreeSurface(WHITE_KING);

	SDL_FreeSurface(BLACK_PAWN);
	SDL_FreeSurface(BLACK_ROOK);
	SDL_FreeSurface(BLACK_KNIGHT);
	SDL_FreeSurface(BLACK_BISHOP);
	SDL_FreeSurface(BLACK_QUEEN);
	SDL_FreeSurface(BLACK_KING);

	BLACK_PAWN = NULL;
	BLACK_ROOK = NULL;
	BLACK_KNIGHT = NULL;
	BLACK_BISHOP = NULL;
	BLACK_QUEEN = NULL;
	BLACK_KING = NULL;

	WHITE_PAWN = NULL;
	WHITE_ROOK = NULL;
	WHITE_KNIGHT = NULL;
	WHITE_BISHOP = NULL;
	WHITE_QUEEN = NULL;
	WHITE_KING = NULL;
	//SDL_Delay(3000);
	SDL_Quit();
	return EXIT_SUCCESS;
}

void onKeyDown(SDLKey key) {
	switch (key)
	{
	case SDLK_ESCAPE:
		finished = true;
		break;
	case SDLK_a:
		if (selectedSquare[0] == -1) {selectedColumn = 0;} else {
			gotoColumn = 0;
		}
		break;
	case SDLK_b:
		if (selectedSquare[0] == -1) {selectedColumn = 1;} else {
			gotoColumn = 1;
		}
		break;
	case SDLK_c:
		if (selectedSquare[0] == -1) {selectedColumn = 2;} else {
			gotoColumn = 2;
		}
		break;
	case SDLK_d:
		if (selectedSquare[0] == -1) {selectedColumn = 3;} else {
			gotoColumn = 3;
		}
		break;
	case SDLK_e:
		if (selectedSquare[0] == -1) {selectedColumn = 4;} else {
			gotoColumn = 4;
		}
		break;
	case SDLK_f:
		if (selectedSquare[0] == -1) {selectedColumn = 5;} else {
			gotoColumn = 5;
		}
		break;
	case SDLK_g:
		if (selectedSquare[0] == -1) {selectedColumn = 6;} else {
			gotoColumn = 6;
		}
		break;
	case SDLK_h:
		if (selectedSquare[0] == -1) {selectedColumn = 7;} else {
			gotoColumn = 7;
		}
		break;
	case SDLK_1:
		if (selectedSquare[0] == -1) {selectedRow = 0;} else {
			gotoRow = 0;
		}
		break;
	case SDLK_2:
		if (selectedSquare[0] == -1) {selectedRow = 1;} else {
			gotoRow = 1;
		}
		break;
	case SDLK_3:
		if (selectedSquare[0] == -1) {selectedRow = 2;} else {
			gotoRow = 2;
		}
		break;
	case SDLK_4:
		if (selectedSquare[0] == -1) {selectedRow = 3;} else {
			gotoRow = 3;
		}
		break;
	case SDLK_5:
		if (selectedSquare[0] == -1) {selectedRow = 4;} else {
			gotoRow = 4;
		}
		break;
	case SDLK_6:
		if (selectedSquare[0] == -1) {selectedRow = 5;} else {
			gotoRow = 5;
		}
		break;
	case SDLK_7:
		if (selectedSquare[0] == -1) {selectedRow = 6;} else {
			gotoRow = 6;
		}
		break;
	case SDLK_8:
		if (selectedSquare[0] == -1) {selectedRow = 7;} else {
			gotoRow = 7;
		}
		break;
	case SDLK_BACKSPACE:
		selectedSquare[0] = -1;
		selectedSquare[1] = -1;
		selectedColumn = -1;
		selectedRow = -1;
		gotoRow = -1;
		gotoColumn = -1;
	case SDLK_KP_ENTER://OK_KEY
		if (selectedColumn != -1 && selectedRow != -1) {
			if (selectedSquare[0] == -1) {
				if (board[7-selectedRow][selectedColumn] == 0 || board[7-selectedRow][selectedColumn] * (turn-0.5) > 0) {//can only select own pieces
					selectedRow = -1;
					selectedColumn = -1;
				} else {
					selectedSquare[1] = selectedRow;
					selectedSquare[0] = selectedColumn;
					selectedRow = -1; 
					selectedColumn = -1;
				}
			}
		} else if (gotoColumn != -1 && gotoRow != -1) {
			int gotoPos[2] = {gotoColumn, gotoRow};
			int legal = isLegalMove(board, selectedSquare, gotoPos, turn);
			if (legal == 1) {//board, selectedSquare, gotoPos
				board[7-gotoRow][gotoColumn] = board[7-selectedSquare[1]][selectedSquare[0]];
				board[7-selectedSquare[1]][selectedSquare[0]] = 0;
				selectedSquare[1] = -1;
				selectedSquare[0] = -1;
				gotoRow = -1;
				gotoColumn = -1;
				turn = abs(turn-1);
			} else if (legal == 0) {
				gotoRow = -1;
				gotoColumn = -1;
			} else {
				if (legal == 3) {finished = true;}
			}
		}
	default:
		break;
	}
}
void selectRow(int row) {
	

}
void outlineSquare (int x, int y, int w, int r, int g, int b) {//x pos, y pos, width, red, green, blue
	SDL_Rect top = {25*x+70, 25*(7-y)+12, 25, w};
	SDL_Rect bottom = {25*x+70, 25*(7-y)+12 + (25-w), 25, w};
	SDL_Rect left = {25*x+70, 25*(7-y)+12, w, 25};
	SDL_Rect right = {25*x+70 + (25-w), 25*(7-y)+12, w, 25};
	SDL_FillRect(screen, &top, SDL_MapRGB(screen->format, r, g, b));
	SDL_FillRect(screen, &bottom, SDL_MapRGB(screen->format, r, g, b));
	SDL_FillRect(screen, &left, SDL_MapRGB(screen->format, r, g, b));
	SDL_FillRect(screen, &right, SDL_MapRGB(screen->format, r, g, b));
}
//lmao funny line cause error
