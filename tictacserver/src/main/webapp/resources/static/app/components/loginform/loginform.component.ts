import {Component} from '@angular/core';
import {Router} from '@angular/router';
import {Http,RequestOptions,Headers} from '@angular/http';

@Component({
    selector: 'loginform',
    templateUrl: 'app/components/loginform/loginform.html'
})
export class LoginFormComponent {

    errMsgHidden: boolean = false;
    errMsg: string;
    
    constructor(private router: Router,
                private http: Http) {
    }

    submit(login: string, password: string): void {
        var json = `{"login": "${login}", "password": "${password}"}`;
        let h = new Headers({'Content-Type': 'application/json'});
        let opt = new RequestOptions({headers: h});
        this.http.post('/TicTacServer-1.0/services/Rest/login', json, opt)
                 .subscribe(r => { this.loginSuccessful(r.status); },
                            r => { this.loginFailed(r.status) });
    }

    isErroMsgHidden(): boolean {
        return this.errMsgHidden;
    }

    private loginSuccessful(statusCode: Number): void {
        console.log("loginSuccessful, status: ", statusCode);
        this.errMsgHidden = true;
    }

    private loginFailed(statusCode: Number) {
        console.log("loginFailed: ", statusCode);
        this.errMsgHidden = false;
        if (statusCode == 404) {
            this.errMsg = "Invalid login/password";
        } else {
            this.errMsg = "Authentication error";
        }
    }
}