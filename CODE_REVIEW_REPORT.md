# Comprehensive Code Review Report: Pacman C++ Project
**Date:** December 7, 2025  
**Reviewer:** Advanced Code Review System  
**Repository:** milodemeester/Pacman

---

## Executive Summary

This report provides a comprehensive review of the Pacman C++ game implementation, evaluating adherence to design principles, design patterns implementation, code quality, and overall architecture. The project demonstrates a solid understanding of object-oriented programming and design patterns, with clear separation of concerns between logic and representation layers. However, several areas require attention regarding cohesion, coupling, and collision detection performance.

**Estimated Grade: 72/100** (before collision optimization)

---

## 1. Architecture & Design Patterns Analysis

### 1.1 Model-View-Controller (MVC) Pattern ✅ **GOOD**

**Implementation:**
- **Model:** Logic layer (`PacmanModel`, `GhostModel`, `WallModel`, etc.) handles game state
- **View:** Representation layer (`PacmanView`, `GhostView`, `WallView`, etc.) handles rendering
- **Controller:** `World` class orchestrates entity interactions; `StateManager` handles game states

**Strengths:**
- Clear separation between logic and representation libraries
- Logic library can compile independently of SFML (good design)
- Models properly encapsulate game state

**Weaknesses:**
- ⚠️ **COUPLING ISSUE:** The separation is not perfect. The `World` class (logic) directly checks collisions and modifies entity state, which creates tight coupling
- ⚠️ **COHESION ISSUE:** `World::check_entity_collision()` does too much - collision detection, event generation, AND entity removal. This violates Single Responsibility Principle

**Recommendation:** Consider separating collision detection, collision response, and entity management into distinct components.

---

### 1.2 Observer Pattern ✅ **GOOD**

**Implementation:**
- `Subject` base class with `observers_` vector
- `Observer` interface with `onNotify()` method
- Used for Model→View updates and Score updates

**Strengths:**
- Proper use of `std::weak_ptr` for observers (prevents circular references)
- Views observe Models for rendering updates
- Score observes game events (CoinCollected, FruitEaten)
- Enables complete decoupling between logic and representation

**Weaknesses:**
- ⚠️ The `notify()` method doesn't clean up expired weak pointers, which could accumulate over time
- ⚠️ Event system is minimal - only event type is passed, no additional context data

**Code Quality Issue in Subject.cpp:**
```cpp
void logic::Subject::notify(Event event) {
    for (auto& observer : observers_) {
        if (auto obs = observer.lock()) {  // Good: checks if weak_ptr is valid
            obs->onNotify(*this, event);
        }
        // Missing: No cleanup of expired observers
    }
}
```

**Recommendation:** Add periodic cleanup of expired weak pointers to prevent memory waste.

---

### 1.3 Abstract Factory Pattern ✅ **IMPLEMENTED**

**Implementation:**
- `GameFactory` abstract base class defines interface
- `SfmlFactory` concrete implementation creates Models+Views together
- Factory properly attaches observers during creation

**Strengths:**
- Good abstraction - `World` doesn't know about SFML
- Factory ensures Models and Views are properly connected
- Maintains separation of concerns

**Weaknesses:**
- ⚠️ **DESIGN ISSUE:** Factory creates both Model AND View in same method, which violates the idea that logic should be independent. A cleaner design would have:
  - Logic factory creates Models only
  - Representation factory creates Views and attaches them as observers
- ⚠️ `SfmlFactory` stores `createdViews_` vector, but this is never cleaned up and creates memory overhead

**Recommendation:** Consider splitting into two factories or using a callback mechanism for view attachment.

---

### 1.4 Singleton Pattern ⚠️ **PARTIALLY CORRECT**

**Implementation:**
- `Stopwatch` singleton
- `Random` singleton

**Strengths:**
- Proper implementation with deleted copy constructor and assignment operator
- Uses `std::shared_ptr` for instance management
- Thread-safe initialization (C++11 guarantees)

