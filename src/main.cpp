#include <Arduino.h>
#include <Ethernet.h>
#include <SPI.h>
#include "JEMonDebug.h"
#include "JEMonChannel.h"
#include "JEMonAPI.h"

//--------------------------------------------------------------------------------------
// Configuration: Global
//--------------------------------------------------------------------------------------
int sdcardPin = 4;       // Arduino SD card pin
int ethernetPin = 53;    // Arduino ethernet pin

byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };   // Local ethernet MAC address
byte bind_address[] = { 192,168,11,50 };                // Local IP address
byte api_address[] = { 10,255,1,12 };                   // Remote API endpoint address
uint16_t api_port = 80;                                 // Remote API endpoint port
char params[400];

//--------------------------------------------------------------------------------------
// Configuration: Emon
//--------------------------------------------------------------------------------------
int wavelengths = 50; // number of wavelengths to sample
int inPinV = 1;       // Analog input pin number that voltage signal is connected to
int inPinI_1 = 0;     // Analog input pin number that current signal is connected to. Channel 1
int inPinI_2 = 2;     // Analog input pin number that current signal is connected to. Channel 2

double VCAL = 1.0537291954;       // Voltage calibration scaler
double ICAL_1 = 0.149154781772;   // Current calibration scaler - channel 1
double ICAL_2 = 0.15124516206064; // Current calibration scaler - channel 2

double PHASECAL = 2.3;   // Shifts voltage relative to current, subtracting any phase shifting caused by components
int emon_timeout = 2000; // how long to wait (ms) if something goes wrong.

JEMonChannel ch1 = JEMonChannel(wavelengths, inPinV, VCAL, PHASECAL, emon_timeout);
JEMonChannel ch2 = JEMonChannel(wavelengths, inPinV, VCAL, PHASECAL, emon_timeout);

//unsigned long wtime;

//--------------------------------------------------------------------------------------
// JEMon Webservice
//--------------------------------------------------------------------------------------
JEMonAPI api = JEMonAPI(ethernetPin, sdcardPin, api_address, api_port);
//JEMonDebug debugUtil;

int main(void)
{
	init();

	setup();

	for (;;)
		loop();

	return 0;
}

//--------------------------------------------------------------------------------------
// Arduino: Main Program
//--------------------------------------------------------------------------------------
void setup() {

  Serial.print("Ethernet PIN: ");
  Serial.print(ethernetPin);
  Serial.print("SD Card PIN: ");
  Serial.print(sdcardPin);
  Serial.print(", IP: ");
  Serial.print(bind_address[0]);
  Serial.print(".");
  Serial.print(bind_address[1]);
  Serial.print(".");
  Serial.print(bind_address[2]);
  Serial.print(".");
  Serial.print(bind_address[3]);

  Serial.begin(115200);
  Ethernet.begin(mac, bind_address);
  delay(1000);
}

