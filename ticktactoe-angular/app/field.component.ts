import {Component} from '@angular/core';
import {GameButton} from './gamebutton.component';

@Component({
    selector: 'field',
    template: ` <div class="container-fluid">            
                    <div class="row">          
                        <div class="btn-group">
                            <gamebutton></gamebutton>
                            <gamebutton></gamebutton>
                            <gamebutton></gamebutton>
                            <gamebutton></gamebutton>
                        </div>
                    </div>
                    <div class="row">
                        <div class=" btn-group">
                            <gamebutton></gamebutton>
                            <gamebutton></gamebutton>
                            <gamebutton></gamebutton>
                            <gamebutton></gamebutton>
                        </div>
                    </div>
                    <div class="row">
                        <div class=" btn-group">
                            <gamebutton></gamebutton>
                            <gamebutton></gamebutton>
                            <gamebutton></gamebutton>
                            <gamebutton></gamebutton>
                        </div>
                    </div>
                    <div class="row">
                        <div class=" btn-group">
                            <gamebutton></gamebutton>
                            <gamebutton></gamebutton>
                            <gamebutton></gamebutton>
                            <gamebutton></gamebutton>
                        </div>
                    </div>
                </div>`
})
export class FieldComponent {
}