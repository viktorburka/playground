package com.tictac.TicTacServer;

public class GameServer
{
	private WebChannel channel;
	
	public GameServer(WebChannel channel) {
		this.channel = channel;
	}
	
	public void run() {
		System.out.println(this.channel.name());
	}
}