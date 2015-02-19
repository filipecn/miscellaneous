#!/usr/bin/env python

import gobject
import gtk
import appindicator
import pygtk
pygtk.require('2.0')
import time

# off state
OFF_ICON = "ubuntuone-client-idle"
OFF_STATE = 0
# pomo time! 
POMO_ICON = "ubuntuone-client-error"
POMO_STATE = 1
# small pause 
PAUSE_ICON = "ubuntuone-client-paused"
PAUSE_STATE = 2
# big pause 
BIG_PAUSE_ICON = "ubuntuone-client-updating"
BIG_PAUSE_STATE = 3

ind = appindicator.Indicator ("example-simple-client",
                              "indicator-messages",
                              appindicator.CATEGORY_APPLICATION_STATUS)

class PomoClock:

    def __init__(self):
	self.pomoTime = 1*60	#pomodoro size
	self.interval = 1*60	#small interval size
	self.bigInterval = 1*60	#big interval size
	self.curPomo = 1	
	
	self.curState = OFF_STATE
	ind.set_attention_icon (OFF_ICON)

	self.bigPomo = 3	#big interval frequency (every bigPomo times)
	self.curTime = self.pomoTime

    def start(self):
	self.curState = POMO_STATE
	ind.set_attention_icon (POMO_ICON)

    def update(self):
        #time.strftime('%H:%M:%S')
	minutes = self.curTime / 60
	seconds = self.curTime % 60
	mzero = "0" if minutes < 10 else ""
	szero = "0" if seconds < 10 else ""
	ind.set_label(mzero + str(minutes) + ":" + szero + str(seconds))
	
	if self.curState == OFF_STATE :
		return True
	if minutes == 0 and seconds == 0 :
			
		if self.curState == POMO_STATE :
			self.curPomo += 1
			if self.curPomo % self.bigPomo == 0 :
				self.curTime = self.bigInterval
				self.curState = BIG_PAUSE_STATE
				ind.set_attention_icon (BIG_PAUSE_ICON)
			else :
				self.curTime = self.interval
				self.curState = PAUSE_STATE
				ind.set_attention_icon (PAUSE_ICON)
		else :
			self.curTime = self.pomoTime
			self.curState = POMO_STATE
			ind.set_attention_icon (POMO_ICON)

	
	print str(self.curState) + " " + str(self.curPomo)
	self.curTime -= 1
	
        return True  #needed to keep the update method in the schedule


clock = PomoClock()

def start_response(w, buf):
  clock.start()

if __name__ == "__main__":
  
  ind.set_status (appindicator.STATUS_ATTENTION)

  # create a menu
  menu = gtk.Menu()
  
  # start button
  start_item = gtk.MenuItem("start")
  menu.append(start_item)
  start_item.connect("activate", start_response, "start")
  start_item.show()

  ind.set_menu(menu)
 
  gtk.timeout_add(1000, clock.update)
  clock.curState = OFF_STATE
  clock.update()

  gtk.main()
