#ifndef ScreenText_h
#define ScreenText_h

#include "Text.h"

/*all the "menu" texts and methods*/

TextField gameStartText(90, 500, 0.3, TEXT_WHITE);
TextField gameRestartText(60, 570, 0.3, TEXT_WHITE);

TextField gameOverText(130, 450, 0.5, TEXT_RED);
TextField youWereHitText(210, 510, 0.2, TEXT_WHITE);

TextField gameWinText(160, 450, 0.5, TEXT_GREEN);
TextField youDefeatedBossText(145, 510, 0.2, TEXT_WHITE);

TextField shootControls(10, 720, 0.2, TEXT_WHITE);
TextField moveControls(10, 750, 0.2, TEXT_WHITE);

//instructions at the lower left
void drawInstructions() {
    shootControls.DrawTextField("z to shoot");
    moveControls.DrawTextField("arrow keys to move");
}

//game start
void drawStartTexts() {
    gameStartText.DrawTextField("press enter to start");
    drawInstructions();
}

//game over
void drawGameOverTexts() {
    gameOverText.DrawTextField("game over");
    youWereHitText.DrawTextField("you were hit");
    gameRestartText.DrawTextField("press enter to restart");
    drawInstructions();
}

//game win
void drawGameWinTexts() {
    gameWinText.DrawTextField("you win");
    youDefeatedBossText.DrawTextField("you defeated the boss");
    gameRestartText.DrawTextField("press enter to restart");
    drawInstructions();
    
}

#endif // !ScreenText_h

