import {Injectable} from '@angular/core';
import {HttpClient} from '@angular/common/http';
import {from, Observable} from 'rxjs';
import {EventModel} from './event.model';
import {Capacitor} from '@capacitor/core';
import {EventLocalService} from './event-local.service';

@Injectable({
  providedIn: 'root'
})
export class EventService {
  private apiUrl = 'http://localhost:18080';

  constructor(private http: HttpClient, private localService: EventLocalService) {
  }

  getEvents(): Observable<EventModel[]> {
    if (this.isNativeIOS())
      return from(this.localService.getEvents());

    return this.http.get<EventModel[]>(`${this.apiUrl}/events`)
  }

  addEvent(event: EventModel): Observable<any> {
    if (this.isNativeIOS())
      return from(this.localService.addEvent(event));

    return this.http.post(`${this.apiUrl}/add-event`, event, {responseType: 'text'});
  }

  updateEvent(event: EventModel): Observable<any> {
    if (this.isNativeIOS())
      return from(this.localService.updateEvent(event));

    return this.http.put(`${this.apiUrl}/events/${event.id}`, event, {responseType: 'text'});
  }

  deleteEventService(id: number): Observable<any> {
    if (this.isNativeIOS()) {
      return from(this.localService.deleteEvent(id));
    }
    return this.http.delete(`${this.apiUrl}/events/${id}`, {responseType: 'text'})
  }

  private isNativeIOS(): boolean {
    return Capacitor.isNativePlatform() && Capacitor.getPlatform() === 'ios';
  }
}
