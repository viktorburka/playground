import {NgModule} from '@angular/core';
import {BrowserModule} from '@angular/platform-browser';
import {LocationStrategy, HashLocationStrategy} from '@angular/common';
import {TicTacToeComponent} from '../tictactoe/tictactoe.component';
import {FieldComponent} from '../field/field.component';
import {GameButton} from '../gamebutton/gamebutton.component';
import {GameLogic} from '../../gamelogic';
import {HttpModule, Http} from '@angular/http';
import {LoadingScreenComponent} from '../../components/loadingscreen/loadingscreen.component';
import {routing} from '../../components/app.routing';
import {LoginFormComponent} from '../../components/loginform/loginform.component';
import {AuthComponent} from '../../components/auth/auth.component';
import {CreateAccountComponent} from '../../components/createaccount/createaccount.component';

@NgModule({
    imports: [BrowserModule,
              HttpModule,
              routing],
    declarations: [TicTacToeComponent,
                   GameButton,
                   FieldComponent,
                   LoadingScreenComponent,
                   LoginFormComponent,
                   AuthComponent,
                   CreateAccountComponent],
    providers: [GameLogic,
                {provide: LocationStrategy, useClass: HashLocationStrategy}],
    bootstrap: [TicTacToeComponent]
})
export class TicTacToeModule {}