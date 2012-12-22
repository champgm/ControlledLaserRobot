#include "SoftwareSerial.h"
#include "Servo.h"
#include <avr/pgmspace.h>
#include <avrpins.h>
#include <max3421e.h>
#include <usbhost.h>
#include <usb_ch9.h>
#include <Usb.h>
#include <usbhub.h>
#include <avr/pgmspace.h>
#include <address.h>
#include <hidboot.h>
#include <printhex.h>
#include <message.h>
#include <hexdump.h>
#include <parsetools.h>

class MouseRptParser : public MouseReportParser
{
protected:
	virtual void OnMouseMove	(MOUSEINFO *mi);
	virtual void OnLeftButtonUp	(MOUSEINFO *mi);
	virtual void OnLeftButtonDown	(MOUSEINFO *mi);
	virtual void OnRightButtonUp	(MOUSEINFO *mi);
	virtual void OnRightButtonDown	(MOUSEINFO *mi);
	virtual void OnMiddleButtonUp	(MOUSEINFO *mi);
	virtual void OnMiddleButtonDown	(MOUSEINFO *mi);
};
void MouseRptParser::OnMouseMove(MOUSEINFO *mi)	
{
    Serial.print("dx=");
    Serial.print(mi->dX, DEC);
    Serial.print(" dy=");
    Serial.println(mi->dY, DEC);
    
//    newY=currentY+(float(mi->dY));
//    newX=currentX+(float(mi->dY));
//    currentY=newY;
//    currentX=newX;
//    myservoy.write(calculateSv(newY));
//    myservox.write(calculateSh(newX));
//    if(currentX>180){
//      currentX=180;
//    }
//    if(currentY>180){
//      currentY=180;
//    }
//    if(currentX<0){
//      currentX=0;
//    }
//    if(currentY<0){
//      currentY=0;
//    }

};
void MouseRptParser::OnLeftButtonUp	(MOUSEINFO *mi)	
{
    Serial.println("L Butt Up");
};
void MouseRptParser::OnLeftButtonDown	(MOUSEINFO *mi)
{
    Serial.println("L Butt Dn");
};
void MouseRptParser::OnRightButtonUp	(MOUSEINFO *mi)
{
    Serial.println("R Butt Up");
};
void MouseRptParser::OnRightButtonDown	(MOUSEINFO *mi)
{
    Serial.println("R Butt Dn");
};
void MouseRptParser::OnMiddleButtonUp	(MOUSEINFO *mi)
{
    Serial.println("M Butt Up");
};
void MouseRptParser::OnMiddleButtonDown	(MOUSEINFO *mi)
{
    Serial.println("M Butt Dn");
};

USB  Usb;
USBHub  Hub(&Usb);
HIDBoot<HID_PROTOCOL_MOUSE>    Mouse(&Usb);
uint32_t next_time;
MouseRptParser  Prs;


int debug=0;
Servo myservox;  //ROTATION
Servo myservoy;  //TILT
int ledPin=2;
float currentX=75;
float currentY=75;
float newY=0;
float newX=0;
float H=33.75;
float pi=3.14159;
float holdY=0;

float calculateSv(float Y){
	//degrees = radians*(pi/180)
	holdY=Y;
	double Sv= 0;
	double Bv= 250.79755;
	double Mv= -1.6670657;
	float rad2deg=atan(Y/H)*(180/pi);
	float AX=rad2deg*Mv;
	Sv=AX+Bv;
	return Sv;
}
float calculateSh(float X){
	//degrees = radians*(pi/180)
	float Sh=0;
	float Bh=78.803589;
	float Mh=-2.4749512;
	float squares=sqrt(pow(X,2)+pow(holdY,2));
	float angle=asin(X/squares)*(180/pi);
	float AX=angle*Mh;
	Sh=(AX+Bh);
	return Sh;
}

void setup()
{
    Serial.begin( 115200 );
    Serial.println("Start");

    if (Usb.Init() == -1)
        Serial.println("OSC did not start.");
  
    delay( 200 );
    next_time = millis() + 5000;
    Mouse.SetReportParser(0,(HIDReportParser*)&Prs);
}

void loop()
{
  Usb.Task();
}

