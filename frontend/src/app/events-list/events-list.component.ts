import {Component, OnInit} from '@angular/core';
import {EventService} from '../event.service';
import {EventModel} from '../event.model';
import {MatDialog, MatDialogModule} from '@angular/material/dialog';
import {MatButtonModule} from '@angular/material/button';
import {AddEventComponent} from '../add-event/add-event.component';
import {MatIcon} from '@angular/material/icon';
import {ConfirmationDialogComponent} from '../confirmation-dialog/confirmation-dialog.component';
import {MatSnackBar} from '@angular/material/snack-bar';
import {MatProgressSpinnerModule} from '@angular/material/progress-spinner';

@Component({
  selector: 'app-events-list',
  standalone: true,
  imports: [
    MatDialogModule,
    MatButtonModule,
    MatIcon,
    MatProgressSpinnerModule,
  ],
  templateUrl: './events-list.component.html',
  styleUrl: './events-list.component.scss'
})
export class EventsListComponent implements OnInit {
  events: EventModel[] = [];
  loading = true;
  error = '';
  sortOrder: string = 'date';
  sortMenuOpened: boolean = false;


  constructor(private eventService: EventService, public dialog: MatDialog, private snackBar: MatSnackBar) {
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

  sortEvents(): void {
    if (this.sortOrder === 'date') {
      this.events.sort((a, b) => {
        const dateComparison = a.date.localeCompare(b.date);
        if (dateComparison != 0)
          return dateComparison;
        return a.hour.localeCompare(b.hour);
      });
    } else if (this.sortOrder === 'title') {
      this.events.sort((a, b) => a.title.localeCompare(b.title));
    } else if (this.sortOrder === 'location') {
      this.events.sort((a, b) => a.location.localeCompare(b.location));
    }
  }

  toggleSortMenu() {
    this.sortMenuOpened = !this.sortMenuOpened;
  }

  selectSortMethod(method: string) {
    this.sortOrder = method;
    this.sortEvents();
    this.toggleSortMenu();
  }

  loadEvents(): void {
    this.loading = true;
    this.eventService.getEvents().subscribe({
      next: (data) => {
        this.events = data;
        this.loading = false;
        this.sortEvents();
      },
      error: () => {
        this.error = 'Eroare la preluarea evenimentelor!';
        this.loading = false;
      }
    })
  }

  showNotification(message: string): void {
    this.snackBar.open(message, 'OK', {
      duration: 3000
    });
  }

  ngOnInit() {
    this.loadEvents();
  }

  deleteEvent(id: number): void {
    console.log(`Utilizatorul vrea sa stearga evenimentul cu ID-ul: ${id}`);
    const eventToDelete = this.events.find(event => event.id === id);

    if (!eventToDelete) {
      console.error('Eroare: Evenimentul nu a fost găsit în listă!');
      return;
    }

    const message: string = `Sunteti sigur ca doriti sa stergeti evenimentul ${eventToDelete.title}?`;

    const dialogRef = this.dialog.open(ConfirmationDialogComponent, {
      width: '500px',
      data: {
        title: 'Confirmare stergere', message: message
      }

    });

    dialogRef.afterClosed().subscribe(result => {
      if (result) this.eventService.deleteEventService(id).subscribe({
        next: () => {
          this.loadEvents();
          this.showNotification('Operatiunea de stergere a fost efectuata cu succes!');
          //console.log('Operatiunea de stergere a fost efectuata cu succes!');
        },
        error: () => {
          this.showNotification('A aparut o eroare in efectuarea stergerii!');
          //console.error('A aparut o eroare la stergerea evenimentului!', err);
        }
      });

      else console.log('Utilizatorul a anulat actiunea de stergere: Cancel');
    });
  }

  openEditDialog(eventToEdit: EventModel): void {
    console.log(`Utilizatorul vrea sa editeze evenimentul cu ID-ul: ${eventToEdit.id}`);
    const dialogRef = this.dialog.open(AddEventComponent, {
        width: '1800px',
        data: eventToEdit
      }
    )

    dialogRef.afterClosed().subscribe(result => {
      if (result) {
        console.log('Dialogul de editare s-a închis cu succes, reîncărcăm evenimentele.');
        this.loadEvents();
      }
    });

  };


}
