import {Routes, RouterModule} from '@angular/router';
import {LoadingScreenComponent} from "./loadingscreen/loadingscreen.component";
import {FieldComponent} from "./field/field.component";

const routes: Routes = [
    {path: '',     component: LoadingScreenComponent},
    {path: 'game', component: FieldComponent}
];

export const routing = RouterModule.forRoot(routes);