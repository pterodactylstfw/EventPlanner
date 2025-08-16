import {Component} from '@angular/core';
import {FormsModule} from '@angular/forms';
import {EventModel} from '../event.model';
import {EventService} from '../event.service';
import {MatDialogRef} from '@angular/material/dialog';

@Component({
  selector: 'app-add-event',
  imports: [FormsModule],
  templateUrl: './add-event.component.html',
  styleUrl: './add-event.component.scss'
})
export class AddEventComponent {

  submitted = false;

  event: EventModel = {
    id: 0,
    title: '',
    description: '',
    date: '',
    hour: '',
    location: ''
  };

  constructor(private eventService: EventService,
              public dialogRef: MatDialogRef<AddEventComponent>) {
  }

  onSubmit() {
    this.submitted = true;
    this.eventService.addEvent(this.event).subscribe({
      next: (response) => {
        console.log('Raspuns de la server:', response);
        alert('Eveniment adaugat cu succes!');
        this.dialogRef.close(true);
      },
      error: (err) => {
        console.error('A aparut o eroare:', err);
        alert('Eroare la adaugarea evenimentului!');
        this.dialogRef.close(false);
      }
    });
  }

  onCancel(): void {
    this.dialogRef.close();
  }
}
