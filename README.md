# Crossword Puzzle Solver (C++)

A constraint-based crossword puzzle generator and solver built in C++.  
This project uses **backtracking (DFS recursion)** to place words into a 10×10 grid while respecting crossword rules.

---

##  Project Overview

This program simulates a crossword construction system that:

- Loads words from a dictionary file (`The Oxford 5000.txt`)
- Places a starting word manually
- Automatically tries to fit additional words into the grid
- Uses **backtracking recursion** to explore valid configurations
- Ensures crossword constraints are respected (no invalid overlaps or adjacency violations)

---

##  Features

###  Core Functionality
- 10×10 crossword grid system
- Manual first word placement (user-defined position + direction)
- Automatic word placement using dictionary
- Backtracking algorithm for solving

###  Constraint System
- Valid word fitting (bounds checking)
- Overlap validation (shared letters must match)
- Adjacency rules (no invalid touching words)
- Duplicate word prevention

###  Algorithm
- Depth-First Search (DFS)
- Recursive backtracking
- State undo (removeWord on failure)

###  Grid Tracking
- Character grid (`grid`)
- Occupancy counter (`gridCount`)
- Placement history (`wordsHist`)

---

##  How It Works

1. User enters the first word and its position
2. Word is placed on the grid
3. Program reads dictionary words
4. For each word:
   - Check if it is safe to place
   - Place it on grid
   - Recursively try to continue solving
   - If failed → backtrack (remove word)
5. Stops when a valid configuration is found

---

##  Algorithm Type

> Depth-First Search (DFS) with Backtracking

This is a classic constraint satisfaction approach used in:
- Puzzle solving
- AI search problems
- Game logic systems

---

##  Tech Stack

- C++
- STL (`vector`, `array`, `fstream`)
- File I/O (dictionary input)
- Recursive algorithms

---

