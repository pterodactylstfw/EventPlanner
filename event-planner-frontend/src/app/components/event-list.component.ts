import { Component, OnInit } from '@angular/core';
import { EventService } from '../services/event.service';
import { Event } from '../models/event.model';

@Component({
  selector: 'app-event-list',
  templateUrl: './event-list.component.html',
  styleUrls: ['./event-list.component.css']
})
export class EventListComponent implements OnInit {
  events: Event[] = [];
  newEvent: Event = {
    title: '',
    description: '',
    date: '',
    time: '',
    location: ''
  };
  editingEvent: Event | null = null;
  loading = false;
  error = '';

  constructor(private eventService: EventService) { }

  ngOnInit(): void {
    this.loadEvents();
  }

  loadEvents(): void {
    this.loading = true;
    this.eventService.getEvents().subscribe({
      next: (events) => {
        this.events = events;
        this.loading = false;
      },
      error: (error) => {
        this.error = 'Failed to load events';
        this.loading = false;
        console.error('Error loading events:', error);
      }
    });
  }

  createEvent(): void {
    if (this.isFormValid(this.newEvent)) {
      this.eventService.createEvent(this.newEvent).subscribe({
        next: (event) => {
          this.events.push(event);
          this.resetForm();
        },
        error: (error) => {
          this.error = 'Failed to create event';
          console.error('Error creating event:', error);
        }
      });
    }
  }

  editEvent(event: Event): void {
    this.editingEvent = { ...event };
  }

  updateEvent(): void {
    if (this.editingEvent && this.isFormValid(this.editingEvent)) {
      this.eventService.updateEvent(this.editingEvent.id!, this.editingEvent).subscribe({
        next: (updatedEvent) => {
          const index = this.events.findIndex(e => e.id === updatedEvent.id);
          if (index !== -1) {
            this.events[index] = updatedEvent;
          }
          this.editingEvent = null;
        },
        error: (error) => {
          this.error = 'Failed to update event';
          console.error('Error updating event:', error);
        }
      });
    }
  }

  deleteEvent(id: number): void {
    if (confirm('Are you sure you want to delete this event?')) {
      this.eventService.deleteEvent(id).subscribe({
        next: () => {
          this.events = this.events.filter(e => e.id !== id);
        },
        error: (error) => {
          this.error = 'Failed to delete event';
          console.error('Error deleting event:', error);
        }
      });
    }
  }

  cancelEdit(): void {
    this.editingEvent = null;
  }

  resetForm(): void {
    this.newEvent = {
      title: '',
      description: '',
      date: '',
      time: '',
      location: ''
    };
  }

  private isFormValid(event: Event): boolean {
    return !!(event.title && event.description && event.date && event.time && event.location);
  }
}