#include <Max3421e.h>
#include <Usb.h>
#include <AndroidAccessory.h>

#define COLUMNS_NUMBER 2
#define ROWS_NUMBER 5

static int ROWS_PINS[ROWS_NUMBER] = {30,31,32,37,34};
static int COLUMNS_PINS[COLUMNS_NUMBER] = {35,36};
static int MATRIX[ROWS_NUMBER][COLUMNS_NUMBER];

boolean _wasAccessoryConnected;

AndroidAccessory acc("Zakos Inc.",
		     "Led-Text-Panel",
		     "Led based text panel, enabled for arduino",
		     "1.0",
		     "http://www.android.com",
		     "0000000012345678");

void setup();
void loop();

void show_leds_matrix(){
  for (int i = 0; i < ROWS_NUMBER ;i ++){
    Serial.print("Row "); Serial.print(i); Serial.print(" : ");
     for (int j= 0; j< COLUMNS_NUMBER ;j ++){
       Serial.print(MATRIX[][]);
       Serial.print(" ");
     }    
     Serial.println();
  } 
}

void applyMatrix(){
         
        for (int i = 0; i < ROWS_NUMBER ;i ++){
          for (int i = 0; i < COLUMNS_NUMBER ;i ++){
             digitalWrite(COLUMNS_PINS[i], LOW);
	   }
        } 
}

void setup_leds()
{
        for (int i = 0; i < COLUMNS_NUMBER ;i ++){
        pinMode(COLUMNS_PINS[i], OUTPUT);
        digitalWrite(COLUMNS_PINS[i], LOW);
	} 
         for (int i = 0; i < ROWS_NUMBER ;i ++){
        //digitalWrite(ROWS_PINS[i], 1);
	pinMode(ROWS_PINS[i], OUTPUT);
        digitalWrite(ROWS_PINS[i], LOW);
        } 
}

void lightUpColumn(int col){
        
        for (int j = 0; j < 10 ;j ++){
          if (j%2==0){  
              for (int i = 0; i < ROWS_NUMBER ;i ++){
                digitalWrite(ROWS_PINS[i], HIGH);
              }
              for (int i = 0; i < COLUMNS_NUMBER ;i ++){
                  digitalWrite(COLUMNS_PINS[i], HIGH);
                }
              digitalWrite(COLUMNS_PINS[col], LOW);
          }else{
                for (int i = 0; i < ROWS_NUMBER ;i ++){
                digitalWrite(ROWS_PINS[i], LOW);
              }
               for (int i = 0; i < COLUMNS_NUMBER ;i ++){
                  digitalWrite(COLUMNS_PINS[i], LOW);
                }
               
              digitalWrite(COLUMNS_PINS[col], HIGH);
          }
          delay(1000);
        }
}

void lightUpRow(int row){
  
  int delay_msec = 1;
  int seconds_to_be_displayed = 2;
  
  int loop_number = (seconds_to_be_displayed / delay_msec) * 1000;
  Serial.print("Using loop_number ");
   Serial.println(loop_number);
          
  for (int j = 0; j < loop_number ;j ++){
          if (j%2==0){  
              for (int i = 0; i < ROWS_NUMBER ;i ++){
                digitalWrite(ROWS_PINS[i], HIGH);
              }
              for (int i = 0; i < COLUMNS_NUMBER ;i ++){
                  digitalWrite(COLUMNS_PINS[i], HIGH);
                }
              digitalWrite(ROWS_PINS[row], LOW);
          }else{
                for (int i = 0; i < ROWS_NUMBER ;i ++){
                digitalWrite(ROWS_PINS[i], LOW);
              }
               for (int i = 0; i < COLUMNS_NUMBER ;i ++){
                  digitalWrite(COLUMNS_PINS[i], LOW);
                }
               
              digitalWrite(ROWS_PINS[row], HIGH);
          }
          delay(delay_msec);
        }
}

void test_column_leds(){
          for (int i = 0; i < COLUMNS_NUMBER ;i ++){
          Serial.print("Lighting up column ");
          Serial.println(i);
             lightUpColumn(i);
	  } 
}

void test_row_leds(){
  for (int i = 0; i < ROWS_NUMBER ;i ++){
          Serial.print("Lighting up row ");
          Serial.println(i);
             lightUpRow(i);
	  } 
}

void test_leds(){
    test_column_leds();
    test_row_leds();
    setup_leds();
}

void setup()
{
        _wasAccessoryConnected = false;
	Serial.begin(115200);
	Serial.println("Starting");

        Serial.println("Initing leds");
	setup_leds();
        test_leds();
	acc.powerOn();
        Serial.println("Started");
}

