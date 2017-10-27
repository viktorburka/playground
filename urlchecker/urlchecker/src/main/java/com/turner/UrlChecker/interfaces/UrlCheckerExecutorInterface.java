package com.turner.UrlChecker.interfaces;

import com.turner.UrlChecker.dbentities.MonitoredUrl;
import com.turner.UrlChecker.dbentities.UrlCheck;

import java.util.List;

/**
 * This interface defines url checker
 * operations.
 */
public interface UrlCheckerExecutorInterface {

    public void addUrl(String url, int freq, int expCode, String expString);
    public void checkUrl(String url, int freq, int expCode,
                         String expString, String token);
    public List<MonitoredUrl> getMonitoredUrls();
    public List<UrlCheck> getUrlChecks();
}
