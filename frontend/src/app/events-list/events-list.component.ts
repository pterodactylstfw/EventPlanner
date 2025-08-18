import {Component, OnInit} from '@angular/core';
import {EventService} from '../event.service';
import {EventModel} from '../event.model';
import {MatDialog, MatDialogModule} from '@angular/material/dialog';
import {MatButtonModule} from '@angular/material/button';
import {AddEventComponent} from '../add-event/add-event.component';
import {MatIcon} from '@angular/material/icon';
import {ConfirmationDialogComponent} from '../confirmation-dialog/confirmation-dialog.component';


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
          console.log('Operatiunea de stergere a fost efectuata cu succes!');
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
      // `result` este `true` dacă ai închis cu succes (din `dialogRef.close(true)`)
      if (result) {
        console.log('Dialogul de editare s-a închis cu succes, reîncărcăm evenimentele.');
        this.loadEvents(); // Apelezi funcția care reface cererea GET către server
      }
    });

  };


}
