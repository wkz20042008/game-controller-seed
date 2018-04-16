/* Game Controller */
#include <mbed.h>
#include <EthernetInterface.h>
#include <rtos.h>
#include <mbed_events.h>

#include <FXOS8700Q.h>
#include <C12832.h>

/* display */
C12832 lcd(D11, D13, D12, D7, D10);

/* event queue and thread support */
Thread dispatch;
EventQueue periodic;

/* Accelerometer */
I2C i2c(PTE25, PTE24);
FXOS8700QAccelerometer acc(i2c, FXOS8700CQ_SLAVE_ADDR1);

/* Input from Potentiometers */
AnalogIn  left(A0);

/* User input states */
/*TODO define variables to hold the users desired actions.
    (roll rate and throttle setting)
*/
/* Task for polling sensors */
void user_input(void){
    motion_data_units_t a;
    acc.getAxis(a);

    /*TODO decide on what roll rate -1..+1 to ask for */

    /*TODO decide on what throttle setting 0..100 to ask for */
}

/* States from Lander */
/*TODO Variables to hold the state of the lander as returned to
    the MBED board, including altitude,fuel,isflying,iscrashed
*/
/*TODO YOU will have to hardwire the IP address in here */
SocketAddress lander("192.168.70.35",65200);
SocketAddress dash("192.168.1.13",65250);

EthernetInterface eth;
UDPSocket udp;

/* Task for synchronous UDP communications with lander */
void communications(void){
    SocketAddress source;

    /*TODO Create and format the message to send to the Lander */

    /*TODO Send and recieve messages
            udp.sendto( lander, <message>, <message length>);
            nsapi_size_or_error_t  n =
             udp.recvfrom(&source, <input buffer>, sizeof(<input>buffer));
    */

    /* Unpack incomming message */
    /*TODO split message into lines*/
    /*TODO for each line */
        /*TODO split into key value pairs */
        /*TODO convert value strings into state variables */

}

/* Task for asynchronous UDP communications with dashboard */
void dashboard(void){
    /*TODO create and format a message to the Dashboard */
    /*TODO send the message to the dashboard:
        udp.sendto( dash, <message>, strlen(<message>));
    */
}

char buffer[512];  //////////////////////////////////////////////////
SocketAddress source;/////////////////////////////////

int main() {
    acc.enable();

    /* ethernet connection : usually takes a few seconds */
    printf("conecting \n");
    eth.connect();
    /* write obtained IP address to serial monitor */
    const char *ip = eth.get_ip_address();
    printf("IP address is: %s\n", ip ? ip : "No IP");

    /* open udp for communications on the ethernet */
    udp.open( &eth);

    printf("lander is on %s/%d\n",lander.get_ip_address(),lander.get_port() );
    printf("dash   is on %s/%d\n",dash.get_ip_address(),dash.get_port() );

sprintf(buffer,"command:!\n throttle: 100\n roll: +0.5");
    udp.sendto( lander, buffer, strlen(buffer));   //////////////////////////////////////
    nsapi_size_or_error_t n = udp.recvfrom( &source, buffer, sizeof(buffer));  ///
    buffer[n]='\0';////
    printf("from %s\n", source.get_ip_address());///
    printf("  at %d\n", source.get_port());///
    printf("data %s\n", buffer);///
    printf("----\n");///




    /* periodic tasks */
    /*TODO call periodic tasks;
            communications, user_input, dashboard
            at desired rates.

      periodic.call_every(<time in ms>, <function to call>);
    */

    /* start event dispatching thread */
    dispatch.start( callback(&periodic, &EventQueue::dispatch_forever) );

    while(1) {
        /* update display at whatever rate is possible */
        /*TODO show user information on the LCD */
        /*TODO set LEDs as appropriate to show boolean states */

        wait(1);/*TODO you may want to change this time
                    to get a responsive display */
    }
}