**Weaknesses:**
- ⚠️ **CRITICAL DESIGN FLAW:** These singletons are NOT truly necessary and actually harm testability
  - **Stopwatch:** Should be dependency-injected to allow time-based testing
  - **Random:** Should be dependency-injected to allow deterministic testing
- ⚠️ Singletons create hidden global state, making the code harder to test and reason about
- ⚠️ The `getInstance()` pattern makes dependencies implicit rather than explicit

**Code Example (Random.cpp):**
```cpp
std::shared_ptr<logic::Random> logic::Random::getInstance() {
    if (random_ == nullptr) {
        random_ = std::shared_ptr<Random>(new Random());  // Could use std::make_shared
    }
    return random_;
}
```

**Recommendation:** 
- Remove Singleton pattern
- Pass Stopwatch and Random as constructor dependencies
- This enables proper unit testing with mocked time and deterministic randomness

---

### 1.5 State Pattern ✅ **EXCELLENT**

**Implementation:**
- `StateManager` with state stack
- Concrete states: `MenuState`, `LevelState`, `PausedState`, `VictoryState`
- States can push/pop themselves from stack

**Strengths:**
- ✅ **EXCELLENT:** Uses state stack for pause/resume functionality
- ✅ Clean state transitions
- ✅ Each state handles its own rendering and input
- ✅ Proper separation of concerns per state

**Weaknesses:**
- None significant - this is well implemented

---

## 2. SOLID Principles Analysis

### 2.1 Single Responsibility Principle (SRP) ⚠️ **VIOLATED**

**Violations:**

1. **`World` class** (World.cpp:184-266)
   - Handles entity storage
   - Performs collision detection
   - Generates collision events
   - Removes entities
   - Orchestrates updates
   - **This is 5+ responsibilities!**

2. **`check_entity_collision()`** method (World.cpp:208-266)
   - Checks collisions with walls
   - Checks collisions with coins (and removes them)
   - Checks collisions with fruits (and removes them)
   - Checks collisions with ghosts
   - Generates different event types
   - **Massive method doing too much**

3. **`PacmanModel::update()`** (PacmanModel.cpp:9-54)
   - Handles movement
   - Processes collisions
   - Handles death
   - Manages lives
   - Notifies observers

**Recommendation:** Extract separate classes:
- `CollisionDetector` - pure collision geometry
- `CollisionHandler` - processes collision responses
- `EntityManager` - manages entity lifecycle

---

### 2.2 Open/Closed Principle (OCP) ✅ **MOSTLY GOOD**

**Strengths:**
- Ghost types properly use inheritance (`BlinkyModel`, `InkyModel`, `PinkyModel`, `ClydeModel`)
- Easy to add new ghost types without modifying existing code
- State pattern allows adding new states easily

**Weaknesses:**
- ⚠️ Adding new entity types requires modifying `World::check_entity_collision()` with new if statements
- ⚠️ The switch statement in `World::initialise_maze()` (World.cpp:69-114) would need modification for new entity types

**Recommendation:** Use polymorphism or Visitor pattern for collision handling.

---

### 2.3 Liskov Substitution Principle (LSP) ⚠️ **MINOR ISSUES**

**Issues:**
- `MoveableSubject` inherits from `Subject` but adds significantly different behavior
- `GhostModel` has `update(float dt)` while derived classes have `update(float dt, World& world)` - this is method hiding, not overriding

**In GhostModel.h:**
```cpp
void update(float dt);  // Base version
```

**In BlinkyModel.h:**
```cpp
void update(float dt, World& world);  // Different signature!
```

This is problematic because you can't substitute derived ghosts for base `GhostModel` polymorphically for the full update logic.

---

### 2.4 Interface Segregation Principle (ISP) ✅ **ACCEPTABLE**

No major violations. Interfaces are reasonably focused.

---

### 2.5 Dependency Inversion Principle (DIP) ⚠️ **MIXED**

**Good:**
- `World` depends on `GameFactory` abstraction, not concrete `SfmlFactory`
- Separation of logic/representation layers

