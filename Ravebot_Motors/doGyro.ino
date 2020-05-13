void gyroscpeSetup() {
  tcaSelect(6);
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0);    
  byte endReturn1 = Wire.endTransmission(true);
  if (endReturn1 != 0) {
    skipGyros();
    return;
  }
  tcaSelect(7);
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0);    
  byte endReturn2 = Wire.endTransmission(true);
  if (endReturn2 != 0) {
    skipGyros();
    return;
  }
  tcaSelect(5);
}



void doGyroscpoes() {
  if (!currentlySkipping) {
     setGyroscopeValues();      
  } else if (timey > nextGyroCheck) {
    currentlySkipping = false;
    gyroscpeSetup();
  } else {
    if (testoMode)
      Serial.println("SKKKKIIIIPPPIIIINNNNNGGGG!!!!!!");
  }
}

void skipGyros() {
  nextGyroCheck = timey + 100;
  currentlySkipping = true;
}

void tcaSelect(uint8_t i) {
if (testoMode) {
  Serial.print("(");
  Serial.print(i);
  Serial.print(")...t1");
  delay(5);
}
  if (i > 7) return;
  Wire.beginTransmission(TCAADDR);
if (testoMode) {
  Serial.print("...t2");
  delay(5);
}
  Wire.write(1 << i);
if (testoMode) {
  Serial.print("...t3");
  delay(5);
}
  byte endReturn2 = Wire.endTransmission(true);
if (testoMode) {
  Serial.println("...t4");
  delay(5);
}
  if (endReturn2 != 0) {
    skipGyros();
    return;
  }
}

void setGyroscopeValues() {
  Serial.print("BEFORE:");
  tcaSelect(6);
  Serial.println("......AFTER");
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  byte endReturn1 = Wire.endTransmission(true);
  if (endReturn1 != 0) {
    skipGyros();
    return;
  }
    
  Wire.requestFrom(MPU,12,true);
  if (Wire.available() != 12) {
    skipGyros();
    return;
  }
  
  AcXLeft=Wire.read()<<8|Wire.read();    
  AcYLeft=Wire.read()<<8|Wire.read();  
  AcZLeft=Wire.read()<<8|Wire.read();  
  GyXLeft=Wire.read()<<8|Wire.read();  
  GyYLeft=Wire.read()<<8|Wire.read();
  GyZLeft=Wire.read()<<8|Wire.read();
  tcaSelect(7);
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  byte endReturn2 = Wire.endTransmission(true);
  if (endReturn2 != 0) {
    skipGyros();
    return;
  }
  Wire.requestFrom(MPU,12,true);
  if (Wire.available() != 12) {
    skipGyros();
    return;
  }
  AcXRight=Wire.read()<<8|Wire.read();    
  AcYRight=Wire.read()<<8|Wire.read();  
  AcZRight=Wire.read()<<8|Wire.read();  
  GyXRight=Wire.read()<<8|Wire.read();  
  GyYRight=Wire.read()<<8|Wire.read();  
  GyZRight=Wire.read()<<8|Wire.read();
  tcaSelect(5);

  if (testoMode) {
    printGyroVals();
  }
}

// AcXLeft,AcYLeft,AcZLeft,GyXLeft,GyYLeft,GyZLeft / AcXRight,AcYRight,AcZRight,GyXRight,GyYRight,GyZRight;
void printGyroVals() {
  Serial.print("YL=");
  Serial.print(AcYLeft);
  Serial.print("  YR= ");
  Serial.println(AcYRight); 
}
