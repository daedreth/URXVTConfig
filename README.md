# URXVTConfig
A graphical user interface tool for configuration of the rxvt-unicode terminal emulator.


# How-to
The "Help" button offers all the information necessary.

> New: Changes all options to default values.

> Load: Loads existing ~.Xdefaults file, it may not work given how different the configuration might be.

> From file: Generates a color scheme from an image using imagemagick.

> Theme Browser: Select a preset color scheme to save or edit as you see fit.

> Save: Saves current settings to ~.Xdefaults.

> Help: You should click that. Alternatively read this file.

> About: You guessed it.


# Dependancies
qt4 - For the GUI.

imagemagick - For generating color schemes from files.

fontconfig and libXft - For font selection.

It also requires rxvt-unicode to be built with "xft" support.
If you do not know what this means, don't worry about it.

# Build it yourself
Requires qt4.

  ~~~ sh
  $ git clone https://github.com/daedreth/URXVTConfig.git
  $ cd URXVTConfig
  $ make
  $ sudo make install
  ~~~

Alternatively, just grab the latest "release".


# Troubleshooting
> I saved the changes, encountered no error message and URXVT still didn't change, what do?

Make sure your "USER" environmental variable has not been altered.

> I keep running into an error message about "not having permissions" to write to the file.

Run `chown -R <username>:<usergroup> /home/<username>` as root to fix that.

> My old configuration is not read properly!

Reset to default values and save to ensure functionality. This tool has a very low tolerance for syntax that doesn't conform to it's settings.

> Why is my transparency not working?

Your composite manager may be disabled, but since we are using fake transparency, it should still work. Check your wallpaper setter.

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
