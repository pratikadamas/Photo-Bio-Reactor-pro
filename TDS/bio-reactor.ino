#define Temp_pin 26
#define Tds_pin 27
#define Turb_pin 28
#define Ph_pin 29
#define Vref 3.3
#define Adc_max 4096
#define Fan_pin 15
#define LED_pin 14
#define size 30
int analogbuffer[size];
int analohtempbuffer[size];
int  analog_turbidity[size];
int index=0;
int temp=25;
float averagevoltage=0;

  float Tdsvalue(float x){

    return (133.42*x*x*x- 255.86*x*x + 857.39*x)*0.5;
  }

 float compensationVoltage(float X,float Y)
 {
   return X/Y;
 }

 float compensationCoefficient()
  {
        return 1.0+0.02*(temperature-25.0);
  }

 float  avg_voltage(int arr[],size)
 {
  int sum=0,i;
  for(i=0;i<size;i++)
   {
     sum=sum+arr[i];
  }
  float avg=sum/size;
 
   return avg;
 }


   float tdsread()
  {
  for(index=0;index<size;index++)
  {
    analogbuffer[index]=analogRead(Tds_pin);
    delay(500);
  }
  float avg_volt=avg_voltage(analogbuffer,size);

  averagevoltage = avg_volt*Vref/Adc_max;

 // float compensationCoefficient = 1.0+0.02*(temperature-25.0);
                                                                        //temperature compensation
     float Com_Coefficient= compensationCoefficient();

//compensationVoltage=averageVoltage/compensationCoefficient;

   float Com_Voltage=compensationVoltage(averagevoltage,Com_Coefficient);
 
// float tdsValue=(133.42*compensationVoltage*compensationVoltage*compensationVoltage - 255.86*compensationVoltage*compensationVoltage + 857.39*compensationVoltage)*0.5;
      
    float tdsValue=Tdsvalue(Com_Voltage);

   return tdsValue;
}


float turbidity_value( float x)
    {

    return 0.00185*x*x-3.22*x+1410.031;
   }


  float Turbidity(){
int i;
 for(i=0;i<size;i++){
  analog_turbidity[i]=analogRead(Tds_pin);
  delay(500);
 }
 float avg_volt=avg_voltage(analog_turbidity,size);
    float Averagevoltage = avg_volt*Vref/Adc_max;
    float turb_value=turbidity_value(Averagevoltage);
    return turb_value;


  }



void setup() {
  // put your setup code here, to run once:
    serial.begin(115200);
    pinMode(Temp_pin,INPUT);
    pinMode(Tds_pin,INPUT);
    pinMode(Turb_pin,INPUT);
    pinMode(Ph_pin,INPUT);
    pinMode(Fan_pin,OUTPUT);
    pinMode(LED_pin,OUTPUT);
    // Turn off the LED initially
    digitalWrite(LED_pin, LOW);
    
}

void loop() {
  // put your main code here, to run repeatedly:
  float tds=tdsread();
  serial.println("TDS VALUE  ");
  serial.print(tds);

   float turb=Turbidity();
   serial.println("TURBIDITY VALUE  ");
  serial.print(turb);



}
