package com.tictac.TicTacServer;

public class PlayerAction {
    //private String action = new String("{\"command\": \"click\", \"pos\": \"1,1\"}");
    //private String action = new String("action");
    private String command;
    private String commandParameter;

    public PlayerAction(String command, String commandParameter) {
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
