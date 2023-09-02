// Rahul Katwala 
package checkers;

import java.util.Scanner;

public class checkers {

  private static boolean TEST_MULTIPLE_JUMP_CHOICES = false;

  private static int RED = 0; // 'r' or 'R' if King
  private static int BLACK = 1; // 'b' or 'B' if King
         
  private Piece[][] pieces; // 8 x 8 for all places on the board
  private int turnPlayer; // RED or BLACK
  private int[] counts; // index 0 for RED and 1 for BLACK

  private Scanner scanner;


  
  // Constructor of the Checkers class
 

  public checkers() {
     if (TEST_MULTIPLE_JUMP_CHOICES) {
       initBoardForTestMultipleJumpChoices();
       turnPlayer = BLACK;
     }
     else {
       initBoard();
       turnPlayer = RED;
     }
     scanner = new Scanner(System.in);
  }

 
  // Initializes the board.


  private void initBoard() {
    pieces = new Piece[8][8];   
    counts = new int[2];

    // Rows 0-2 have RED pieces and 6-8 have BLACK pieces, Rows 3-4 empty 
    for (int i = 0; i < 8; i++) {
      if (i == 3 || i == 4) {
        continue;
      }

      // Set player to RED or BLACK to populate the board spaces
      int player = (i < 3) ? RED : BLACK;

      for (int j = 1 - i%2; j < 8; j+=2) {
        Piece piece = new Piece(player, false);
        piece.setCoordinate(i,j);
        pieces[i][j] = piece;
        counts[player] += 1;
      }
    }
  }
  
  

  // Initializes the board to test multiple jump choices.
  private void initBoardForTestMultipleJumpChoices() {
    pieces = new Piece[8][8];   
    counts = new int[2];

    Piece piece = new Piece(RED, false);
    piece.setCoordinate(1,4);
    pieces[1][4] = piece;
    counts[RED] += 1;

    piece = new Piece(RED, false);
    piece.setCoordinate(1,6);
    pieces[1][6] = piece;
    counts[RED] += 1;

    piece = new Piece(RED, false);
    piece.setCoordinate(3,4);
    pieces[3][4] = piece;
    counts[RED] += 1;

    piece = new Piece(BLACK, false);
    piece.setCoordinate(4,3);
    pieces[4][3] = piece;
    counts[BLACK] += 1;
  }

 
  // Converts a piece to a character to print.


  private char pieceChar(Piece piece) {

    // If there is no piece print '-'
    if (piece == null) {
      return '_';
    }

    // Check if there is a RED or BLACK piece and print 'o' or 'x'
    char c = (piece.getPlayer() == RED ? 'x' : 'o');

    // Check if piece is a King
    if (piece.isKing()) {
      c += ('A' - 'a');
    }

    return c;
  }

  // Prints and shows the board to the players.

  public void printBoard() {

    // Show the column headings for each column a - h
    System.out.println("  a b c d e f g h");

    // Show the pieces in each spot
    for (int i = 0; i < 8; i++) {
      System.out.printf("%d", i+1);
      for (int j = 0; j < 8; j++) {
        System.out.printf(" %c", pieceChar(pieces[i][j]));
      }
      System.out.println();
    }
    System.out.printf("(Red %d vs %d Black)%n", counts[RED], counts[BLACK]);
  }


  // This method just returns the counts for RED or BLACK 


  public int[] getCounts() {
    return counts;
  }

  // Gets the list of coordinates which can be moved to.
  // If jumpOnly flag is true, it only checks for jump.


  private int[][] canMoveTo(Piece piece, boolean jumpOnly) {
    if (piece == null) {
      return null;
    }
    int row = piece.getRow();
    int col = piece.getColumn();
    int player = piece.getPlayer();
    boolean king = piece.isKing();

    int[][] indecesTo = new int[4][];
    for (int i = 0; i < 4; i++) {
      indecesTo[i] = null;
    }
    int count = 0;

    // Processes the upper row and lower row of the piece.
    for (int i = row-1 ; i <= row+1; i+=2) {

      // Checks the boundary.
      if (i < 0 || i > 7) {
        continue;
      }
      if (! king) {
        // A normal piece can only move forward.
        if (player == RED) {
          if (i < row) {
            continue;
          }
        }
        else {
          if (i > row) {
            continue;
          }
        }
      }

      // Processes the left column and right column of the piece.
      for (int j = col-1 ; j <= col+1; j+=2) {

        // Checks the boundary.
        if (j < 0 || j > 7) {
          continue;
        }

        // Checks the piece in (i,j).
        Piece pieceTo = pieces[i][j];
        if (pieceTo == null) {
          // empty
          if (! jumpOnly) {
            indecesTo[count++] = new int[] {i,j};
          }
          continue;
        }

        if (pieceTo.getPlayer() == player) {
          // same color piece
          continue;
        }

        // Checks jump
        if (i == 0 || i == 7 || j == 0 || j == 7) {
          // edge
          continue;
        }

        int i1 = i + (i - row);
        int j1 = j + (j - col);

        pieceTo = pieces[i1][j1];
        if (pieceTo == null) {
          // Can jump.
          indecesTo[count++] = new int[] {i1,j1};
          continue;
        }
      }
    }
    if (count == 0) {
      return null;
    }
    return indecesTo;
  }

  // In this method the RED or BLACK take turns to move the pieces


