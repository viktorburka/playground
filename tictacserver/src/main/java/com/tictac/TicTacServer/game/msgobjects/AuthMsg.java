package com.tictac.TicTacServer.game.msgobjects;

public class AuthMsg {

    private String login;
    private String password;

    public String getLogin() { return this.login; }
    public void setLogin(String login) { this.login = login; }

    public String getPassword() { return this.password; }
    public void setPassword(String password) { this.password = password; }
}
