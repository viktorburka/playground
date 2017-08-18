import {Routes, RouterModule} from '@angular/router';
import {LoadingScreenComponent} from "./loadingscreen/loadingscreen.component";
import {FieldComponent} from "./field/field.component";
import {LoginFormComponent} from './loginform/loginform.component';
import {AuthComponent} from './auth/auth.component';
import {CreateAccountComponent} from './createaccount/createaccount.component';

const routes: Routes = [
    {path: '',      component: LoadingScreenComponent},
    {path: 'game',  component: FieldComponent},
    {path: 'login', component: AuthComponent,
        children: [
            {path: '',               component: LoginFormComponent},
            {path: 'create-account', component: CreateAccountComponent}
    ]}
];

export const routing = RouterModule.forRoot(routes);