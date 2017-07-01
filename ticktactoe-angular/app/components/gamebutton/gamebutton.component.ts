import {Component, Input, Output, EventEmitter} from '@angular/core';
import {GameLogic} from '../../gamelogic';

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

    constructor(private gameLogic: GameLogic) {
    }

    getBackgroundColor(): string {
        return this.gameLogic.buttonColor(this.position);
    }
    
    buttonClicked() {
        console.log("Position: " + this.position);
        this.gameLogic.onLastPositionChanged(this.position);
    }
}