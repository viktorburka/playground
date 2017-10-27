package com.turner.UrlChecker.dbentities;

/**
 * This class represents url check
 * database record as Java class.
 */
public class UrlCheck {

    private String url;
    private String timeChecked;
    private int statusCode;
    private String state;

    public UrlCheck(String url, String timeChecked, int statusCode, String state) {
        this.url = url;
        this.timeChecked = timeChecked;
        this.statusCode = statusCode;
        this.state = state;
    }

    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
    }

    public String getTimeChecked() {
        return timeChecked;
    }

    public void setTimeChecked(String timeChecked) {
        this.timeChecked = timeChecked;
    }

    public int getStatusCode() {
        return statusCode;
    }

    public void setStatusCode(int statusCode) {
        this.statusCode = statusCode;
    }

    public String getState() {
        return state;
    }

    public void setState(String state) {
        this.state = state;
    }
}
