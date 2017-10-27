package com.turner.UrlChecker.beans.common;

import com.turner.UrlChecker.dbentities.*;
import com.turner.UrlChecker.interfaces.DataRepository;
import org.springframework.dao.IncorrectResultSizeDataAccessException;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.RowMapper;
import org.springframework.stereotype.Repository;

import javax.inject.Inject;
import java.sql.*;
import java.text.SimpleDateFormat;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Calendar;
import java.util.List;

/**
 * This class implements JDBC access to SQL database
 * providing such operations as adding URLs, checks,
 * querying user accounts, URLs and checks
 */
@Repository
public class JdbcRepository implements DataRepository {

    // jdbc operations entity
    private JdbcTemplate jdbc;

    @Inject
    public JdbcRepository(JdbcTemplate jdbcOperations) {
        this.jdbc = jdbcOperations;
    }

    /**
     * This method reads user account by a given token.
     * Only one user account will be retrieved. If user
     * account with the given token is not found, null
     * value will be returned.
     * @param token The API Key token
     */
    @Override
    public UserAccount login(String token) {
        UserAccount a;
        try {
            a = jdbc.queryForObject("select * from Auth where token=(?)",
                                    new Object[]{token},
                                    new int[]{Types.VARCHAR},
                                    new AccountRowMapper());
        } catch (IncorrectResultSizeDataAccessException ex) {
            System.out.println("IncorrectResultSizeDataAccessException");
            System.out.println(ex.getMessage());
            return null;
        }
        return a;
    }

    /**
     * This method adds to the database the URL that is being
     * checked.
     * @param url The URL to be added
     * @param freq The frequency in seconds
     * @param expCode The expected return code
     * @param expString The expected string. It can be optional
     */
    @Override
    public void addUrl(String url, int freq, int expCode, String expString) {

        String updateSql = "insert into Urls (url, frequency, expectedStatus, expectedString) values (?,?,?,?)";

        Object[] values = new Object[] { url, freq, expCode, expString };
        int[] types = new int[] { Types.VARCHAR, Types.INTEGER, Types.INTEGER, Types.VARCHAR };

        jdbc.update(updateSql, values, types);
    }

    /**
     * This method adds check to the database.
     * @param url The URL of the check
     * @param statusCode The returned status code
     * @param state The state. Can be SUCCESS or FAILURE
     */
    @Override
    public void addCheckResult(String url, int statusCode, String state) {

        String updateSql = "insert into UrlChecks (url, timeChecked, statusCode, state) values (?,?,?,?)";

        long timeNow = Calendar.getInstance().getTimeInMillis();
        java.sql.Timestamp timeChecked = new java.sql.Timestamp(timeNow);

        Object[] values = new Object[] { url, timeChecked, statusCode, state };
        int[] types = new int[] { Types.VARCHAR, Types.TIMESTAMP, Types.INTEGER, Types.VARCHAR };

        jdbc.update(updateSql, values, types);

        String strTime = new SimpleDateFormat("MM/dd/yyyy HH:mm:ss").format(timeChecked);
        System.out.println("Add check to the table");
        System.out.format("Url: %s %n", url);
        System.out.format("Date time: %s %n", strTime);
        System.out.format("Status Code: %d %n", statusCode);
        System.out.format("State: %s %n", state);
        System.out.println("");
    }

    /**
     * This method returns EmailsSettings object that
     * contains SMTP settings to send notification emails.
     */
    @Override
    public EmailSettings getEmailSettings() {
        List<EmailSettings> es;
        try {
            es = jdbc.query("select * from EmailSettings",
                            new EmailSettingsRowMapper());
        } catch (IncorrectResultSizeDataAccessException ex) {
            System.out.println("IncorrectResultSizeDataAccessException");
            System.out.println(ex.getMessage());
            return null;
        }
        return es.size() != 0 ? es.get(0) : null;
    }

