import { Component, AfterViewInit } from '@angular/core';
import { Http, RequestOptions, Headers } from '@angular/http';

@Component({
    selector: 'app-root',
    templateUrl: './app.component.html'
})
export class AppComponent {
    title = 'app';

    errMsgHidden: boolean = true;
    errMsg: string = "Error!";

    urls: any[] = [];
    urlChecks: any[] = [];

    constructor(private http: Http) {
    }

    ngAfterViewInit() {
        this.getValues();
    }

    public getValues(): void {
        this.urls = [];
        this.getUrls('/api/urls/?format=json');
        this.urlChecks = [];
        this.getUrlChecks('/api/urlchecks/?format=json');
    }

    public isErroMsgHidden(): boolean {
        return this.errMsgHidden;
    }

    private getUrls(url): void {
        this.http.get(url)
            .subscribe(r => { this.urlOperationSuccessful(r.status, r.json()); },
            r => { this.operationFailed(r.status) });
    }

    private getUrlChecks(url): void {
        this.http.get(url)
            .subscribe(r => { this.checkOperationSuccessful(r.status, r.json()); },
            r => { this.operationFailed(r.status) });
    }

    private urlOperationSuccessful(statusCode: number, json: any): void {
        console.log("operationSuccessful, status: ", statusCode);
        console.log("operationSuccessful, json: ", json);
        this.errMsgHidden = true;
        this.urls = this.urls.concat(json.objects);
        if (json.meta.next) {
            this.getUrls(json.meta.next);
        }
    }

    private checkOperationSuccessful(statusCode: number, json: any): void {
        console.log("operationSuccessful, status: ", statusCode);
        console.log("operationSuccessful, json: ", json);
        this.errMsgHidden = true;
        this.urlChecks = this.urlChecks.concat(json.objects);
        if (json.meta.next) {
            this.getUrlChecks(json.meta.next);
        }
    }

    private operationFailed(statusCode: number) {
        console.log("operationFailed: ", statusCode);
        this.errMsgHidden = false;
        this.errMsg = `Communication error: ${statusCode}`;
    }

    private populate(): void {
        this.urls = [{
            url: "http://www.google.com",
            freq: 3,
            expStatus: 200,
            expString: ""
        },
        {
            url: "http://www.turner.com",
            freq: 5,
            expStatus: 200,
            expString: ""
        }]

        for (var i = 0; i < 8; i++) {
            this.urls.push({
                url: "http://www.turner.com",
                freq: 5,
                expStatus: 200,
                expString: ""
            });
        }

        this.urlChecks = [{
            url: "http://www.google.com",
            timeChecked: "11:45:12",
            statusCode: 200,
            state: "SUCCESS"
        },
        {
            url: "http://www.turner.com",
            timeChecked: "12:32:12",
            statusCode: 200,
            state: "SUCCESS"
        }]

        for (var i = 0; i < 200; i++) {
            this.urlChecks.push({
                url: "http://www.turner.com",
                timeChecked: "12:32:12",
                statusCode: 200,
                state: "SUCCESS"
            });
        }
    }
}
