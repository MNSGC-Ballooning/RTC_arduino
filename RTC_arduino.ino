// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include <SD.h>
#include "RTClib.h"

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif

//#define chipSelect 8  //Sparkfun micro-SD shield(*for micro SD)
//#define chipSelect 10 //Adafruit SD shield(*for micro SD)

//File datalog;                     //File object for datalogging (*for micro SD)
//char filename[] = "LOGGER00.csv"; //Give your file a name here (*for micro SD)
//bool SDactive = false;            //used to check for SD card before attempting to log (*for micro SD)

RTC_DS1307 rtc;

double instantTime;
double pastTime;
double delayTime = 0;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup () {

  #ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
  #endif
  
  Serial.begin(115200);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

    //if( !rtc.isrunning()){      If you don't want to set a new time
    //following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    //This line sets the RTC with an explicit date & time, for example to set
    //May 24, 2019 at 10:8:52am you would call:
    //rtc.adjust(DateTime(2019, 5, 24, 10, 8, 52));

    /*pinMode(10, OUTPUT);      //Needed for SD library, regardless of shield used (*for micro SD)(*for micro SD)

    Serial.print("Initializing SD card...");
    if(!SD.begin(chipSelect))                                 //attempt to start SD communication (*for micro SD)
      Serial.println("Card failed, or not present");          //print out error if failed; remind user to check card (*for micro SD)
    else {                                                    //if successful, attempt to create file (*for micro SD)
      Serial.println("Card initialized.\nCreating File..."); //(*for micro SD)
      for (byte i = 0; i < 100; i++) // (*for micro SD)
      {                        //can create up to 100 files with similar names, but numbered differently (*for micro SD)
        filename[6] = '0' + i/10; //(*for micro SD)
        filename[7] = '0' + i%10; //(*for micro SD)
        if (!SD.exists(filename)) {                           //if a given filename doesn't exist, it's available (*for micro SD)
        datalog = SD.open(filename, FILE_WRITE);            //create file with that name (*for micro SD)
        SDactive = true;                                    //activate SD logging since file creation was successful(*for micro SD)
        Serial.println("Logging to: " + String(filename));  //Tell user which file contains the data for this run of the program (*for micro SD)
        break;                                              //Exit the for loop now that we have a file (*for micro SD)
       }
    }
    if (!SDactive) Serial.println("No available file names; clear SD card to enable logging"); (*for micro SD)
    }

    String header = "Year, Month, Day, Hour, Min, Sec";  //setup data format, and print it to the monitor and SD card
    Serial.println(header); // Prints set-up to SD card (*for micro SD)
    if (SDactive) {  // (*for micro SD)
      datalog.println(header); //(*for micro SD)
      datalog.close(); //(*for micro SD)
    } */                                                    //(*for micro SD)
}


void loop () {
    DateTime now = rtc.now();
    DateTime past = DateTime(2019, 6, 1, 9, 30, 0); // Adjust reference date here

    Serial.println("Now ");
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    Serial.println();


    /*Serial.println("Past ");
    Serial.print(past.year(), DEC);
    Serial.print('/');
    Serial.print(past.month(), DEC);
    Serial.print('/');
    Serial.print(past.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[past.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(past.hour(), DEC);
    Serial.print(':');
    Serial.print(past.minute(), DEC);
    Serial.print(':');
    Serial.print(past.second(), DEC);
    Serial.println();
    Serial.print(past.unixtime());
    Serial.println();*/

    /*
     * Code for comma separated date
     * 
    Serial.print(now.year(), DEC);
    Serial.print(',');
    Serial.print(monthConvert(now.month()), DEC);
    Serial.print(',');
    Serial.print(now.day(), DEC);
    Serial.print(",");
    Serial.print(now.hour(), DEC);
    Serial.print(',');
    Serial.print(now.minute(), DEC);
    Serial.print(',');
    Serial.print(now.second(), DEC);
    Serial.println();
    */

    /*if (!SD.exists(filename)) {                           //if a given filename doesn't exist, it's available (*for micro SD)
      datalog = SD.open(filename, FILE_WRITE);            //create file with that name (*for micro SD)
      SDactive = true;                                    //activate SD logging since file creation was successful (*for micro SD)
      Serial.println("Logging to: " + String(filename));  //Tell user which file contains the data for this run of the program (*for micro SD)
                                                   //Exit the for loop now that we have a file (*for micro SD)
    } //(*for micro SD)
    

    String data = (String) now.year() + "," + (String) now.month() + "," + (String) now.day() + "," + (String) now.hour() + "," + (String) now.minute() + "," + (String) now.second(); (*for micro SD)
    if (SDactive) { //(*for micro SD)
      datalog = SD.open(filename, FILE_WRITE); // (*for micro SD)
      datalog.println(data);          //print data to SD card..  (*for micro SD)
      datalog.close();                //close file afterward to ensure data is saved properly (*for micro SD)
    }*/                                 // (*for micro SD)
    
    
    Serial.print("Since 9:30:00 6/1/2019 = "); // Adjust reference date here
    Serial.print(timeSec(now, past) + delayTime);
    Serial.print(" seconds");
    
    Serial.println();
    delay(3000);
    delayTime+=3;
}

int monthConvert(String Month)
{
  int m;
  switch(Month[0])
  {
    case 'J': m = Month[1] == 'a' ? 1 : m = Month[2] == 'n' ? 6: 7; break;
    case 'F': m = 2; break;
    case 'A': m = Month[2] == 'r' ? 4 : 8; break;
    case 'M': m = Month[2] == 'r' ? 3 : 5; break;
    case 'S': m = 9; break;
    case 'O': m = 10; break;
    case 'N': m = 11; break;
    case 'D': m = 12; break;
  }
  return m;
}

double timeSec(DateTime now, DateTime past)
{
  instantTime = now.unixtime();
  pastTime = past.unixtime();
  //Serial.println(instantTime);
  //Serial.println();
  //Serial.println(pastTime);
  //Serial.println();
  return (instantTime - pastTime);
}
