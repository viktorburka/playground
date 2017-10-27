package com.turner.UrlChecker.beans.rest;

import com.turner.UrlChecker.dbentities.MonitoredUrl;
import com.turner.UrlChecker.dbentities.UrlCheck;
import com.turner.UrlChecker.interfaces.UrlCheckerExecutorInterface;
import com.turner.UrlChecker.interfaces.AuthenticationInterface;
import com.turner.UrlChecker.messages.msgobjects.RegisterUrlMsg;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import java.util.List;

/**
 * This class implements RESTful endpoint.
 * It provides functionality for managing UrlChecker
 * functionality through web services API.
 */
@Controller
public class UrlCheckerRestEndpoint {

    // user authentication service
    @Autowired
    AuthenticationInterface authService;

    // url checker service
    @Autowired
    UrlCheckerExecutorInterface urlChecker;

    UrlCheckerRestEndpoint() {
        System.out.println("UrlCheckerRestEndpoint constructor");
    }

    /**
     * This method implements mapping for registering checked URL.
     * It converts POST request body JSON content to
     * appropriate message instance through @RequestBody annotation.
     * @param msg The input JSON object
     * @param token The API Key token to authenticate user request
     */
    @RequestMapping(value = "registerurl", method = RequestMethod.POST)
    @ResponseBody
    @ResponseStatus(HttpStatus.OK)
    public void registerUrl(@RequestBody RegisterUrlMsg msg,
                            @RequestHeader("apikey") String token)
    {
        System.out.println("url:");
        System.out.println(msg.getUrl());
        System.out.println("freq:");
        System.out.println(msg.getFreq());
        System.out.println("expCode:");
        System.out.println(msg.getExpCode());
        System.out.println("expString:");
        System.out.println(msg.getExpString());
        System.out.println("token:");
        System.out.println(token);

        // check whether token is permitted
        authService.checkCredentials(token);

        // add URL to the database
        urlChecker.addUrl(msg.getUrl(), msg.getFreq(),
                msg.getExpCode(), msg.getExpString());

        // start checking URL
        urlChecker.checkUrl(msg.getUrl(), msg.getFreq(),
                            msg.getExpCode(), msg.getExpString(),
                            token);
    }

    /**
     * This method returns a list of monitored URLs as JSON object.
     */
    @RequestMapping(value = "urls", method = RequestMethod.GET)
    @ResponseBody
    @ResponseStatus(HttpStatus.OK)
    public List<MonitoredUrl> getUrls()
    {
        System.out.println("geturls");
        return urlChecker.getMonitoredUrls();
    }

    /**
     * This method returns a list of URL checks as JSON object.
     */
    @RequestMapping(value = "urlchecks", method = RequestMethod.GET)
    @ResponseBody
    @ResponseStatus(HttpStatus.OK)
    public List<UrlCheck> getUrlChecks()
    {
        System.out.println("urlchecks");
        return urlChecker.getUrlChecks();
    }
}
