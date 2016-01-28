#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>

#include "gpio/gpio.h"
#include "gpio/input.h"

#define GPIO_PIN_LED        GPIO_PIN_17
#define GPIO_PIN_BUTTON     GPIO_PIN_04

static void setLedState(int inputValue);

/*
 * Program main entry point
 */
int main()
{
    int returnStatus = EXIT_SUCCESS;

    // Tidy up if required
    gpioUnexport(GPIO_PIN_BUTTON);
    gpioUnexport(GPIO_PIN_LED);

    // Setup GPIO pins
    returnStatus = gpioExportAndDirection(GPIO_PIN_BUTTON, GPIO_INPUT);
    assert(returnStatus == EXIT_SUCCESS);

    returnStatus = gpioExportAndDirection(GPIO_PIN_LED, GPIO_OUTPUT);
    assert(returnStatus == EXIT_SUCCESS);

    // Create input parameters
    GPIO_INPUT_PARAMETERS inputParameters =
    {
        .gpioPin            = GPIO_PIN_BUTTON,
        .sleepDelay         = 10000,
        .inputValueChanged  = setLedState
    };

    // Create input thread
    returnStatus = pthread_create(&inputParameters.threadId, NULL, &inputPollGpioPin, (void*)&inputParameters);
    assert(returnStatus == EXIT_SUCCESS);

    // Key thread running until enter key pressed
    printf("Press ENTER to quit\n");
    getchar();

    // Terminate input thread
    inputParameters.terminate = true;

    returnStatus = pthread_join(inputParameters.threadId, NULL);
    assert(returnStatus == EXIT_SUCCESS);

    // Tidy up
    returnStatus = gpioUnexport(GPIO_PIN_LED);
    assert(returnStatus == EXIT_SUCCESS);

    returnStatus = gpioUnexport(GPIO_PIN_BUTTON);
    assert(returnStatus == EXIT_SUCCESS);

    return returnStatus;
}

/*
 * Change the state of the Led
 */
static void setLedState(int inputValue)
{
    int returnStatus = gpioWrite(GPIO_PIN_LED, inputValue);
    assert(returnStatus == EXIT_SUCCESS);
}
