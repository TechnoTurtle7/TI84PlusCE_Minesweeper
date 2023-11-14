#pragma once

#include <stdio.h>
#include <math.h>

#include <graphx.h>
#include "gfx/gfx.h"

#include "debug.h"
#include "mathutils.h"

void setupGraphics() {
	gfx_Begin();
    
    gfx_SetDrawBuffer(); //using blit buffer (see https://ce-programming.github.io/toolchain/libraries/graphx.html#buffering-graphics)
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    gfx_SetTransparentColor(0);
    gfx_SetTextFGColor(2);
    gfx_SetColor(1);
    
    gfx_FillScreen(1);
}
void drawRemainingFlags(int flagsUsed) {
    //number
    int width = gfx_GetStringWidth("00");
    gfx_FillRectangle_NoClip(GFX_LCD_WIDTH - width - 1, 18, width, 9);
    
    char* string = (char*) calloc(3, sizeof(int));
    int flagsLeft = 10 - flagsUsed;
    sprintf(string, "%d%d", flagsLeft / 10, flagsLeft % 10);
    
    gfx_PrintStringXY(string, GFX_LCD_WIDTH - gfx_GetStringWidth(string) - 1, 18);
    free(string);
    
    //flag icon
    gfx_TransparentSprite_NoClip(sprites_tile_2, GFX_LCD_WIDTH - maxint((width - 16) / 2, 1) - 16, 1);
}
void drawVersion() {
    int width = gfx_GetStringWidth(VERSION);
    
    gfx_PrintStringXY(VERSION, GFX_LCD_WIDTH - width - 1, GFX_LCD_HEIGHT - 9);
}
void drawTile(int x, int y, int* board, int* mask, int selX, int selY) {
    int tileX = 80 + x * 16;
    int tileY = 40 + y * 16;
    
    switch(mask[10 * y + x]) {
        case MASK_COVERED:
            gfx_Sprite_NoClip(sprites_tile_0, tileX, tileY);
            break;
        case MASK_FLAGGED:
            gfx_Sprite_NoClip(sprites_tile_0, tileX, tileY);
            gfx_TransparentSprite_NoClip(sprites_tile_2, tileX, tileY);
            break;
        case MASK_UNCOVERED:
            gfx_Sprite_NoClip(sprites_tile_1, tileX, tileY);
            
            if(board[10 * y + x] == BOARD_MINE)
                gfx_TransparentSprite_NoClip(sprites_tile_3, tileX, tileY);
            else if(board[10 * y + x] > BOARD_CLEAR)
                gfx_TransparentSprite_NoClip(sprites_tiles[4 + board[10 * y + x]], tileX, tileY);
            
            break;
        default:
            exit(1);
            break;
    }
    
    if(x == selX && y == selY) {
        gfx_TransparentSprite_NoClip(sprites_tile_4, tileX, tileY);
    }
}
void drawBoard(int* board, int* mask, int selX, int selY, int flagsUsed) {
    for(int y = 0; y < 10; y++) {
        for(int x = 0; x < 10; x++) {
            drawTile(x, y, board, mask, selX, selY);
        }
    }
    
    gfx_PrintStringXY("[ARROWS] - Select", 1, 1);
    gfx_PrintStringXY("[2nd] - Uncover", 1, 11);
    gfx_PrintStringXY("[alpha] - Flag", 1, 21);
    gfx_PrintStringXY("[del] - Quit", 1, GFX_LCD_HEIGHT - 9);
    
    drawRemainingFlags(flagsUsed);
    drawVersion();
}
