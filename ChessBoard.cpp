//  C++ Programming Lab 3 - Chess
//
//  Author: Will Moyle
//  Last Updated: 09/12/2014

//  CHESS BOARD FUNCTION DEFINITION FILE

#include "ChessBoard.hpp"

// -----------------------------------------------------------------------------
// CHESSBOARD FUNCTIONS


// START OF ChessBoard constructor
ChessBoard::ChessBoard()
{
  startBoard();
}
// END OF FUNCTION


// START OF ChessBoard destructor
ChessBoard::~ChessBoard()
{
  clearBoard();
}
// END OF FUNCTION


// START OF FUNCTION resetBoard()
void ChessBoard::resetBoard()
{
  clearBoard();
  startBoard();
}
// END OF FUNCTION


// START OF FUNCTION setBoard
void ChessBoard::startBoard()
{
  whiteTurn = true;
  gameActive = true;
  
  // create 32 Pieces on the heap:
  wr1 = new Rook("White's Rook", true, "A1", this);
  wr2 = new Rook("White's Rook", true, "H1", this);
  br1 = new Rook("Black's Rook", false, "A8", this);
  br2 = new Rook("Black's Rook", false, "H8", this);
  
  wb1 = new Bishop("White's Bishop", true, "C1", this);
  wb2 = new Bishop("White's Bishop", true, "F1", this);
  bb1 = new Bishop("Black's Bishop", false, "C8", this);
  bb2 = new Bishop("Black's Bishop", false, "F8", this);
    
  wk1 = new Knight("White's Knight", true, "B1", this);
  wk2 = new Knight("White's Knight", true, "G1", this);
  bk1 = new Knight("Black's Knight", false, "B8", this);
  bk2 = new Knight("Black's Knight", false, "G8", this);
    
  wq = new Queen("White's Queen", true, "D1", this);
  bq = new Queen("Black's Queen", false, "D8", this);
    
  wk = new King("White's King", true, "E1", this);
  bk = new King("Black's King", false, "E8", this);
    
  wp1 = new Pawn("White's Pawn", true, "A2", this);
  wp2 = new Pawn("White's Pawn", true, "B2", this);
  wp3 = new Pawn("White's Pawn", true, "C2", this);
  wp4 = new Pawn("White's Pawn", true, "D2", this);
  wp5 = new Pawn("White's Pawn", true, "E2", this);
  wp6 = new Pawn("White's Pawn", true, "F2", this);
  wp7 = new Pawn("White's Pawn", true, "G2", this);
  wp8 = new Pawn("White's Pawn", true, "H2", this);
    
  bp1 = new Pawn("Black's Pawn", false, "A7", this);
  bp2 = new Pawn("Black's Pawn", false, "B7", this);
  bp3 = new Pawn("Black's Pawn", false, "C7", this);
  bp4 = new Pawn("Black's Pawn", false, "D7", this);
  bp5 = new Pawn("Black's Pawn", false, "E7", this);
  bp6 = new Pawn("Black's Pawn", false, "F7", this);
  bp7 = new Pawn("Black's Pawn", false, "G7", this);
  bp8 = new Pawn("Black's Pawn", false, "H7", this);
    
  cout << "A new chess game is started!\n";
}
// END OF FUNCTION


// START OF FUNCTION clearBoard()
void ChessBoard::clearBoard()
{
  board.clear();

  // remove all 32 pieces from the heap:
  delete wr1;
  delete wr2;
  delete br1;
  delete br2;
  delete wb1;
  delete wb2;
  delete bb1;
  delete bb2;
  delete wk1;
  delete wk2;
  delete bk1;
  delete bk2;
  delete wq;
  delete bq;
  delete wk;
  delete bk;
  delete wp1;
  delete wp2;
  delete wp3;
  delete wp4;
  delete wp5;
  delete wp6;
  delete wp7;
  delete wp8;
  delete bp1;
  delete bp2;
  delete bp3;
  delete bp4;
  delete bp5;
  delete bp6;
  delete bp7;
  delete bp8;
}
// END OF FUNCTION


// START OF FUNCTION giveBoard
Piece* ChessBoard::giveBoard(string key)
{
  return board[key];
}
// END OF FUNCTION


// START OF FUNCTION setBoard
void ChessBoard::setBoard(string key, Piece* piece)
{
  board[key] = piece;
}
// END OF FUNCTION


// START OF FUNCTION addActivePiece
void ChessBoard::addActivePiece(Piece* piece)
{
  activePieces.push_back(piece);
}
// END OF FUNCTION


// START OF FUNCTION removeActivePiece
void ChessBoard::removeActivePiece(Piece* piece)
{
  activePieces.remove(piece);
}
// END OF FUNCTION


// START OF FUNCTION checkTurn
bool ChessBoard::checkTurn(Piece * mover)
{
  if (mover->giveColour() == whiteTurn)
    {
      return true;
    }
  return false;
}
// END OF FUNCTION


// START OF FUNCTION checkCheck
bool ChessBoard::checkCheck(bool isWhiteTurn)
{
  // run through every active Piece
  for (PieceIterator it = activePieces.begin(); 
       it != activePieces.end(); it++)
    {
      
      /* if the Piece has the same colour as 'isWhiteTurn' the check if
	 that Piece is targetting its opponent's King */
      if ((*it)->giveColour() == isWhiteTurn
	  && (*it)->targetingKing())
	{
	  return true;
	}
    }
  return false;
}
// END OF FUNCTION


