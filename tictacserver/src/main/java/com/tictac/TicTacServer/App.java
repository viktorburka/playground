package com.tictac.TicTacServer;

import org.springframework.context.support.ClassPathXmlApplicationContext;

public class App 
{
    public static void main( String[] args )
    {
		ClassPathXmlApplicationContext context = 
		    new ClassPathXmlApplicationContext("tictacserver.xml");
		GameServer server = context.getBean(GameServer.class);
		server.run();
        System.out.println( "Hello World!" );
    }
}
