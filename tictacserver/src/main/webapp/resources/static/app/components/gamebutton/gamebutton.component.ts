import {Component, Input, Output, EventEmitter} from '@angular/core';
import {Http} from '@angular/http';
import {GameLogic} from '../../gamelogic';
import {PlayerAction} from '../../gamelogic';
import {GameResult} from '../../gamelogic';
import {Observable} from "rxjs/Observable";
import 'rxjs/add/operator/map';

@Component({
    selector: 'gamebutton',
    styleUrls: ['app/components/gamebutton/gamebutton.css'],
    template: `<button
                id="gamebutton"
                [style.background-image]="getBackgroundColor()"
                (click)="buttonClicked()">
               </button>`
})
export class GameButton {
    @Input() position: string;

    constructor(private gameLogic: GameLogic,
                private http: Http) {
    }

    getBackgroundColor(): string {
        return this.gameLogic.buttonColor(this.position);
    }
    
    buttonClicked() {
        console.log("Position: " + this.position);
        this.gameLogic.onLastPositionChanged(this.position);
        if (this.gameLogic.state == GameResult.Continue) {
            this.http.post('/TicTacServer-1.0/services/Rest/products', '{}')
                     .map(res => res.json())
                     .subscribe(d => { console.log("command: " + d.command + ", parameter: " + d.commandParameter); });
        }
    }
}