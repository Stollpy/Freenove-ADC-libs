#include <pigpio.h>
#include <stdio.h>

class ADCDevice {
    protected:
        int _fd;
    public:
        int address;
        int cmd;

        ADCDevice();
        virtual ~ADCDevice(){};
        int detectI2C(int addr);
        virtual int analogRead(int chn);
};

class PCF8591:public ADCDevice {
    public:
        PCF8591(int addr = 0x48);
        int analogRead(int chn);
        int analogWrite(int value);
};

class ADS7830: public ADCDevice {
    public:
        ADS7830(int addr = 0x4b);
        int analogRead(int chn);
};