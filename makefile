OBJ = ChessMain.o Pieces.o ChessBoard.o
EXEC = chess
TAGS = g++ -Wall -g

$(EXEC): $(OBJ)
	$(TAGS) $(OBJ) -o $(EXEC)

%.o: %.cpp
	$(TAGS) -c $<

clean:
	rm -f $(OBJ) $(EXEC)
