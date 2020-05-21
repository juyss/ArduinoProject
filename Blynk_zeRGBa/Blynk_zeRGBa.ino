#define BLYNK_PRINT Serial // This prints to Serial Monitor
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Define your Physical RGB LED pins here
#define RedPin 14  // Set RED RGB pin
#define GrnPin 12  // Set GREEN RGB pin
#define BluPin 13  // Set BLUE RGB pin

// Define your Virtual pins here
#define zeRGBa V0  // Set virtual RGB widget
#define rSlide V1  // Set virtual RGB widget
#define gSlide V2  // Set virtual RGB widget
#define bSlide V3  // Set virtual RGB widget
#define vRed V4  // Set virtual Red LED widget
#define vGreen V5  // Set virtual Green LED widget
#define vBlue V6  // Set virtual Blue LED widget
#define vRGB V7  // Set virtual RGB widget
#define HEXdisplay V8  // Set virtual RGB widget

int rrr, ggg, bbb;  // Set RED BLUE GREEN channels

char auth[] = "XeomZ9ZGyqRAL7GzSU_FwUuy4IgQsBxb";
char ssid[] = "Tenda_A0D9B8";
char pass[] = "yang1314ai";
//char server[] = "xxx.xxx.xxx.xxx";  // IP for your Local Server
char server[] = "iot.haotech.xyz";  // URL for Blynk Cloud Server
int port = 8080;



void setup() {
  //Serial.begin(9600);  // BLYNK_PRINT data

  pinMode(RedPin, OUTPUT);  // Set RED pinMode
  pinMode(GrnPin, OUTPUT);  // Set GREEN pinMode
  pinMode(BluPin, OUTPUT);  // Set BLUE pinMode

  Blynk.virtualWrite(vRGB, 255);  // Activate vRGB
  Blynk.setProperty(vRGB, "color", "#000000");  // Set vRGB to Black

  WiFi.begin(ssid, pass); 
  Blynk.config(auth, server, port);
  Blynk.connect();
}



BLYNK_CONNECTED() {
  Blynk.syncAll();  // Synchronize hardware with App widgets when connected
}



void loop() {
  Blynk.run();
}



//===== RED slider =====
BLYNK_WRITE(rSlide) { // START Blynk Function
  rrr = param.asInt(); // get a RED channel value
  Blynk.virtualWrite(vRed, rrr);  // Red LED intensity
  Blynk.virtualWrite(zeRGBa, rrr, ggg, bbb);  // Sync zeRGBa position
  RGBprocess(); // Run Arduino funtion
}  // END Blynk Function


//===== GREEN slider =====
BLYNK_WRITE(gSlide) { // START Blynk Function
  ggg = param.asInt(); // get a GREEN channel value
  Blynk.virtualWrite(vGreen, ggg);  // Green LED intensity
  Blynk.virtualWrite(zeRGBa, rrr, ggg, bbb);  // Sync zeRGBa position
  RGBprocess(); // Run Arduino funtion
}  // END Blynk Function


//===== BLUE slider =====
BLYNK_WRITE(bSlide) { // START Blynk Function
  bbb = param.asInt(); // get a BLUE channel value
  Blynk.virtualWrite(vBlue, bbb);  // Blue LED intensity
  Blynk.virtualWrite(zeRGBa, rrr, ggg, bbb);  // Sync zeRGBa position
  RGBprocess(); // Run Arduino funtion
}  // END Blynk Function



//===== zeRGBa Widget  =====
BLYNK_WRITE(zeRGBa) { // START Blynk Function
  rrr = param[0].asInt(); // get a RED channel value
  ggg = param[1].asInt(); // get a GREEN channel value
  bbb = param[2].asInt(); // get a BLUE channel value
  Blynk.virtualWrite(rSlide, rrr);  // Sync RED Slider position
  Blynk.virtualWrite(vRed, rrr);  // Red LED intensity
  Blynk.virtualWrite(gSlide, ggg);  // Sync Green slider position
  Blynk.virtualWrite(vGreen, ggg);  // Green LED intensity
  Blynk.virtualWrite(bSlide, bbb);  // Sinc Blue slider position
  Blynk.virtualWrite(vBlue, bbb);  // Blue LED intensity
  RGBprocess(); // Run Arduino funtion
}  // END Blynk Function



//===== Physical RGB LED Control and HEX conversion =====
void RGBprocess() {  // START Arduino funtion

  /*----- Comment out unneeded grouping based on device and RGB type ----- */
  // ESP with Common Anode+ RGB LED (共阳RGB灯)
//   analogWrite(RedPin, (255 - rrr) * 4 + 4); // Write to RED RGB pin
//   analogWrite(GrnPin, (255 - ggg) * 4 + 4); // Write to GREEN RGB pin
//   analogWrite(BluPin, (255 - bbb) * 4 + 4); // Write to BLUE RGB pin

  // ESP with Common Cathode- RGB LED (共阴RGB灯)
  analogWrite(RedPin, rrr*4+4);  // Write to RED RGB pin
  analogWrite(GrnPin, ggg*4+4);  // Write to GREEN RGB pin
  analogWrite(BluPin, bbb*4+4);  // Write to BLUE RGB pin

  // Arduino with Common Anode+ RGB LED
  //analogWrite(RedPin, 255-rrr);  // Write to RED RGB pin
  //analogWrite(GrnPin, 255-ggg);  // Write to GREEN RGB pin
  //analogWrite(BluPin, 255-bbb);  // Write to BLUE RGB pin

  // Arduino with Common Cathode- RGB LED
  //analogWrite(RedPin, rrr);  // Write to RED RGB pin
  //analogWrite(GrnPin, ggg);  // Write to GREEN RGB pin
  //analogWrite(BluPin, bbb);  // Write to BLUE RGB pin
  /*-----------------------------------------------------------------------*/

  String strRED = String(rrr, HEX);  // Convert RED DEC to HEX
  if (rrr < 16) {
    strRED = String("0" + strRED);  // Buffer with 0 if required
  }  // END if
  String strGRN = String(ggg, HEX);  // Convert GREEN DEC to HEX
  if (ggg < 16)  {
    strGRN = String("0" + strGRN);  // Buffer with 0 if required
  }  // END if
  String strBLU = String(bbb, HEX);  // Convert BLUE DEC to HEX
  if (bbb < 16)  {
    strBLU = String("0" + strBLU);  // Buffer with 0 if required
  }  // END if
  String HEXstring = String("#" + strRED + strGRN + strBLU);  // Combine HEX fragments
  HEXstring.toUpperCase();  // Change HEX value to all upper case for ease of visuals
  Blynk.setProperty(HEXdisplay, "color", HEXstring);  // Change background colour of HEX Data Label
  Blynk.virtualWrite(HEXdisplay, HEXstring);  // Display HEX data
  Blynk.setProperty(vRGB, "color", HEXstring);  // Send formatted HEX colour to vRGB
}  // END Arduino Function
