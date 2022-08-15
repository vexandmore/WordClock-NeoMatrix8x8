void month(void) {
  int month = theTime.month();
  
  uint64_t base = 0xF, shift = 60; 
  for (int i = 0; i < month; i++) {
    mask |= base << (shift - 4*i);
  }
  applyMask(); // apply phrase mask to colorshift function
}
