#!/bin/bash
RAW="test.raw"
WAV="test.wav"
WAV16="test16.wav"

UUID="your yandex uuid"
KEY="your yandex key"

if [ -s $RAW ];then
	ffmpeg -f u8 -ar 10000 -ac 1 -i $RAW -y $WAV
	ffmpeg -i $WAV -ar 16000 -y $WAV16
	echo -n > $RAW
	mpv $WAV

curl -X POST -H "Content-Type: audio/x-wav" --data-binary "@$WAV16" \
"https://asr.yandex.net/asr_xml?uuid=$UUID&key=$KEY&topic=queries" | \
sed -n -e '/variant\.*>/,/<\/variant/p' | \
sed '/<\/variant>/!d' | \
sed 's/<v\(.*\)">//' | \
sed 's/<\(.*\)//' | \
sed 's/\s//'


else
	echo "empty raw"
fi

