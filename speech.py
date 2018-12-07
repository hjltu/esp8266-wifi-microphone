#!/usr/bin/env python3

"""
    sudo pip3 install SpeechRecognition

"""

import speech_recognition as sr

r = sr.Recognizer()

sample = sr.AudioFile('test16.wav')
with sample as source:
    audio = r.record(source)

print(r.recognize_google(audio, language="ru_RU"))