    /**
     * This method returns a list of email settings
     * to send notification emails.
     */
    @Override
    public List<EmailProperty> getEmailProperties() {
        List<EmailProperty> es;
        try {
            es = jdbc.query("select * from EmailProperties",
                            new EmailPropertiesRowMapper());
        } catch (IncorrectResultSizeDataAccessException ex) {
            System.out.println("IncorrectResultSizeDataAccessException");
            System.out.println(ex.getMessage());
            return null;
        }
        return es;
    }

    /**
     * This method returns a list of URLs being checked.
     */
    @Override
    public List<MonitoredUrl> getMonitoredUrls() {
        List<MonitoredUrl> urls;
        try {
            urls = jdbc.query("select * from Urls", new MonitoredUrlRowMapper());
        } catch (IncorrectResultSizeDataAccessException ex) {
            System.out.println("IncorrectResultSizeDataAccessException");
            System.out.println(ex.getMessage());
            return null;
        }
        return urls;
    }

    /**
     * This method returns a list of URL checks.
     */
    @Override
    public List<UrlCheck> getUrlChecks() {
        List<UrlCheck> urlChecks;
        try {
            urlChecks = jdbc.query("select * from UrlChecks", new UrlCheckRowMapper());
        } catch (IncorrectResultSizeDataAccessException ex) {
            System.out.println("IncorrectResultSizeDataAccessException");
            System.out.println(ex.getMessage());
            return null;
        }
        return urlChecks;
    }

    /**
     * This is a helper class that converts jdbc records
     * to UserAccount object
     */
    private static final class AccountRowMapper implements RowMapper<UserAccount> {
        public UserAccount mapRow(ResultSet rs, int rowNum) throws SQLException {
            String name = rs.getString("user");
            String token = rs.getString("token");
            String email = rs.getString("email");
            boolean notifyUser = rs.getBoolean("notify");
            return new UserAccount(name, token, email, notifyUser);
        }
    }

    /**
     * This is a helper class that converts jdbc records
     * to EmailSettings object
     */
    private static final class EmailSettingsRowMapper implements RowMapper<EmailSettings> {
        public EmailSettings mapRow(ResultSet rs, int rowNum) throws SQLException {
            String host = rs.getString("host");
            int port = rs.getInt("port");
            String protocol = rs.getString("protocol");
            String username = rs.getString("username");
            String password = rs.getString("password");
            return new EmailSettings(host, port, protocol, username, password);
        }
    }

    /**
     * This is a helper class that converts jdbc records
     * to EmailProperty object
     */
    private static final class EmailPropertiesRowMapper implements RowMapper<EmailProperty> {
        public EmailProperty mapRow(ResultSet rs, int rowNum) throws SQLException {
            String name = rs.getString("name");
            String value = rs.getString("value");
            return new EmailProperty(name, value);
        }
    }

    /**
     * This is a helper class that converts jdbc records
     * to MonitoredUrl object
     */
    private static final class MonitoredUrlRowMapper implements RowMapper<MonitoredUrl> {
        public MonitoredUrl mapRow(ResultSet rs, int rowNum) throws SQLException {
            String url = rs.getString("url");
            int frequency = rs.getInt("frequency");
            int expectedStatus = rs.getInt("expectedStatus");
            String expectedString = rs.getString("expectedString");
            return new MonitoredUrl(url, frequency, expectedStatus, expectedString);
        }
    }

    /**
     * This is a helper class that converts jdbc records
     * to UrlCheck object
     */
    private static final class UrlCheckRowMapper implements RowMapper<UrlCheck> {
        public UrlCheck mapRow(ResultSet rs, int rowNum) throws SQLException {
            String url = rs.getString("url");
            LocalDateTime timeChecked = rs.getTimestamp("timeChecked").toLocalDateTime();
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("MM/dd/yyyy hh:mm:ss a");
            String formattedDateTime = timeChecked.format(formatter);
            int statusCode = rs.getInt("statusCode");
            String state = rs.getString("state");
            return new UrlCheck(url, formattedDateTime, statusCode, state);
        }
    }
}
