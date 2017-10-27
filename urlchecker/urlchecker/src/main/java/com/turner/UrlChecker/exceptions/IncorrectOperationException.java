package com.turner.UrlChecker.exceptions;

import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.ResponseStatus;

/**
 * This class represents exception thrown
 * in a case of wrong arguments or incorrect
 * operation. This leads to 406 HTML code
 * to be returned as response to the client.
 */
@ResponseStatus(HttpStatus.NOT_ACCEPTABLE)
public class IncorrectOperationException extends RuntimeException {
    public IncorrectOperationException(String msg) {
        super(msg);
    }
}
