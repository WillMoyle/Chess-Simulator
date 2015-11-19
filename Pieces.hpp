//  C++ Programming Lab 3 - Chess
//
//  Author: Will Moyle
//  Last Updated: 09/12/2014

//  PIECES HEADER FILE

#ifndef Pieces_hpp
#define Pieces_hpp

using namespace std;

// -----------------------------------------------------------------------------
// FORWARD DECLARE CLASSES:
class ChessBoard;


// -----------------------------------------------------------------------------
// TYPE DEFINITIONS:
typedef list<pair<int, int> > MovesList;
typedef MovesList::iterator MovesIterator;


// -----------------------------------------------------------------------------
// ERROR CONSTANTS
const static int VALID_MOVE = 0;
const static int INVALID_COORDS = 1;
const static int ILLEGAL_MOVE = 2;
const static int BLOCKED_MOVE = 3;
const static int SELF_TAKING = 4;


// -----------------------------------------------------------------------------
// DECLARATION OF CLASS Piece
class Piece {
private:
  string name;
  bool inPlay;
  string position;
    
protected:
  bool isWhite;
  string symbol;
  MovesList moves;
  ChessBoard* game;

  /* Parameters: None
     Post conditions: Virtual function. For subclasses, the attribute 'moves' 
                      now contains a list of integer pairs, each of which is a 
		      possible move for this Piece. This list does not take into
		      account the Piece's current position on the board (i.e. 
		      some moves may go over the board's edge
     Returns: None */
  virtual void setMoves() {return;};
  
  /* Parameters: None
     Post conditions: None
     Returns: the attribute 'position' as a string */
  string givePosition();
  
  /* Parameters: a string 'target'
     Post conditions: if 'target' is a valid two character coordinate, function
                      sets parameter 'position' to 'target', else the function
		      does nothing.
     Returns: None */
  void setPosition(string target);
  
  /* Parameters: None
     Post conditions: None
     Returns: the attribute 'symbol' as a string */
  string giveSymbol();

  /* Parameters: None
     Post conditions: None
     Returns: the attribute 'name' as a string */    
  string giveName();

  /* Parameters: None
     Post conditions: None
     Returns: the attribute 'inPlay' as a string */    
  bool giveInPlay();

  /* Parameters: a boolean 'newState'
     Post conditions: parameter 'inPlay' now has value 'newState'
     Returns: None */    
  void setInPlay(bool newState);

  /* Parameters: None
     Post conditions: None
     Returns: the attribute 'isWhite' as a boolean */     
  bool giveColour();

  /* Parameters: None
     Post conditions: None
     Returns: the attribute 'moves' as a list of integer pairs */ 
  MovesList giveMoves();

  /* Parameters: a string 'target'
     Post conditions: None
     Returns: a predefined static integer named:
              VALID_MOVE  - this Piece is able to move to the position given by 
              coordinates 'target' given the current state of the board.
	      INVALID_COORDS - coordinates 'target' are not on the board
	      ILLEGAL_MOVE - movement from 'position' to 'target' is not 'moves'
	      BLOCKED_MOVE - movement from 'position' to 'target' is blocked
	      SELF_TAKING - 'target' contains another of the mover's pieces */ 
  int validMove(string target);

  /* Parameters: a string 'target'
     Post conditions: None
     Returns: true if 'target' is a two character string of the form XY
              with X between 'A' and 'H' and Y between '1' and '8', 
	      else false */ 
  bool validCoords(string target);

  /* Parameters: None
     Post conditions: None
     Returns: true if there exists a valid move for this piece from 
              'position' to the opponent's King, else false */ 
  bool targetingKing();

  /* Parameters: a string 'target'
     Post conditions: None
     Returns: true if a move this piece from 'position' to 'target' 
              would place the opponent in check */ 
  bool selfCheckingMove(string target);
    
public:
  /* CONSTRUCTOR
     Parameters: strings 'title' and 'target', boolean 'white' and a pointer to
                 a ChessBoard object 'play'
     Post conditions: This Piece's attributes are set (name-title, isWhite-white,
                      position-target, game-play)
                      Assigns a pointer to this Piece to 'games' board Map under
                      key position.
                      Adds pointer to this Piece to 'games' list of active pieces
                      Runs this->setMoves()
     Returns: None */
  Piece(string title, bool white, string target, ChessBoard* play);

  /* DESTRUCTOR
     Parameters: none
     Post conditions: removes the pointer to this Piece from 'games' list of
                      active pieces
     Returns: none */
  virtual ~Piece();

  friend class ChessBoard;
};

// -----------------------------------------------------------------------------
// DECLARATION OF SUBCLASSES OF Piece


class Rook: public Piece {

  /* Parameters: none
     Post conditions: Attribute 'moves' now contains a list of integer pairs
                      representing all of the possible moves for a Rook to make
     Returns: none */
  void setMoves();

public:
  Rook(string title, bool white, string target, ChessBoard* play);
};


class Bishop: public Piece {

  /* Parameters: none
     Post conditions: Attribute 'moves' now contains a list of integer pairs
                      representing all of the possible moves for a Bishop to 
		      make
     Returns: none */
  void setMoves();

public:
  Bishop(string title, bool white, string target, ChessBoard* play);
};


class Knight: public Piece {
  /* Parameters: none
     Post conditions: Attribute 'moves' now contains a list of integer pairs
                      representing all of the possible moves for a Knight to 
		      make
     Returns: none */
  void setMoves();
public:
  Knight(string title, bool white, string target, ChessBoard* play);
};


class Queen: public Piece {

  /* Parameters: none
     Post conditions: Attribute 'moves' now contains a list of integer pairs
                      representing all of the possible moves for a Queen to 
		      make
     Returns: none */
  void setMoves();

public:
  Queen(string title, bool white, string target, ChessBoard* play);
};


class King: public Piece {

  /* Parameters: none
     Post conditions: Attribute 'moves' now contains a list of integer pairs
                      representing all of the possible moves for a King to 
		      make
     Returns: none */
  void setMoves();

public:
  King(string title, bool white, string target, ChessBoard* play);
};


class Pawn: public Piece {

  /* Parameters: none
     Post conditions: Attribute 'moves' now contains a list of integer pairs
                      representing all of the possible moves for a King to 
		      make
     Returns: none */
  void setMoves();

public:
  Pawn(string title, bool white, string target, ChessBoard* play);
};


#endif
