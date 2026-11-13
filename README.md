# C++20 Terminal Ballistics & Multi-Particle Physics Engine

A 60-FPS real-time 2D physics and ballistic trajectory interception engine built in modern C++20 for the command line, featuring zero-dependency dirty-region ANSI rendering.

## Core Engineering Features
- **Dirty-Region Terminal Rendering (60 FPS):** Updates only modified `(row, col)` coordinates using raw ANSI cursor escape sequences (`\033[row;colH`) with manual stream flushing (`std::flush`), eliminating full-screen redraw flicker.
- **Euler Integration & Restitution Physics:** Simulates real-time gravitational acceleration ($g = 9.8\text{ m/s}^2$) and inelastic boundary collisions ($e = 0.8$) across 4 walls.
- **3 Operational Modes:**
  1. **Single-Particle Ballistics:** Interactive launch simulation with custom initial coordinates, velocity, and launch angle.
  2. **Automated Mid-Air Ballistic Interceptor:** Analytically computes required intercept velocity vectors $(v_{Ix}, v_{Iy})$ to snipe a moving projectile target in mid-air within a fixed time window.
  3. **Multi-Particle Simulation:** Simulates up to 200 simultaneous bouncing particles using `std::vector<Ball>` and static Mersenne Twister (`std::mt19937`) random distributions.
- **Input Sanitization:** Guards all user coordinate and particle count inputs against out-of-bounds memory/grid states using `std::clamp`.

## Project Architecture
```text
cpp-terminal-ballistics/
├── include/
│   └── physics.h      # Particle state struct and physics/rendering declarations
├── src/
│   ├── main.cpp       # Simulation loop and mode controller
│   └── physics.cpp    # Boundary restitution, ANSI cursor control, and RNG engines
└── README.md