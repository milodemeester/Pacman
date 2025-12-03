# Architecture Overview

## Project Structure

```
Pacman/
├── Logic/                    # Game logic library (independent of SFML)
│   ├── include/
│   │   ├── World.h          # Main game controller
│   │   ├── Subject.h        # Observer pattern base
│   │   ├── Observer.h       # Observer pattern interface
│   │   ├── GameFactory.h    # Abstract Factory
│   │   ├── PacmanModel.h    # Player model
│   │   ├── GhostModel.h     # Base ghost class
│   │   ├── InkyModel.h      # Random ghost (Type 1)
│   │   ├── Type2Ghost.h     # Forward-chasing ghost (Pinky, Blinky)
│   │   ├── ClydeModel.h     # Direct-chasing ghost (Type 3)
│   │   ├── Score.h          # Score tracking (Observer)
│   │   ├── Stopwatch.h      # Singleton timer
│   │   └── Random.h         # Singleton RNG
│   └── src/
│       └── [implementation files]
│
├── Representation/          # SFML-based views
│   ├── include/
│   │   ├── Game.h           # Main game class
│   │   ├── StateManager.h   # State pattern manager
│   │   ├── State.h          # State base class
│   │   ├── MenuState.h      # Menu screen state
│   │   ├── LevelState.h     # Gameplay state
│   │   ├── PausedState.h    # Pause screen state
│   │   ├── VictoryState.h   # Victory/defeat state
│   │   ├── SfmlFactory.h    # Concrete Factory
│   │   ├── Camera.h         # Coordinate projection
│   │   ├── EntityView.h     # View base class
│   │   └── [specific view files]
│   └── src/
│       └── [implementation files]
│
├── Utilities/               # Shared utilities
│   ├── utils.h
│   └── utils.cpp
│
├── data/                    # Game assets
│   ├── maps/
│   │   └── map1.txt
│   ├── fonts/
│   │   └── score_font.TTF
│   ├── sprite.png
│   └── high_scores.txt
│
└── main.cpp                 # Entry point
```

## Design Patterns Implemented

### 1. Model-View-Controller (MVC)

```
┌─────────────────────────────────────────────────────────────┐
│                         CONTROLLER                          │
│  ┌─────────────────────────────────────────────────────┐   │
│  │              World (Game Controller)                 │   │
│  │  - Manages all entities                             │   │
│  │  - Handles collisions                               │   │
│  │  - Coordinates game logic                           │   │
│  │  - Updates all models                               │   │
│  └─────────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────────┘
                           │
                           │ updates
                           ▼
┌─────────────────────────────────────────────────────────────┐
│                          MODELS                             │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐     │
│  │ PacmanModel  │  │  GhostModel  │  │  CoinModel   │     │
│  │              │  │  - InkyModel │  │  FruitModel  │     │
│  │ - Position   │  │  - Blinky    │  │  WallModel   │     │
│  │ - Direction  │  │  - Pinky     │  │              │     │
│  │ - Lives      │  │  - Clyde     │  │              │     │
│  │ - Speed      │  │  - AI logic  │  │              │     │
│  └──────────────┘  └──────────────┘  └──────────────┘     │
│         │                  │                  │             │
│         └──────────────────┴──────────────────┘             │
│                           │                                 │
│                      inherits from                          │
│                           │                                 │
│                    ┌──────▼──────┐                         │
│                    │   Subject   │                         │
│                    │  (Observable)│                         │
│                    └─────────────┘                         │
└─────────────────────────────────────────────────────────────┘
                           │
                           │ notifies
                           ▼
┌─────────────────────────────────────────────────────────────┐
│                          VIEWS                              │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐     │
│  │ PacmanView   │  │  GhostView   │  │  CoinView    │     │
│  │              │  │              │  │  FruitView   │     │
│  │ - Sprite     │  │ - Sprites    │  │  WallView    │     │
│  │ - Animation  │  │ - Animation  │  │              │     │
│  │ - Rendering  │  │ - Color      │  │              │     │
│  └──────────────┘  └──────────────┘  └──────────────┘     │
│         │                  │                  │             │
│         └──────────────────┴──────────────────┘             │
│                           │                                 │
│                      inherits from                          │
│                           │                                 │
│                    ┌──────▼──────┐                         │
│                    │ EntityView  │                         │
│                    │  (Observer) │                         │
│                    └─────────────┘                         │
└─────────────────────────────────────────────────────────────┘
```

