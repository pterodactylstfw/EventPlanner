import {Component, Inject, OnInit} from '@angular/core';
import {FormsModule} from '@angular/forms';
import {EventModel} from '../event.model';
import {EventService} from '../event.service';
import {MAT_DIALOG_DATA, MatDialogActions, MatDialogContent, MatDialogRef} from '@angular/material/dialog';
import {MatSnackBar} from '@angular/material/snack-bar';
import {MatFormFieldModule} from '@angular/material/form-field';
import {MatError, MatInputModule} from '@angular/material/input';
import {MatButtonModule} from '@angular/material/button';

@Component({
  selector: 'app-add-event',
  imports: [FormsModule,
    MatFormFieldModule,
    MatInputModule,
    MatButtonModule,
    MatError, MatDialogContent, MatDialogActions],
  templateUrl: './add-event.component.html',
  styleUrl: './add-event.component.scss'
})
export class AddEventComponent implements OnInit {

  submitted = false;

  event: EventModel = {
    id: 0,
    title: '',
    description: '',
    date: '',
    hour: '',
    location: ''
  };

  isEditMode: boolean = false;

  constructor(private eventService: EventService,
              public dialogRef: MatDialogRef<AddEventComponent>, @Inject(MAT_DIALOG_DATA) public data: EventModel, private snackBar: MatSnackBar) {
  }

  ngOnInit() {
    if (this.data) {
      this.event = {...this.data};
      this.isEditMode = true;
    }
  }

  onSubmit() {
    this.submitted = true;
    if (!this.isEditMode) {
    this.eventService.addEvent(this.event).subscribe({
      next: (response) => {
        console.log('Raspuns de la server:', response);
        this.showNotification('Eveniment adaugat cu succes!');
        this.dialogRef.close(true);
      },
      error: (err) => {
        console.error('A aparut o eroare:', err);
        this.showNotification('Eroare la adaugarea evenimentului!');
        // alert('Eroare la adaugarea evenimentului!');
        this.dialogRef.close(false);
      }
    });
    } else {
      this.eventService.updateEvent(this.event).subscribe({
        next: (response) => {
          console.log('Raspuns de la server:', response);
          this.showNotification('Evenimentul a fost editat cu succes!');
          // alert('Evenimentul a fost editat cu succes!');
          this.dialogRef.close(true);
        },
        error: (err) => {
          console.error('A aparut o eroare: ', err);
          this.showNotification('A aparut o eroare la editarea evenimentului!');
          // alert('A aparut o eroare la editarea evenimentului!');
          this.dialogRef.close(false);
        }
      });
    }
  }

  showNotification(message: string): void {
    this.snackBar.open(message, 'OK', {
      duration: 3000
    });
  }

  onCancel(): void {
    this.dialogRef.close();
  }
}
