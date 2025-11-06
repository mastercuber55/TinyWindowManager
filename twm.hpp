/*
    MIT License

    Copyright (c) 2025 Cube Nerd

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to
   deal in the Software without restriction, including without limitation the
   rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
   sell copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
   IN THE SOFTWARE.
*/
#pragma once

#ifndef TWM
#define TWM

#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <vector>

namespace TWM {
struct Window {

  Rectangle Bounds;
  bool Dragging = false;
  bool Active = false;

  virtual void Init();
  virtual void Draw();
};
extern std::vector<Window *> States;
void MakeMoveable(Window *win, float TitleBarHeight = 20.0f);
void Update();
void Draw();
} // namespace TWM

#endif

#ifdef TWM_IMPLEMENTATION
#undef TWM_IMPLEMENTATION

namespace TWM {

void Window::Init() {}
void Window::Draw() {}

std::vector<Window *> States;
void MakeMoveable(Window *win, float TitleBarHeight) {

  Rectangle TitleBar = {win->Bounds.x, win->Bounds.y, win->Bounds.width,
                        TitleBarHeight};

  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
      CheckCollisionPointRec(GetMousePosition(), TitleBar)) {
    win->Dragging = true;
  }

  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    win->Dragging = false;

  if (win->Dragging) {
    Vector2 delta = GetMouseDelta();
    win->Bounds.x += delta.x;
    win->Bounds.y += delta.y;
  }
}

void Update() {
  Vector2 Mouse = GetMousePosition();

  for (int i = (int)States.size() - 1; i >= 0; i--) {
    Window *win = States[i];

    if (win->Active)
      MakeMoveable(win);
    else
      continue;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        CheckCollisionPointRec(Mouse, States[i]->Bounds)) {
      States.erase(States.begin() + i);
      States.push_back(win);
      break;
    }
  }
}
void Draw() {
  if (States.size() > 1) {
    GuiLock();
    for (size_t i = 0; i < States.size() - 1; i++) {
      States[i]->Draw();
    }
    GuiUnlock();
  }
  States.back()->Draw();
}
} // namespace TWM

#endif