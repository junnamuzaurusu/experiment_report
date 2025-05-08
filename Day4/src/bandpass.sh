#!/bin/bash

# ダウンサンプリングのレートを設定
sox ./sound/doremi.wav -t raw -b 16 -c 1 -e s -r 44100 - | ./bandpass 8192 600 800| play -t raw -b 16 -c 1 -e s -r 44100 -
