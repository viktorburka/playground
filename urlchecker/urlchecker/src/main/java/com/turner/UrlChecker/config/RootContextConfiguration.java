package com.turner.UrlChecker.config;

import org.springframework.context.annotation.AdviceMode;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.core.Ordered;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.datasource.DriverManagerDataSource;
import org.springframework.transaction.annotation.EnableTransactionManagement;

import javax.sql.DataSource;

/**
 * This class implements Spring root context
 * and bootstraps the application.
 */
@Configuration
@ComponentScan(basePackages = "com.turner.UrlChecker.beans.common")
@EnableTransactionManagement(
        mode = AdviceMode.PROXY, proxyTargetClass = false,
        order = Ordered.LOWEST_PRECEDENCE
)
public class RootContextConfiguration
{
    /**
     * This method creates JDBC data source bean
     * used by JdbcTemplate entity.
     */
    @Bean
    public DataSource dataSource() {
        DriverManagerDataSource ds = new DriverManagerDataSource();
        ds.setDriverClassName("com.mysql.jdbc.Driver");
        ds.setUrl("jdbc:mysql://localhost:3306/UrlChecker");
        ds.setUsername("victor");
        ds.setPassword("");
        return ds;
    }

    /**
     * This method creates JdbcTemplate, the main
     * entity for SQL database operations.
     */
    @Bean
    public JdbcTemplate jdbcTemplate(DataSource dataSource) {
        return new JdbcTemplate(dataSource);
    }
}
