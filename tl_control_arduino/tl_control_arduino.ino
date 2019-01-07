/*
 * rosserial TrafficLight controller
 * 20190107,hokamoto@hhq.suzuki.co.jp
 */

#include <ros.h>
#include <std_msgs/String.h>

#define PIN_RED    7
#define PIN_YELLOW 6
#define PIN_GREEN  5
#define PIN_LEFT   4
#define PIN_CENTER 3
#define PIN_RIGHT  2

ros::NodeHandle  nh;

String tl_state;
byte pinOut;

void messageCb( const std_msgs::String& msg){
  digitalWrite(13, HIGH-digitalRead(13));  //toggle led  
  tl_state = msg.data;
  pinOut = 0b00000000;
  if(tl_state.indexOf("RED")>=0)   { pinOut |= 0b10000000; }
  if(tl_state.indexOf("YELLOW")>=0){ pinOut |= 0b01000000; }
  if(tl_state.indexOf("GREEN")>=0) { pinOut |= 0b00100000; }
  if(tl_state.indexOf("LEFT")>=0)  { pinOut |= 0b00010000; }
  if(tl_state.indexOf("CENTER")>=0){ pinOut |= 0b00001000; }
  if(tl_state.indexOf("RIGHT")>=0) { pinOut |= 0b00000100; }
}

ros::Subscriber<std_msgs::String> sub("tl_state", messageCb );

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

unsigned int counter;

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(PIN_RED,    OUTPUT);
  pinMode(PIN_YELLOW, OUTPUT);
  pinMode(PIN_GREEN,  OUTPUT);
  pinMode(PIN_LEFT,   OUTPUT);
  pinMode(PIN_CENTER, OUTPUT);
  pinMode(PIN_RIGHT,  OUTPUT);

  pinOut = 0b00000000;
  counter = 0;
  
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);
}

char buf[100];

void loop()
{
  /*
  digitalWrite(PIN_RED,    pinOut & 0b10000000);
  digitalWrite(PIN_YELLOW, pinOut & 0b01000000);
  digitalWrite(PIN_GREEN,  pinOut & 0b00100000);
  digitalWrite(PIN_LEFT,   pinOut & 0b00010000);
  digitalWrite(PIN_CENTER, pinOut & 0b00001000);
  digitalWrite(PIN_RIGHT,  pinOut & 0b00000100);
  */
  PORTD = pinOut;
  
  String msgString;
  msgString.concat(String(pinOut,BIN));
  msgString.concat(",");
  msgString.concat(String(PORTD,BIN));
  msgString.concat(",");
  msgString.concat(tl_state);
  msgString.concat(",");
  msgString.concat(String(counter++));
  int len=msgString.length();
  msgString.toCharArray(buf,len+1);
  str_msg.data = buf;
  chatter.publish( &str_msg );
  nh.spinOnce();
  delay(100);
}
