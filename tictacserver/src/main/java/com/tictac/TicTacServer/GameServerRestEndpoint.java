package com.tictac.TicTacServer;

import com.tictac.TicTacServer.config.annotation.RestEndpoint;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

@RestEndpoint
public class GameServerRestEndpoint {

    @RequestMapping(value = "account", method = RequestMethod.OPTIONS)
    public ResponseEntity<Void> discover()
    {
        HttpHeaders headers = new HttpHeaders();
        headers.add("Allow","OPTIONS,HEAD,GET,POST");
        return new ResponseEntity(null, headers, HttpStatus.NO_CONTENT);
    }
}
