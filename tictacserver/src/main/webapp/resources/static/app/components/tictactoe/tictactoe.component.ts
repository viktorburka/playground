import {Component, OnInit} from '@angular/core';
import {Router} from '@angular/router';
import {Http} from '@angular/http';
import {FieldComponent} from '../field/field.component';

@Component({
    selector: 'tictactoe-game',
    template: `<router-outlet></router-outlet>`
})
export class TicTacToeComponent implements OnInit {
    
    constructor(private router: Router,
                private http: Http) {
    }

    ngOnInit() {
        this.router.navigate(['game']);
    }
}