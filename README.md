# URXVTConfig
A graphical user interface tool for configuration of the rxvt-unicode terminal emulator.


![urxvtconfig screenshot](http://i.imgur.com/vCnijHx.png)


# How-to
- File
	- New: Resets all configuration options to the default values.
	- Load from custom file: Loads a specifiable configuration file.
	- Load from Xdefaults: Same as above, loads `~/.Xdefaults`.
	- Load from Xresources: Same as above, loads `~/.Xresources`.
	- Save to custom file: Saves currently selected options to a custom file.
	- Save to Xdefaults: Same as above, saves to `~/.Xdefaults`.
	- Save to Xresources: Same as above, saves to `~/.Xresources`.
	- Colors from file: Generates a color scheme using an image, refer to "Colors from file" further down below.
	- Quit: Rather selfexplanatory.

- Presets
	- Select one of premade and shamelessly borrowed color schemes!

- User Presets
	- Choose Preset: Select one from your saved themes, refer to "Custom Themes" further down below.
	- Save Preset: Saves currently selected colors to the preset database.

- Help
	- Help: Sends you to view this file.
	- About: Displays a tiny window with general information.


# Dependencies
`qt5` - For the GUI.

`imagemagick` - For generating color schemes from files.

`fontconfig` and `libXft` - For font selection.

It also requires rxvt-unicode to be built with "xft" support.
If you do not know what this means, don't worry about it.


# How do I get it

- Arch

We're on the AUR now, use your favorite AUR helper.

**https://aur.archlinux.org/packages/urxvtconfig**

This will build from the latest commit on the "master" branch.

- Gentoo

`urxvtconfig` is part of the main portage tree.

**https://packages.gentoo.org/packages/x11-misc/urxvtconfig**

Sync your portage and `emerge --ask --verbose x11-misc/urxvtconfig`

- Other distributions

As time passes, I will try to get this into as many repositories as I can, for now, just grab the latest release.

I highly recommend to build it yourself as described just below:


# Build it yourself
Requires qt5 (qmake) and is highly encouraged.

  ~~~ sh
  $ git clone https://github.com/daedreth/URXVTConfig.git
  $ cd URXVTConfig
  $ qmake -qt=qt5 source/URXVTConfig.pro
  $ make
  $ sudo make install
  ~~~

If qmake does **not** appear to be working, you have to specify the full path to the qmake executable.

`/usr/lib64/qt5/bin/qmake source/URXVTConfig.pro`


# Colors from file

If you have `imagemagick` installed, you can attempt to generate a nicely looking theme from an image.

The way this works is, we extract enough colors without duplicates and apply, you are obviously free to modify them once generated.


# Custom themes

You can easily save and load custom themes.

Create the following file to get started: `~/.config/urxvtconfig/presets.db`.

You can save your selected colors under a specific name to use at a later time, or load from the file.

It goes without saying that it's possible to manually edit the file in order to add or remove presets, the syntax for a preset is as follows:
(make sure each one is on a new line)

`Theme Name: <foreground>,<background>,<cursorColor>,<16 other colors>`

Where the colors are HTML color codes, separated by commas. (HEX)
Save a configuration and manually edit the file to see exactly how that works.

The name may contain spaces and special characters, the only character it can not contain is a colon `:`.


# Configuration

You can modify the way URXVTConfig works by creating and editing a configuration file.

By default, the file it is looking for upon launch is `~/.config/urxvtconfig/config`.

The syntax and possible options so far are:

`no_warnings: true | false` - If set to true, we will stop nagging about installing third party plugins and a few other annoying warnings.

`no_backups: true | false` - If set to true, we will stop asking if you'd like to create a backup each time you save your configuration.

As this project grows, I will be adding more configuration options if necessary.


# Troubleshooting
- I saved the changes, encountered no error message and URXVT still didn't change, what do?
	- Make sure your "USER" environmental variable has not been altered.

- I keep running into an error message about "not having permissions" to write to the file.
	- Run `chown -R <username>:<usergroup> /home/<username>` as root to fix that.
	- This will restore permissions to your "home" directory.

- My old configuration is not read properly!
	- Reset to default values and save to ensure functionality. This tool has a very low tolerance for syntax that doesn't conform to it's settings.

- Why is my transparency not working?
	- Your composite manager may be disabled. Try fake transparency.

- I enabled certain plugins and they do nothing!
	- Install them via your distributions package manager (ex.g urxvt-perls).

# Contribution guidelines

This is a rather basic project, pull requests are welcome.
Issues will be resolved as fast as possible.

The code is to remain as simple to modify and as readable as only possible.

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