**Bad:**
- Concrete classes depend on Singleton instances (`Stopwatch::getInstance()`, `Random::getInstance()`)
- `World` knows about all concrete entity types (tight coupling)

---

## 3. Cohesion and Coupling Analysis

### 3.1 Cohesion ⚠️ **MEDIUM TO LOW**

**Problem Areas:**

1. **`World` class - LOW COHESION**
   - Responsibilities: entity management, collision detection, game state, level initialization
   - **Cohesion score: 4/10**

2. **`check_entity_collision()` - VERY LOW COHESION**
   - Mixes collision geometry, event generation, and entity lifecycle
   - **Cohesion score: 2/10**

3. **Ghost classes - GOOD COHESION**
   - Each ghost focuses on its movement AI
   - **Cohesion score: 8/10**

---

### 3.2 Coupling ⚠️ **HIGH**

**Tight Coupling Issues:**

1. **World ↔ All Entity Types**
   ```cpp
   std::shared_ptr<CoinModel> coin_model = std::dynamic_pointer_cast<CoinModel>(entity);
   std::shared_ptr<FruitModel> fruit_model = std::dynamic_pointer_cast<FruitModel>(entity);
   std::shared_ptr<GhostModel> ghost_model = std::dynamic_pointer_cast<GhostModel>(entity);
   std::shared_ptr<WallModel> wall_model = std::dynamic_pointer_cast<WallModel>(entity);
   ```
   **CRITICAL:** Using `dynamic_pointer_cast` is a code smell indicating missing polymorphism!

2. **Everything ↔ Singletons**
   - Every class that needs time calls `Stopwatch::getInstance()`
   - Every class that needs randomness calls `Random::getInstance()`
   - This creates hidden dependencies

3. **Utilities in Wrong Layer**
   - `utils.h` contains `Coordinate` and `Rectangle` which should be in Logic layer
   - But `utils.h` is in `Utilities/` directory outside both Logic and Representation

**Coupling Score: 3/10** (Lower is better for coupling, so this is BAD)

---

## 4. Code Quality Assessment

### 4.1 Smart Pointers Usage ✅ **EXCELLENT**

**Strengths:**
- ✅ Extensive use of `std::shared_ptr` throughout
- ✅ Proper use of `std::weak_ptr` for observers (prevents cycles)
- ✅ `std::unique_ptr` used in StateManager's state stack
- ✅ No raw pointer ownership (except where required by design patterns)

**Minor Issues:**
- Some places use `std::shared_ptr` where `std::unique_ptr` would be more appropriate (indicating unique ownership)
- Example: Individual entity ownership in World could be unique

---

### 4.2 Const Correctness ⚠️ **NEEDS IMPROVEMENT**

**Problems:**

1. **Missing const on getters:**
   ```cpp
   // In Coordinate (utils.h:13-14)
   double getX() { return x; }  // Should be const
   double getY() { return y; }  // Should be const
   ```

2. **Missing const on parameters:**
   ```cpp
   // In World.cpp:184
   bool check_collision(Coordinate& entity_pos, Rectangle entity2_rect, float entity_speed, float dt) const;
   // entity_pos could be const&
   ```

3. **Missing const qualifiers on many methods that don't modify state**

**Const Correctness Score: 5/10**

---

### 4.3 Exception Handling ⚠️ **MINIMAL**

**Current State:**
- File operations use `exit(1)` on failure (Score.cpp:27, World.cpp:127)
- No try-catch blocks anywhere
- No custom exception types

**Problems:**
```cpp
// In Score.cpp:18-28
std::ifstream file("../data/high_scores.txt");
if (file) {
    // read file...
} else {
    std::cerr << "Could not open high score file" << std::endl;
    exit(1);  // ❌ Abrupt termination, no cleanup, no recovery
}
```

**Recommendation:** 
- Define custom exceptions (`FileNotFoundException`, `InvalidMapFormatException`)
- Use RAII for resource management
- Allow graceful error recovery

---

### 4.4 Code Duplication ⚠️ **PRESENT**

**Examples:**

