import {Routes} from '@angular/router';
import {EventsListComponent} from './events-list/events-list.component';
import {AddEventComponent} from './add-event/add-event.component';

export const routes: Routes = [
  {path: '', component: EventsListComponent},
  {path: 'add-event', component: AddEventComponent}
];
