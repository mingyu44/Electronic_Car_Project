//Blightness Sensor Adress is 0x23
//IR Temperature Sensor Adress is 0x5A

#include <pm2008_i2c.h>
#include <NewPing.h>
#include <Wire.h>
#include <BH1750.h>
#include <Adafruit_MLX90614.h>

#define MaxDistance 2000
#define Buzer 10

int i;
int state[4];

BH1750 lightMeter;
PM2008_I2C pm2008_i2c;
Adafruit_MLX90614 mlx = Adafruit_MLX90614(0x5A);

//sonar(TrigPin, EchoPin, MaxDistance);
NewPing sonar[2] = { 
      NewPing(2, 3, MaxDistance), //front UltraSonic sensor
    NewPing(4, 5, MaxDistance), //back UltraSonic sensor
};

void Reset()
{
    for(i = 0; i < 2; i++)
        state[i] = 0;
}

void PrintValue()
{
    for(i = 0; i < 2; i++)
    {          
        Serial.print(i);
        Serial.print(" Ping : ");
        Serial.print(sonar[i].ping_cm());
        Serial.println("cm");
        if(sonar[i].ping_cm() <= 35)
            state[i] = 3;
        else if(sonar[i].ping_cm() <= 65)
            state[i] = 2;
        else if(sonar[i].ping_cm() <= 90)
            state[i] = 1;
        else
            state[i] = 0;
    }
}

void PrintDistance()    // 기어 변경에 따른 전/후방 표시 변경 
{   
    // 전방(전진)일 경우 
    if(state[0] == 1)
    {
        Serial.println("Front Warnnig");
    }
    else if(state[0] == 2)
    {
        Serial.println("Front Danger");
    }
    else if(state[0] == 3)
    {
        Serial.println("Front very Danger");
    }
    else
    {
        Serial.println("Front Good!");
    }
        
    // 후방(후진)일 경우  
    if(state[1] == 1)
    {
        Serial.println("Back Warnnig");
    }
    else if(state[1] == 2 || state[1] == 3)
    {
        Serial.println("Back Danger");
        Siren();
    }
    else
    {
        Serial.println("Back Good!");
    }
    
}

void Siren()
{
    digitalWrite(Buzer, HIGH);
    delay(300);
    digitalWrite(Buzer, LOW);
    delay(300);
}

void PM2008()
{
    uint8_t ret = pm2008_i2c.read();

    uint8_t pm1p0_grade = 0;
    uint8_t pm2p5_grade = 0;
    uint8_t pm10p_grade = 0;
    uint8_t total_grade = 0;
    
    if (ret == 0) {
    // PM 1.0
    if (pm2008_i2c.pm1p0_grimm < 16)
        pm1p0_grade = 1;
    else if (pm2008_i2c.pm1p0_grimm < 51)
        pm1p0_grade = 2;
    else if (pm2008_i2c.pm1p0_grimm < 101)
        pm1p0_grade = 3;
    else
        pm1p0_grade = 4;

    // PM 2.5
    if (pm2008_i2c.pm2p5_grimm < 16)
        pm2p5_grade = 1;
    else if (pm2008_i2c.pm2p5_grimm < 51)
        pm2p5_grade = 2;
    else if (pm2008_i2c.pm2p5_grimm < 101)
        pm2p5_grade = 3;
    else
        pm2p5_grade = 4;

    // PM 10
    if (pm2008_i2c.pm10_grimm < 31)
        pm10p_grade = 1;
    else if (pm2008_i2c.pm10_grimm < 81)
        pm10p_grade = 2;
    else if (pm2008_i2c.pm10_grimm < 151)
      pm10p_grade = 3;
    else
        pm10p_grade = 4;
    
    // Get worst grade
    total_grade = max(pm1p0_grade, pm2p5_grade);
    total_grade = max(total_grade, pm10p_grade);

    Serial.print("Air: ");
    
    switch (total_grade) {
        case 1:
            Serial.println("Good!");
            break;
        case 2:
            Serial.println("Normal!");
            break;
        case 3:
            Serial.println("Bad!");
            break;
        case 4:
            Serial.println("Worst!");
            break;
        default:
            break;
        }
    }
}

void Blightness()
{
    float lux = lightMeter.readLightLevel();
    Serial.print("Light: ");
    Serial.print(lux);
    Serial.println(" lx");
}

void Temperature()
{
    Serial.print("Ambient = "); 
    Serial.print(mlx.readAmbientTempC());
     
    Serial.print("*C\tObject = "); 
    Serial.print(mlx.readObjectTempC()); 
    Serial.println("*C");

    Serial.println();
}

void setup() {
    Serial.begin(9600);
    Wire.begin();
    lightMeter.begin();
    mlx.begin();
    pm2008_i2c.begin();
    pm2008_i2c.command();
    pinMode(Buzer, OUTPUT);
    
    delay(1000);
}

void loop() {
    Serial.println("===============================================");
    Reset();
    PrintValue();
    PrintDistance();
    
    PM2008();
    Blightness();
    Temperature();
}
