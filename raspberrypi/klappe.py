import time
import RPi.GPIO as GPIO


# pin definitions
motor_r = 13  # Rechtsrum drehen (auf)
motor_l = 12  # Linksrum drehen  (zu)0
taster_1 = 7  # oberer Taster  
taster_2 = 6  # unterer Taster

# setup
GPIO.setup(GPIO.BCM)
GpIO.setup(motor_r, GPIO.OUT)
GpIO.setup(motor_l, GPIO.OUT)
GpIO.setup(taster_1, GPIO.IN)
GpIO.setup(taster_2, GPIO.IN)

GPIO.output(motor_r, GPIO.HIGH)
GPIO.output(motor_l, GPIO.HIGH)
GPIO.output(8, GPIO.HIGH)
# setup end
# ---------------------------
print("Programm start")


def klappe_runter():
    GPIO.output(motor_r, GPIO.HIGH)

    while(klappe_position() != 0):
        print("Bewege nach unten")

    GPIO.output(motor_r, GPIO.HIGH)
    time.sleep(0.05)

def klappe_hoch():
    GPIO.output(motor_l, GPIO.HIGH)

    while(klappe_position() != 1):
        print("Bewege nach oben")

    GPIO.output(motor_l, GPIO.HIGH)
    time.sleep(0.05)


def klappe_position():
    # Ergebnis:
    #  1: (Klappe oben)
    #  0: (Klappe unten)
    #  2: (Klappe in Bewegung)

    klappe_status = 10
    val_unten = GPIO.input(taster_2)
    val_oben = GPIO.input(taster_1)

    if(val_unten == GPIO.LOW && val_oben == GPIO.LOW):
        return 0
    else if(val_unten == GPIO.HIGH && val_oben == GPIO.HIGH)
        return 1
    else:
        return 2

def loop():
    time.sleep(5)
    klappe_runter()
    time.sleep(5)
    klappe_hoch()


while(true):
    loop()