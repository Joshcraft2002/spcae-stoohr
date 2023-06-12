#ifndef MainMethods_h
#define MainMethods_h

/*update and drawing methods*/

//update player
void updatePlayer() {
    alphaShip.Update();
}

//update bullets and collisions
void updateBullets() {
    for (int i = 0; i < bullets.size(); i++)
    {
        //update bullets
        bullets.at(i)->Update();

        //check player collision with enemy bullets
        if (!bullets.at(i)->isFriendly())
            if (alphaShip.checkCollision(bullets.at(i)) && gameState == GameState::PLAYING)
                gameState = GameState::GAME_OVER;

        //check enemy collision with friendly bullets, while enemies exist
        if (bullets.at(i)->isFriendly() && !enemies.empty()) {
            for (int j = 0; j < enemies.size(); j++) {
                //check collision of enemy while game state is playing and not during boss transition
                if (enemies.at(j)->checkCollision(bullets.at(i)) && gameState == GameState::PLAYING && playingState != PlayingState::BOSS_TRANSITION) {
                    enemies.at(j)->damage(bullets.at(i)->getDamage()); //damage enemy based on damage of bullet
                    bullets.at(i)->callHit();
                }
            }
        }

        //remove hit bullets
        if (bullets.at(i)->hasHit()) {
            delete(bullets.at(i));
            bullets.erase(bullets.begin() + i);
        }
    }   
}

//update enemies
void updateEnemies() {
    for (int i = 0; i < enemies.size(); i++)
    {
        //update enemies
        enemies.at(i)->Update();

        //remove killed enemies
        if (!enemies.at(i)->isAlive()) {

            delete(enemies.at(i));
            enemies.erase(enemies.begin() + i);
        }
    }
}

//draw objects in a certain order
void drawObjects() {
    //space background
    drawSpaceBackground();

    //player ship
    if (gameState != GameState::GAME_OVER)
        alphaShip.DrawObject();

    //enemy bullets
    for (int i = 0; i < bullets.size(); i++)
        if (!bullets.at(i)->isFriendly())
            bullets.at(i)->DrawObject();

    //enemies
    for (int i = 0; i < enemies.size(); i++)
        enemies.at(i)->DrawObject();

    //player bullets
    for (int i = 0; i < bullets.size(); i++)
        if (bullets.at(i)->isFriendly())
            bullets.at(i)->DrawObject();

    //healthbars
    for (int i = 0; i < enemies.size(); i++)
        enemies.at(i)->DrawHealthBar();
}

#endif // !BulletCollisions_h

