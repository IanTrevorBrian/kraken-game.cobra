//This file defines functions that control the snake based on keyboard inputs.

#include "controller.h"
#include <iostream>
#include <SDL2/SDL.h>  //for macOS.  #include "SDL.h" for windows

#include "snake.h"

//Changing the snake movement direction safely to ensure snake cannot collide with itself.
//condition is true if either the input is not opposite the current direction, or the snake is size 1.
void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

//checking for all pending SDL events with SDL_PollEvent retrieving each one by one
void Controller::HandleInput(bool &running, Snake &snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {    //quit event user clicks the window X button.
      running = false;
    } else if (e.type == SDL_KEYDOWN) {   //Handles directional keys.
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(snake, Snake::Direction::kUp,   //snake can only move UP if it is not currently moving DOWN.
                          Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, Snake::Direction::kLeft, //snake can only move left if it is not currently moving right.
                          Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;
      }
    }
  }
}

/*
Snake Movement Rules:

| Snake Direction | Input | Snake Size | Condition Result | Action                       |
| --------------- | ----- | ---------- | ---------------- | ---------------------------- |
| RIGHT           | LEFT  | 5          | FALSE            | Ignore input, keep RIGHT     |
| RIGHT           | LEFT  | 1          | TRUE             | Accept input, change to LEFT |
| RIGHT           | UP    | 5          | TRUE             | Accept input, change to UP   |
*/