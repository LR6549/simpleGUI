## SimpleGui (SFML 3.0.0)

**SimpleGui** is a lightweight, header-only GUI library built on top of SFML 3.0.0. It provides basic GUI elements such as buttons and labels, designed for quick integration into SFML projects with minimal setup.

## Key features:
- **Widgets:** Supports buttons and labels with customizable text, colors, and states.
- **Mouse Handling:** Tracks mouse position and button states for interactive widgets.
- **State Management:** Widgets have `Normal`, `Hovered`, `Active`, and `Disabled` states.
- **Threaded Updates:** Optional background thread to update and render widgets automatically.
- **Customizable Styling:** Easily set text, background, and outline colors for each widget state.
- **Collision Detection:** Built-in Axis-Aligned Bounding Box (AABB) collision checks for interaction detection.

Designed for simplicity, **SimpleGui** is ideal for small projects or prototypes where full-featured GUI frameworks are overkill.

## Project Status: Work in Progress

**This project is not finished!** Current TODO list includes:

- Integrate **JFLX_Header** libraries for extended functionality.
- Eventual switch from **SFML 3.0.0** to **SDL3** for broader platform support.
- Implementation of additional widgets such as **Entries, Images, Menubars**, and more. (Keyboard handling)
- Refinement of current functionality, including **thread management, rendering optimizations**, and general stability improvements.
