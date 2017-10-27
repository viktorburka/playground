package com.turner.UrlChecker;

import com.turner.UrlChecker.config.HomePageContextConfiguration;
import com.turner.UrlChecker.config.RestServletContextConfiguration;
import com.turner.UrlChecker.config.RootContextConfiguration;
import org.springframework.web.WebApplicationInitializer;
import org.springframework.web.context.ContextLoaderListener;
import org.springframework.web.context.support.AnnotationConfigWebApplicationContext;
import org.springframework.web.servlet.DispatcherServlet;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.ServletRegistration;

/**
 * This class boostraps the application. It creates proper
 * Spring context configuration classes that in its turn
 * instantiate helper and business logic beans.
 */
public class Bootstrap implements WebApplicationInitializer {

    /**
     * This method creates appropriate Spring context and
     * beans to boostrap the application.
     * @param container The web application servlet context
     */
    public void onStartup(ServletContext container) throws ServletException
    {
        ServletRegistration.Dynamic dispatcher;

        // root context
        AnnotationConfigWebApplicationContext rootContext =
                new AnnotationConfigWebApplicationContext();
        rootContext.register(RootContextConfiguration.class);
        container.addListener(new ContextLoaderListener(rootContext));

        // static web context
        AnnotationConfigWebApplicationContext homePageContext =
                new AnnotationConfigWebApplicationContext();
        homePageContext.register(HomePageContextConfiguration.class);

        dispatcher = container.addServlet("homePageViewDispatcher", new DispatcherServlet(homePageContext));
        dispatcher.setLoadOnStartup(1);
        dispatcher.addMapping("/");

        // REST context
        AnnotationConfigWebApplicationContext restContext =
                new AnnotationConfigWebApplicationContext();
        restContext.register(RestServletContextConfiguration.class);

        dispatcher = container.addServlet("springRestDispatcher", new DispatcherServlet(restContext));
        dispatcher.setLoadOnStartup(2);
        dispatcher.addMapping("/services/Rest/*");
    }
}
