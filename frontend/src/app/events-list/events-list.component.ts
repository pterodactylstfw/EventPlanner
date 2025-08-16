import {Component, OnInit} from '@angular/core';
import {EventService} from '../event.service';
import {EventModel} from '../event.model';
import {MatDialog, MatDialogModule} from '@angular/material/dialog';
import {MatButtonModule} from '@angular/material/button';
import {AddEventComponent} from '../add-event/add-event.component';


@Component({
  selector: 'app-events-list',
  standalone: true,
  imports: [
    MatDialogModule,
    MatButtonModule
  ],
  templateUrl: './events-list.component.html',
  styleUrl: './events-list.component.scss'
})
export class EventsListComponent implements OnInit {
  events: EventModel[] = [];
  loading = true;
  error = '';

  constructor(private eventService: EventService, public dialog: MatDialog) {
  }

  openAddEventDialog(): void {
    const dialogRef = this.dialog.open(AddEventComponent, {
      width: '500px',
    });

    dialogRef.afterClosed().subscribe(result => {
      console.log('Dialogul a fost inchis');
      if (result) this.loadEvents();
    });
  }

  loadEvents(): void {
    this.loading = true;
    this.eventService.getEvents().subscribe({
      next: (data) => {
        this.events = data;
        this.loading = false;
      },
      error: (err) => {
        this.error = 'Eroare la preluarea evenimentelor!';
        this.loading = false;
      }
    })
  }

  ngOnInit() {
    this.loadEvents();
  }
}
