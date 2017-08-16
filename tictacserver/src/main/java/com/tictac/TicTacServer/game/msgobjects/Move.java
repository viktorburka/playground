package com.tictac.TicTacServer.game.msgobjects;

public class Move {

    private String player;
    private String pos;

    public void setPlayer(String player) {
        this.player = player;
    }

    public String getPlayer() {
        return this.player;
    }

    public void setPos(String pos) {
        this.pos = pos;
    }

    public String getPos() {
        return this.pos;
    }

    public int row() {
        return Integer.parseInt(this.pos.split(",")[0]);
    }

    public int column() {
        return Integer.parseInt(this.pos.split(",")[1]);
    }
}
