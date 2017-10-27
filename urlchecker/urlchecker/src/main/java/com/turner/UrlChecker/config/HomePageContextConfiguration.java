package com.turner.UrlChecker.config;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.ViewResolver;
import org.springframework.web.servlet.config.annotation.DefaultServletHandlerConfigurer;
import org.springframework.web.servlet.config.annotation.EnableWebMvc;
import org.springframework.web.servlet.config.annotation.ResourceHandlerRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurerAdapter;
import org.springframework.web.servlet.view.InternalResourceViewResolver;

/**
 * This class implements HTML come page
 * context.
 */
@EnableWebMvc
@Configuration
@ComponentScan(basePackages = "com.turner.UrlChecker.beans.home")
public class HomePageContextConfiguration extends WebMvcConfigurerAdapter {

    /**
     * This method registers redirects for static content
     * such as HTML
     */
    @Override
    public void addResourceHandlers(ResourceHandlerRegistry registry) {
        registry.addResourceHandler("/node_modules/**")
                .addResourceLocations("/resources/static/node_modules/");
        registry.addResourceHandler("/**")
                .addResourceLocations("/resources/static/");
    }

    @Override
    public void configureDefaultServletHandling(DefaultServletHandlerConfigurer configurer) {
        configurer.enable();
    }

    /**
     * This method registers model for home HTML page.
     */
    @Bean
    public ViewResolver getViewResolver() {
        InternalResourceViewResolver resolver = new InternalResourceViewResolver();
        resolver.setPrefix("/WEB-INF/jsp/");
        resolver.setSuffix(".jsp");
        return resolver;
    }
}