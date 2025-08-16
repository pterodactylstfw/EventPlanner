import {Injectable} from '@angular/core';
import {HttpClient} from '@angular/common/http';
import {Observable} from 'rxjs';

export interface EventModel {
  id: number;
  title: string;
  description: string;
  date: string;
  hour: string;
  location: string;
}

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
}
