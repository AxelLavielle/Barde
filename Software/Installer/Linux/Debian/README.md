# Control file

Package : name of package
Version : verison number //must start with a numeric character
Section : base
Priority : optional
Depends : dependance de lib
Architecture : all
Maintainer : creator of the .deb package //example <example@mail.com>
Description : Description of the package
Homepage : website of the package

# Files Architecture

- Barde/
--- DEBIAN/
----- control // config file
----- preinst // preinstallation script if needed must have chmod 755
----- postinst // postinstallation script if needed must have chmod 755
----- prerm // preremove script if needed must have chmod 755
----- postrm // postremove script if needed must have chmod 755
--- usr/
----- bin/
------- BardeClient //binary


# Compilation

`sudo dpkg-deb --build nom_du_paquet`

# Installation

`sudo dpkg -i nom_du_paquet.deb`

# If dependencies missing

`sudo apt-get -f install`

# Remove

`sudo apt-get remove nom_du_paquet`


