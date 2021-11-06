import time
import RPi.GPIO as GPIO
import datetime

# pin definitions
motor_auf_r = 22  # Rechtsrum drehen (auf)
motor_l_zu = 18  # Linksrum drehen  (zu)
taster_1 = 38  # oberer Taster  
taster_2 = 40  # unterer Taster

taster_manuell_hoch = 36
taster_manuell_runter = 32

# setup
GPIO.setmode(GPIO.BOARD)

GPIO.setup(motor_auf_r, GPIO.OUT)
GPIO.setup(motor_l_zu, GPIO.OUT)
GPIO.setup(taster_1, GPIO.IN, pull_up_down = GPIO.PUD_DOWN)
GPIO.setup(taster_2, GPIO.IN, pull_up_down = GPIO.PUD_DOWN)
GPIO.setup(taster_manuell_hoch, GPIO.IN, pull_up_down = GPIO.PUD_DOWN)
GPIO.setup(taster_manuell_runter, GPIO.IN, pull_up_down = GPIO.PUD_DOWN)

GPIO.output(motor_auf_r, GPIO.HIGH)
GPIO.output(motor_l_zu, GPIO.HIGH)
# setup end
# ---------------------------
print("Programm start")


def klappe_runter():
    GPIO.output(motor_l_zu, GPIO.LOW)

    while(klappe_position() != 0 and not abbrechen()):
        print("Bewege nach unten")

    GPIO.output(motor_l_zu, GPIO.HIGH)
    time.sleep(0.05)

def klappe_hoch():
    GPIO.output(motor_auf_r, GPIO.LOW)

    while(klappe_position() != 1 and not abbrechen()):
        print("Bewege nach oben")

    GPIO.output(motor_auf_r, GPIO.HIGH)
    time.sleep(0.05)


def klappe_position():
    # Ergebnis:
    #  1: (Klappe oben)
    #  0: (Klappe unten)
    #  2: (Klappe in Bewegung)

    val_unten = GPIO.input(taster_2)
    val_oben = GPIO.input(taster_1)
    mins = datetime.datetime.now().minute

    if val_unten == 0 and val_oben == 0:
        print("Zeit-Minuten: ", mins)
        print("Position: UNhTEN")
        return 0
    elif(val_unten == 1 and val_oben == 1):
        print("Zeit-Minuten: ", mins)
        print("Position: OBEN")
        return 1
    else:
        print("Position: UNTERWEGS")
        print("Zeit-Minuten: ", mins)
        return 2


def abbrechen():
    return False

def loop():
    try:
        mins = datetime.datetime.now().minute

        if(GPIO.input(taster_manuell_hoch) == 1):
            klappe_hoch()
        elif(GPIO.input(taster_manuell_runter) == 1):
            klappe_runter()
        elif(mins == 00):
            klappe_hoch()
        elif(mins == 10):
            klappe_runter()
        elif(mins == 20):
            klappe_hoch()
        elif(mins == 30):
            klappe_runter()
        elif(mins == 40):
            klappe_hoch()
        elif(mins == 50):
            klappe_runter()
    except KeyboardInterrupt:
        GPIO.cleanup()
        print("Programm abgebrochen!")

    


while(True):
    loop()
