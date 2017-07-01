import {NgModule} from '@angular/core';
import {BrowserModule} from '@angular/platform-browser';
import {MinesweeperComponent} from './minesweeper.component';
import {FieldComponent} from './field.component';
import {GameButton} from './gamebutton.component';
import {GameLogic} from './gamelogic';

@NgModule({
    imports: [BrowserModule],
    declarations: [MinesweeperComponent,
                   GameButton,
                   FieldComponent],
    providers: [GameLogic],
    bootstrap: [MinesweeperComponent]
})
export class MinesweeperModule {}