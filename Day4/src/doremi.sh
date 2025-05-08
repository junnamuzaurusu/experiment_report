#!/bin/bash

# ダウンサンプリングのレートを設定
sox ./sound/doremi.wav -t raw -b 16 -c 1 -e s -r 44100 - | ./a.out 5 | play -t raw -b 16 -c 1 -e s -r 8820 -

