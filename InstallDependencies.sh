#! /bin/bash

case $PRETTY_NAME in
    "Arch Linux"|"Manjaro")
        pacman -Sy sdl2 sdl2_image gd ;;
    "Ubuntu"|"Linux Mint"|"Xubuntu"|"Kubuntu")
        apt install sdl2 sdl2_image gd ;;
    *)
        echo "Some problem with distro identifiing ocurred :-( Please install packages: sdl2 sdl2_image gd" ;;
