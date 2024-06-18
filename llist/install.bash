#!/bin/bash

if [ "$(id -u)" != "0" ]; then
    >&2 echo "Must be executed as root"
    exit 1
fi

echo "Installing library and headers ..."
cp libllist.so /usr/local/lib/ || { echo "Failed to copy libllist.so"; exit 1; }
cp llist.h /usr/local/include/ || { echo "Failed to copy llist.h"; exit 1; }
/sbin/ldconfig || { echo "ldconfig failed"; exit 1; }

echo "Installing man pages ..."
mkdir -p /usr/local/man/man3 || { echo "Failed to create man directory"; exit 1; }
cp man/*.3 /usr/local/man/man3/ || { echo "Failed to copy man pages"; exit 1; }
/usr/bin/mandb || { echo "mandb failed"; exit 1; }

echo "All set!"
