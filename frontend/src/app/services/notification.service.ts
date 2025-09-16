import {Injectable} from '@angular/core';
import {EventModel} from '../event.model';
import {LocalNotifications} from '@capacitor/local-notifications';

@Injectable({
  providedIn: 'root'
})
export class NotificationService {

  constructor() {
  }

  async requestPermission(): Promise<boolean> {
    const result = await LocalNotifications.requestPermissions();
    // result.display == 'granted' sau 'denied'
    return result.display === 'granted';
  }

  transformDateTime(event: EventModel): Date | null {
    const dateStr: string = event.date + 'T' + event.hour;
    const date: Date = new Date(dateStr);
    if (isNaN(date.getTime())) {
      console.log("Eroare la transformarea datei: dateIsNaN");
      return null;
    }
    return date;
  }


  async scheduleNotification(event: EventModel, hoursBefore: number): Promise<boolean> {
    let date = this.transformDateTime(event);
    if (!date)
      return false;

    date.setHours(date.getHours() - hoursBefore);

    if (date <= new Date()) {
      console.log("Notificare in trecut.");
      return false;
    }

    const notification = {
      id: event.id,
      title: event.title,
      body: event.description,
      schedule: {at: date},
    };
    try {
      LocalNotifications.schedule({notifications: [notification]});
      return true;
    } catch (error) {
      console.log("Eroare planificare notificare!");
      return false;
    }


  }

}
