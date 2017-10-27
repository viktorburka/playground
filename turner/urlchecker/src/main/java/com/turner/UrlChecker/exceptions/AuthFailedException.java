package com.turner.UrlChecker.exceptions;

import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.ResponseStatus;

/**
 * This class represents exception thrown
 * in a case of unauthorized access. This leads
 * to 401 HTML code to be returned as response
 * to the client.
 */
@ResponseStatus(HttpStatus.UNAUTHORIZED)
public class AuthFailedException extends RuntimeException
{
    public AuthFailedException(String msg) {
        super(msg);
    }
}