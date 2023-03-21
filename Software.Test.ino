/*Calibrates ADE9000*/
/*The calibration inputs are stored in the ADE9000CalibrationInputs.h file. The phase and parameter being calibrated is input through the serial console*/
/*Calbration constants are computed and stored in the EEPROM */
/*Caibration should be done with the end application settings. If any  parameters(GAIN,High pass corner,Integrator settings) are changed, the device should be recalibrated*/
/*This application assumues the PGA_GAIN among all current channels is same.Also, the PGA_GAIN among all voltage channels should be same*/

#include <SPI.h>
#include <ADE9000RegMap.h>
#include <ADE9000API.h>
#include <math.h>
#include <Wire.h>

ADE9000Class ade9000;
#define ADE9000_h

#define SPI_SPEED 5000000
#define CS_PIN 1
#define PM_1 4
#define IRQ_1 3

void setup() {
  Serial.begin(9600);
  ade9000.init(CS_PIN, PM_1, IRQ_1, SPI_SPEED);
}


void loop() {
  uint32_t temperature_cfg = ade9000.read32(ADDR_TEMP_CFG);
  uint32_t temperature_rslt = ade9000.read32(ADDR_TEMP_RSLT);

  float temperature = ((temperature_rslt >> 8) & 0xFF) + ((temperature_rslt & 0xFF) / 256.0);
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  delay(1000);
}
