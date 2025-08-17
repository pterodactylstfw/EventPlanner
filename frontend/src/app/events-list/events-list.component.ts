import {Component, OnInit} from '@angular/core';
import {EventService} from '../event.service';
import {EventModel} from '../event.model';
import {MatDialog, MatDialogModule} from '@angular/material/dialog';
import {MatButtonModule} from '@angular/material/button';
import {AddEventComponent} from '../add-event/add-event.component';
import {MatIcon} from '@angular/material/icon';


@Component({
  selector: 'app-events-list',
  standalone: true,
  imports: [
    MatDialogModule,
    MatButtonModule,
    MatIcon
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

  protected readonly confirm = confirm;

  openAddEventDialog(): void {
    const dialogRef = this.dialog.open(AddEventComponent, {
      width: '1800px',
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
      error: () => {
        this.error = 'Eroare la preluarea evenimentelor!';
        this.loading = false;
      }
    })
  }


  ngOnInit() {
    this.loadEvents();
  }

  deleteEvent(id: number): void {
    console.log(`Utilizatorul vrea sa stearga evenimentul cu ID-ul: ${id}`);
    if (confirm(`Sunteti sigur ca doriti sa stergeti evenimentul?`)) {
      this.eventService.deleteEventService(id).subscribe({
        next: (response: any) => {
          console.log('Raspuns de la server:', response);
          this.loadEvents();
        },
        error: (err: any) => {
          alert('A aparut o eroare in stergerea evenimentului!');
          console.error('A aparut o eroare: ', err)
        }
      });
    } else console.log('Utilizatorul a anulat actiunea de stergere: Cancel');

  }
}
