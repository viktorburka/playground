create table if not exists "email_settings" (
	"id" integer NOT NULL PRIMARY KEY AUTOINCREMENT,
	"email" text NOT NULL,
	"password" text NOT NULL,
	"smtpHost" text NOT NULL,
	"smtpPort" integer NOT NULL,
	"tls" integer NOT NULL,
	"notify" integer NOT NULL
);

insert into email_settings (email, password, smtpHost, smtpPort, tls, notify)
                    values ('john.ow.richard@gmail.com', '', 'smtp.gmail.com', 587, 1, 1);

select * from email_settings;