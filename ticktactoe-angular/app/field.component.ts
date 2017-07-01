import {Component} from '@angular/core';
import {GameButton} from './gamebutton.component';

// enum CellState {Closed = 1, Opened_X = 2, Opened_O = 3};
// enum Player    {Player1, Player2};

@Component({
    selector: 'field',
    templateUrl: 'app/field.html'
})
export class FieldComponent {

    // private fieldMatrix: CellState[][];
    // private player: Player;
    // private MaxSize: number;

    // constructor() {
    //     this.MaxSize = 4;
    //     this.player = Player.Player1;
    //     this.fieldMatrix = [];
    //     for (let i=0; i<this.MaxSize; ++i) {
    //         this.fieldMatrix[i] = [];
    //         for (let j=0; j<this.MaxSize; ++j) {
    //             this.fieldMatrix[i][j] = CellState.Closed;
    //         }
    //     }
    // }

    // private checkGame() {
        
    // }

    // private switchPlayer() {
    //     this.player = (this.player == Player.Player1 ? Player.Player2 : Player.Player1);
    // }

    // onLastPositionChanged(position: string) {
    //     console.log("onLastPositionChanged:" + position);
    //     if (position.length != 2) {
    //         console.log("Wrong position value: " + position.length + "!");
    //     } else {
    //         var row: number = Number(position.charAt(0));
    //         var col: number = Number(position.charAt(1));
    //         if ((row >= 0 && row < this.MaxSize) && 
    //             (col >= 0 && col < this.MaxSize)) {
    //             if (this.fieldMatrix[row][col] == CellState.Closed) {
    //                 this.fieldMatrix[row][col] = (this.player == Player.Player1 ? CellState.Opened_X
    //                                                                             : CellState.Opened_O);
    //                 this.checkGame();
    //                 this.switchPlayer();
    //             }
    //         }
    //     }
    // }
}