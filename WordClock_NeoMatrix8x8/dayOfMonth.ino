
void dayOfMonth() {
  // display the D in the upper-right corner, for day
  mask |= 0x100000000000000;
  
  int day = theTime.day();
  if (day == 1) {
    ONE;
  } else if (day == 2) {
    TWO;
  } else if (day == 3) {
    THREE;
  } else if (day == 4) {
    FOUR;
  } else if (day == 5) {
    FIVE;
  } else if (day == 6) {
    SIX;
  } else if (day == 7) {
    SEVEN;
  } else if (day == 8) {
    EIGHT;
  } else if (day == 9) {
    NINE;
  } else if (day == 10) {
    TEN;
  } else if (day == 11) {
    ELEVEN;
  } else if (day == 12) {
    TWELVE;
  } else if (day == 13) {
    THIR;
    TEEN;
  } else if (day == 14) {
    FOUR;
    TEEN;
  } else if (day == 15) {
    FIF;
    TEEN;
  } else if (day == 16) {
    SIX;
    TEEN;
  } else if (day == 17) {
    SEVEN;
    TEEN;
  } else if (day == 18) {
    EIGHT;
    TEEN;
  } else if (day == 19) {
    NINE;
    TEEN;
  } else if (day == 20) {
    TWENTY;
  } else if (day == 21) {
    TWENTY;
    ONE;
  } else if (day == 22) {
    TWENTY;
    TWO;
  } else if (day == 23) {
    TWENTY;
    THREE;
  } else if (day == 24) {
    TWENTY;
    FOUR;
  } else if (day == 25) {
    TWENTY;
    FIVE;
  } else if (day == 26) {
    TWENTY;
    SIX;
  } else if (day == 27) {
    TWENTY;
    SEVEN;
  } else if (day == 28) {
    TWENTY;
    EIGHT;
  } else if (day == 29) {
    TWENTY;
    NINE;
  } else if (day == 30) {
    TWENTY;
    TEN;
    ONE;
  } else if (day == 31) {
    TWENTY;
    TEN;
    TWO;
  }
  applyMask(); // apply phrase mask to colorshift function
}
