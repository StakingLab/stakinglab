
Debian
====================
This directory contains files used to package labxd/labx-qt
for Debian-based Linux systems. If you compile labxd/labx-qt yourself, there are some useful files here.

## stakinglab: URI support ##


labx-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install labx-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your stakinglabqt binary to `/usr/bin`
and the `../../share/pixmaps/stakinglab128.png` to `/usr/share/pixmaps`

labx-qt.protocol (KDE)

