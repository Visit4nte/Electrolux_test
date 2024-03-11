/* Q4) Imagine that you have a microcontroller that communicates to a generic system that may consist
of several other boards via UART. How do you ensure that each message is properly sent and
that its content is correct?
Now imagine that you receive a message and an interruption is triggered every time a new
information is received. Inside every message you have a different command, and for every
command you have different payloads, receiving positive and negative values.
Implement the interrupt and the parser functions in a generic way using the C language*/

#include "driver/uart.h"
#include "freertos/queue.h"
#include "freertos/task.h"

#define MyUart UART_NUM_0 // Define UART0 to be used (USB UART in ESP32)
#define BufferSize (1024) // Define the buffer size

static QueueHandle_t UartQueue; // Create a queue to UART

uint8_t *data = (uint8_t *) malloc(BufferSize); //Allocate memory space to buffer

//---------------------------------- UART Configs
uart_config_t UartSetup = {
    .baud_rate = 9600, 
    .data_bits = UART_DATA_8_BITS, // Define the data size
    .parity = UART_PARITY_EVEN, // Choose the type of parity bit validation (off, even or odd)
    .stop_bits = UART_STOP_BITS_1, // Choose the "end" bit Value
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
};

//--------------------------------- UART interrupt event
static void TaskUartEvent(void *pvParameters){
    
    uart_event_t event;

    size_t buffered_size;

    uint8_t *dtmp = (uint8_t *) malloc(BufferSize); //Alocatte the buffer in the memory

    while (1){
        if (xQueueReceive(UartQueue, (void * )&event, (portTickType)portMAX_DELAY)) // Verify if something happens
            { 
            uart_write_bytes(UART_NUM_0, (const char *) "Event: ", 8); // Send to serial monitor "Event"

//----------------------------------- Verify the type of event and resolve it
            switch (event.type){
            case UART_DATA: // Main Event, data received successfully
                digitalWrite(21, LOW); // light off the led when a interrupt occours 
                break;

            case UART_FIFO_OVF: // Queue overflow problem
                uart_flush(MyUart); // Cleans buffer
                break;

            case UART_BUFFER_FULL: // Buffer full problem
                uart_flush(MyUart);
                break;

            case UART_BREAK: // Occurs when TX holds the line in low state for too much time
                
                break;

            case UART_PARITY_ERR: // Verify parity bit, for this case "even"
                
                break;

            case UART_FRAME_ERR: // UART can't identify clearly when the payload starts and finish
                
                break;

            case UART_PATTERN_DET:
                
                break;

            default:
                
                //drawText("unknown error",0,0); //Unknown happens
                break;
            }
        }
    }

    //it cleans the allocated memory
    free(dtmp);
    dtmp = NULL;

    vTaskDelete(NULL); //Task complete, delete task
}

void setup() {
 
 pinMode(21, OUTPUT);
 digitalWrite(21, HIGH);

//-------------------------------------- UART Setup
  uart_param_config(MyUart, &UartSetup);
  uart_set_pin(MyUart, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
  uart_driver_install(MyUart, BufferSize * 2, BufferSize * 2, 10, &UartQueue, 0);
  uart_enable_pattern_det_intr(MyUart, '+', 3, 10000, 10, 10);

  xTaskCreatePinnedToCore(TaskUartEvent,"TaskUartEvent",10000,NULL,1,NULL,0);
}

void loop() {
  int len = uart_read_bytes(MyUart, data, BufferSize, 100 / portTICK_RATE_MS);
  if (len > 0){
    uart_write_bytes(UART_NUM_0, (const char *) data, len);
    delay(3000);
    digitalWrite(21, HIGH); //Light ON when the program runs 
  }
}