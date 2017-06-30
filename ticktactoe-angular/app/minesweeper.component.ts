import {Component} from '@angular/core';
import {FieldComponent} from './field.component';

@Component({
    selector: 'minesweeper-game',
    template: `<field></field>`
})
export class MinesweeperComponent {

    name: string;

    constructor() {
        this.name = 'Minesweeper';
    }
}