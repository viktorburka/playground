import {NgModule} from '@angular/core';
import {BrowserModule} from '@angular/platform-browser';
import {TicTacToeComponent} from '../tictactoe/tictactoe.component';
import {FieldComponent} from '../field/field.component';
import {GameButton} from '../gamebutton/gamebutton.component';
import {GameLogic} from '../../gamelogic';

@NgModule({
    imports: [BrowserModule],
    declarations: [TicTacToeComponent,
                   GameButton,
                   FieldComponent],
    providers: [GameLogic],
    bootstrap: [TicTacToeComponent]
})
export class TicTacToeModule {}