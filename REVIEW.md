# Review

---
## 전체 구조
```
Main.cpp
├─Game.h
│   ├─Paddle.h
│   │   └─Config.h
│   ├─Ball.h
│   │   └─Config.h
│   ├─Config.h
│   ├─GameStats.h
│   │   └─Config.h
│   ├─GameSound.h
│   │  └─Config.h
│   └─Background.h
│       └─Config.h
└─ Random.h ← Global
```
---

### Main.cpp
```
int main()
{
    Game app;

    while(app.IsRunning())
    {
        app.ProcessEvents();
        app.Update();
        app.Render();
    }
}
/*
게임 루프 순으로 구성    
ProcessEvents -> Update -> Render
*/
```

---

### Game.h

```
// Game.h

class Game
{
public:
    Game();
    
    auto IsRunning      ()  const   ->bool; 
    auto ProcessEvents  ()          ->void; 
    auto Update         ()          ->void; 
    auto Render         ()          ->void; 
    auto GetGlobalBounds()  const   ->sf::FloatRect;
    auto Restart        ()          ->void;

private:
    sf::RenderWindow    window_             ;
    sf::Clock           clock_              ;
    Paddle              paddle_             ;
    std::vector<Ball>   balls_              ;
    sf::Clock           ballSpawnClock_     ;

    auto HandleCollisions()          ->void ;

    GameStats           stats_              ;
    GameSound           sound_              ;
    Background          background_         ;    
};

/*

*/
```
---

#### Game.cpp

```
// Game.cpp
#include "Game.h"
#include <algorithm>

Game::Game()
    :window_{sf::VideoMode({static_cast<int>(Config::WIN_WIDTH),
                            static_cast<int>(Config::WIN_HEIGHT)}),"Bounce"}
{
    window_.setFramerateLimit(Config::FRAME);
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
    //어떤 하드웨어 환경에서도 동일한 Frame당 속도를 유지하게 제어하기 위해 deltaTime을 변수로 선언
    float deltaTime = clock_.restart().asSeconds();

    // 일정 시간이 지나면 Ball 객체를 생성, 시계는 리셋
    if(ballSpawnClock_.getElapsedTime().asSeconds() > Config::ONE_THIRD)
    {
        balls_.emplace_back();
        ballSpawnClock_.restart();
    }

    // paddle의 Input에 deltaTime을 전달
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
    if(ballsMissd>0)
    {
        stats_.SetLives(stats_.GetLives()-ballsMissd);
    }
}

auto Game::Restart()->void
{
    balls_.clear();
    ballSpawnClock.restart();
    stats_.Reset();
}
```

---
### Paddle.h 
```
#pragma once
#include<SFML/Graphics.hpp>
#include"Config.h"

class Paddle
{
private:

    sf::RectangleShape shape_;

public:
    Paddle();

    auto Draw           (sf::RenderWindow& window_) const  -> void;
    auto Move           (float deltaTime)                  -> void;
    auto GetGlobalBounds()                          const  ->sf::FloatRect;
    
};
```
---

#### Paddle.cpp
```
#include <Paddle.h>
#include <algorithm>

Paddle::Paddle()
    :shape_{sf::Vector2f{120, 20}}
{
    shape_.setFillColor({60,90,60,255});
    shape_.setOrigin(shape_.getGeometricCenter());
    shape_.setPosition({Config::WIN_WIDTH*Config::HALF, Config::WIN_HEIGHT*Config::THREE_QUARTERS});
}

auto Paddle::Draw(sf::RenderWindow& window_) const->void
{
    window_.draw(shape_);
}

auto Paddle::Move(float deltaTime) -> void
{

    sf::Vector2f prevposition  = shape_.getPosition(); 

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        shape_.move({+Config::USER_SPEED*deltaTime*2,Config::ZERO});
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        shape_.move({-Config::USER_SPEED*deltaTime*2,Config::ZERO});
    }
    
    float halfWidth = shape_.getSize().x*Config::HALF;
    
    /*
    if(shape_.getPosition().x < halfWidth || 600-halfWidth <= shape_.getPosition().x)
        shape_.setPosition(prevposition);
    아래와 같다.
    */

    // clamp (v, lo, hi), v값을 lo에서 hi까지 clamp(제한)시킴.
    float mapsize = std::clamp(shape_.getPosition().x, halfWidth, Config::WIN_WIDTH-halfWidth);
    shape_.setPosition({mapsize, shape_.getPosition().y});
    
}


auto Paddle::GetGlobalBounds() const   ->sf::FloatRect
{
    return shape_.getGlobalBounds();
}
```
---
### Ball.h 

---

#### Ball.cpp

---

### Random.h 

---

#### Random.cpp 

---
### GameStats.h 

---

#### GameStats.cpp

---
### GameSound.h 

---

#### GameSound.cpp

---
### Background.h 

---
#### Background.cpp

---

### Config.h

---



