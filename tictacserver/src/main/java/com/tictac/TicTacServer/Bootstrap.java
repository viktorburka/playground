package com.tictac.TicTacServer;

import com.tictac.TicTacServer.config.HomePageContextConfiguration;
import com.tictac.TicTacServer.config.RestServletContextConfiguration;
import com.tictac.TicTacServer.config.RootContextConfiguration;
import org.springframework.web.WebApplicationInitializer;
import org.springframework.web.context.ContextLoaderListener;
import org.springframework.web.context.support.AnnotationConfigWebApplicationContext;
import org.springframework.web.servlet.DispatcherServlet;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.ServletRegistration;

public class Bootstrap implements WebApplicationInitializer {

    public void onStartup(ServletContext container) throws ServletException
    {
        ServletRegistration.Dynamic dispatcher;

        // root context
        AnnotationConfigWebApplicationContext rootContext =
                new AnnotationConfigWebApplicationContext();
        rootContext.register(RootContextConfiguration.class);
        container.addListener(new ContextLoaderListener(rootContext));

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

        DispatcherServlet servlet = new DispatcherServlet(restContext);
        servlet.setDispatchOptionsRequest(true);

        dispatcher = container.addServlet("springRestDispatcher", servlet);
        dispatcher.setLoadOnStartup(2);
        dispatcher.addMapping("/services/Rest/*");
    }
}
