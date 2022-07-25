#include <LiquidCrystal_I2C.h>    //ic2 라이브러리 실행       
LiquidCrystal_I2C lcd(0x27, 16, 2); 


int Vo = A0;  //팬,rgb,센서의 핀 위치 설정  
int V_LED = 2;

float Vo_value = 0;
float Voltage = 0;
float dustDensity = 0;

int LED_R = 9;
int LED_G = 10;
int LED_B = 11;

int FAN = A1;

void setup() {
  
  Serial.begin(9600);

  pinMode(V_LED, OUTPUT);    //rgb설정
  pinMode(Vo, INPUT);

  lcd.init();                
  lcd.backlight();          //초기설정
  pinMode(LED_R, OUTPUT); 
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  digitalWrite(LED_R, LOW); 
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);

  pinMode(FAN, OUTPUT);     //팬 초기설정
  digitalWrite(FAN, LOW);
}

void loop() {
  digitalWrite(V_LED, LOW);
  delayMicroseconds(280);
  Vo_value = analogRead(Vo);
  delayMicroseconds(40);
  digitalWrite(V_LED, HIGH);
  delayMicroseconds(9680);

  Voltage = Vo_value / 1024 * 5.0;
  dustDensity = (Voltage - 0.3) / 0.005;
  Serial.println(dustDensity);


  lcd.clear();        
  lcd.home();        
  if( dustDensity > 150 ){          //수치에 알맞게 lcd에 표시
    lcd.print("AIR : VERY BAD!!");   
  }else if( dustDensity > 80){   
    lcd.print("AIR : BAD!      ");   
  }else if( dustDensity > 30){  
    lcd.print("AIR : NORMAL     ");   
  }else{                    
    lcd.print("AIR : GOOD      ");   
  }
  lcd.setCursor(0, 1); 
  lcd.print("ug/m3:");   //단위는 ug/m3 
  lcd.print(dustDensity);

  if(dustDensity > 150){        //수치에 알맞게 rgb설정
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
  }else if(dustDensity > 80){
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, HIGH);    
  }else if(dustDensity > 30){
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, LOW);    
  }else{
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, LOW);    
  }


  if(dustDensity > 120){     //일정 수치 이상시 팬 작동
    digitalWrite(FAN, HIGH);
  }else{
    digitalWrite(FAN, LOW);    
  }
  
  delay(1000);

}
