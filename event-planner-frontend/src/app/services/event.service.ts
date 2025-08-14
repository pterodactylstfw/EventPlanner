import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Observable } from 'rxjs';
import { map } from 'rxjs/operators';
import { Event } from '../models/event.model';

@Injectable({
  providedIn: 'root'
})
export class EventService {
  private apiUrl = 'http://localhost:8080/api/events';

  constructor(private http: HttpClient) { }

  // Get all events
  getEvents(): Observable<Event[]> {
    return this.http.get<Event[]>(this.apiUrl).pipe(
      map(events => events.map(event => this.convertDateFormat(event)))
    );
  }

  // Get event by ID
  getEventById(id: number): Observable<Event> {
    return this.http.get<Event>(`${this.apiUrl}/${id}`).pipe(
      map(event => this.convertDateFormat(event))
    );
  }

  // Create new event
  createEvent(event: Event): Observable<Event> {
    const apiEvent = this.convertDateFormatForApi(event);
    return this.http.post<Event>(this.apiUrl, apiEvent, {
      headers: new HttpHeaders({
        'Content-Type': 'application/json'
      })
    }).pipe(
      map(newEvent => this.convertDateFormat(newEvent))
    );
  }

  // Update event
  updateEvent(id: number, event: Event): Observable<Event> {
    const apiEvent = this.convertDateFormatForApi(event);
    return this.http.put<Event>(`${this.apiUrl}/${id}`, apiEvent, {
      headers: new HttpHeaders({
        'Content-Type': 'application/json'
      })
    }).pipe(
      map(updatedEvent => this.convertDateFormat(updatedEvent))
    );
  }

  // Delete event
  deleteEvent(id: number): Observable<any> {
    return this.http.delete(`${this.apiUrl}/${id}`);
  }

  // Convert API date format (DD/MM/YYYY) to HTML date format (YYYY-MM-DD)
  private convertDateFormat(event: Event): Event {
    if (event.date && event.date.includes('/')) {
      const [day, month, year] = event.date.split('/');
      event.date = `${year}-${month.padStart(2, '0')}-${day.padStart(2, '0')}`;
    }
    return event;
  }

  // Convert HTML date format (YYYY-MM-DD) to API date format (DD/MM/YYYY)
  private convertDateFormatForApi(event: Event): Event {
    const apiEvent = { ...event };
    if (event.date && event.date.includes('-')) {
      const [year, month, day] = event.date.split('-');
      apiEvent.date = `${day}/${month}/${year}`;
    }
    return apiEvent;
  }
}