### 2. Observer Pattern

```
┌──────────────────────────────────────────────────────────────┐
│                        Subject                               │
│  ┌────────────────────────────────────────────────────┐     │
│  │  - observers_: vector<Observer*>                   │     │
│  │  + addObserver(Observer*)                          │     │
│  │  + removeObserver(Observer*)                       │     │
│  │  + notify(Event)                                   │     │
│  └────────────────────────────────────────────────────┘     │
│                   ▲                    ▲                     │
│                   │                    │                     │
│        ┌──────────┴──────────┐        │                     │
│        │                     │        │                     │
│  ┌─────┴──────┐       ┌─────┴────────┴──────┐             │
│  │ PacmanModel│       │    GhostModel        │             │
│  │ CoinModel  │       │    etc.              │             │
│  │ FruitModel │       │                      │             │
│  └────────────┘       └──────────────────────┘             │
└──────────────────────────────────────────────────────────────┘
                           │
                           │ notifies
                           ▼
┌──────────────────────────────────────────────────────────────┐
│                        Observer                              │
│  ┌────────────────────────────────────────────────────┐     │
│  │  + onNotify(Subject&, Event&)                      │     │
│  └────────────────────────────────────────────────────┘     │
│                   ▲                    ▲                     │
│                   │                    │                     │
│        ┌──────────┴──────────┐        │                     │
│        │                     │        │                     │
│  ┌─────┴──────┐       ┌─────┴────────┴──────┐             │
│  │ EntityView │       │       Score          │             │
│  │ - Pacman   │       │ - Tracks points      │             │
│  │ - Ghost    │       │ - High scores        │             │
│  │ - Coin     │       │                      │             │
│  │ - Fruit    │       │                      │             │
│  └────────────┘       └──────────────────────┘             │
└──────────────────────────────────────────────────────────────┘

Events: EntityPositionChanged, EntityDirectionChanged,
        CoinCollected, FruitEaten, GhostEaten, etc.
```

### 3. Abstract Factory Pattern

```
┌──────────────────────────────────────────────────────────────┐
│                   AbstractFactory                            │
│  ┌────────────────────────────────────────────────────┐     │
│  │  GameFactory                                       │     │
│  │  + createPacman()   → shared_ptr<Subject>          │     │
│  │  + createGhost()    → shared_ptr<Subject>          │     │
│  │  + createCoin()     → shared_ptr<Subject>          │     │
│  │  + createFruit()    → shared_ptr<Subject>          │     │
│  │  + createWall()     → shared_ptr<Subject>          │     │
│  └────────────────────────────────────────────────────┘     │
│                           ▲                                  │
│                           │                                  │
│                    implements                                │
│                           │                                  │
│  ┌────────────────────────┴───────────────────────────┐     │
│  │            SfmlFactory                             │     │
│  │  - Creates models AND attaches SFML views          │     │
│  │  - Returns model with view already observing       │     │
│  │  + createPacman()   → PacmanModel + PacmanView     │     │
│  │  + createGhost()    → GhostModel + GhostView       │     │
│  │  + createCoin()     → CoinModel + CoinView         │     │
│  │  + createFruit()    → FruitModel + FruitView       │     │
│  │  + createWall()     → WallModel + WallView         │     │
│  └────────────────────────────────────────────────────┘     │
└──────────────────────────────────────────────────────────────┘

Benefits:
- World (logic) doesn't know about SFML
- Can create alternative factories (e.g., TextFactory for testing)
- Views automatically attached during creation
```

