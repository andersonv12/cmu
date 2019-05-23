#define GRNLED D2
int stagrn = LOW;

#define REDLED D4
int stared = LOW;

void iniciaGPIO(void){
  
  pinMode(GRNLED, OUTPUT);
  digitalWrite(GRNLED, LOW);

  pinMode(REDLED, OUTPUT);
  digitalWrite(REDLED, LOW);
  
}
