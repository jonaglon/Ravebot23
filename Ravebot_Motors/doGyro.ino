void gyroscpeSetup() {
  tcaSelect(6);
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission(true);
  tcaSelect(7);
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission(true);
  tcaSelect(5);
}

void tcaSelect(uint8_t i) {
  if (i > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}

void setGyroscopeValues() {
  tcaSelect(6);
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true);
  AcXLeft=Wire.read()<<8|Wire.read();    
  AcYLeft=Wire.read()<<8|Wire.read();  
  AcZLeft=Wire.read()<<8|Wire.read();  
  GyXLeft=Wire.read()<<8|Wire.read();  
  GyYLeft=Wire.read()<<8|Wire.read();
  GyZLeft=Wire.read()<<8|Wire.read();
  Wire.endTransmission();
  tcaSelect(7);
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true);
  AcXRight=Wire.read()<<8|Wire.read();    
  AcYRight=Wire.read()<<8|Wire.read();  
  AcZRight=Wire.read()<<8|Wire.read();  
  GyXRight=Wire.read()<<8|Wire.read();  
  GyYRight=Wire.read()<<8|Wire.read();  
  GyZRight=Wire.read()<<8|Wire.read();  
  Wire.endTransmission();
  tcaSelect(5);
}

/* AcXLeft,AcYLeft,AcZLeft,GyXLeft,GyYLeft,GyZLeft / AcXRight,AcYRight,AcZRight,GyXRight,GyYRight,GyZRight;
void printVals() {
  Serial.print("YL=");
  Serial.print(AcYLeft);
  Serial.print("  YR= ");
  Serial.println(AcYRight); 
} */
