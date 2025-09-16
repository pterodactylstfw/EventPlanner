import {Component, OnInit, signal, ViewEncapsulation} from '@angular/core';
import {RouterOutlet} from '@angular/router';
import {NotificationService} from './services/notification.service';

@Component({
  selector: 'app-root',
  imports: [RouterOutlet],
  templateUrl: './app.html',
  styleUrl: './app.scss',
  encapsulation: ViewEncapsulation.None
})
export class App implements OnInit {
  constructor(private notificationService: NotificationService) {
  }

  ngOnInit(): void {
    this.notificationService.requestPermission();
  }

  protected readonly title = signal('frontend');
}
