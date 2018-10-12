package com.webtechexplorer.springhttps;

import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.RequestMapping;

@RestController
public class HealthController {

    @RequestMapping("/health")
    public String health() {
        return "OK";
    }

}