// START OF FUNCTION checkCheckMate
bool ChessBoard::checkCheckmate()
{
  PieceIterator it1;
  MovesIterator it2;
  MovesList currentMoves;
  string tempPosition;
  bool checkMate(true);
  
  // run through every active Piece
  for (it1 = activePieces.begin();
       it1 != activePieces.end(); it1++)
    {
      // check it's that Piece's turn
      if ((*it1)->giveColour() != whiteTurn)
	{
	  currentMoves = (*it1)->giveMoves();
	  
	  // run through every move of that Piece
	  for (it2 = currentMoves.begin();
	       it2 != currentMoves.end(); it2++)
	    {
	      tempPosition.assign((*it1)->givePosition());
	      tempPosition[0] += (*it2).first;
	      tempPosition[1] += (*it2).second;
	      
	      /* if that move is valid and doesn't result in the player 
		 being in check then set 'checkMate' false */
	      if (((*it1)->validMove(tempPosition) == VALID_MOVE)
		  && !(*it1)->selfCheckingMove(tempPosition))
		{
		  checkMate = false;
		} 
	    }
	}
    }  
  
  /* if there exists one possible move for the player that doesn't end with
     the player in check, then 'checkMate' will be false. Otherwise there will
     be no possible move and 'checkMate' will be true */
  return checkMate;
}
// END OF FUNCTION


// START OF FUNCTION submitMove
void ChessBoard::submitMove(string start, string end)
{
  Piece * movingPiece = board[start];
  Piece * targetPosition = board[end];
  int error = 0;
  bool taken(false);

  // check the game is still running
  if(!gameActive)
    {
      cout << "This game has already finished.\n";
      return;
    }

  // check there is a piece at 'start'
  if(movingPiece == NULL)
    {
      cout << "There is no piece at position ";
      cout << start << "!\n";
      return;
    }

  // check the move from 'start' to 'end' is valid
  error = movingPiece->validMove(end);

  // print appropriate error message if move is invalid
  switch(error)
    {
    case INVALID_COORDS:
      cout << "The target coordinates are not on the board!\n";
      return;
    case ILLEGAL_MOVE:
    case BLOCKED_MOVE:
    case SELF_TAKING:
      cout << movingPiece->giveName();
      cout << " cannot move to " << end << "!\n";
      return;
    default:
      break;
    }

  // check if it is the Piece's turn
  if(!checkTurn(movingPiece))
    {
      cout << "It is not ";
      if (movingPiece->giveColour()) {cout << "White";}
      else {cout << "Black";}
      cout << "'s turn to move!\n";
      return;
    }

  // check that the move would not put the player in check
  if (movingPiece->selfCheckingMove(end))
    {
      cout << "Moving " << movingPiece->giveName() << " would put ";
      if (movingPiece->giveColour()) {cout << "White";}
      else {cout << "Black";}
      cout << " in check!\n";
      return;
    }

  // if a piece is taken, remove if from the board
  if(targetPosition != NULL)
    {     
      taken = true;
      targetPosition->setInPlay(false);      
      removeActivePiece(targetPosition);
    }
  
  // print out message stating move and if a piece is taken
  cout << movingPiece->giveName() << " moves from " << start << " to " << end;
  if (taken) {cout << " taking " << board[end]->giveName();}
  cout << "\n";
  
  movingPiece->setPosition(end);
  board[end] = movingPiece;
  board[start] = NULL;
  
  // check if the piece is in check
  if(checkCheck(whiteTurn))
    {
      // check if there is a possible move for the opponent
      if(checkCheckmate())
        {
	  // the opponent is in check and cannot move so it is checkmate
	  if (!whiteTurn) {cout << "White";}
	  else {cout << "Black";}
	  cout << " is in checkmate\n";
	  gameActive = false;
        }
      else
	{
	  // the opponent is in check but can move 
	  if (!whiteTurn) {cout << "White";}
	  else {cout << "Black";}
	  cout << " is in check\n";
	}
    }
  
  else if (checkCheckmate())
    {
      // the opponent is not in check but cannot move so it is stalemate
      cout << "The game has ended in a stalemate\n";
      gameActive = false;
    }

  // swap the current player
  whiteTurn = !whiteTurn;
    
}
// END OF FUNCTION


// START OF FUNCTION printBoard
void ChessBoard::printBoard()
{
  int i, j;
  string coordinates;
  cout << "\nPRINTING BOARD:\n\n\t";
  cout << "  A  B  C  D  E  F  G  H\n\t";
  for (i = '8'; i >= '1'; i--)
    {
      cout << " +--+--+--+--+--+--+--+--+\n\t" << i-48;
      for (j = 'A'; j <= 'H'; j++)
	{
	  coordinates.clear();
	  coordinates += j;
	  coordinates += i;
	  cout << "|";
            
	  Piece *tempPtr = board[coordinates];
	  if (tempPtr != NULL)
	    cout << tempPtr->giveSymbol();
	  else
	    cout << "  ";
	}
      cout << "|\n\t";
    }
  cout << " +--+--+--+--+--+--+--+--+\n\t";
  cout << "  A  B  C  D  E  F  G  H\n";
}
// END OF FUNCTION
