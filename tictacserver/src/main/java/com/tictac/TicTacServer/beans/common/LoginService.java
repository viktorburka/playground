package com.tictac.TicTacServer.beans.common;

import com.tictac.TicTacServer.interfaces.AuthenticationInterface;
import com.tictac.TicTacServer.interfaces.GameRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class LoginService implements AuthenticationInterface {

    @Autowired
    GameRepository repository;

    @Override
    public boolean login(String login, String password) {
        return this.repository.login(login, password) != null;
    }
}
