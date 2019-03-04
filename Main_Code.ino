//Including relevant libraries
#include <Wire.h>

//Defining relevant addresses for I2C
#define D6T_ADDRESS 0x0A //Address for the D6T Sensor
#define D6T_COMMAND 0x4C //Command to retrieve information from D6T

//Initializing variables for relevant D6T input data
int ReadMem [35]; //Info from D6T
float temp_ref; //Reference temp 
float temp_pixels [16]; //4x4 pixel temperatures 

unsigned long int milli_time;    //variable to hold the time

int x = 0;

void setup() {
  //Intialize I2C ports
  Wire.begin();
  Serial.begin(9600);
  delay (500);
    Serial.println("CLEARDATA");        //This string is defined as a 
                                      // commmand for the Excel VBA 
                                      // to clear all the rows and columns
  Serial.println("LABEL,Computer Time,Time (Milli Sec.),Temp1,Temp2,Temp3,Temp4,Temp5,Temp6,Temp7,Temp8,Temp9,Temp10,Temp11,Temp12,Temp13,Temp14,Temp15,Temp16");  
                                      //LABEL command creates label for 
                                      // columns in the first row with bold font

}


void loop() {
  
  int i;

  //Asking D6T for data retrieval 
  Wire.beginTransmission (D6T_ADDRESS);
  Wire.write(D6T_COMMAND);
  Wire.endTransmission();

  //Retrieval and proccessing of data 
  Wire.requestFrom (D6T_ADDRESS, 35);

  //Filling data into memory 
  for (i = 0; i < 35; i++)
  {
    ReadMem [i] = Wire.read();
  }

  //Proccessing data into celcius
  //Byte 01 = Reference temperature
  //Byte 2-33 = Pixel temperature data
  //Byte 34 = Packet error check
  temp_ref = (ReadMem[0] + (ReadMem[1]*256))*0.1; //Reference temperature 

  //Pixel temperature data
  for (i = 0; i < 16; i++)
  {
    temp_pixels[i] = (ReadMem[(i*2+2)] + (ReadMem[(i*2+3)]*256))*0.1;
  }

 if (temp_pixels[0] > 0) //Check to see if there is data
 {
 milli_time = millis();
  Serial.print("DATA,TIME,");
  Serial.print(milli_time);
  Serial.print(",");
  Serial.print(temp_pixels[1]);
    Serial.print(",");
  Serial.print(temp_pixels[2]);
    Serial.print(",");
  Serial.print(temp_pixels[3]);
      Serial.print(",");
  Serial.print(temp_pixels[4]);
      Serial.print(",");
  Serial.print(temp_pixels[5]);
      Serial.print(",");
  Serial.print(temp_pixels[6]);
      Serial.print(",");
  Serial.print(temp_pixels[7]);
      Serial.print(",");
  Serial.print(temp_pixels[8]);
      Serial.print(",");
  Serial.print(temp_pixels[9]);
      Serial.print(",");
  Serial.print(temp_pixels[10]);
      Serial.print(",");
  Serial.print(temp_pixels[11]);
      Serial.print(",");
  Serial.print(temp_pixels[12]);
      Serial.print(",");
  Serial.print(temp_pixels[13]);
      Serial.print(",");
  Serial.print(temp_pixels[14]);
      Serial.print(",");
  Serial.print(temp_pixels[15]);
      Serial.print(",");
  Serial.println(temp_pixels[16]);  
  delay(100);                    //Take samples every one second
  
 }
   


//  //Display temperature readings
//  float tempC;
//
//  //Print temperature readings in celsius
//  if (temp_pixels[0] > 0) //Check to see if there is data
//  {
//    for (i = 0; i < 16; i++)
//    {
//      tempC = temp_pixels[i];
//      Serial.print (tempC);
//      Serial.print(',');
//    }
//    Serial.print (temp_ref);
//    Serial.print (',');
//    Serial.println();
//  }  


  
}
