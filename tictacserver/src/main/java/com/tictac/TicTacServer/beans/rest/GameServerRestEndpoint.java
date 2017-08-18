package com.tictac.TicTacServer.beans.rest;

import com.tictac.TicTacServer.exceptions.ResourceNotFoundException;
import com.tictac.TicTacServer.game.msgobjects.AuthMsg;
import com.tictac.TicTacServer.game.msgobjects.MoveMsg;
import com.tictac.TicTacServer.game.GameLogic;
import com.tictac.TicTacServer.interfaces.AuthenticationInterface;
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
    AuthenticationInterface authService;

    GameServerRestEndpoint() {
        System.out.println("GameServerRestEndpoint constructor");
    }

    @RequestMapping(value = "login", method = RequestMethod.POST)
    @ResponseStatus(HttpStatus.OK)
    public void login(@RequestBody AuthMsg auth)
    {
        System.out.printf("login: %s; password: %s\n", auth.getLogin(), auth.getPassword());
        if (!authService.login(auth.getLogin(), auth.getPassword())) {
            System.out.printf("Invalid login: %s or password: %s\n", auth.getLogin(), auth.getPassword());
            throw new ResourceNotFoundException();
        }
    }

    @RequestMapping(value = "gamestatus", method = RequestMethod.GET)
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

    @RequestMapping(value = "currentplayer", method = RequestMethod.GET)
    @ResponseBody
    @ResponseStatus(HttpStatus.OK)
    public String currentPlayer()
    {
        String response = String.format("{\"player\": \"%s\"}", gameLogic.getCurrentPlayer().name());
        return response;
    }

    @RequestMapping(value = "move", method = RequestMethod.POST)
    @ResponseBody
    @ResponseStatus(HttpStatus.OK)
    public String move(@RequestBody MoveMsg move)
    {
        this.gameLogic.move(GameLogic.Player.valueOf(move.getPlayer()),
                            move.row(),
                            move.column());

        String response = String.format("{\"player\": \"%s\"}", gameLogic.getCurrentPlayer().name());
        return response;
    }
}