void loop() { 

  //-------------------------------------------------------------------------------------------
  // 1) Calculate energy monitor values
  //-------------------------------------------------------------------------------------------
  ch1.emon_calc(inPinI_1, ICAL_1); //Energy Monitor calc function for channel 1, pass Arduino analog in pin nummber and calibration coefficient
  ch2.emon_calc(inPinI_2, ICAL_2); //Energy Monitor calc function, for channel 2, pass Arduino analog in pin nummber and calibration coefficient

  delay(2000);
  ch1.wh = ch1.wh + ch1.whInc; //Accumulate wh for channel 1 until ethernet send
  ch2.wh = ch2.wh + ch2.whInc; //Accumulate wh for channel 2 until ethernet send

  // Channel 1 - realPower
  char pRealPower1[16];
  char pRealPower1Text[13] = "&realPower1=";
  dtostrf(ch1.realPower, 3, 15, pRealPower1);
  strcat(params, pRealPower1Text);
  strcat(params, pRealPower1);

  // Channel 1 - apparentPower
  char pApparentPower1[6];
  char pApparentPower1Text[17] = "&apparentPower1=";
  dtostrf(ch1.apparentPower, 3, 15, pApparentPower1);
  strcat(params, pApparentPower1Text);
  strcat(params, pApparentPower1);

  // Channel 1 - powerFactor
  char pPowerFactor1[16];
  char pPowerFactor1Text[15] = "&powerFactor1=";
  dtostrf(ch1.powerFactor, 3, 15, pPowerFactor1);
  strcat(params, pPowerFactor1Text);
  strcat(params, pPowerFactor1);

  // Channel 1 - Vrms
  char pVrms1[16];
  char pVrms1Text[8] = "&Vrms1=";
  dtostrf(ch1.Vrms, 3, 15, pVrms1);
  strcat(params, pVrms1Text);
  strcat(params, pVrms1);

  // Channel 1 - Irms
  char pIrms1[16];
  char pIrms1Text[8] = "&Irms1=";
  dtostrf(ch1.Irms, 3, 15, pIrms1);
  strcat(params, pIrms1Text);
  strcat(params, pIrms1);

  // Channel 1 - whInc
  char pWhInc1[16];
  char pWhInc1Text[9] = "&whInc1=";
  dtostrf(ch1.whInc, 3, 15, pWhInc1);
  strcat(params, pWhInc1Text);
  strcat(params, pWhInc1);

  // Channel 1 - wh
  char pWh1[16];
  char pWh1Text[6] = "&wh1=";
  dtostrf(ch1.wh, 3, 15, pWh1);
  strcat(params, pWh1Text);
  strcat(params, pWh1);

  // Channel 2 - realPower
  char pRealPower2[16];
  char pRealPower2Text[13] = "&realPower2=";
  dtostrf(ch2.realPower, 3, 15, pRealPower2);
  strcat(params, pRealPower2Text);
  strcat(params, pRealPower2);

  // Channel 2 - apparentPower
  char pApparentPower2[6];
  char pApparentPower2Text[17] = "&apparentPower2=";
  dtostrf(ch2.apparentPower, 3, 15, pApparentPower2);
  strcat(params, pApparentPower2Text);
  strcat(params, pApparentPower2);

  // Channel 2 - powerFactor
  char pPowerFactor2[16];
  char pPowerFactor2Text[15] = "&powerFactor2=";
  dtostrf(ch2.powerFactor, 3, 15, pPowerFactor2);
  strcat(params, pPowerFactor2Text);
  strcat(params, pPowerFactor2);

  // Channel 2 - Vrms
  char pVrms2[16];
  char pVrms2Text[8] = "&Vrms2=";
  dtostrf(ch2.Vrms, 3, 15, pVrms2);
  strcat(params, pVrms2Text);
  strcat(params, pVrms2);

  // Channel 2 - Irms
  char pIrms2[16];
  char pIrms2Text[8] = "&Irms2=";
  dtostrf(ch2.Irms, 3, 15, pIrms2);
  strcat(params, pIrms2Text);
  strcat(params, pIrms2);

  // Channel 2 - whInc
  char pWhInc2[16];
  char pWhInc2Text[9] = "&whInc2=";
  dtostrf(ch2.whInc, 3, 15, pWhInc2);
  strcat(params, pWhInc2Text);
  strcat(params, pWhInc2);
  
  // Channel 2 - wh
  char pWh2[16];
  char pWh2Text[6] = "&wh2=";
  dtostrf(ch2.wh, 3, 15, pWh2);
  strcat(params, pWh2Text);
  strcat(params, pWh2);
  
  api.post("/index.php/IndexController/arduino", params);

  /*
  Serial.println("");
  Serial.println("------------------------------------------");
  Serial.print("Free Memory: ");
  Serial.println(freemem());
  Serial.println("------------------------------------------");
  Serial.println("");
  */

  delay(3000);
}

/*
int freemem() {

 int free_memory;

 if((int)__brkval == 0)
   free_memory = ((int)&free_memory) - ((int)&__bss_end);
 else
   free_memory = ((int)&free_memory) - ((int)__brkval);

 return free_memory;
}
*/
