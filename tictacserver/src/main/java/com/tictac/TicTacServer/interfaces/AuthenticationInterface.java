package com.tictac.TicTacServer.interfaces;

import com.tictac.TicTacServer.Player;

public interface AuthenticationInterface {

    public boolean login(String login, String password);
}