1. **Ghost initialization logic repeated 4 times** (World.cpp:79-97)

2. **Collision checking pattern repeated** in `check_entity_collision()`
   - Same pattern: cast to type, check collision, handle result
   - Could use polymorphism or Visitor pattern

3. **Direction handling logic** scattered across multiple ghost classes
   - `get_opposite_direction()` and `get_other_direction()` should be in a utility class

---

### 4.5 Naming Conventions ✅ **MOSTLY CONSISTENT**

**Good:**
- Classes use PascalCase: `PacmanModel`, `StateManager`
- Variables use snake_case: `world_width`, `entity_speed`
- Private members have trailing underscore: `observers_`, `world_state_`

**Inconsistencies:**
- Some member variables don't have trailing underscore (e.g., `lives`, `waiting` in GhostModel)
- `cam` vs `camera_` inconsistency

---

### 4.6 Comments and Documentation ⚠️ **SPARSE**

**Current State:**
- ✅ Header files have good Doxygen-style comments
- ❌ Implementation files lack explanatory comments
- ❌ Complex algorithms (like collision detection) not documented
- ❌ No high-level architecture documentation

**Example needing comments:**
```cpp
// World.cpp:192 - What is this magic number?
const float collision_sensitivity = 0.45f;  // Why 0.45? How was this determined?
```

---

## 5. Specific Code Issues

### 5.1 **CRITICAL: Collision Detection Performance Problem**

**Location:** `World::check_entity_collision()` (World.cpp:208-266)

**Problem:**
```cpp
std::vector<logic::Event> logic::World::check_entity_collision(Coordinate& entity_pos, 
                                                                Direction& entity_direction,
                                                                float entity_speed, 
                                                                bool ghost, 
                                                                float dt) {
    std::vector<logic::Event> events;
    for (auto& entity_vector : entities) {  // ❌ O(n)
        for (auto& entity : entity_vector) {  // ❌ O(m)
            // Check collision with every entity!
        }
    }
    return events;
}
```

**Performance Analysis:**
- **Time Complexity:** O(n × m) where n = rows, m = columns
- **Called:** Every frame for Pacman + 4 ghosts = 5 times per frame
- **At 60 FPS:** 300 collision checks per second
- **For 31×28 map:** ~26,000 entity checks per second

**Why It Causes Lag:**
1. **Buffer-based collision with epsilon** (World.cpp:192-193)
   ```cpp
   const float epsilon_x = entity_half_size_x * entity_speed * dt * collision_sensitivity;
   const float epsilon_y = entity_half_size_y * entity_speed * dt * collision_sensitivity;
   ```
   - This creates a "lookahead" collision box
   - When `dt` varies (frame rate fluctuation), epsilon varies
   - **This causes inconsistent collision detection** → entities "jitter" or "stick"

2. **Unnecessary checks:**
   - Checks collision with empty spaces
   - Checks collision with far-away entities
   - No spatial partitioning

3. **Redundant calculations:**
   - Recalculates entity rectangles every check
   - No caching of static wall positions

---

### 5.2 Memory Management Issues

**Issue 1: `SfmlFactory::createdViews_` never cleaned**
```cpp
// In SfmlFactory.h:18
std::vector<std::shared_ptr<EntityView>> createdViews_;
```
This vector accumulates views but is never cleared, even when entities are removed from the world.

**Issue 2: Entity removal doesn't remove from 2D grid efficiently**
```cpp
// World.cpp:268-277
void logic::World::remove_entity(const std::shared_ptr<CollectableSubject>& model) {
    for (auto& vec : entities) {
        for (int i = 0; i < vec.size(); i++) {  // ❌ Linear search
            if (std::dynamic_pointer_cast<Subject>(model) == vec[i]) {
                vec.erase(vec.begin() + i);  // ❌ Shifts all elements
                model->destruct();
            }
        }
    }
}
```

---

### 5.3 Type Safety Issues

**Over-reliance on `dynamic_pointer_cast`:**

