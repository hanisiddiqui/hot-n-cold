import processing.serial.*;


//Serial Info
String portName = "COM5";
Serial port;
int BaudRate = 9600;
String inString; 

//Temprature Variables
float [] tdata = new float [17];
float [] TempData = new float [17];

//Miscallaneous Variables
String buff;
PFont font;
float colorGreen;
int lbTemp = 15;
int hbTemp = 40;

//Initial Setup
void setup() {
  size (640, 640);

  port = new Serial (this, portName, BaudRate);
  port.bufferUntil('\n');

  //Setting font for display

  font = loadFont("ArialMT-48.vlw");
  textFont(font, 40);
}

void draw() {
  background (0, 0, 0);

  int j = 0;
  int x = 0;

  do
  {
    if ((tdata[j] != tdata[j]) || (tdata[j] > 50))
    {
      j++;
    } else
    {
      TempData[x] = tdata[j];
      j++;
      x++;
    }
    print("tdata");
    println();
    printArray (tdata);
    println();
    printArray (TempData);
    println();
  }
  while (j < tdata.length);





  for (int i = 0; i < TempData.length; i++) {

    colorGreen = map(TempData[i], lbTemp, hbTemp, 255, 0);
    fill(255, colorGreen, 0);

    rect((i%4)*160, floor(i/4)*160, 160, 160);
    if (TempData[i]<5) {
      fill(255);
    } else {
      fill(0);
    }

    textAlign (CENTER, CENTER);
    textSize (40);
    text (str(TempData[i]), (i%4)*160+80, floor(i/4)*160+80);
    textSize(20);

    text("Relative Temperature " + str(TempData[0]), 140, 10);
  }
}

void serialEvent (Serial port)
{
  inString = port.readStringUntil('\n');
  inString = inString.substring(0, inString.length() - 1);
  tdata = float(split(inString, ','));
}
