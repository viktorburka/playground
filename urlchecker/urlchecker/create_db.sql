CREATE DATABASE IF NOT EXISTS UrlChecker;

use UrlChecker;

CREATE USER IF NOT EXISTS 'victor'@'localhost' IDENTIFIED BY '';

GRANT ALL PRIVILEGES ON * . * TO 'victor'@'localhost';
FLUSH PRIVILEGES;

CREATE TABLE IF NOT EXISTS `Urls`(`id` int unsigned NOT NULL AUTO_INCREMENT, 
								  `url` varchar(10000) NOT NULL,
								  `frequency` int unsigned NOT NULL,
								  `expectedStatus` int unsigned NOT NULL,
								  `expectedString` varchar(10000) DEFAULT NULL,
								  PRIMARY KEY (`id`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE IF NOT EXISTS `UrlChecks`(`id` int unsigned NOT NULL AUTO_INCREMENT, 
									   `url` varchar(10000) NOT NULL,
									   `timeChecked` datetime NOT NULL,
									   `statusCode` int unsigned NOT NULL,
									   `state` varchar(10) NOT NULL,
									   PRIMARY KEY (`id`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE IF NOT EXISTS `Auth`(`id` int unsigned NOT NULL AUTO_INCREMENT, 
								  `user` varchar(100) NOT NULL,
								  `token` varchar(100) NOT NULL,
								  `email` varchar(100) NOT NULL,
								  `notify` boolean NOT NULL,
								  PRIMARY KEY (`id`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE IF NOT EXISTS `EmailSettings`(`id` int unsigned NOT NULL AUTO_INCREMENT, 
										   `host` varchar(100) NOT NULL,
										   `port` int unsigned NOT NULL,
										   `protocol` varchar(100) NOT NULL,
										   `username` varchar(100) NOT NULL,
										   `password` varchar(100) NOT NULL,
										   PRIMARY KEY (`id`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
                             
CREATE TABLE IF NOT EXISTS `EmailProperties`(`id` int unsigned NOT NULL AUTO_INCREMENT, 
											 `name` varchar(100) NOT NULL,
											 `value` varchar(100) NOT NULL,
											 PRIMARY KEY (`id`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8;

# user name (any);
# API Key;
# email a notification about 3 failures will be sent to;
# flag whether to send email or not (only 0 or 1)
insert into Auth (user, token, email, notify) values ("victor", "1234-5678-9012-3456", "burka.victor@gmail.com", 0);

# smtp server;
# port;
# protocol;
# login;
# password;
insert into EmailSettings (host, port, protocol, username, password) values ("smtp.gmail.com", 587, "smtp", "john.ow.richard@gmail.com", "");

insert into EmailProperties (name, value) values ("mail.smtp.auth", "true");
insert into EmailProperties (name, value) values ("mail.smtp.starttls.enable", "true");
insert into EmailProperties (name, value) values ("mail.transport.protocol", "smtp");
insert into EmailProperties (name, value) values ("mail.smtp.connectiontimeout", "3000");
insert into EmailProperties (name, value) values ("mail.smtp.timeout", "3000");

Select * from Urls;
Select * from UrlChecks;
select * from Auth;
Select * from EmailSettings;
Select * from EmailProperties;