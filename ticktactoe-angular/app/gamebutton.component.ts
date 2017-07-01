import {Component, Input, Output, EventEmitter} from '@angular/core';
import {GameLogic} from './gamelogic';

@Component({
    selector: 'gamebutton',
    styleUrls: ['app/gamebutton.css'],
    template: `<button
                id="gamebutton"
                [style.background-image]="getBackgroundColor()"
                (click)="buttonClicked()">
               </button>`
})
export class GameButton {
    @Input() position: string;
    //@Output() lastPosition: EventEmitter<String> = new EventEmitter();

    constructor(private gameLogic: GameLogic) {
    }

    getBackgroundColor(): string {
        //return "powderblue";
        return this.gameLogic.buttonColor(this.position);
    }
    
    buttonClicked() {
        console.log("Position: " + this.position);
        //this.lastPosition.emit(this.position);
        this.gameLogic.onLastPositionChanged(this.position);
    }
}