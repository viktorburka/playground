package com.turner.UrlChecker.beans.home;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

/**
 * This class implements static content endpoint
 * that serves static content such as HTML,
 * CSS to the user.
 */
@Controller
public class HomePageEndpoint {

    HomePageEndpoint() {
        System.out.println("HomePageEndpoint constructor");
    }

    /**
     * Return main HTML page.
     */
    @RequestMapping("/")
    public String homepage(){
        return "homepage";
    }
}
