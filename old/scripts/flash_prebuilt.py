#!/usr/bin/env python2

import telnetlib
import subprocess
import signal
import time

###############################################################
# This script will automatically flash the STM32 discovery board 
# using OpenOCD. The working directory is assumed to be the
# project root
###############################################################

###############################################################
# We need to be able to send a SIGTERM (ctrl-c) to GDB
# without killing openocd or this script. Set up a custom
# signal handler here that essentially ignores SIGTERM
###############################################################
def signal_handler(signal, frame):
    pass # do nothing

###############################################################
# Start up the openocd thread
###############################################################

# We need gdb to respond to a SIGINT (ctrl-c), but by default,
# that will cause every other child process to die, including 
# openocd. Disable sigint, then re-enable it after the child 
# spawns. The child inherits the current state of signal 
# handlers.
signal.signal(signal.SIGINT, signal.SIG_IGN)
openocd = subprocess.Popen(["openocd", "-f", "board/st_nucleo_h743zi.cfg"])
time.sleep(2) # Wait for this to start up

# Set up a custom signal handler so that SIGINT doesn't kill
# this script
signal.signal(signal.SIGINT, signal_handler)

###############################################################
# Flash the new image to the development board
###############################################################

# Create the flashable image
subprocess.call(["arm-none-eabi-objcopy", "-Obinary", "firmware/CANT.elf", "firmware/CANT.bin"])

# Flash the image
tn = telnetlib.Telnet("127.0.0.1", "4444")
tn.read_until("> ")
tn.write("poll\n")
tn.read_until("> ")
tn.write("reset halt\n")
tn.read_until("> ")
tn.write("flash probe 0\n")
tn.read_until("> ")
tn.write("flash write_image erase firmware/CANT.bin 0x08000000\n")
tn.read_until("> ")
tn.write("reset\n")
tn.read_until("> ")
tn.write("exit\n")
tn.close()

time.sleep(2)

# Gracefully exit openocd
openocd.terminate()

