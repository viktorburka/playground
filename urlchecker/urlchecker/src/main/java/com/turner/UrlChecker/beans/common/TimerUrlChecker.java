package com.turner.UrlChecker.beans.common;

import com.turner.UrlChecker.dbentities.*;
import com.turner.UrlChecker.exceptions.AuthFailedException;
import com.turner.UrlChecker.exceptions.IncorrectOperationException;
import com.turner.UrlChecker.interfaces.DataRepository;
import com.turner.UrlChecker.interfaces.UrlCheckerExecutorInterface;
import javafx.util.Pair;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.mail.MailException;
import org.springframework.mail.SimpleMailMessage;
import org.springframework.mail.javamail.JavaMailSender;
import org.springframework.mail.javamail.JavaMailSenderImpl;
import org.springframework.stereotype.Service;
import org.springframework.web.client.RestTemplate;

import javax.annotation.PreDestroy;
import java.util.*;

/**
 * This class implements url checker through timer.
 * Provides such operations as adding URLs, checks,
 * querying URLs and checks, starting checking job, etc.
 */
@Service
public class TimerUrlChecker implements UrlCheckerExecutorInterface {

    // list of jobs
    private List<Timer> timers;

    // map used for tracking number of failures
    private Map<TimerTask, Integer> failedChecks;

    // data access entity
    @Autowired
    DataRepository repository;

    TimerUrlChecker() {
        timers = Collections.synchronizedList(new LinkedList<>());
        failedChecks = Collections.synchronizedMap(new HashMap<>());
    }

    /**
     * This method will be called upon bean deallocation.
     * It is necessary to stop the timers for monitoring URLs.
     */
    @PreDestroy
    public void destroy() {
        // since we may have up to 10 tasks, iterate over the list
        // and shut down each of them for proper resources deallocation
        Iterator iterator = timers.iterator();
        while (iterator.hasNext()) {
            Timer t = (Timer)iterator.next();
            t.cancel();
        }
        System.out.println("TimerUrlChecker: destroy bean");
    }

    /**
     * Add URL being checked to the database.
     * @param url The URL to be added
     * @param freq The frequency in seconds
     * @param expCode The expected return code
     * @param expString The expected string. It can be optional
     */
    @Override
    public void addUrl(String url, int freq, int expCode, String expString) {
        repository.addUrl(url, freq, expCode, expString);
    }

    /**
     * Start checking URL. If number of URLs is more than 10,
     * no new URLs will be added. If number of consecutive failures
     * is 3 and an option to send notification email is set,
     * an email will be sent notifying the user that 3 consecutive
     * failures have happened.
     * @param url The URL to be added
     * @param freq The frequency in seconds
     * @param expCode The expected return code
     * @param expString The expected string. It can be optional
     * @param token The token of the user who added the check
     */
    @Override
    public void checkUrl(String url, int freq, int expCode,
                         String expString, String token) {

        // get user account and check whether send
        // notification email option is set
        UserAccount p = this.repository.login(token);
        final boolean sendEmail = p.isNotify();

        // check max 10 checkers limitation

        if (timers.size() == 10) {
            System.out.println("Maximum number of url checkers has been reached !");
            throw new IncorrectOperationException("Maximum number of url checkers has been reached !");
        }

        // do values check

        if (url.isEmpty()) {
            System.out.println("Passed URL is empty!");
            throw new IncorrectOperationException("Passed URL is empty!");
        }

        if (freq <= 0) {
            System.out.println("Passed frequency is incorrect!");
            throw new IncorrectOperationException("Passed frequency is incorrect!");
        } else if (freq > 3600) {
            System.out.println("Will continue but frequency value seems too large");
        }

        if (expCode < 100 || expCode >= 600) {
            System.out.println("Passed expected return code is incorrect!");
            throw new IncorrectOperationException("Passed expected return code is incorrect!");
        }

        // create timer and add to the list of jobs
        Timer timer = new Timer();
        timers.add(timer);

        TimerTask task = new TimerTask() {

            @Override
            public void run() {

                // call get on the URL
                RestTemplate restTemplate = new RestTemplate();
                ResponseEntity<String> result = restTemplate.getForEntity(url, String.class);

                // check whether returned status code matches the expected
                int statusCode = result.getStatusCode().value();
                boolean success = isCorrect(statusCode, expCode, result.getBody(), expString);

                // save URL check to the database
                repository.addCheckResult(url, statusCode, success ? "SUCCESS" : "FAILURE");

                if (!success) {
                    int counter = failedChecks.get(this);
                    System.out.printf("Counter: %d\n", counter);
                    counter += 1;
                    if (counter == 3 && sendEmail) {
                        // if 3 consecutive failures and send
                        // email option is set
                        sendEmail(url);
                    } else {
                        // increment number of consecutive failures
                        failedChecks.put(this, counter);
                    }
                } else {
                    // if success, reset number of consecutive failures
                    failedChecks.put(this, 0);
                }
            }
        };

        // add the task to monitor for failures
        failedChecks.put(task, 0);

        // start the task
        timer.schedule(task, 0, freq * 1000);
    }

