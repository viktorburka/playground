package com.turner.UrlChecker.dbentities;

/**
 * This class represents checked url
 * database record as Java class.
 */
public class MonitoredUrl {

    private String url;
    private int frequency;
    private int expectedStatus;
    private String expectedString;

    public MonitoredUrl(String url, int frequency, int expectedStatus, String expectedString) {
        this.url = url;
        this.frequency = frequency;
        this.expectedStatus = expectedStatus;
        this.expectedString = expectedString;
    }

    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
    }

    public int getFrequency() {
        return frequency;
    }

    public void setFrequency(int frequency) {
        this.frequency = frequency;
    }

    public int getExpectedStatus() {
        return expectedStatus;
    }

    public void setExpectedStatus(int expectedStatus) {
        this.expectedStatus = expectedStatus;
    }

    public String getExpectedString() {
        return expectedString;
    }

    public void setExpectedString(String expectedString) {
        this.expectedString = expectedString;
    }
}
