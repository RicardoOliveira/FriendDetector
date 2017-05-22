#include "./esppl_functions.h"

/*
 * Define you friend's list size here
 */
#define LIST_SIZE 2
/*
 * This is your friend's MAC address list
 */
uint8_t friendmac[LIST_SIZE][ESPPL_MAC_LEN] = {
   {0x11, 0x11, 0x11, 0x11, 0x11, 0x11}
  ,{0x22, 0x22, 0x22, 0x22, 0x22, 0x22}
  };
/*
 * This is your friend's name list
 * put them in the same order as the MAC addresses
 */
String friendname[LIST_SIZE] = {
   "Friend 1"
  ,"Friend 2"
  };

bool maccmp(uint8_t *mac1, uint8_t *mac2) {
  for (int i=0; i < ESPPL_MAC_LEN; i++) {
    if (mac1[i] != mac2[i]) {
      return false;
    }
  }
  return true;
}

void cb(esppl_frame_info *info) {
  for (int i=0; i<LIST_SIZE; i++) {
    if (maccmp(info->sourceaddr, friendmac[i]) || maccmp(info->receiveraddr, friendmac[i])) {
      Serial.printf("\n%s is here! :)", friendname[i].c_str());
    }
  }
}

void setup() {
  delay(500);
  Serial.begin(115200);
  esppl_init(cb);
}

void loop() {
  esppl_sniffing_start();
  while (true) {
    for (int i = ESPPL_CHANNEL_MIN; i <= ESPPL_CHANNEL_MAX; i++ ) {
      esppl_set_channel(i);
      while (esppl_process_frames()) {
        //
      }
    }
  }  
}