void loop()
{
	byte err;
	byte idle;
	static byte count = 0;
	byte msg[3];
	long touchcount;
        Serial.print("\r\nLooping");

	if (acc.isConnected()) {
  
          if (_wasAccessoryConnected){
            
            
          }else{
          
          }
		Serial.print("\r\nAccessory is connected");

                int len = acc.read(msg, sizeof(msg), 1);
		int i;
		byte b;
		uint16_t val;
		int x, y;
		char c0;

//		if (len > 0) {
//			// assumes only one command per packet
//			if (msg[0] == 0x2) {
//				if (msg[1] == 0x0)
//					analogWrite(LED1_RED, 255 - msg[2]);
//				else if (msg[1] == 0x1)
//					analogWrite(LED1_GREEN, 255 - msg[2]);
//				else if (msg[1] == 0x2)
//					analogWrite(LED1_BLUE, 255 - msg[2]);
//				else if (msg[1] == 0x3)
//					analogWrite(LED2_RED, 255 - msg[2]);
//				else if (msg[1] == 0x4)
//					analogWrite(LED2_GREEN, 255 - msg[2]);
//				else if (msg[1] == 0x5)
//					analogWrite(LED2_BLUE, 255 - msg[2]);
//				else if (msg[1] == 0x6)
//					analogWrite(LED3_RED, 255 - msg[2]);
//				else if (msg[1] == 0x7)
//					analogWrite(LED3_GREEN, 255 - msg[2]);
//				else if (msg[1] == 0x8)
//					analogWrite(LED3_BLUE, 255 - msg[2]);
//				else if (msg[1] == 0x10)
//					servos[0].write(map(msg[2], 0, 255, 0, 180));
//				else if (msg[1] == 0x11)
//					servos[1].write(map(msg[2], 0, 255, 0, 180));
//				else if (msg[1] == 0x12)
//					servos[2].write(map(msg[2], 0, 255, 0, 180));
//			} else if (msg[0] == 0x3) {
//				if (msg[1] == 0x0)
//					digitalWrite(RELAY1, msg[2] ? HIGH : LOW);
//				else if (msg[1] == 0x1)
//					digitalWrite(RELAY2, msg[2] ? HIGH : LOW);
//			}
//		}
//
//		msg[0] = 0x1;
//
//		b = digitalRead(BUTTON1);
//		if (b != b1) {
//			msg[1] = 0;
//			msg[2] = b ? 0 : 1;
//			acc.write(msg, 3);
//			b1 = b;
//		}
//
//		b = digitalRead(BUTTON2);
//		if (b != b2) {
//			msg[1] = 1;
//			msg[2] = b ? 0 : 1;
//			acc.write(msg, 3);
//			b2 = b;
//		}
//
//		b = digitalRead(BUTTON3);
//		if (b != b3) {
//			msg[1] = 2;
//			msg[2] = b ? 0 : 1;
//			acc.write(msg, 3);
//			b3 = b;
//		}
//
//		b = digitalRead(JOY_SWITCH);
//		if (b != b4) {
//			msg[1] = 4;
//			msg[2] = b ? 0 : 1;
//			acc.write(msg, 3);
//			b4 = b;
//		}
//
//		switch (count++ % 0x10) {
//		case 0:
//			val = analogRead(TEMP_SENSOR);
//			msg[0] = 0x4;
//			msg[1] = val >> 8;
//			msg[2] = val & 0xff;
//			acc.write(msg, 3);
//			break;
//
//		case 0x4:
//			val = analogRead(LIGHT_SENSOR);
//			msg[0] = 0x5;
//			msg[1] = val >> 8;
//			msg[2] = val & 0xff;
//			acc.write(msg, 3);
//			break;
//
//		case 0x8:
//			read_joystick(&x, &y);
//			msg[0] = 0x6;
//			msg[1] = constrain(x, -128, 127);
//			msg[2] = constrain(y, -128, 127);
//			acc.write(msg, 3);
//			break;
//
////		case 0xc:
////			touchcount = touch_robot.capSense(5);
////
////			c0 = touchcount > 750;
////
////			if (c0 != c) {
////				msg[0] = 0x1;
////				msg[1] = 3;
////				msg[2] = c0;
////				acc.write(msg, 3);
////				c = c0;
////			}
////
////			break;
//		}
	} else {
  
          if (_wasAccessoryConnected){
          }else{
          }
		Serial.print("\r\nAccessory not connected");
                // reset outputs to default values on disconnect
	}

	delay(10);
}
