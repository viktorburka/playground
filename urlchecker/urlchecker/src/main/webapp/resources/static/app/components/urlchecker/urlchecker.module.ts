import {NgModule} from '@angular/core';
import {BrowserModule} from '@angular/platform-browser';
import {HttpModule, Http} from '@angular/http';
import {DatabaseViewComponent} from '../../components/databaseview/databaseview.component';

@NgModule({
    imports: [BrowserModule,
              HttpModule],
    declarations: [DatabaseViewComponent],
    bootstrap: [DatabaseViewComponent]
})
export class UrlCheckerModule {}