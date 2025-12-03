# Bug Summary - Quick Reference

## Critical Bugs Found

### 🔴 Bug 1: Ghosts Randomly Spawn to Start-Location
**File:** `Logic/src/Subject.cpp`  
**Line:** 74-76  
**Severity:** CRITICAL

**Problem:**
```cpp
void logic::Subject::go_to_center() {
    set_position(starting_position_);
}
```
The `starting_position_` is set implicitly during the first `set_position()` call, which may happen at the wrong time during initialization.

**Fix:**
Explicitly set `starting_position_` in entity constructors or during World initialization.

---

### 🔴 Bug 2: Pacman Gets Slow When Turning Near Walls
**File:** `Logic/src/PacmanModel.cpp`  
**Line:** 20  
**Severity:** HIGH

**Problem:**
```cpp
if (!world.check_wall_collision(next_pos_if_turned, wanted_direction, speed_, false, dt)) {
    set_position(next_pos_if_turned);
    set_direction(wanted_direction);
    return; // ← BUG: Returns here without moving in current direction!
}
```

When Pacman tries to turn but hits a wall, the function returns early WITHOUT continuing movement in the current direction. This creates the "glue" effect.

**Fix:**
```cpp
if (!world.check_wall_collision(next_pos_if_turned, wanted_direction, speed_, false, dt)) {
    set_position(next_pos_if_turned);
    set_direction(wanted_direction);
    // Don't return here - fall through to continue current movement
}
```

---

### 🟡 Bug 3: Score Doesn't Get Displayed
**File:** `Representation/src/LevelState.cpp`  
**Line:** 43  
**Severity:** MEDIUM

**Problem:**
```cpp
levelTitle_.setFont(font_);
levelTitle_.setFillColor(sf::Color::Yellow);
livesTitle_.setString("Level: " + std::to_string((world_.get_level())));  // ← Wrong variable!
```

Copy-paste error - should be `levelTitle_.setString(...)` not `livesTitle_.setString(...)`

**Fix:**
```cpp
levelTitle_.setString("Level: " + std::to_string((world_.get_level())));
```

---

### 🟡 Bug 4: Inky Sometimes Turns Around
**File:** `Logic/src/InkyModel.cpp`  
**Lines:** 33-40  
**Severity:** MEDIUM

**Problem:**
```cpp
// If inky just came out frightened mode, turn around
if (!chasing_mode && !was_frightened_) {  // ← Confusing logic
    was_frightened_ = true;
    Direction reversed = get_opposite_direction(current_direction);
    Coordinate final_pos = calculate_new_position(dt, reversed, current_location);
    return {reversed, final_pos};
}
```

The condition and variable naming are confusing. This is meant to detect entering fear mode but the logic is unclear.

**Fix:**
Refactor to use explicit state transition events or clearer naming.

---

## Additional Bugs Found

### 🔴 Bug 5: Ghost Speed Uses Wrong Fraction
**File:** `Logic/src/World.cpp`  
**Lines:** 170-173  
**Severity:** CRITICAL

**Problem:**
```cpp
inky->set_speed(basic_ghost_speed*pacman_speed_fraction_);   // ← Should be ghost_speed_fraction_!
blinky->set_speed(basic_ghost_speed*pacman_speed_fraction_);
pinky->set_speed(basic_ghost_speed*pacman_speed_fraction_);
clyde->set_speed(basic_ghost_speed*pacman_speed_fraction_);
```

**Fix:**
```cpp
inky->set_speed(basic_ghost_speed*ghost_speed_fraction_);
blinky->set_speed(basic_ghost_speed*ghost_speed_fraction_);
pinky->set_speed(basic_ghost_speed*ghost_speed_fraction_);
clyde->set_speed(basic_ghost_speed*ghost_speed_fraction_);
```

---

### 🔴 Bug 6: Missing Break Statement
**File:** `Logic/src/World.cpp`  
**Line:** 149  
**Severity:** CRITICAL

**Problem:**
```cpp
case 4: {
    frightened_mode_duration_ = 3000;
    ghost_speed_fraction_ = 0.8f;
    pacman_speed_fraction_ = 0.8f;
}  // ← MISSING break; Falls through to case 5!
case 5: {
    frightened_mode_duration_ = 2000;
    ghost_speed_fraction_ = 0.9f;
    pacman_speed_fraction_ = 0.9f;
    break;
}
```

**Fix:**
Add `break;` after the case 4 block.

---

### 🔴 Bug 7: Fear Mode Pathfinding Broken
**File:** `Logic/src/Type2Ghost.cpp`  
**Line:** 122  
**Severity:** CRITICAL

**Problem:**
```cpp
else {
    // maximize the manhatten value
    best_manhattan = std::numeric_limits<double>::min(); // ← BUG: Inside loop!
    if (mnhtn_distance > best_manhattan) {
```

`best_manhattan` is reset inside the for loop instead of before it, breaking the maximization logic.

**Fix:**
Move the initialization outside the loop (it's already done correctly on line 92, so just remove line 122).

---

## Summary

**Total Bugs Found:** 7  
**Critical:** 5  
**High:** 1  
**Medium:** 1  

**Quick Fixes (< 5 minutes):**
- Bug 3: Change variable name (1 line)
- Bug 5: Change variable names (4 lines)
- Bug 6: Add break statement (1 line)
- Bug 7: Remove one line

**Medium Fixes (< 30 minutes):**
- Bug 2: Remove early return (1 line, but needs testing)

**Complex Fixes (> 30 minutes):**
- Bug 1: Refactor initialization logic
- Bug 4: Refactor state transition logic

**Estimated Total Fix Time:** 2-4 hours
