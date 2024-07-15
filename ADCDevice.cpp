#include "ADCDevice.hpp"

#define I2C_SMBUS 1
#define I2C_FLAG 0

ADCDevice::ADCDevice(){
    address = 0;
    gpioInitialise(); // gpio initialise
}

int ADCDevice::detectI2C(int addr){
    _fd = i2cOpen(I2C_SMBUS, addr, I2C_FLAG);

    if (_fd < 0) {
        printf("Error address : 0x%x \n",addr);
        return 0 ;
    } else {
        if(i2cWriteByte(_fd,0) < 0){
            printf("Not found device in address 0x%x \n",addr);
            return 0;
        } else {
            printf("Found device in address 0x%x \n",addr);
            return 1 ;
        }
    }
}

int ADCDevice::analogRead(int chn){
    printf("Implemented in subclass! \n");
    return 0;
}

PCF8591::PCF8591(int addr)
{
    address = addr;
    cmd = 0x40; //The default command for PCF8591 is 0x40.

    gpioInitialise(); // gpio initialise

    detectI2C(address);
    printf("PCF8591 setup successful! \n");
}

int PCF8591::analogRead(int chn){
    i2cWriteByte(_fd, cmd+chn);
    i2cReadByte(_fd);
    i2cWriteByte(_fd, cmd+chn);
    return i2cReadByte(_fd);
}
int PCF8591::analogWrite(int value){
    return i2cWriteByteData(_fd, cmd, value);
}

ADS7830::ADS7830(int addr)
{
    address = addr;
    cmd = 0x84; //The default command for ADS7830 is 0x84.

    gpioInitialise(); // initialize gpio

    detectI2C(address);
    printf("ADS7830 setup successful! \n");
}

int ADS7830::analogRead(int chn){
    i2cWriteByte(_fd, cmd|(((chn<<2 | chn>>1)&0x07)<<4));
    return i2cReadByte(_fd);
}
