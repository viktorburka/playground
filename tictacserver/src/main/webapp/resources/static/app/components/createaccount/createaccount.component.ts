import {Component} from '@angular/core';
import {Router} from '@angular/router';
import {Http,RequestOptions,Headers} from '@angular/http';

@Component({
    selector: 'create-account',
    templateUrl: 'app/components/createaccount/createaccount.html'
})
export class CreateAccountComponent {

    errMsgHidden: boolean = false;
    errMsg: string;

    isErroMsgHidden(): boolean {
        return this.errMsgHidden;
    }

    createAccount(login: string, password: string,
                  firstName: string, lastName: string) {
                    
    }
}