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
                [disabled]="isButtonDisabled()"
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

    isButtonDisabled(): Boolean {
        return this.gameLogic.blocked;
    }
    
    buttonClicked() {
        console.log("Position: " + this.position);
        //this.gameLogic.onLastPositionChanged(this.position);
        if (this.gameLogic.state == GameResult.Continue) {
            var player = this.gameLogic.playerName;
            var row: number = Number(this.position.charAt(0));
            var col: number = Number(this.position.charAt(1));
            var pos: String = row + "," + col;
            var json = `{"player": "${player}",
                         "pos": "${pos}"}`;
            this.http.post('/TicTacServer-1.0/services/Rest/move', json)
                     .map(res => res.json())
                     .subscribe(d => { console.log("pos: " + d.pos + ", type: " + d.type); 
                                       this.updateField(d.pos, d.type, d.game); });
        }
    }

    private updateField(pos: String, type: String, game: String) {
        this.gameLogic.move(this.position);
        this.checkGameResult(game);
    }

    private checkGameResult(result: String) {
        if (result == "won") {
            console.log("Player " + this.gameLogic.playerName + " won!");
        } else if (result == "continue") {
            this.switchPlayer();
        } else {
            console.log("Tie! Everyone did great. Try again");
        }
        this.state = result;
    }

}