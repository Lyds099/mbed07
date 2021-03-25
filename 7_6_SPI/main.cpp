#include "mbed.h"

Thread thread1;

//master

SPI spi(D11, D12, D13); // mosi, miso, sclk
DigitalOut cs(D9);

void master()
{
   int number = 0 ;

   while(1){
   // Chip must be deselected
   cs = 1;

   // Setup the spi for 8 bit data, high steady state clock,
   // second edge capture, with a 1MHz clock rate
   spi.format(8, 3);
   spi.frequency(1000000);

   // Select the device by seting chip select low
   cs = 0;

   printf("send number = %d\n", number);

   int response = spi.write(number);
   ThisThread::sleep_for(500ms);
   printf("response from slave = %d\n",response);
   //cs = 1; // Deselect the device
   number += 1 ;
   }

}


int main()
{
   thread1.start(master);
}

// #include "mbed.h"

// SPISlave device(D11, D12, D13, D9); //mosi, miso, sclk,cs

// DigitalOut led(LED3);

// int main()
// {
//    //device.reply(0x00); // Prime SPI with first reply
//    while (1)
//    {
//       device.frequency(1000000);
//       //device.reply(0x00);

//       if (device.receive())
//       {
//             int v = device.read(); // Read byte from master
//             printf("read from master : v = %d\n", v);
//             v = v + 1 ;
//             device.reply(v);
//             led = !led; // led turn blue/orange if device receive

//       }
//    }
// }