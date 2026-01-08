#include "GameStats.h"
#include <fstream>

GameStats::GameStats()
    :font_{"Content/Montserrat.ttf"},
    scoreText_{font_},
    livesText_{font_},
    highScoreText_{font_}
{
    scoreText_.setPosition({10,10});
    scoreText_.setFillColor(sf::Color::White);
    SetScore(Config::ZERO);
    
    livesText_.setPosition({10,60});
    livesText_.setFillColor(sf::Color::White);
    SetLives(Config::FIVE);
    
    highScoreText_.setPosition({10,110});
    highScoreText_.setFillColor(sf::Color::Yellow);

    if(std::fstream file {"Content/highScore.txt"})
    {
        file>> highScore_;
    }
    else 
    {
        highScore_ = Config::ZERO;
    }
    SetHighScore(highScore_);
}

auto GameStats::Draw(sf::RenderWindow& window_) ->void
{
    window_.draw(scoreText_);
    window_.draw(livesText_);
    window_.draw(highScoreText_);
}

auto GameStats::SetScore(int scores) ->void
{
    score_ = scores;
    scoreText_.setString("Score: " + std::to_string(score_));
}

auto GameStats::SetHighScore(int highScore) ->void
{
    highScore_ = highScore;
    highScoreText_.setString("HighScore: " + std::to_string(highScore_));
}

auto GameStats::SetLives(int lives) ->void
{
    lives_ = lives;
    livesText_.setString("Live: " + std::to_string(lives_));
}

auto GameStats::GetScore() const->int
{
    return score_;
}

auto GameStats::GetHighScore() const->int
{
    return highScore_;
}

auto GameStats::GetLives() const->int
{
    return lives_;
}

auto GameStats::Reset()->void
{
    if(score_>highScore_) 
    {
        if(std::ofstream file{"Content/highScore.txt"})
        {
            file << score_;
        }
        SetHighScore(score_);
    }
    SetScore(Config::ZERO);
    SetLives(Config::FIVE);
}