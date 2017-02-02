# URXVTConfig
A graphical user interface tool for configuration of the rxvt-unicode terminal emulator.


![urxvtconfig screenshot](http://i.imgur.com/giZG6Go.png)


# How-to
The "Help" button offers all the information necessary.

> New: Changes all options to default values.

> Load from file: Loads existing configuration file, it may not work given how different the configuration might be.

> Load .Xdefaults: Same as above, loads the Xdefaults file.

> Load .Xresources: Same as above, loads the Xresources file.

> From file: Generates a color scheme from an image using imagemagick.

> Theme Browser: Select a preset color scheme to save or edit as you see fit.

> Save to file: Saves current settings to a file.

> Save to .Xdefaults: Same as above, saves to the Xdefaults file.

> Save to .Xresources: Same as above, saves to the Xresources file.

> Help: Sends you to read this file.

> About: You guessed it.


# Dependancies
qt4 - For the GUI.

imagemagick - For generating color schemes from files.

fontconfig and libXft - For font selection.

It also requires rxvt-unicode to be built with "xft" support.
If you do not know what this means, don't worry about it.


# How to get
We're on the AUR now, use your favorite AUR helper.

**https://aur.archlinux.org/packages/urxvtconfig**

This will build from the latest commit on the "master" branch.


# Build it yourself
Requires qt4 and is highly encouraged.

  ~~~ sh
  $ git clone https://github.com/daedreth/URXVTConfig.git
  $ cd URXVTConfig
  $ qmake source/URXVTConfig.pro
  $ make
  $ sudo make install
  ~~~


Alternatively, if all else fails, just grab the latest "release".


# Troubleshooting
> I saved the changes, encountered no error message and URXVT still didn't change, what do?

Make sure your "USER" environmental variable has not been altered.

> I keep running into an error message about "not having permissions" to write to the file.

Run `chown -R <username>:<usergroup> /home/<username>` as root to fix that.
This will restore permissions to your "home" directory.

> My old configuration is not read properly!

Reset to default values and save to ensure functionality. This tool has a very low tolerance for syntax that doesn't conform to it's settings.

> Why is my transparency not working?

Your composite manager may be disabled. Try fake transparency.

> I enabled certain plugins and they do nothing!

Install them via your distributions package manager (ex.g urxvt-perls).


# Contributing
This is a rather basic project, pull requests are welcome.

Issues will be resolved as fast as possible.


# License
    This file is part of URXVTConfig.

    URXVTConfig is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    URXVTConfig is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with URXVTConfig.  If not, see <http://www.gnu.org/licenses/>.


# Credits
- The QTeam, for a framework that isn't horrible.
- Jesskas, for motivation.
- Seriel, for creating the PKGBUILD.
