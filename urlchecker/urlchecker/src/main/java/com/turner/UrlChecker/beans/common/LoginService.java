package com.turner.UrlChecker.beans.common;

import com.turner.UrlChecker.dbentities.UserAccount;
import com.turner.UrlChecker.exceptions.AuthFailedException;
import com.turner.UrlChecker.interfaces.AuthenticationInterface;
import com.turner.UrlChecker.interfaces.DataRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

/**
 * This class implements authentication by querying given
 * token in the database.
 */
@Service
public class LoginService implements AuthenticationInterface {

    // database access entity
    @Autowired
    DataRepository repository;

    /**
     * This method checks whether a user with given
     * credentials (token) exists. If the user doesn't
     * exist, a AuthFailedException exception will be
     * thrown, resulting in returning 401 HTTP code.
     * @param token The API Key token
     */
    @Override
    public void checkCredentials(String token) {
        UserAccount p = this.repository.login(token);
        if (p == null) {
            String s = String.format("Invalid credentials: %s\n", token);
            System.out.printf(s);
            throw new AuthFailedException(s);
        }
    }
}