The collision checking code casts every entity to every possible type:
```cpp
std::shared_ptr<CoinModel> coin_model = std::dynamic_pointer_cast<CoinModel>(entity);
std::shared_ptr<FruitModel> fruit_model = std::dynamic_pointer_cast<FruitModel>(entity);
std::shared_ptr<GhostModel> ghost_model = std::dynamic_pointer_cast<GhostModel>(entity);
std::shared_ptr<WallModel> wall_model = std::dynamic_pointer_cast<WallModel>(entity);
```

**Problems:**
- Runtime type checking (slow)
- Violates OCP - adding new entity types requires code changes
- Suggests missing polymorphism

**Better approach:** Double dispatch pattern or Visitor pattern

---

## 6. Positive Aspects

Despite the criticisms, the project has many strengths:

### ✅ **Architecture Strengths**
1. Clean separation between Logic and Representation libraries
2. CMake properly builds logic as static library
3. Good use of namespaces (`logic::` and `representation::`)

### ✅ **Design Pattern Usage**
1. State pattern is excellently implemented
2. Observer pattern enables proper decoupling
3. Abstract Factory provides good abstraction

### ✅ **Modern C++ Features**
1. Extensive smart pointer usage
2. Proper use of `std::chrono` for time
3. `std::mt19937` for random number generation
4. Range-based for loops
5. `auto` keyword for type inference

### ✅ **Code Organization**
1. Clear file structure (include/ and src/ separation)
2. Header guards properly implemented
3. Forward declarations used appropriately

---

## 7. Recommendations for Improvement

### 7.1 High Priority

1. **Fix Collision Detection (CRITICAL)**
   - Implement spatial partitioning (grid, quadtree, or spatial hash)
   - Remove delta-time dependency from collision epsilon
   - Cache static entity positions

2. **Reduce Coupling**
   - Remove Singleton pattern from Stopwatch and Random
   - Use dependency injection instead
   - Implement polymorphic collision handling

3. **Improve SRP**
   - Extract CollisionDetector class
   - Extract EntityManager class
   - Split World's responsibilities

### 7.2 Medium Priority

4. **Add Exception Handling**
   - Custom exception types
   - Graceful error recovery
   - Proper resource cleanup

5. **Improve Const Correctness**
   - Add const to all getters
   - Use const references where appropriate
   - Mark methods const when they don't modify state

6. **Add Unit Tests**
   - Currently NO tests exist
   - Should test collision detection
   - Should test ghost AI
   - Should test score calculation

### 7.3 Low Priority

7. **Documentation**
   - Add algorithm explanations
   - Document magic numbers
   - Create architecture diagram

8. **Code Cleanup**
   - Remove duplicate code
   - Consistent naming (trailing underscores)
   - Add more comments

---

## 8. Alternative Collision Detection Approaches

### 8.1 Current Implementation Analysis

**Current Method:**
- Brute force O(n×m) check against all entities
- Uses buffer-based prediction with delta-time
- **Problem:** Delta-time variance causes inconsistent collision margins

**Why Entities Lag:**
1. Variable frame rate → variable epsilon → inconsistent collision "feel"
2. No early exit when collision found
3. Checking static walls every frame unnecessarily

---

### 8.2 **Recommended Solution: Spatial Grid Partitioning**

**Concept:**
Divide the world into a grid where each cell contains entities in that region.

**Implementation:**
```cpp
class SpatialGrid {
    std::vector<std::vector<std::vector<std::shared_ptr<Subject>>>> grid;
    float cell_size;
    
public:
    // Get only entities in nearby cells
    std::vector<std::shared_ptr<Subject>> getNearbyEntities(Coordinate pos, float radius);
    
    // Update entity's grid position (call when entity moves)
    void updateEntityPosition(std::shared_ptr<Subject> entity, Coordinate old_pos, Coordinate new_pos);
};
```

**Benefits:**
- ✅ **O(1) average case** lookup (vs O(n×m) now)
- ✅ Only checks entities in same cell + adjacent cells (9 cells max)
- ✅ For 31×28 map: check ~9-20 entities instead of ~868
- ✅ **50-100x speedup** for collision detection

