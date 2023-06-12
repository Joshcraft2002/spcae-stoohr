#ifndef GameState_h
#define GameState_h

enum class GameState {
    START,
    PLAYING,
    GAME_OVER,
    GAME_WIN
};

enum class PlayingState {
    STAGE,
    BOSS_TRANSITION,
    BOSS
};

//set initial state to start
GameState gameState = GameState::START;
PlayingState playingState = PlayingState::STAGE;

#endif // !GameState_h

