#include <SD.h>

File myFile;

const int chipSelect_SD_default = 27;
const int chipSelect_SD = chipSelect_SD_default;

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  delay(1000);
  Serial.print("Initializing SD card...");

  pinMode(chipSelect_SD_default, OUTPUT);
  digitalWrite(chipSelect_SD_default, HIGH);

  pinMode(chipSelect_SD, OUTPUT);
  digitalWrite(chipSelect_SD, HIGH);
   
  if (!SD.begin(chipSelect_SD)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  if (SD.exists("/test.txt")) {
 	Serial.println("Deleting existing file");
	  SD.remove("/test.txt");
  }
  
  myFile = SD.open("/test.txt", FILE_WRITE);
  
  if (myFile) {
  	char buf[1024];
  	for(int i = 0; i < 1024; i++) {
  		buf[i] = rand();
  	}
    Serial.print("Writing 10MB to test.txt...");
    uint32_t startTime = millis();
    uint32_t bytes = 0;
    while (bytes < 10485760UL) {
    	myFile.write((const uint8_t *)buf, 1024);
    	bytes += 1024;
    }
	
    myFile.close();
    uint32_t endTime = millis();
    Serial.println("done.");
    Serial.print("Time taken: ");
    Serial.print(endTime - startTime);
    Serial.println("ms");
  } else {
    Serial.println("error opening test.txt");
  }
  
  myFile = SD.open("/test.txt");
  if (myFile) {
    Serial.println("Reading data from test.txt:");
    uint32_t startTime = millis();
   
    while (myFile.available()) {
    	(void)myFile.read();
    }
    myFile.close();
    uint32_t endTime = millis();
    Serial.println("done.");
    Serial.print("Time taken: ");
    Serial.print(endTime - startTime);
    Serial.println("ms");
  } else {
    Serial.println("error opening test.txt");
  }
}

void loop()
{
}


