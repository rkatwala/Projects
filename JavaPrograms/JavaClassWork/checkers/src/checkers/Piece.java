// Rahul Katwala
package checkers;

public class Piece {

	  private int player;
	  private boolean king;
	  private int row;
	  private int column;

	  public Piece(int player, boolean king) {
	    this.player = player;
	    this.king = king;
	  }

	  public int getPlayer() {
	    return player;
	  }

	  public boolean isKing() {
	    return king;
	  }
	  public void setKing(boolean king) {
	    this.king = king;
	  }

	  public int getRow() {
	    return row;
	  }
	  public int getColumn() {
	    return column;
	  }

	  public void setCoordinate(int row, int column) {
	    this.row = row;
	    this.column = column;
	  }
	}
