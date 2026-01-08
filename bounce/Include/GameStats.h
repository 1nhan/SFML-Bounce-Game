#pragma once
#include <SFML/Graphics.hpp>
#include "Config.h"

class GameStats
{
public:
    GameStats();

    auto Draw(sf::RenderWindow& window_)->void;

    auto SetScore(int score)            ->void;
    auto SetHighScore(int SetHighScore) ->void;
    auto SetLives(int lives)            ->void;

    auto GetScore() const               ->int;
    auto GetHighScore() const           ->int;
    auto GetLives() const               ->int;

    auto Reset()                        ->void;    
private:
    sf::Font    font_;
    sf::Text    scoreText_;
    sf::Text    livesText_;
    sf::Text    highScoreText_;


    int score_      ;
    int highScore_  ;
    int lives_      ;
};