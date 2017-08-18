package com.tictac.TicTacServer.interfaces;

import com.tictac.TicTacServer.Player;

public interface GameRepository {

    public Player login(String login, String password);
}
