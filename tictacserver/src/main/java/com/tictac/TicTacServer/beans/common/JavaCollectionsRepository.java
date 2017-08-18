package com.tictac.TicTacServer.beans.common;

import com.tictac.TicTacServer.Player;
import com.tictac.TicTacServer.interfaces.GameRepository;
import org.springframework.stereotype.Repository;

import java.util.HashMap;
import java.util.Map;

@Repository
public class JavaCollectionsRepository implements GameRepository {

    private Map<Long,Player> playersTable = new HashMap<>();

    protected interface TableInitializer {
        void addPlayer(long id, String login, String password);
    }

    public JavaCollectionsRepository() {

        System.out.println("JavaCollectionsRepository constructor");

        TableInitializer f = (id, login, password) -> {
            Long playerId = id;
            Player p = new Player(id);
            p.setLogin(login);
            p.setPassword(password);
            playersTable.put(playerId, p);
        };

        long id = 0;

        f.addPlayer(id++, "1", "2");
        f.addPlayer(id++, "player1", "player1");
        f.addPlayer(id++, "player2", "player2");
        f.addPlayer(id  , "player3", "player3");

        for (Player p : playersTable.values()) {
            System.out.printf("JavaCollectionsRepository login: %s, password: %s\n", p.getLogin(), p.getPassword());
        }
    }

    public Player login(String login, String password) {
        System.out.println("In login method");
        for (Player p : playersTable.values()) {
            System.out.printf("player login: %s, password: %s\n", p.getLogin(), p.getPassword());
            if (p.getLogin().equals(login) &&
                p.getPassword().equals(password)) {
                return p;
            }
        }
        return null;
    }
}
