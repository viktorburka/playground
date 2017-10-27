package com.turner.UrlChecker.messages.msgobjects;

/**
 * This class represents register
 * URL JSON object as Java class.
 */
public class RegisterUrlMsg {

    private String url;
    private int freq;
    private int expCode;
    private String expString;

    public String getUrl() { return url; }
    public void setUrl(String newUrl) { url = newUrl; }

    public int getFreq() { return freq; }
    public void setFreq(int newFreq) { freq = newFreq; }

    public int getExpCode() { return expCode; }
    public void setExpCode(int newExpCode) { expCode = newExpCode; }

    public String getExpString() { return expString; }
    public void setExpString(String newExpString) { expString = newExpString; }
}
