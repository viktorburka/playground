package com.turner.UrlChecker.dbentities;

/**
 * This class represents user account
 * database record as Java class.
 */
public class UserAccount {

    private String name;
    private String token;
    private String email;
    private boolean notify;

    public UserAccount(String name, String token,
                       String email, boolean notify) {
        this.name = name;
        this.token = token;
        this.email = email;
        this.notify = notify;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getToken() {
        return token;
    }

    public void setToken(String token) {
        this.token = token;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public boolean isNotify() {
        return notify;
    }

    public void setNotify(boolean notify) {
        this.notify = notify;
    }
}
