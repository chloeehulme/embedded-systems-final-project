"""
   A basic GUI that triggers a webhook when a button is pressed.
   Uses:  RPi model 3
   Author: Chloe Hulme
"""

from tkinter import *
import tkinter.font
import requests
import time

# GUI definitions
win = Tk()
win.title("Dispense a glass of water")
myFont = tkinter.font.Font(family='Helvetica', size=15, weight="bold")


# Sends an HTML POST request to IFTTT for the event 'water'
def dispense():
    r = requests.post('https://maker.ifttt.com/trigger/water/with/key/dH8ev94dnFQG3FdaZNGEn5', params={"value1":"none","value2":"none","value3":"none"})


# Sends an HTML POST request to IFTTT for the event 'retract'
def retract():
    r = requests.post('https://maker.ifttt.com/trigger/retract/with/key/dH8ev94dnFQG3FdaZNGEn5', params={"value1":"none","value2":"none","value3":"none"})


# Closes window
def close():
    win.destroy()


# Create widgets
Water = Button(win, text='Water!', font=myFont, command=dispense, bg='DeepSkyBlue2', height=3, width=24)
Retract = Button(win, text='Retract Dispenser', font=myFont, command=retract, bg='grey80', height=3, width=15)

# Positions widgets
Water.grid(row=0, column=1)
Retract.grid(row=1, column=1)

# Create additional exit button
exitButton = Button(win, text='Exit', font=myFont, command=close, bg='seashell1', height=1, width=6)
exitButton.grid(row=3, column=4)

# Link top RHS x to close function
win.protocol("WM_DELETE_WINDOW", close)

win.mainloop()
