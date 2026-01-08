#include "Game.h"
#include <algorithm>

Game::Game()
    :window_{sf::VideoMode({static_cast<int>(Config::WIN_WIDTH),
                            static_cast<int>(Config::WIN_HEIGHT)}),"Bounce"}
{
    window_.setFramerateLimit(Config::FRAME);
    // window_.setVerticalSyncEnabled(true); 둘 중 하나만
}

auto Game::IsRunning      () const    ->bool
{
    return window_.isOpen();    
} 

auto Game::ProcessEvents  ()          ->void
{
    while(const auto event = window_.pollEvent())
    {
        if(event->is<sf::Event::Closed>())
        {
            window_.close();
        }
    }
} 

auto Game::Update() ->void
{
    float deltaTime = clock_.restart().asSeconds();

    if(ballSpawnClock_.getElapsedTime().asSeconds() > Config::ONE_THIRD)
    {
        
        balls_.emplace_back();
        ballSpawnClock_.restart();
    }

    paddle_.Move(deltaTime);

    for(Ball& ball: balls_)
        ball.Move(deltaTime);
    
    HandleCollisions(); 

    if(stats_.GetLives() <= Config::ZERO)
    {
        Restart();
    }
} 

auto Game::Render() ->void
{
    window_.clear();
    
    background_.Draw(window_);
    stats_.Draw(window_);
    paddle_.Draw(window_);

    for(const Ball& ball: balls_)
        ball.Draw(window_);
    
    window_.display();
} 

auto Game::HandleCollisions() ->void
{
    sf::FloatRect paddleBounds = paddle_.GetGlobalBounds();
    
    for(Ball& ball:balls_)
    {
        sf::FloatRect ballBounds = ball.GetGlobalBounds();
        bool isCollisions = ballBounds.findIntersection(paddleBounds).has_value();
    
        if(isCollisions && ball.GetDirection().y>Config::ZERO)
        {
            ball.Bounce();
            stats_.SetScore(stats_.GetScore()+Config::ONE);
            sound_.PlayBounceSound();
        }
    }

    std::size_t ballsMissd = std::erase_if(balls_, [](const Ball& ball) {return ball.IsOutside();});
    if(ballsMissd>Config::ZERO)
    {
        stats_.SetLives(stats_.GetLives()-ballsMissd);
    }
}

auto Game::Restart()->void
{
    balls_.clear();
    ballSpawnClock_.restart();
    stats_.Reset();
}