### 4. Singleton Pattern

```
┌──────────────────────────────────────────────────────────────┐
│                        Stopwatch                             │
│  ┌────────────────────────────────────────────────────┐     │
│  │  - static instance: shared_ptr<Stopwatch>          │     │
│  │  - deltaTime: float                                │     │
│  │  + getInstance() → shared_ptr<Stopwatch>           │     │
│  │  + update()                                        │     │
│  │  + getDeltaTime() → float                         │     │
│  │  + get_now() → time_point                         │     │
│  └────────────────────────────────────────────────────┘     │
│                                                              │
│  Used by: All entities for time-based movement              │
│           Score for time-based scoring                      │
│           World for fear mode timing                        │
└──────────────────────────────────────────────────────────────┘

┌──────────────────────────────────────────────────────────────┐
│                         Random                               │
│  ┌────────────────────────────────────────────────────┐     │
│  │  - static instance: shared_ptr<Random>             │     │
│  │  - generator: mt19937                              │     │
│  │  + getInstance() → shared_ptr<Random>              │     │
│  │  + getNumber(min, max) → int                       │     │
│  └────────────────────────────────────────────────────┘     │
│                                                              │
│  Used by: Ghost AI for random direction choices             │
└──────────────────────────────────────────────────────────────┘
```

### 5. State Pattern

```
┌──────────────────────────────────────────────────────────────┐
│                      StateManager                            │
│  ┌────────────────────────────────────────────────────┐     │
│  │  - stateStack: stack<unique_ptr<State>>            │     │
│  │  + pushState(unique_ptr<State>)                    │     │
│  │  + popState()                                      │     │
│  │  + processInput(Event&)                            │     │
│  │  + update(double)                                  │     │
│  │  + render(RenderWindow&)                           │     │
│  └────────────────────────────────────────────────────┘     │
│                           │                                  │
│                      manages                                 │
│                           ▼                                  │
│  ┌────────────────────────────────────────────────────┐     │
│  │                    State (abstract)                 │     │
│  │  + processInput(Event&, RenderWindow&)             │     │
│  │  + update(double)                                  │     │
│  │  + render(RenderWindow&)                           │     │
│  └────────────────────────────────────────────────────┘     │
│                           ▲                                  │
│        ┌──────────────────┼──────────────────┐             │
│        │                  │                  │             │
│  ┌─────┴──────┐  ┌───────┴────────┐  ┌──────┴────────┐    │
│  │ MenuState  │  │  LevelState    │  │ PausedState   │    │
│  │            │  │  - World       │  │               │    │
│  │ - Scores   │  │  - Entities    │  │ - Resume      │    │
│  │ - Play btn │  │  - Gameplay    │  │ - Quit        │    │
│  └────────────┘  └────────────────┘  └───────────────┘    │
│                           │                                  │
│                           │                                  │
│                  ┌────────┴────────┐                        │
│                  │  VictoryState   │                        │
│                  │  - Win/Lose msg │                        │
│                  │  - Next level   │                        │
│                  └─────────────────┘                        │
└──────────────────────────────────────────────────────────────┘

State Transitions:
MenuState → LevelState (on Play click)
LevelState → PausedState (on Escape)
LevelState → VictoryState (win/lose)
PausedState → LevelState (resume)
PausedState → MenuState (quit)
VictoryState → LevelState (next level)
VictoryState → MenuState (game over)
```

## Class Hierarchy

### Entity Hierarchy

```
Subject (abstract)
├── MoveableSubject (abstract)
│   ├── PacmanModel
│   └── GhostModel (abstract)
│       ├── InkyModel (random AI)
│       ├── Type2Ghost (forward-chasing AI)
│       │   ├── PinkyModel (leaves at 0s)
│       │   └── BlinkyModel (leaves at 5s)
│       └── ClydeModel (direct-chasing AI, leaves at 10s)
│
├── CollectableSubject (abstract)
│   ├── CoinModel
│   └── FruitModel
│
└── WallModel
```

