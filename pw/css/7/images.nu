#!/usr/bin/env nu

let factor = '3.5%';

run-external convert '-resize' $factor 'og-amogus-1.png' 'amogus-1.png'
run-external convert '-resize' $factor 'og-amogus-2.png' 'amogus-2.png'
run-external magick 'montage' '-background' '#00000000' 'amogus-1.png' 'amogus-2.png' 'amogus.png'