    /**
     * This method returns a list of monitored URLs.
     */
    public List<MonitoredUrl> getMonitoredUrls() {
        return this.repository.getMonitoredUrls();
    }

    /**
     * This method returns a list URL checks.
     */
    public List<UrlCheck> getUrlChecks() {
        return this.repository.getUrlChecks();
    }

    /**
     * This method sends an email to the user
     * notifying about URL checks failed for
     * 3 consecutive times.
     */
    private void sendEmail(String failedUrl) {

        // get email settings from the database
        EmailSettings es = repository.getEmailSettings();
        List<EmailProperty> ep = repository.getEmailProperties();

        JavaMailSenderImpl mailSender = new JavaMailSenderImpl();

        Properties sendProperties = new Properties();

        // set send properties
        Iterator<EmailProperty> iterator = ep.iterator();
        while (iterator.hasNext()) {
            EmailProperty p = iterator.next();
            sendProperties.setProperty(p.getName(), p.getValue());
            System.out.printf("name: %s, value: %s\n", p.getName(), p.getValue());
        }

        // set email settings
        mailSender.setHost(es.getHost());
        mailSender.setPort(es.getPort());
        mailSender.setProtocol(es.getProtocol());
        mailSender.setUsername(es.getUsername());
        mailSender.setPassword(es.getPassword());
        mailSender.setJavaMailProperties(sendProperties);

        System.out.println(es.getHost());
        System.out.println(es.getPort());
        System.out.println(es.getProtocol());
        System.out.println(es.getUsername());
        System.out.println(es.getPassword());

        SimpleMailMessage message = new SimpleMailMessage();

        // build text of email message
        String text = String.format("%s%s%s%s",
                "Hello,\r\n\r\n",
                "UrlChecker has encountered 3 consecutive status failures for ",
                failedUrl,
                "\r\n\r\nSincerely yours,\nUrlChecker");

        // set email attributes
        message.setFrom("john.ow.richard@gmail.com");
        message.setTo("burka.victor@gmail.com");
        message.setSubject("UrlChecker notification");
        message.setText(text);

        // send email
        try {
            mailSender.send(message);
        } catch (MailException ex) {
            System.out.println("MailException");
            System.out.println(ex.getMessage());
        }
    }

    /**
     * This method checks whether actual code
     * matches expected code and if expected
     * string is provided, whether it matches
     * the actual response string.
     */
    private boolean isCorrect(int receivedCode, int expectedCode,
                              String receivedString, String expectedString) {
        boolean result = (receivedCode == expectedCode);
        // check result string only if expected string is specified i.e. its length > 0
        if (expectedString.length() != 0) {
            result = result && receivedString.equals(expectedString);
        }
        return result;
    }
}