### View Hierarchy

```
EntityView (abstract, implements Observer)
├── PacmanView
│   - Sprite animation
│   - Direction-based sprites
│
├── GhostView
│   - Walking animation
│   - Fear mode color change
│   - Direction-based eye sprites
│
├── CoinView
│   - Simple sprite
│
├── FruitView
│   - Simple sprite
│
└── WallView
    - Visible/invisible walls
```

## Coordinate System

```
World Coordinate System (Normalized)
  
  (-1, 1) ┌─────────────────────┐ (1, 1)
          │                     │
          │   Game World        │
          │   [-1, 1] x [-1, 1] │
          │                     │
 (-1, -1) └─────────────────────┘ (1, -1)

           Camera.project()
                  ↓

Screen Coordinate System (Pixels)
  
   (0, 0) ┌─────────────────────┐ (W, 0)
          │                     │
          │   SFML Window       │
          │   [0, W] x [0, H]   │
          │                     │
   (0, H) └─────────────────────┘ (W, H)
```

Benefits:
- Resolution independent game logic
- Easy scaling and aspect ratio handling
- Clean separation of concerns

## Game Loop

```
┌─────────────────────────────────────────────────────────┐
│                    Main Game Loop                       │
│                                                         │
│  1. Process Input                                       │
│     - Poll SFML events                                  │
│     - Current state handles input                       │
│     - Translate to game actions                         │
│                                                         │
│  2. Update                                              │
│     - Stopwatch calculates deltaTime                    │
│     - Current state updates                             │
│       • World updates all entities                      │
│       • Collision detection                             │
│       • AI decisions                                    │
│       • Score calculation                               │
│     - State transitions                                 │
│                                                         │
│  3. Render                                              │
│     - Clear window                                      │
│     - Current state renders                             │
│       • EntityViews draw sprites                        │
│       • UI elements (score, lives, level)               │
│     - Display window                                    │
│                                                         │
│  4. Repeat                                              │
└─────────────────────────────────────────────────────────┘
```

## Data Flow

```
User Input → Game → StateManager → Current State
                                         │
                     ┌───────────────────┼───────────────────┐
                     ▼                   ▼                   ▼
                  World             UI Elements         Other Logic
                     │
        ┌────────────┼────────────┐
        ▼            ▼            ▼
    Pacman       Ghosts       Collectables
        │            │            │
        └────────────┴────────────┘
                     │
                notify(Event)
                     │
        ┌────────────┴────────────┐
        ▼                         ▼
   EntityViews                  Score
   (rendering)              (calculation)
```

## Key Design Decisions

### 1. Logic/Representation Separation
- **Logic library:** Pure C++, no SFML dependencies
- **Representation:** SFML-specific code
- **Communication:** Through Observer pattern and abstract factory

### 2. Smart Pointer Usage
- `shared_ptr` for entities (multiple ownership in World and views)
- `unique_ptr` for states (StateManager has exclusive ownership)
- Raw pointers for observers (⚠️ should be weak_ptr)

### 3. Time-Based Movement
- All movement multiplied by deltaTime
- Ensures consistent speed across different frame rates
- Speeds defined as units per millisecond

### 4. File-Based Configuration
- Maps loaded from text files
- High scores persisted to file
- Easy level design without recompilation

---

## Identified Design Issues

### High Coupling
- World knows about all entity types
- Entities need World reference for collision checking
- Consider dependency injection or collision resolver pattern

### Missing Patterns
- **Strategy Pattern:** Could eliminate ghost AI duplication
- **Command Pattern:** Could improve input handling and collision responses
- **Visitor Pattern:** Could improve entity type resolution

### Observer Implementation
- Should use weak_ptr instead of raw pointers
- Risk of dangling pointers if observers destroyed before subjects

### Singleton Misuse
- Returns shared_ptr instead of reference
- Allows multiple "copies" of singleton
- Makes testing difficult

---

**End of Architecture Overview**
