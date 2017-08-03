package com.tictac.TicTacServer;

import com.tictac.TicTacServer.config.annotation.HomePage;
import org.springframework.web.bind.annotation.RequestMapping;

@HomePage
public class HomePageEndpoint {

    @RequestMapping("/")
    public String homepage(){
        return "homepage";
    }
}
