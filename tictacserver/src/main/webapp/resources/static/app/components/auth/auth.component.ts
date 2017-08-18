import {Component} from '@angular/core';
import {Router} from '@angular/router';
import {Http} from '@angular/http';

@Component({
    selector: 'authentication',
    template: `<router-outlet></router-outlet>`
})
export class AuthComponent {
    
    constructor(private router: Router,
                private http: Http) {
    }
}