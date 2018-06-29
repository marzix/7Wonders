# 7Wonders
2-player game based on the "7 Wonders: Duel" board game: http://www.7wondersduel.com/7wonders-duel.php?lang=en
Developed as a colledge project in a group of 3.
Developing years: 2016

INTRODUCTION

The main purpose of this program was to familiarize ourselves with a neural network library of our choosing.
The program is a simplified version of the "7 Wonders" game, containing an NPC whose decisions are made with a use
of the developed neural network.

IMPLEMENTATION

The game has been developed in C++ programming language with a use of Fast Artificial Neural Network Library (FANN).
The library can be used with C, C++, PHP, Python and Delphi language, as well as Matematica environment.
The implemented neural network has 6 data inputs (era number and 5 floating point numbers reprezenting cards).
The network produces 5 outputs (four zeros and a 1 number indicating which card has been picked from the deck).
The file AIWonder.data contains an input data sets and expected outputs for the neural network training.
The AIWonder.net is a file generated based on the training stage and it contains the trained neural network.
The game can be in 3 modes: Human vs Human, Human vs AI, AI vs AI.

EXTERNAL SPECIFICATION

The game is designed for playing in the Terminal and only for the Windows platform. 
Start the game from the Terminal, providing two arguments defining the type of players:
  h - human player
  a - AI player
Example:
  7Wonders.exe h a
  
GAME RULES

The game is divided to 3 eras in which players buy buildings that enable them to develop one of 7 wolrd wonders.
The purpose of the game is to collect the highest number of points from following sources: military victories, 
owned coins, the level of our world wonder advancement, civil buildings development, comercial buildings developement,
guild cards and science buildings development.

The game is a turn-based match. In each turn a player has to choose one of 5 available cards to buy or sell. 
The human-player interface contains the following information:
  - era number
  - number of owned coins
  - a list of owned cards
  - an information to choose a new card
  - a list of available cards to choose from in this round
  
 After choosing the number of a card which we want to buy/sell we receive an information about if the card has been added
 to our deck or sold for coins (if we can't afford buying it). The last information given in our round is about
 the number of point that we currently have (calculated based on the points assigned to each card we owned + number of coins
 divided by 3). 
 
 At the end of each era the players enter a battle and based on the military points they own (points from military cards)
 they receive points for the battle. The game ends at the end of the 3 era, where the information about the winning
 player is prompted to the screen.
