package com.tictac.TicTacServer.config;

public class GameLogic {

    public enum Status {
        Available,
        Player2Required,
        GameOn
    }

    private Status status;

    public GameLogic() {
        this.status = Status.Available;
    }

    public Status getStatus() {
        return this.status;
    }

    public void setStatus(Status status) {
        this.status = status;
    }

    public void joinGame() {
        if (this.status == Status.Available) {
            this.status = Status.Player2Required;
        } else if (this.status == Status.Player2Required) {
            this.status = Status.GameOn;
            startGame();
        }
    }

    private void startGame() {

    }
}
