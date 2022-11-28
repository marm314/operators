#!/bin/bash

export var=$(pwd)
sed 's+PATH+'$var'+g' commutators_tmp.cpp > commutators.cpp
