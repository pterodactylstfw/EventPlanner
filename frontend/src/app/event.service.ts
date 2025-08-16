import {Injectable} from '@angular/core';
import {HttpClient} from '@angular/common/http';
import {Observable} from 'rxjs';
import {EventModel} from './event.model';

@Injectable({
  providedIn: 'root'
})
export class EventService {
  private apiUrl = 'http://localhost:18080';

  constructor(private http: HttpClient) {
  }

  getEvents(): Observable<EventModel[]> {
    return this.http.get<EventModel[]>(`${this.apiUrl}/events`)
  }

  addEvent(event: EventModel): Observable<any> {
    return this.http.post(`${this.apiUrl}/add-event`, event, {responseType: 'text'});

  }
}
