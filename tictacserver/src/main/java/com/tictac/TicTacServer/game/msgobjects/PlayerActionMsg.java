package com.tictac.TicTacServer.game.msgobjects;

public class PlayerActionMsg {

    private String command;
    private String commandParameter;

    public PlayerActionMsg(String command, String commandParameter) {
        this.command = command;
        this.commandParameter = commandParameter;
    }

    public String getCommand() {
        return this.command;
    }

    public void setCommand(String c) {
        this.command = c;
    }

    public String getCommandParameter() {
        return this.commandParameter;
    }

    public void setCommandParameter(String cp) {
        this.commandParameter = cp;
    }
}
