#define Temp_pin 26
#define Tds_pin 12
#define Turb_pin 32
#define Ph_pin 14
#define Vref 3.3
#define Adc_max 4096
 #define Fan_pin 15
#define LED_pin 14
const int size =30;
 float temperature=30.2;
 //int index=0;
// TDS SENSOR

int analogbuffer[size];
int analohtempbuffer[size];
int  analog_turbidity[size];
//int index=0;
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
        return ( 1.0+0.02*(temperature-25.0));
  }

 float average(int arr[], int size)
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
  for(int i=0;i<size;i++)
  {
    analogbuffer[i]=analogRead(Tds_pin);
    delay(500);
  }
  float avg_volt=average(analogbuffer,size);

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
    for(i=0;i<size;i++){
      Serial.println(analog_turbidity[i]);
    }


  }


    //PH SENSOR

 int analogph_buffer[size];
  float ph_sensor;
  float ph_voltage;
  float ph_value;

   float phread(){
    int i;
    for( i=0;i<size;i++){
        analogph_buffer[i]=analogRead(Ph_pin);
        delay(500);

    }
        ph_sensor=average(analogph_buffer,size);

        ph_voltage=ph_sensor*(3.3/4096.0);

        ph_value=3.3*ph_voltage;

         return ph_value;
    
   }



void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
    pinMode(Temp_pin,INPUT);
    pinMode(Tds_pin,INPUT);
    pinMode(Turb_pin,INPUT);
    pinMode(Ph_pin,INPUT);
      
}

void loop(){
  // put your main code here, to run repeatedly:
 float tds=tdsread();
 Serial.println("TDS VALUE  ");
  Serial.print(tds);

   float turb=Turbidity();
   Serial.println("TURBIDITY VALUE  ");
  Serial.print(turb);
  delay(1000);

 float PH_value=phread();
 Serial.println("PH VALUE ");
 Serial.print(PH_value);



}
