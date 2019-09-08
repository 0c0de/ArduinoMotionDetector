#include <NewPing.h>
#include <SoftwareSerial.h>
#include <DFMiniMp3.h>

//Trigger pin set to D1
//Echo pin set to D2
//SoftwareSerial pin is D3,D4 (RX and TX respectively) 


// implement a notification class,
// its member methods will get called 
//
class Mp3Notify
{
public:
  static void OnError(uint16_t errorCode)
  {
    // see DfMp3_Error for code meaning
    Serial.println();
    Serial.print("Com Error ");
    Serial.println(errorCode);
  }
  static void OnPlayFinished(uint16_t track)
  {
    Serial.print("Play finished for #");
    Serial.println(track);  
  }
  static void OnCardOnline(uint16_t code)
  {
    Serial.println("Card online ");
  }
  static void OnUsbOnline(uint16_t code)
  {
    Serial.println("USB Disk online ");
  }
  static void OnCardInserted(uint16_t code)
  {
    Serial.println("Card inserted ");
  }
  static void OnUsbInserted(uint16_t code)
  {
    Serial.println("USB Disk inserted ");
  }
  static void OnCardRemoved(uint16_t code)
  {
    Serial.println("Card removed ");
  }
  static void OnUsbRemoved(uint16_t code)
  {
    Serial.println("USB Disk removed ");
  }
};

// instance a DFMiniMp3 object, 
// defined with the above notification class and the hardware serial class
//DFMiniMp3<HardwareSerial, Mp3Notify> mp3(Serial1);

// Some arduino boards only have one hardware serial port, so a software serial port is needed instead.
// comment out the above definition and uncomment these lines

SoftwareSerial secondarySerial(D3, D4); // RX, TX
DFMiniMp3<SoftwareSerial, Mp3Notify> mp3(secondarySerial);
NewPing sonar(D1,D2, 25);

void setup() 
{
  Serial.begin(115200);
  Serial.println("initializing..."); 
  mp3.begin();
  mp3.reset(); 
  mp3.setVolume(24);
  
  uint16_t mode = mp3.getPlaybackMode();
  Serial.print("playback mode ");
  Serial.println(mode);
  
  Serial.println("starting...");
}

void loop() 
{
  // calling mp3.loop() periodically allows for notifications 
  // to be handled without interrupts
  if(sonar.ping_cm() <= 25){
      mp3.playRandomTrackFromAll();
  }
  
  mp3.loop();
}
