#ifndef SceneMethods_h
#define SceneMethods_h

/*Methods related to scene setup*/

//setup scene for stage playing state
void startPlayingStateStage();
//setup scene for boss playing state
void startPlayingStateBossTransition();
//setup scene for boss playing state
void startPlayingStateBoss();

//run things for stage playing state
void playingStateStage();
//run things for boss transition state
void playingStateBossTransition();
//run things for boss playing state
void playingStateBoss();

//clear bullets & enemies and reset player position
void resetScene();

EnemyBoss* boss; //pointer to boss enemy where needed

void startPlayingStateStage() {
    gameState = GameState::PLAYING;
    playingState = PlayingState::STAGE;

    //spawn bolters
    for (int i = 1; i <= 5; i++)
    {
        EnemyBolter* bolter = new EnemyBolter(100, -230 * i, &alphaShip);
        for (int j = 0; j < 360; j += 10) {
            theta = ((j - 90) / 180.0f) * 3.14159;
            bolter->wayPointSet.addWayPoint(300 + 200 * sin(theta), 200 + 150 * cos(theta));
        }
        enemies.push_back(bolter);
    }
    
}

void playingStateStage() {
    if (enemies.empty()) {
        startPlayingStateBossTransition();
    }
}

void startPlayingStateBossTransition() {
    playingState = PlayingState::BOSS_TRANSITION;
    boss = new EnemyBoss();
    enemies.push_back(boss);
}

void playingStateBossTransition() {
    //move boss until in position
    if (!boss->position.matches(300, 200))
        boss->moveTo(300, 200);
    else
        startPlayingStateBoss();
}

void startPlayingStateBoss() {
    playingState = PlayingState::BOSS;
    boss->setSpeed(20.0f);
}

void playingStateBoss() {
    if (enemies.empty()) {
        gameState = GameState::GAME_WIN;
    }
}

void resetScene() {
    //clear bullets
    for (int i = 0; i < bullets.size(); i++)
        delete(bullets.at(i));
    bullets.clear();
    //clear enemies
    for (int i = 0; i < enemies.size(); i++)
        delete(enemies.at(i));
    enemies.clear();
    //yes
    boss = NULL;
    //reset player position
    alphaShip.position.setValues(300, 700);
    startPlayingStateStage();
}

#endif // !SceneMethods_h

