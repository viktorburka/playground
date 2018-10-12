package com.webtechexplorer.springhttps.client;

import org.apache.http.HttpEntity;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.util.EntityUtils;

public class Application {

	public static void main(String[] args) {

		CloseableHttpClient httpclient = HttpClients.createDefault();

		HttpGet httpGet = new HttpGet("https://localhost:8443/health");

		try (CloseableHttpResponse response = httpclient.execute(httpGet)) {

			HttpEntity entity = response.getEntity();

	        System.out.println(response.getStatusLine());

			EntityUtils.consume(entity);

		} catch (Exception e) {
			System.err.println("Http request error: " + e.getMessage());
			return;
		}
	}

}
