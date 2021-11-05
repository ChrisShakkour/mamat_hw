#!/bin/bash
# scrape players bash script


# set working params
URL='https://www.premierleague.com/players'
O_FILE='./player_results.csv'
PLAYERS='./players'
P_URLS='./urls.txt'


#clean dir
rm -Rf $PLAYERS
rm -Rf $O_FILE
rm -Rf $P_URLS


# get players file
wget $URL


# find all relevant players URL's
# and dump to urls.txt
grep -oP "\/players\/[0-9]*\/[a-zA-Z-]*\/overview" $PLAYERS > $P_URLS
rm -Rf $PLAYERS


# replace /players with URL
sed -i "s|\/players|$URL|g" $P_URLS


# count num of players
N_PLAYERS=`cat $P_URLS | wc -l`
echo "Total players: $N_PLAYERS" > $O_FILE


# go over players urls
# and get relevant data
while read line;
do
    wget $line
    N_MID=`cat overview | grep -ioP "midfielder" | wc -l`
    rm -Rf ./overview
    if [[ $N_MID -gt 0 ]] ; then
	echo "$line,midfield,$N_MID" >> $O_FILE 
    fi
done < $P_URLS

rm -Rf $P_URLS
#cat $O_FILE




