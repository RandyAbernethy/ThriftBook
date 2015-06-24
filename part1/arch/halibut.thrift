struct Date {
    1: i16  year
    2: i16  month
    3: i16  day
}

service HalibutTracking {
    i32 GetCatchInPoundsToday()
    i32 GetCatchInPoundsByDate(1: Date dt, 2: double tm)
}

