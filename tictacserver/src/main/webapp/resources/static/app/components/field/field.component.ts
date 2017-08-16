import {Component, AfterViewInit} from '@angular/core';
import {Http} from '@angular/http';
import {GameButton} from '../gamebutton/gamebutton.component';
import {GameLogic} from '../../gamelogic';
import {Observable} from 'rxjs/Rx';

@Component({
    selector: 'field',
    templateUrl: 'app/components/field/field.html'
})
export class FieldComponent implements AfterViewInit {

    private message: String;
    private timer: any;
    private sub: any;

    constructor(private http: Http,
                private gameLogic: GameLogic) {        
    }

    ngAfterViewInit() {
        this.message = 'Waiting for game to load...';
        this.gameLogic.blocked = true;
        this.http.get('/TicTacServer-1.0/services/Rest/currentplayer')
                 .map(res => res.json())
                 .subscribe(d => { console.log("currentplayer: " + d.player);
                                   this.play(d.player, true); });
    }

    private play(player: String, firstTime: Boolean) {
        if (this.gameLogic.playerName == player) {
            this.sub.unsubscribe();
            this.gameLogic.blocked = false;
            this.message = 'Your turn to click!';
        } else {
            this.gameLogic.blocked = true;
            this.message = 'Waiting for the other player to click...';
            if (firstTime) {
                this.timer = Observable.timer(1000,1000);
                this.sub = this.timer.subscribe( t => { this.pollGameStatus(); });
            }
        }
    }

    private pollGameStatus() {
        console.log("before poll game status");
        this.http.get('/TicTacServer-1.0/services/Rest/currentplayer')
                 .map(res => res.json())
                 .subscribe(d => { console.log("poll game status: " + d.player);
                                   this.play(d.player, false); });
    }
}