/*
  SD card datalogger

  This example shows how to log data from three analog sensors
  to an SD car.

  The circuit:
   analog sensors on analog ins 0, 1, and 2
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)
*/
#include <DFRobot_BMX160.h>
#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;
DFRobot_BMX160 bmx160;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  delay(100);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  //init the hardware bmx160  
  if (bmx160.begin() != true){
    Serial.println("init false");
    while(1);
  }
   delay(100);


  Serial.print("Initializing SD card...");
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
}

void loop() {
  
  sBmx160SensorData_t Omagn, Ogyro, Oaccel;

  /* Get a new sensor event */
  bmx160.getAllData(&Omagn, &Ogyro, &Oaccel);


  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog1.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    /* Display the magnetometer results (magn is magnetometer in uTesla) */
    dataFile.print("Magnetometer   ->  ");  
    dataFile.print("X: "); dataFile.print(Omagn.x  ); dataFile.print("  ");
    dataFile.print("Y: "); dataFile.print(Omagn.y  ); dataFile.print("  ");
    dataFile.print("Z: "); dataFile.print(Omagn.z  ); dataFile.print("  ");
    dataFile.println("uT");

    //*******************************************************************
    /* Display the gyroscope results (gyroscope data is in g) */
    dataFile.print("Gyroscope      ->  ");
    dataFile.print("X: "); dataFile.print(Ogyro.x  ); dataFile.print("  ");
    dataFile.print("Y: "); dataFile.print(Ogyro.y  ); dataFile.print("  ");
    dataFile.print("Z: "); dataFile.print(Ogyro.z  ); dataFile.print("  ");
    dataFile.println("g");

    //*******************************************************************
     /* Display the accelerometer results (accelerometer data is in m/s^2) */
    dataFile.print("Aaccelerometer ->  ");
    dataFile.print("X: "); dataFile.print(Oaccel.x); dataFile.print("  ");
    dataFile.print("Y: "); dataFile.print(Oaccel.y); dataFile.print("  ");
    dataFile.print("Z: "); dataFile.print(Oaccel.z); dataFile.print("  ");
    dataFile.println("m/s^2");
     
    dataFile.println("");
    delay(500);
    dataFile.close();
    Serial.println("Writing to SD-card");
  }
   
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}





  //bmx160.setLowPower();   //disable the gyroscope and accelerometer sensor
  //bmx160.wakeUp();        //enable the gyroscope and accelerometer sensor
  //bmx160.softReset();     //reset the sensor
  
  /** 
   * enum{eGyroRange_2000DPS,
   *       eGyroRange_1000DPS,
   *       eGyroRange_500DPS,
   *       eGyroRange_250DPS,
   *       eGyroRange_125DPS
   *       }eGyroRange_t;
   **/
  //bmx160.setGyroRange(eGyroRange_500DPS);
  
  /**
   *  enum{eAccelRange_2G,
   *       eAccelRange_4G,
   *       eAccelRange_8G,
   *       eAccelRange_16G
   *       }eAccelRange_t;
   */
  //bmx160.setAccelRange(eAccelRange_4G);
