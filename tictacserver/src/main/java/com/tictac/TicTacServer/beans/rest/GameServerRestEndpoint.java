package com.tictac.TicTacServer.beans.rest;

import com.tictac.TicTacServer.beans.common.GameRepository;
import com.tictac.TicTacServer.game.msgobjects.Move;
import com.tictac.TicTacServer.game.msgobjects.PlayerAction;
import com.tictac.TicTacServer.game.GameLogic;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.ResponseStatus;
import org.springframework.web.bind.annotation.RequestBody;

@Controller
public class GameServerRestEndpoint {

    GameLogic gameLogic = new GameLogic();

    @Autowired
    GameRepository repository;

    GameServerRestEndpoint() {
        System.out.println("GameServerRestEndpoint constructor");
    }

    @RequestMapping(value = "products", method = RequestMethod.GET)
    @ResponseBody
    @ResponseStatus(HttpStatus.OK)
    public PlayerAction read()
    {
        return (new PlayerAction("click", "1,1"));
    }

    @RequestMapping(value = "gamestatus", method = RequestMethod.GET, produces="application/json")
    @ResponseBody
    @ResponseStatus(HttpStatus.OK)
    public String gameStatus()
    {
        String json = String.format("{\"status\": \"%s\"}", gameLogic.getStatus().name());
        return json;
    }

    @RequestMapping(value = "join", method = RequestMethod.GET)
    @ResponseBody
    @ResponseStatus(HttpStatus.OK)
    public String joinGame()
    {
        gameLogic.joinGame();
        return "{}";
    }

    @RequestMapping(value = "currentplayer", method = RequestMethod.GET, produces="application/json")
    @ResponseBody
    @ResponseStatus(HttpStatus.OK)
    public String currentPlayer()
    {
        String response = String.format("{\"player\": \"%s\"}", gameLogic.getCurrentPlayer().name());
        return response;
    }

    @RequestMapping(value = "move", method = RequestMethod.POST, produces="application/json")
    @ResponseBody
    @ResponseStatus(HttpStatus.OK)
    public String move(@RequestBody Move move)
    {
        this.gameLogic.move(GameLogic.Player.valueOf(move.getPlayer()),
                            move.row(),
                            move.column());

        String response = String.format("{\"player\": \"%s\"}", gameLogic.getCurrentPlayer().name());
        return response;
    }

    @RequestMapping(value = "login", method = RequestMethod.POST)
    @ResponseBody
    @ResponseStatus(HttpStatus.OK)
    public void login(@RequestBody Move move)
    {
//        if (this.repository.authenticate(login, password)) {
//        }
    }
}
