# 🪟 TinyWindowManager

**TinyWindowManager (TWM)** is a minimal, flexible window manager for lightweight GUI projects.  
It handles basic window logic (position, dragging, focus, etc.) — while leaving **rendering** entirely up to you.

Currently, it’s designed to integrate easily with tools like [rayGUI](https://github.com/raysan5/raygui), but aims to stay **renderer-independent**.

> 🧩 A tiny foundation for custom GUI systems — simple, modular, and extensible.

## ✨ Features

- 🪟 **Window logic only:** manages window state, position, and focus
- 🧱 **Simple interface:** `Window` structs + static functions for updates and drawing  
- ⚡ **Lightweight:** no dependencies, minimal code footprint  
- 🧠 **Easy to use:** override `Init()` and `Draw()` for defining behavior  


## ⚙️ API Overview

```cpp
namespace TWM {

struct Window {
    Rectangle Bounds;
    bool Dragging = false;
    bool Active = false;

    virtual void Init() {}
    virtual void Draw() {}
};

extern std::vector<Window *> States;

void MakeMoveable(Window* win, float TitleBarHeight = 20.0f);
void Update();
void Draw();

} // namespace TWM
```
## 📦 Build

TinyWindowManager is written in **C++**, header-only.
Just include `TWM.hpp` in your project and define `TWM_IMPLEMENTATION` once before importing it

## 📜 License

MIT License — free for personal and commercial use.
Contributions and pull requests are welcome!
