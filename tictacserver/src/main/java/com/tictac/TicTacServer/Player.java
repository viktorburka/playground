package com.tictac.TicTacServer;

public class Player {

    private long id;
    private String login;
    private String password;

    public Player(long id) { this.id = id; }

    public long getId() { return this.id; }

    public String getLogin() { return this.login; }
    public void setLogin(String login) { this.login = login; }

    public String getPassword() { return this.password; }
    public void setPassword(String password) { this.password = password; }
}
