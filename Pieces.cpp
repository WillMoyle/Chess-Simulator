//  C++ Programming Lab 3 - Chess
//
//  Author: Will Moyle
//  Last Updated: 09/12/2014

//  PIECES FUNCTION DEFINITION FILE

#include "ChessBoard.hpp"
#include <cmath>


// -----------------------------------------------------------------------------
// PIECE FUNCTIONS


// START OF PIECE CONSTRUCTOR
Piece::Piece(string title, bool white, string target, ChessBoard* play) :
  name(title), position(target), isWhite(white), game(play)
{
  game->setBoard(position, this);
  game->addActivePiece(this);
  
  // run setMoves() function to assign appropriate moves to Piece
  setMoves();
}
// END OF CONSTRUCTOR


// START OF PIECE DESTRUCTOR
Piece::~Piece()
{
  game->removeActivePiece(this);
}
// END OF DESTRUCTOR


// START OF FUNCTION givePosition
string Piece::givePosition()
{
  return position;
}
// END OF FUNCTION


// START OF FUNCTION setPosition
void Piece::setPosition(string target)
{
  if (validCoords(target))
    position = target;
}
// END OF FUNCTION


// START OF FUNCTION giveSymbol
string Piece::giveSymbol()
{
  return symbol;
}
// END OF FUNCTION


// START OF FUNCTION giveName
string Piece::giveName()
{
  return name;
}
// END OF FUNCTION


// START OF FUNCTION giveInPlay
bool Piece::giveInPlay()
{
  return inPlay;
}
// END OF FUNCTION


// START OF FUNCTION setInPlay
void Piece::setInPlay(bool newState)
{
  inPlay = newState;
}
// END OF FUNCTION


// START OF FUNCTION giveColour
bool Piece::giveColour()
{
  return isWhite;
}
// END OF FUNCTION

// START OF FUNCTION giveMoves
MovesList Piece::giveMoves()
{
  return moves;
}
// END OF FUNCTION


// START OF FUNCTION validMove
int Piece::validMove(string target) {
    
  int i, k, isX, moveX, moveY;
  pair<int, int> movement;
  string tempCoords;
  Piece* tempPtr;
    
  moveX = target[0] - position[0];
  moveY = target[1] - position[1];
  movement = make_pair(moveX, moveY);

  // Check that the target coordinates are on the board
  if (!validCoords(target)) {
    return INVALID_COORDS;
  }
    
  // Check that piece can perform the required move  
  bool inMovesList(false);
  for (MovesIterator it = moves.begin(); it != moves.end(); it++)
    {
      if (*it == movement) {inMovesList = true;}
    }
    
  if (!inMovesList) {
    return ILLEGAL_MOVE;
  }
    
  tempCoords.assign(position);

  // Special case for moving pawns
  if (symbol[1] == 'P')
    {
      // Pawn trying to move two spaces after its first move
      if (game->giveBoard(target) == NULL)
	{
	  if ((moveX != 0 && moveY != 0)
	      || (abs(moveY) == 2 
		  && position[1] != '2' 
		  && position[1] != '7'))
	      return ILLEGAL_MOVE;
	}
      // Pawn trying to take a piece in front
      else
	{
	  if (moveX == 0)
	    return BLOCKED_MOVE;
	}
    }
  
  // Check vertical & horizontal movements for blocking pieces
  if (moveX == 0 || moveY == 0)
    {
      if (moveX != 0)
        {
	  k = moveX;
	  isX = 0;
        }
      else
        {
	  k = moveY;
	  isX = 1;
        }

      for (i = 1; i < abs(k); i++)
        {
	  tempCoords[isX] += k/abs(k);
	  tempPtr = game->giveBoard(tempCoords);
	  if (tempPtr != NULL)
            {
	      return BLOCKED_MOVE;
            }
        }
        
    }
  
  // Check diagonal movements for blocking pieces
  else if (abs(moveX) == abs(moveY))
    {
      for (i = 1; i < abs(moveX); i++)
        {
	  tempCoords[0] += moveX/abs(moveX);
	  tempCoords[1] += moveY/abs(moveY);
	  if (game->giveBoard(tempCoords) != NULL 
	      && (tempCoords.compare(target) != 0))
	    {
	      return BLOCKED_MOVE;
	    }
	}
    }

  // Check if the target position contains a piece from the mover's team
  tempPtr = game->giveBoard(target);

  if (tempPtr != NULL)
    {
      if (tempPtr->giveColour() == isWhite)
	{
	  return SELF_TAKING;
	}
    }
    
  return VALID_MOVE;
}
// END OF FUNCTION


// START OF FUNCTION validCoords
bool Piece::validCoords(string target)
{
  /* check if target has 2 characters and represents valid
     coordinates between A1 and H8 */

  if (target.length() == 2 && target[0] >= 'A' && target[0] <= 'H'
      && target[1] >= '1' && target[1] <= '8')
    return true;
  else
    return false;
}
// END OF FUNCTION


// START OF FUNCTION targetingKing
bool Piece::targetingKing()
{
  MovesIterator it;
  string tempTarget;
  Piece * tempPtr;

  // check every possible move for this Piece
  for (it = moves.begin(); it != moves.end(); it++)
    {
      tempTarget.assign(position);
      tempTarget[0] += (*it).first;
      tempTarget[1] += (*it).second;

      tempPtr = game->giveBoard(tempTarget);

      /* return true if there is a valid move from the piece to the 
	 opponents King */
      if (tempPtr != NULL 
	  && tempPtr->giveSymbol()[1] == 'K'
	  && tempPtr->giveColour() != isWhite
	  && validMove(tempTarget) == VALID_MOVE)
	{
	  return true;
	}
    }

  return false;
}
// END OF FUNCTION


