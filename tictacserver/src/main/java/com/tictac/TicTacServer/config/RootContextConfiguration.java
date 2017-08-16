package com.tictac.TicTacServer.config;

import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;

@Configuration
@ComponentScan(basePackages = "com.tictac.TicTacServer.beans.common")
public class RootContextConfiguration {

}
