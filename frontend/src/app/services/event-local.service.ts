import {Injectable} from '@angular/core';
import {Preferences} from '@capacitor/preferences';
import {EventModel} from '../event.model';

@Injectable({
  providedIn: 'root'
})

export class EventLocalService {
  private key = 'events';

  async getEvents(): Promise<EventModel[]> {
    const {value} = await Preferences.get({key: this.key});
    return value ? JSON.parse(value) : [];
  }

  async addEvent(event: EventModel): Promise<void> {
    const events = await this.getEvents();
    const maxID = events.length > 0 ? Math.max(...events.map(e => e.id)) : 0;
    event.id = maxID + 1;
    events.push(event);
    await Preferences.set({key: this.key, value: JSON.stringify(events)});
  }

  async updateEvent(event: EventModel): Promise<void> {
    let events = await this.getEvents();
    events = events.map(e => e.id === event.id ? event : e);
    await Preferences.set({key: this.key, value: JSON.stringify(events)});
  }

  async deleteEvent(id: number): Promise<void> {
    let events = await this.getEvents();
    events = events.filter(e => e.id !== id);
    await Preferences.set({key: this.key, value: JSON.stringify(events)});
  }
}
