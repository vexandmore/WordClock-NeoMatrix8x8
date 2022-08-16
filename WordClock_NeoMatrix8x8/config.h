// Do you live in a country or territory that observes Daylight Saving Time?
// https://en.wikipedia.org/wiki/Daylight_saving_time_by_country
// Use 1 if you observe DST, 0 if you don't. This is programmed for DST in the US / Canada. If your territory's DST operates differently,
// you'll need to modify the code in the calcTheTime() function to make this work properly.
//#define OBSERVE_DST 1

// Define US or EU rules for DST comment out as required. More countries could be added with different rules in DST_RTC.cpp
#define RULES_DST "US" // US DST rules
// #define RULES_DST "EU" // EU DST rules


// brightness based on time of day- could try warmer colors at night?
#define DAYBRIGHTNESS 20
#define NIGHTBRIGHTNESS 10

// cutoff times for day / night brightness. feel free to modify.
#define MORNINGCUTOFF 7  // when does daybrightness begin?   7am
#define NIGHTCUTOFF   22 // when does nightbrightness begin? 10pm


// define delays
#define FLASHDELAY 250  // delay for startup "flashWords" sequence
#define SHIFTDELAY 100   // controls color shifting speed
// These delays are for switching between showing the time,moon, etc phases
#define SHOW_TIME_DURATION  60000  // how long to show the time (ms)
#define SHOW_MOON_DURATION  3000   // how long to show the moon (ms)
#define SHOW_DAY_DURATION   3000   // how long to show the day of month (ms)
#define SHOW_MONTH_DURATION 3000   // how long to show the month (ms)
#define SHOW_YEAR_DURATION  3000   // how long to show the year (ms)
