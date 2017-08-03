package com.tictac.TicTacServer.config;

import org.springframework.web.WebApplicationInitializer;
import org.springframework.web.context.support.AnnotationConfigWebApplicationContext;
import org.springframework.web.servlet.DispatcherServlet;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.ServletRegistration;

public class Bootstrap implements WebApplicationInitializer {

    public void onStartup(ServletContext container) throws ServletException
    {
        //container.getServletRegistration("default").addMapping("/resource/*");

        ServletRegistration.Dynamic dispatcher;

        AnnotationConfigWebApplicationContext homePageContext =
                new AnnotationConfigWebApplicationContext();
        homePageContext.register(HomePageContextConfiguration.class);

        dispatcher = container.addServlet("homePageViewDispatcher", new DispatcherServlet(homePageContext));
        dispatcher.setLoadOnStartup(1);
        dispatcher.addMapping("/");

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
