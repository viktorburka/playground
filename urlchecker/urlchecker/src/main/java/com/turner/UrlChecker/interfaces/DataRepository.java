package com.turner.UrlChecker.interfaces;

import com.turner.UrlChecker.dbentities.*;

import java.util.List;

/**
 * This interface defines database
 * access methods.
 */
public interface DataRepository {

    public UserAccount login(String token);

    public void addUrl(String url, int freq, int expCode, String expString);
    public void addCheckResult(String url, int statusCode, String state);

    public EmailSettings getEmailSettings();
    public List<EmailProperty> getEmailProperties();
    public List<MonitoredUrl> getMonitoredUrls();
    public List<UrlCheck> getUrlChecks();
}
