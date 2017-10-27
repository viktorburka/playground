import {Component, AfterViewInit } from '@angular/core';
import {Http,RequestOptions,Headers} from '@angular/http';

@Component({
    selector: 'urlchecker',
    templateUrl: 'app/components/databaseview/databaseview.html'
})
export class DatabaseViewComponent implements AfterViewInit {

    errMsgHidden: boolean = true;
    errMsg: string = "Error!";

    urls: [{
        url: string,
        frequency: number,
        expectedStatus: number,
        expectedString: string
    }];

    urlChecks: [{
        url: string,
        timeChecked: string,
        statusCode: number,
        state: string
    }];
    
    constructor(private http: Http) {
    }

    ngAfterViewInit() {
        this.getValues();
    }

    public getValues(): void {
        //this.populate();
        this.http.get('/UrlChecker-1.0/services/Rest/urls')
                 .subscribe(r => { this.urlOperationSuccessful(r.status, r.json()); },
                            r => { this.operationFailed(r.status) });
        this.http.get('/UrlChecker-1.0/services/Rest/urlchecks')
                 .subscribe(r => { this.checkOperationSuccessful(r.status, r.json()); },
                            r => { this.operationFailed(r.status) });
    }

    public isErroMsgHidden(): boolean {
        return this.errMsgHidden;
    }

    private urlOperationSuccessful(statusCode: number, json: any): void {
        console.log("operationSuccessful, status: ", statusCode);
        console.log("operationSuccessful, json: ", json);
        this.errMsgHidden = true;
        this.urls = json;
    }

    private checkOperationSuccessful(statusCode: number, json: any): void {
        console.log("operationSuccessful, status: ", statusCode);
        console.log("operationSuccessful, json: ", json);
        this.errMsgHidden = true;
        this.urlChecks = json;
    }

    private operationFailed(statusCode: number) {
        console.log("operationFailed: ", statusCode);
        this.errMsgHidden = false;
        if (statusCode == 404) {
            this.errMsg = "Invalid login/password";
        } else {
            this.errMsg = "Authentication error";
        }
    }

    private populate(): void {
        this.urls = [{
            url : "http://www.google.com",
            frequency: 3,
            expectedStatus : 200,
            expectedString : ""
        },
        {
            url : "http://www.turner.com",
            frequency: 5,
            expectedStatus : 200,
            expectedString : ""
        }]

        for (var i = 0; i < 8; i++) {
            this.urls.push({
                    url : "http://www.turner.com",
                    frequency: 5,
                    expectedStatus : 200,
                    expectedString : ""
                });
        }

        this.urlChecks = [{
            url : "http://www.google.com",
            timeChecked: "11:45:12",
            statusCode : 200,
            state : "SUCCESS"
        },
        {
            url : "http://www.turner.com",
            timeChecked: "12:32:12",
            statusCode : 200,
            state : "SUCCESS"
        }]

        for (var i = 0; i < 200; i++) {
            this.urlChecks.push({
                url : "http://www.turner.com",
                timeChecked: "12:32:12",
                statusCode : 200,
                state : "SUCCESS"
            });
        }
    }
}