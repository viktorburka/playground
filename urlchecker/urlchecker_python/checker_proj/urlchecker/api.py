from tastypie.resources import ModelResource
from tastypie.constants import ALL
from tastypie.authentication import Authentication, ApiKeyAuthentication
from tastypie.authorization import Authorization

import time
import sys
import json
import sqlite3
import httplib
import datetime
import smtplib
import os
    
from email.MIMEMultipart import MIMEMultipart
from email.MIMEText import MIMEText
from threading import Thread

from models import Urls, UrlChecks

class WorkerThread(Thread):
    #def __init__(self):
    #    Thread.__init__(self)

    url = ""
    freq = 1 # 1 sec timeout by default
    expCode = 200
    expString = ""
    numberOfFailures = 0
    email = ""

    def setUrl(self, url):
        self.url = url

    def setFrequency(self, freq):
        self.freq = freq

    def setExpectedCode(self, expCode):
        self.expCode = expCode

    def setExpectedString(self, expString):
        self.expString = expString

    def setNotificationEmail(self, email):
        self.email = email
 
    def run(self):
        while(1):
            print >>sys.stderr, self.getName()

            conn = httplib.HTTPSConnection(self.url)
            conn.request("GET", "/")
            
            response = conn.getresponse()
            timeNow = datetime.datetime.now().strftime("%x %X %p")
            success = self.successOrFailure(response.status, self.expCode,
                                            response.read(), self.expString)
            if not success:
                self.numberOfFailures += 1
            else:
                self.numberOfFailures = 0
            
            values = [self.url, timeNow, response.status,
                      "SUCCESS" if success else "FAILURE"]
            print >>sys.stderr, values
            
            self.saveToDatabase(values)

            if self.numberOfFailures == 3:
                self.sendEmail(self.email, self.url)
                self.numberOfFailures = 0

            time.sleep(self.freq)

    def saveToDatabase(self, values):

        conn = sqlite3.connect('db.sqlite3')
        c = conn.cursor()
        c.execute("insert into urlchecker_urlchecks (url, timeChecked, statusCode, state) values (?,?,?,?)", values)
        conn.commit()
        conn.close()

    def successOrFailure(self, actualStatus, expectedStatus,
                         actualString, expectedString):
        result = (actualStatus == expectedStatus)
        if len(expectedString) > 0:
            result = result and (actualString == expectedString)
        return result

    def sendEmail(self, recipient, url):

        conn = sqlite3.connect('db.sqlite3')
        cursor = conn.cursor()
        cursor.execute('select * from email_settings')
        settings = cursor.fetchone()
        
        print >>sys.stderr, "Len:"
        print >>sys.stderr, settings

        user     = settings[1]
        password = settings[2]
        host     = settings[3]
        port     = settings[4]
        tls      = settings[5]
        notify   = settings[6]

        print >>sys.stderr, "Settings: ", user, password, host, port, tls, notify

        if not notify:
            return

        #recipient = 'burka.victor@gmail.com'
        message = """
        Hello,

        UrlChecker has encountered 3 consecutive status failures for %(url)s

        Sincerely yours,
        UrlChecker
        """ % {'url': url}

        msg = MIMEMultipart()
        msg['From'] = user
        msg['To'] = recipient
        msg['Subject'] = "UrlChecker notification"
        msg.attach(MIMEText(message))

        print >>sys.stderr, "Sending email..."
        mailServer = smtplib.SMTP(host, port)
        if tls:
            mailServer.ehlo()
            mailServer.starttls()
            mailServer.ehlo()
        mailServer.login(user, password)
        mailServer.sendmail(user, recipient, msg.as_string())
        mailServer.close()

class ResigsterUrlResource(ModelResource):
    class Meta:
        queryset = Urls.objects.all()
        resource_name = 'registerurl'
        authentication = ApiKeyAuthentication()
        allowed_methods = ['post']
        authorization = Authorization()

    jobs = []

    def post_list(self, request, **kwargs):

        #print >>sys.stderr, request.user, request.user.email

        #TO-DO: return error code or throw exception
        if len(self.jobs) == 10:
            print >>sys.stderr, "Maximum number of checks (10) is reached"
            return super(ResigsterUrlResource, self).post_list(request)

        body_unicode = request.body.decode('utf-8')
        body = json.loads(body_unicode)
        url = body['url']
        freq = body['freq']
        expCode = body['expCode']
        expString = body['expString']

        print >>sys.stderr, "url: ", url

        thread = WorkerThread()
        self.jobs.append([thread])

        thread.setName('Thread ' + str(len(self.jobs)))
        thread.setUrl(url)
        thread.setFrequency(freq)
        thread.setExpectedCode(expCode)
        thread.setExpectedString(expString)
        thread.setNotificationEmail(request.user.email)

        thread.start()

        return super(ResigsterUrlResource, self).post_list(request)

class UrlsResource(ModelResource):
    class Meta:
        queryset = Urls.objects.all()
        resource_name = 'urls'
        authentication = Authentication()
        allowed_methods = ['get']
        #authorization = Authorization()

    # def get_list(self, request, **kwargs):
    #     print >>sys.stderr, 'get_list'
    #     return super(UrlsResource, self).get_list(request)

class UrlChecksResource(ModelResource):
    class Meta:
        queryset = UrlChecks.objects.all()
        resource_name = 'urlchecks'
        authentication = Authentication()
        allowed_methods = ['get']
        #authorization = Authorization()
