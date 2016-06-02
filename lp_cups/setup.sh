#!/bin/bash

make clean;
make;
sudo chown root lp_cups;
sudo chgrp root lp_cups;
sudo chmod u+s lp_cups;
