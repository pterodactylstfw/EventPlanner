import {Component, OnInit} from '@angular/core';
import {EventModel, EventService} from '../event.service';

@Component({
  selector: 'app-events-list',
  standalone: true,
  imports: [],
  templateUrl: './events-list.component.html',
  styleUrl: './events-list.component.scss'
})
export class EventsListComponent implements OnInit {
  events: EventModel[] = [];
  loading = true;
  error = '';

  constructor(private eventService: EventService) {
  }

  ngOnInit() {
    this.eventService.getEvents().subscribe({
      next: (data) => {
        this.events = data;
        this.loading = false;
      },
      error: (_err) => { // Schimbat din 'err' în '_err'
        this.error = 'Eroare la preluarea evenimentelor!';
        this.loading = false;
      }
    });
  }
}
