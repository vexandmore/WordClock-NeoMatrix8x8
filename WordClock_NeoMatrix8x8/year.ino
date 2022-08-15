void year() {
  int year = theTime.year();
  if (year < 2021 || year > 2029) {
    // can't handle this - use binary
    mask |= year;
  } else if (year == 2021) {
    TWENTY;
    ONE;
  } else if (year == 2022) {
    TWENTY;
    TWO;
  } else if (year == 2023) {
    TWENTY;
    THREE;
  } else if (year == 2024) {
    TWENTY;
    FOUR;
  } else if (year == 2025) {
    TWENTY;
    FIVE;
  } else if (year == 2026) {
    TWENTY;
    SIX;
  } else if (year == 2027) {
    TWENTY;
    SEVEN;
  } else if (year == 2028) {
    TWENTY;
    EIGHT;
  } else if (year == 2029) {
    TWENTY;
    NINE;
  }
  applyMask();
}