// START OF FUNCTION selfCheckingMove
bool Piece::selfCheckingMove(string target)
{
  Piece* tempPtr;
  bool selfCheck;
  string startPosition;

  // see if the move to 'target' would take an opponent's piece
  tempPtr = game->giveBoard(target);
  
  if (tempPtr != NULL)
    {
      // temporarily remove the piece at 'target'
      tempPtr->setPosition("A0");
      game->removeActivePiece(tempPtr);
    }

  startPosition.assign(position);

  // temporarily move this piece to 'target'
  setPosition(target);  
  game->setBoard(target, this);
  game->setBoard(startPosition, NULL);

  // see if this piece's team is now in check
  selfCheck = game->checkCheck(!isWhite);

  // move this piece back to its original position
  setPosition(startPosition);
  game->setBoard(target, tempPtr);
  game->setBoard(startPosition, this);
  
  if (tempPtr != NULL)
    {
      // if necessary return the opponent's piece to 'target'
      tempPtr->setPosition(target);
      game->addActivePiece(tempPtr);
    }

  return selfCheck;
}
// END OF FUNCTION


// -----------------------------------------------------------------------------
// FUNCTIONS FOR PIECE SUBCLASSES


// ROOK CONSTRUCTOR
Rook::Rook(string title, bool white, string target, ChessBoard* play)
  : Piece(title, white, target, play) {setMoves();}


// BISHOP CONSTRUCTOR
Bishop::Bishop(string title, bool white, string target, ChessBoard* play)
  : Piece(title, white, target, play) {setMoves();}


// KNIGHT CONSTRUCTOR
Knight::Knight(string title, bool white, string target, ChessBoard* play)
  : Piece(title, white, target, play) {setMoves();}


// QUEEN CONSTRUCTOR
Queen::Queen(string title, bool white, string target, ChessBoard* play)
  : Piece(title, white, target, play) {setMoves();}


// KING CONSTRUCTOR
King::King(string title, bool white, string target, ChessBoard* play)
  : Piece(title, white, target, play) {setMoves();}


// PAWN CONSTRUCTOR
Pawn::Pawn(string title, bool white, string target, ChessBoard* play)
  : Piece(title, white, target, play) {setMoves();}


// START OF FUNCTION Rook::setMoves
void Rook::setMoves()
{
  for(int i = 1; i <= 7; i++)
    {
      moves.push_back(make_pair(i,0));
      moves.push_back(make_pair(-i,0));
      moves.push_back(make_pair(0,i));
      moves.push_back(make_pair(0,-i));
    }
  if (isWhite)
    symbol = "WR";
  else
    symbol = "BR";
}
// END OF FUNCTION


// START OF FUNCTION Bishop::setMoves
void Bishop::setMoves()
{
  for(int i = 1; i <= 7; i++)
    {
      moves.push_back(make_pair(i,i));
      moves.push_back(make_pair(-i,i));
      moves.push_back(make_pair(i,-i));
      moves.push_back(make_pair(-i,-i));
    }
  if (isWhite)
    symbol = "WB";
  else
    symbol = "BB";
}
// END OF FUNCTION

// START OF FUNCTION Knight::setMoves
void Knight::setMoves()
{
  moves.push_back(make_pair(1,2));
  moves.push_back(make_pair(1,-2));
  moves.push_back(make_pair(-1,2));
  moves.push_back(make_pair(-1,-2));
  moves.push_back(make_pair(2,1));
  moves.push_back(make_pair(2,-1));
  moves.push_back(make_pair(-2,1));
  moves.push_back(make_pair(-2,-1));
  if (isWhite)
    symbol = "Wk";
  else
    symbol = "Bk";
}
// END OF FUNCTION


// START OF FUNCTION Queen::setMoves
void Queen::setMoves()
{
  for(int i = 1; i <= 7; i++)
    {
      moves.push_back(make_pair(i,i));
      moves.push_back(make_pair(-i,i));
      moves.push_back(make_pair(i,-i));
      moves.push_back(make_pair(-i,-i));
      moves.push_back(make_pair(i,0));
      moves.push_back(make_pair(-i,0));
      moves.push_back(make_pair(0,i));
      moves.push_back(make_pair(0,-i));
    }
  if (isWhite)
    symbol = "WQ";
  else
    symbol = "BQ";
}
// END OF FUNCTION


// START OF FUNCTION King::setMoves
void King::setMoves()
{
  moves.push_back(make_pair(1,0));
  moves.push_back(make_pair(1,1));
  moves.push_back(make_pair(0,1));
  moves.push_back(make_pair(-1,1));
  moves.push_back(make_pair(-1,0));
  moves.push_back(make_pair(-1,-1));
  moves.push_back(make_pair(0,-1));
  moves.push_back(make_pair(1,-1));
    
  if (isWhite)
    symbol = "WK";
  else
    symbol = "BK";
}
// END OF FUNCTION


// START OF FUNCTION Pawn::setMoves
void Pawn::setMoves()
{
  int i(1);
    
  if(!isWhite)
    {
      i = -1;
    }
    
  moves.push_back(make_pair(0,i));
  moves.push_back(make_pair(0,2*i));
  moves.push_back(make_pair(1,i));
  moves.push_back(make_pair(-1,i));
    
  if (isWhite)
    symbol = "WP";
  else
    symbol = "BP";
}
// END OF FUNCTION
