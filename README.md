# 2D Black Hole Gravitational Lensing Simulation

A real-time physics simulation demonstrating gravitational lensing and light ray deflection around a black hole, implemented in C++ using SFML graphics library.

![Black Hole Simulation](https://img.shields.io/badge/C%2B%2B-17-blue) ![SFML](https://img.shields.io/badge/SFML-Graphics-green) ![Physics](https://img.shields.io/badge/Physics-General%20Relativity-red)

## 🌌 Overview

This simulation visualizes how light rays are deflected by the intense gravitational field of a black hole, demonstrating the fascinating phenomenon of gravitational lensing predicted by Einstein's General Theory of Relativity. Multiple colored light rays travel from the left side of the screen toward a central black hole, where they follow realistic curved trajectories based on actual physics equations.

## 🎓 Educational Background

The physics concepts and equations implemented in this simulation were learned from:
**Physics 161: Black Holes** by **Kim Griest**

This course provided the theoretical foundation for understanding:
- General Relativity principles
- Schwarzschild geometry
- Gravitational lensing effects
- Light ray deflection calculations
- Event horizon physics

## ✨ Features

### Real Physics Implementation
- **Gravitational Lensing**: Light rays bend according to simplified General Relativity equations
- **Impact Parameter Calculations**: Deflection based on perpendicular distance to black hole
- **Schwarzschild Radius**: Accurate event horizon representation
- **Relativistic Corrections**: Applied for realistic light bending behavior

### Visual Components
- **Black Hole Core**: Central singularity representation
- **Event Horizon**: Translucent boundary showing point of no return
- **Multi-colored Light Rays**: Easy tracking of individual photon paths
- **Real-time Path Visualization**: Shows complete curved trajectories
- **Reference Grid**: Spatial orientation assistance
- **Dynamic Statistics**: Live count of active light rays

### Simulation Behavior
- **Automatic Ray Generation**: Continuous spawning at varied heights
- **Distance-based Deflection**: Closer rays experience stronger bending
- **Ray Absorption**: Photons crossing event horizon disappear
- **Smooth Animation**: 60 FPS real-time physics calculation

## 🎮 Controls

| Key | Action |
|-----|--------|
| `ESC` | Exit simulation |
| `R` | Reset simulation (clear all rays) |

## 🔬 Physics Equations Used

### Gravitational Force
```
F = GM/r²
```
Where:
- G = Gravitational constant (scaled for visualization)
- M = Black hole mass
- r = Distance from black hole center

### Light Deflection Angle (Approximated)
```
θ ≈ 4GM/(c²b)
```
Where:
- θ = Deflection angle
- c = Speed of light
- b = Impact parameter (perpendicular distance)

### Numerical Integration
- **Verlet Integration**: For smooth, stable trajectory calculations
- **Constant Light Speed**: Maintains c while allowing direction changes

## 🛠️ Technical Implementation

### Dependencies
- **SFML 2.x**: Graphics, Window, and System modules
- **C++17**: Modern C++ features and standard library
- **Windows**: Optimized for Windows environment

### Key Classes
- `BlackHole`: Manages gravitational source and visual representation
- `LightRay`: Handles individual photon physics and path tracking
- `BlackHoleSimulation`: Main simulation loop and event handling
- `Vector2f`: Custom 2D vector mathematics

### File Structure
```
2DBlackHole/
├── BlackHole.cpp          # Main simulation source code
├── BlackHole.exe          # Compiled executable
├── README.md              # This documentation
├── sfml-graphics-2.dll    # SFML graphics library
├── sfml-window-2.dll      # SFML window library
└── sfml-system-2.dll      # SFML system library
```

## 🚀 Building and Running

### Prerequisites
- MinGW-w64 with GCC
- SFML 2.x development libraries
- Windows operating system

### Compilation
```bash
g++ -std=c++17 -g BlackHole.cpp -o BlackHole.exe -lsfml-graphics -lsfml-window -lsfml-system
```

### Execution
```bash
BlackHole.exe
```

## 📊 Observable Phenomena

When running the simulation, you can observe:

1. **Light Bending**: Rays curve smoothly around the massive object
2. **Variable Deflection**: Different angles based on proximity to black hole
3. **Event Horizon Effect**: Complete absorption of rays crossing the boundary
4. **Impact Parameter Dependency**: Closer approaches result in stronger deflection
5. **Multiple Ray Paths**: Demonstration of how spacetime curvature affects photons

## 🔍 Real-World Applications

This simulation demonstrates principles used in:
- **Gravitational Lensing Astronomy**: Detecting distant galaxies and dark matter
- **Einstein Ring Observations**: Perfect alignment creating ring-shaped images
- **Exoplanet Detection**: Microlensing events revealing planets
- **Black Hole Imaging**: Techniques used by Event Horizon Telescope

## 🎯 Learning Objectives

This project demonstrates understanding of:
- General Relativity concepts
- Numerical physics simulation
- Real-time graphics programming
- Object-oriented design principles
- Mathematical physics implementation

## 🙏 Acknowledgments

- **Kim Griest** - Physics 161: Black Holes course instructor
- **SFML Community** - Excellent graphics library and documentation
- **Einstein** - For revolutionizing our understanding of gravity and spacetime

## 📝 License

This project is created for educational purposes as part of physics coursework.

---

*"The important thing is not to stop questioning. Curiosity has its own reason for existing."* - Albert Einstein