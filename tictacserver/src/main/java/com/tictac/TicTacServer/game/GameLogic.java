package com.tictac.TicTacServer.game;

public class GameLogic {

    public enum Status {
        Available,
        Player2Required,
        GameOn
    }

    public enum CellType {
        Closed,
        Opened_X,
        Opened_O
    }

    public enum Player {
        Player_1,
        Player_2
    }

    private final int FieldSize = 4;
    private Status status;
    private CellType[][] field;
    private Player player;

    public GameLogic() {
        this.status = Status.Available;
        this.field = new CellType[FieldSize][FieldSize];
        this.player = Player.Player_1;
    }

    public Status getStatus() {
        return this.status;
    }

    public void setStatus(Status status) {
        this.status = status;
    }

    public Player getCurrentPlayer() {
        return this.player;
    }

    public void joinGame() {
        if (this.status == Status.Available) {
            this.status = Status.Player2Required;
        } else if (this.status == Status.Player2Required) {
            this.status = Status.GameOn;
            startGame();
        }
    }

    public void move(Player player, int row, int column) {
        if (row >= 0 && row < this.FieldSize &&
            column >=0 && column < this.FieldSize) {
            if (field[row][column] == CellType.Closed) {
                field[row][column] = this.player == Player.Player_1 ? CellType.Opened_X :
                                                                      CellType.Opened_O;
            }
        }
    }

    private void startGame() {
        for (int i=0; i<FieldSize; ++i) {
            for (int j=0; j<FieldSize; ++j) {
                this.field[i][j] = CellType.Closed;
            }
        }
        player = Player.Player_1;
    }
}
