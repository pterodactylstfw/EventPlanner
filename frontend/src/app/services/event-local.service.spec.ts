import {TestBed} from '@angular/core/testing';

import {EventLocalService} from './event-local.service';

describe('EventLocalService', () => {
  let service: EventLocalService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(EventLocalService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
