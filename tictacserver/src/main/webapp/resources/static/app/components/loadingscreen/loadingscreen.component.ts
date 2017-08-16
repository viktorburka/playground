import {Component, AfterViewInit } from '@angular/core';
import {ActivatedRoute} from '@angular/router';
import {Http} from '@angular/http';
import {Router} from '@angular/router';
import {Observable} from 'rxjs/Rx';
import {GameLogic} from '../../gamelogic';

@Component({
    selector: 'loading-screen',
    styleUrls: ['app/components/loadingscreen/loadingscreen.css'],
    templateUrl: 'app/components/loadingscreen/loadingscreen.html'
})
export class LoadingScreenComponent implements AfterViewInit {

    private state: Number;
    private message: String;
    private timer: any;
    private sub: any;

    constructor(private http: Http,
                private router: Router,
                private gameLogic: GameLogic) {
    }

    ngAfterViewInit() {
        this.message = 'Loading game...';
        this.http.get('/TicTacServer-1.0/services/Rest/gamestatus')
                 .map(res => res.json())
                 .subscribe(d => { console.log("gamestatus: " + d.status);
                                   this.startGame(d.status); });
    }

    private startGame(status: String) {

        if (status == "GameOn") {
            this.message = 'Game server players capacity is maxed out. Please try again later';
        }
        else if (status == "Player2Required") {
            this.http.get('/TicTacServer-1.0/services/Rest/join')
                 .map(res => res.json())
                 .subscribe(d => { this.gameLogic.playerName = 'Player_2'; this.router.navigate(['/game']); });
        }
        else if (status == "Available") {
            console.log('Trying to join the game');
            this.http.get('/TicTacServer-1.0/services/Rest/join')
                 .map(res => res.json())
                 .subscribe(d => { this.gameLogic.playerName = 'Player_1';
                                   this.message = 'Waiting for the Player 2 to join...';
                                   this.timer = Observable.timer(1000,5000);
                                   this.sub = this.timer.subscribe( t => { this.pollGameStatus(); });
                 });
        }
    }

    private pollGameStatus() {
        console.log("before poll game status");
        this.http.get('/TicTacServer-1.0/services/Rest/gamestatus')
                 .map(res => res.json())
                 .subscribe(d => { console.log("poll game status: " + d.status);
                                   this.joinGame(d.status); }/*,
                            this.sub.unsubscribe()*/);
    }

    private joinGame(status: String) {
        if (status == "GameOn") {
            this.sub.unsubscribe();
            this.router.navigate(['/game']);
        }
    }
}