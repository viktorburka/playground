package com.tictac.TicTacServer.beans.home;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class HomePageEndpoint {

    HomePageEndpoint() {
        System.out.println("HomePageEndpoint constructor");
    }

    @RequestMapping("/")
    public String homepage(){
        return "homepage";
    }
}
