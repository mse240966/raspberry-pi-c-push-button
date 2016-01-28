# Raspberry Pi C Push Button

Another little C program. This time to have a go at software GPIO input with a push button. So my C GPIO library using the 'sysfs interface' is slowly moving along!

The code important to this little project is gpio/input.c, gpio/input.h and main.c.  This is where all the new GPIO input code lives.

![pushbutton](https://github.com/mse240966/raspberry-pi-c-push-button/blob/master/docs/pushButton.jpg "Push Button")

## Example

```bash
$ sudo ./pushButton
Press ENTER to quit
```

## Circuit

![circuit](https://github.com/mse240966/raspberry-pi-c-push-button/blob/master/docs/pushButtonCircuit.png "Breadboard Circuit")