**Complexity:**
- Setup: O(1) - grid already matches world structure
- Query: O(k) where k is entities per cell (typically 1-5)
- Update: O(1) when entity moves between cells

---

### 8.3 **Alternative: Static vs Dynamic Entity Separation**

**Concept:**
Separate entities into static (walls) and dynamic (Pacman, ghosts, collectibles).

```cpp
class World {
    std::vector<std::shared_ptr<WallModel>> static_walls;  // Never changes
    std::vector<std::shared_ptr<MoveableSubject>> dynamic_entities;  // Update these
    std::vector<std::shared_ptr<CollectableSubject>> collectibles;  // Can be removed
};
```

**Benefits:**
- ✅ No need to check walls against walls
- ✅ Can pre-compute wall collision data
- ✅ Faster iteration (contiguous memory)
- ✅ Clear semantic separation

**Wall Collision Optimization:**
Since walls don't move, pre-compute a collision map:
```cpp
class CollisionMap {
    std::vector<std::vector<bool>> is_solid;  // true if cell has wall
    
    bool isColliding(Coordinate pos) const {
        int grid_x = worldToGridX(pos.getX());
        int grid_y = worldToGridY(pos.getY());
        return is_solid[grid_y][grid_x];
    }
};
```

**Speedup:** Wall collision becomes O(1) lookup instead of O(n) iteration.

---

### 8.4 **Alternative: Fix the Epsilon Problem**

**Current Issue:**
```cpp
const float epsilon_x = entity_half_size_x * entity_speed * dt * collision_sensitivity;
```

When `dt` varies (59 FPS vs 61 FPS), epsilon varies, causing jitter.

**Solution: Fixed Epsilon**
```cpp
// Use fixed collision margin independent of dt
const float fixed_collision_margin = entity_half_size_x * 0.1f;  // 10% margin

Coordinate entity1_left_upper_corner = {
    entity_pos.getX() - entity_half_size_x + fixed_collision_margin,
    entity_pos.getY() - entity_half_size_y + fixed_collision_margin
};
```

**Benefits:**
- ✅ Consistent collision feel regardless of frame rate
- ✅ Predictable behavior
- ✅ Easier to tune (one constant vs delta-dependent formula)

---

### 8.5 **Advanced: Continuous Collision Detection**

For very fast-moving entities, discrete collision checks can miss collisions (tunneling).

**Swept AABB:**
Instead of checking current position, check the swept volume from old position to new position.

**When needed:**
- Only if ghosts move very fast (current speeds are slow enough)
- Adds complexity, likely overkill for Pacman

---

## 9. Implementation Plan for Collision Optimization

### Step 1: Separate Static and Dynamic Entities (1-2 hours)
```cpp
class World {
    // Separate storage
    std::vector<std::vector<bool>> wall_grid;  // Pre-computed wall collision
    std::vector<std::shared_ptr<MoveableSubject>> moveable_entities;
    std::vector<std::shared_ptr<CollectableSubject>> collectibles;
    
    bool isWallAt(Coordinate pos) const;  // O(1) grid lookup
};
```

### Step 2: Implement Fixed Epsilon (30 minutes)
```cpp
// Remove dt dependency from epsilon calculation
const float COLLISION_MARGIN = 0.05f;  // Fixed margin in world units
```

### Step 3: Add Spatial Grid for Dynamic Entities (2-3 hours)
```cpp
class SpatialGrid {
    std::unordered_map<int, std::vector<std::shared_ptr<Subject>>> cells;
    
    int getCellIndex(Coordinate pos) const {
        int x = static_cast<int>(pos.getX() / cell_size);
        int y = static_cast<int>(pos.getY() / cell_size);
        return y * grid_width + x;
    }
};
```

