
Debian
====================
This directory contains files used to package gpkrd/gpkr-qt
for Debian-based Linux systems. If you compile gpkrd/gpkr-qt yourself, there are some useful files here.

## gpkr: URI support ##


gpkr-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install gpkr-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your gpkrqt binary to `/usr/bin`
and the `../../share/pixmaps/gpkr128.png` to `/usr/share/pixmaps`

gpkr-qt.protocol (KDE)

