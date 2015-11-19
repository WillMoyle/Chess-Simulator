//  C++ Programming Lab 3 - Chess
//
//  Author: Will Moyle
//  Last Updated: 09/12/2014

//  CHESS BOARD HEADER FILE

#ifndef ChessBoard_hpp
#define ChessBoard_hpp

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <utility>
#include "Pieces.hpp"

// -----------------------------------------------------------------------------
// FORWARD DECLARE CLASSES:
class Piece;
class Rook;
class Bishop;
class Knight;
class Queen;
class King;
class Pawn;


// -----------------------------------------------------------------------------
// TYPE DEFINITIONS:
typedef map<string, Piece*> Board;
typedef list<Piece *> PieceList;
typedef PieceList::iterator PieceIterator;


// -----------------------------------------------------------------------------
// DECLARATION OF CLASS ChessBoard
class ChessBoard {
private:
  Board board;
  Rook *wr1, *wr2, *br1, *br2;
  Bishop *wb1, *wb2, *bb1, *bb2;
  Knight *wk1, *wk2, *bk1, *bk2;
  Queen *wq, *bq;
  King *wk, *bk;
  Pawn *wp1, *wp2, *wp3, *wp4, *wp5, *wp6, *wp7, *wp8;
  Pawn *bp1, *bp2, *bp3, *bp4, *bp5, *bp6, *bp7, *bp8;
    
  PieceList activePieces;
  bool whiteTurn;
  bool gameActive;

  /* Parameters: None
     Post conditions: - 'whiteTurn' is set to true as white goes first
                      - 'gameActive' is set to true
                      - Creates 32 new Pieces on the heap, corresponding to 
		        the 32 pointer attributes, with appropriate conditions
		      - Prints out introduction message
     Returns: None */
  void startBoard();

  /* Parameters: None
     Post conditions: deletes all 32 Pieces from the heap
     Returns: None */
  void clearBoard();

  /* Parameters: a string 'target'
     Post conditions: None 
     Returns: the function returns the Piece pointer mapped to the string 'key'
              in the map 'board'. If there is no Piece is 'target' position,
              function returns NULL pointer */
  Piece* giveBoard(string key);

  /* Parameters: a string 'target' and a pointer to a Piece 'piece'.
     Post conditions: in the map 'board', creates a key 'target' and a mapped
                      value, 'piece'
     Returns: None */
  void setBoard(string key, Piece* piece);

  /* Parameters: a pointer to a Piece 'piece'
     Post conditions: 'piece' added to the back of the list 'activePieces'
     Returns: None */
  void addActivePiece(Piece* piece);

  /* Parameters: a pointer to a Piece 'piece'
     Post conditions: Removes the first occurence of 'piece' from 'activePieces'
     Returns: None */
  void removeActivePiece(Piece* piece);
  
  /* Parameters: a pointer to a Piece 'mover'
     Post conditions: None
     Returns: true if mover->isWhite matches 'whiteTurn', else returns false */
  bool checkTurn(Piece* mover);
  
  /* Parameters: boolean 'isWhiteTurn'
     Post conditions: None
     Returns: true if there exists a Piece in 'activePieces' that has 'isWhite'
              opposite to 'isWhiteTurn' and for which there is a valid move
              from the Piece to the opposition's King, else returns false */
  bool checkCheck(bool isWhiteTurn);
    
  /* Parameters: None
     Post conditions: None
     Returns: false if there exists a valid move for any piece that doesn't
              result in checkCheck() returning true, else returns true */
  bool checkCheckmate();

public:    
  
  /* CONSTRUCTOR
     Parameters: None
     Post conditions: runs startBoard() member function
     Returns: None */
  ChessBoard();
    
  /* DESTRUCTOR
     Parameters: None
     Post conditions: runs clearBoard() member function
     Returns: None */
  ~ChessBoard();

  /* Parameters: None
     Post conditions: runs clearBoard() followed by startBoard() member functions
     Returns: None */
  void resetBoard();

  /* Parameters: None
     Post conditions: moves a Piece from coordinates 'start' to 'end' if such a
                      move is valid. Also runs functions checking for Check,
		      CheckMate and StaleMate and prints out corresponding
		      messages
     Returns: None */
  void submitMove(string start, string end);
       
  /* HELPER FUNCTION
     Parameters: None
     Post conditions: Prints out a representation of the 'board' attribute
                      to the screen
     Returns: None */
  void printBoard();
  
  friend class Piece;
};

#endif