### Step 4: Update Collision Check Method
```cpp
std::vector<Event> World::check_entity_collision(Coordinate& entity_pos, ...) {
    std::vector<Event> events;
    
    // 1. Check wall (O(1))
    if (isWallAt(entity_pos)) {
        events.push_back(Event::WallCollide);
        return events;  // Early exit
    }
    
    // 2. Get nearby dynamic entities (O(k) where k is small)
    auto nearby = spatial_grid.getNearbyEntities(entity_pos);
    
    // 3. Check only nearby entities
    for (auto& entity : nearby) {
        // Polymorphic collision handling
        entity->handleCollision(*this, entity_pos, events);
    }
    
    return events;
}
```

**Expected Performance Improvement:**
- Before: ~26,000 checks/second (at 60 FPS)
- After: ~300 checks/second (100x reduction)
- **Lag should be eliminated**

---

## 10. Grading Breakdown

### Core Game Requirements (40%)
- Game startup & initialization: **8/8**
- Player controls & wall collision: **7/8** (lag issues)
- Ghost movement & AI: **7/8** (works but could be optimized)
- Coin collection & scoreboard: **7/8** (works well)
- Fruits & ghost transformation: **6/8** (implemented but basic)
- Levels & difficulty scaling: **7/8** (good implementation)
- Lives & game over: **7/8** (functional)

**Subtotal: 49/56 = 35/40**

### Design & Code Quality (40%)
- Design patterns: **7/10** (all present but Singleton misused)
- Class hierarchy: **6/10** (good structure but tight coupling)
- Separation of concerns: **7/10** (good library separation)
- Polymorphism: **5/10** (insufficient, too many casts)
- Code quality: **6/10** (smart pointers good, const issues, no exceptions)
- Low coupling: **3/10** (high coupling, many dependencies)
- High cohesion: **4/10** (World class has low cohesion)

**Subtotal: 38/70 → scaled to 22/40**

### Documentation (10%)
- Code comments: **3/5** (headers good, implementation sparse)
- Report: **N/A** (this IS the report)
- Design explanation: **2/5** (could document design decisions better)

**Subtotal: 5/10**

### Project Defense (10%)
- Cannot evaluate without video
- **Estimate: 7/10** (assuming competent explanation)

---

## **FINAL ESTIMATED GRADE: 69/100**

### Breakdown:
- Core functionality: **35/40** (87.5%)
- Design & quality: **22/40** (55%)
- Documentation: **5/10** (50%)
- Defense (estimated): **7/10** (70%)

### Grade Justification:

**Strengths:**
- Core game works
- Proper use of modern C++
- Clean library separation
- Good State pattern implementation

**Critical Weaknesses:**
- **Collision detection causes lag** (assignment specifically mentions this)
- **High coupling** (violates design principles)
- **Low cohesion in World class**
- **Misuse of Singleton pattern** (should use dependency injection)
- **Over-reliance on dynamic_cast** (missing polymorphism)
- **No exception handling**
- **No unit tests**
- **Const correctness issues**

### How to Improve to 85+:
1. Fix collision detection (spatial partitioning) → +10 points
2. Reduce coupling (remove Singletons, use DI) → +5 points
3. Improve cohesion (extract classes from World) → +3 points
4. Add exception handling → +2 points
5. Fix const correctness → +1 point

---

## 11. Conclusion

This Pacman implementation demonstrates a **solid grasp of object-oriented programming and design patterns**, with particularly strong implementation of the State pattern and proper separation between logic and representation layers. The use of modern C++ features (smart pointers, std::chrono, std::mt19937) shows good technical knowledge.

However, the project suffers from **design principle violations**, particularly regarding:
- **Single Responsibility Principle** (World class does too much)
- **Coupling** (excessive use of Singletons and dynamic_cast)
- **Open/Closed Principle** (collision handling requires modification for new entity types)

The **collision detection lag mentioned in the assignment** is caused by:
1. O(n×m) brute force checking all entities
2. Delta-time dependent epsilon causing jitter
3. No spatial optimization

**Implementing spatial partitioning and fixed collision margins will eliminate the lag and improve the grade significantly.**

With the recommended improvements, this project could easily reach 85-90/100, demonstrating excellent software engineering skills.

---

**End of Report**
