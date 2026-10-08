# UNO Game in C++

A simple command-line implementation of the UNO card game written in C++.

The project was built primarily to practice **Object-Oriented Programming, STL containers, inheritance, dynamic memory, and basic game logic** in C++.

## Features

- Play UNO against a computer-controlled opponent
- Standard UNO deck with:
  - Number cards
  - Skip cards
  - Reverse cards
  - +2 cards
  - Wild cards
  - Wild +4 cards
- Randomized deck using `std::shuffle`
- Colored terminal output using ANSI escape codes
- Basic bot decision-making
- Automatic deck recycling when the draw pile becomes empty
- Player card validation
- Wild card color selection
- Basic handling of action cards

## How It Works

The game starts with two players:

- **You**
- **Computer (Bot)**

Both players receive 7 cards. One card is then placed on the discard pile.

On your turn, you can:

1. Play a valid card.
2. Draw a card if you have no playable card.
3. Choose whether to play the drawn card if it is valid.
4. Select a color when playing a Wild card.

The bot uses a simple strategy to decide which card to play.

The game continues until one player reaches the winning condition.

## Classes

### `Card`

The base class for all cards.

Stores the card's:

- Color
- Symbol

It also provides functions for displaying and accessing card information.

### `NumberCard`

Represents UNO number cards.

### `ActionCard`

Represents:

- Skip
- Reverse
- +2

### `WildCard`

Represents:

- Wild
- Wild +4

It also handles the special behavior of wild cards and changing their active color.

### `Deck`

Responsible for:

- Creating the UNO deck
- Shuffling cards
- Drawing cards
- Adding cards back to the deck
- Tracking the number of remaining cards

### `Person`

Represents a player's hand.

Responsible for:

- Adding cards
- Playing cards
- Checking whether a card is playable
- Checking whether the player has playable cards
- Displaying the player's cards

## Concepts Used

This project uses several C++ concepts, including:

- Classes and objects
- Inheritance
- Polymorphism
- Virtual functions
- Constructors and destructors
- Encapsulation
- `std::vector`
- Pointers
- Dynamic memory allocation
- Iterators
- `std::shuffle`
- Random number generation
- Basic game-state management

## Requirements

- C++ compiler supporting C++11 or later
- Terminal with ANSI escape code support

## Running the Game

Clone the repository:

```bash
git clone <repository-url>
cd <repository-folder>
```

Compile the program:

```bash
g++ -std=c++11 main.cpp -o uno
```

Run the game:

```bash
./uno
```

## Project Structure

The current version is implemented as a single C++ source file:

```text
.
├── main.cpp
└── README.md
```

## Notes

This is a **small learning project** rather than a complete implementation of every official UNO rule.

The main purpose of the project was to practice implementing a playable C++ program using object-oriented programming, STL containers, inheritance, pointers, and basic game logic.

The bot uses a simple decision-making strategy and is not intended to be an advanced UNO AI.

## Possible Improvements

- Split classes into separate `.h` and `.cpp` files
- Improve the bot's strategy
- Add support for multiple human players
- Improve input validation
- Implement more complete UNO rules
- Improve terminal UI
- Replace raw pointers with smart pointers
- Add automated tests
- Improve memory management