import {Injectable} from '@angular/core';
import {Capacitor} from '@capacitor/core';

@Injectable({
  providedIn: 'root'
})
export class PlatformService {
  isNativeIOS(): boolean {
    return Capacitor.isNativePlatform() && Capacitor.getPlatform() === 'ios';
  }

  isDesktop(): boolean {
    return !Capacitor.isNativePlatform();
  }
}