  public void turn() {
    Piece piece = null;   
    int[][] indecesTo = null;

    // Selects the piece of the turn player.
    while (true) {
      System.out.printf("%s's turn: ", (turnPlayer == RED ? "Red" : "Black"));
      System.out.flush();
      String s = scanner.next().trim();
      int[] index = toIndex(s);
      if (index == null) {
        System.out.println("Invalid input. Please try again.");
        continue;
      }
      int row = index[0];
      int col = index[1];
      piece = pieces[row][col];
      indecesTo = canMoveTo(piece, false);
      if (indecesTo == null) {
        System.out.println("Cannot move. Please try again.");
        continue;
      }
      break;
    }

    // Selects the move.
    int[] indexTo = null;

    if (indecesTo[1] == null) {
      // In case of just one move possible, no need of user input.
      indexTo = indecesTo[0];
    }

    else {

      // In case of multiple move choices, offer choices to move.
      System.out.printf("%s: Where to move?", (turnPlayer == RED ? "Red" : "Black"));
      int n = 0;
      for (n = 0; n < 4; n++) {
        int[] indexTo1 = indecesTo[n];
        if (indexTo1 == null) {
          break;
        }
        if (n > 0) {
          System.out.print(",");
        }
        System.out.printf(" %d)%c%c", n+1, 'a'+indexTo1[1], '1'+indexTo1[0]);
      }
      // At the end of loop, n is the number of move choices.

      while (true) {
        // Prints the prompt.
        System.out.print("  ");
        System.out.flush();
        // Scans user input.
        String s = scanner.next().trim();
        // Parses the input.
        if (s == null || s.length() != 1) {
          System.out.println("Invalid input!");
          continue;
        }

        int i = s.charAt(0) - '1';
        if (i < 0 || i >= n) {
          System.out.println("Invalid input!");
          continue;
        }

        indexTo = indecesTo[i];
        break;
      }
    }

    // Actually, moves the piece to a new place.
    boolean jumped = move(piece, indexTo[0], indexTo[1]);

    // If the piece jumped an opponent piece, checks multiple jumps.
    while (jumped) {
      indecesTo = canMoveTo(piece, true);
      if (indecesTo == null) {
        break;
      }

      // Prints the board.
      printBoard();

      if (indecesTo[1] == null) {
        // In case of just one move possible, no need of user input.
        indexTo = indecesTo[0];
      }
      else {
        // In case of multiple move choices, offer choices to move.
        System.out.printf("%s: Where to jump?", (turnPlayer == RED ? "Red" : "Black"));
        int n = 0;
        for (n = 0; n < 4; n++) {
          int[] indexTo1 = indecesTo[n];
          if (indexTo1 == null) {
            break;
          }
          if (n > 0) {
            System.out.print(",");
          }
          System.out.printf(" %d)%c%c", n+1, 'a'+indexTo1[1], '1'+indexTo1[0]);
        }
        // At the end of loop, n is the number of move choices.

        while (true) {
          // Prints the prompt.
          System.out.print(" > ");
          System.out.flush();
          // Scans user input.
          String s = scanner.next().trim();
          // Parses the input.
          if (s == null || s.length() != 1) {
            System.out.println("Invalid input!");
            continue;
          }

          int i = s.charAt(0) - '1';
          if (i < 0 || i >= n) {
            System.out.println("Invalid input!");
            continue;
          }
  
          indexTo = indecesTo[i];
          break;
        }
      }
      jumped = move(piece, indexTo[0], indexTo[1]);
    }
    turnPlayer = (turnPlayer == RED) ? BLACK : RED;
    return;
  }

  // Parses the string to the coordinate.


  private int[] toIndex(String s) {
    if (s == null || s.length() != 2) {
      return null;
    }
    int i = s.charAt(1) - '1';
    if (i < 0 || i > 7) {
      return null;
    }
    int j = s.charAt(0) - 'a';
    if (j < 0 || j > 7) {
      return null;
    }
    return new int[] {i,j};
  }


  // Moves apiece to new coordinate. Returns true if it jumps.

  public boolean move(Piece piece, int row, int column) {
    int originalRow = piece.getRow();
    int originalColumn = piece.getColumn();
    pieces[originalRow][originalColumn] = null;
    pieces[row][column] = piece;
    if (! piece.isKing()) {
      // If a normal piece reaches the end, it becomes the king.
      if (row == 0 || row == 7) {
        piece.setKing(true);
      }
    }
    piece.setCoordinate(row, column);

    // jump
    int diff = row - originalRow;
    if (diff == 2 || diff == -2) {
      diff /= 2;
      row = originalRow + diff;
      diff = column - originalColumn;
      diff /= 2;
      column = originalColumn + diff;
      // Kills the opponent piece.
      pieces[row][column] = null;
      // Updates the counter (the number of remaining pieces).
      counts[piece.getPlayer() == RED ? BLACK : RED] -= 1;
      return true;
    }
    else {
      return false;
    }
  }
//--------------------------------------------------------------------------------------------
  // This is the main program
  

  public static void main(String[] args) throws Exception {
	  System.out.println("To click a piece first choose the column letter it is in then the row number. For example b3. \nAfter selecting the piece, then choose the choice number of the moves possible. If there is only one move avilable, it will do it for you. \n");;
    // If the first argument is "t", it tests multiple jump choices.
    if (args.length > 0 && args[0].charAt(0) == 't') {
      TEST_MULTIPLE_JUMP_CHOICES = true;
    }

    // Call the constructor for the game
    checkers checkers = new checkers();

    // Loop for the game, until RED or BLACK wins
    while (true) {

      checkers.printBoard();
      int[] counts = checkers.getCounts();

      // If there are no RED pieces left, BLACK wins
      if (counts[RED] == 0) {
        System.out.println("Black wins!");
        break;
      }

      // If there are no BLACK pieces left, RED wins
      else if (counts[BLACK] == 0) {
        System.out.println("Red wins!");
        break;
      }

      // RED and BLACK take turns
      checkers.turn();     
    }
  }
}
