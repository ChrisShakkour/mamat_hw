#!/bin/bash
#Line 12: Putting the input in a variable
#Line 14: Reading the rules
#Line 15: Ignoring the spaces, the tabs and the notes (everything after #)
#Lines 16-31: Filtering the packets with the rules that are seperated by ","
#Lines 32-36: Adding the filtered packets to those that were filtered
#                before with rules from a different line
#Line 41: Printing all the packets that were filtered by all rules in the
#           requested order

ex=./firewall.exe
input="$(cat)"
s=0
while read line; do
    line="$(echo "$line" | cut -f1 -d"#" | tr -d ' ' | tr -d '\t')"
    if [[ "$line" ]]; then

	rule="$(echo $line | cut -f1 -d",")"
        n=1
        a=0
        packs="$input"
        while [[ "$rule" && "$packs" && "$packs" != "" ]]; do
            a=1
            n=$((n+1))
            x="$(echo "$packs" | "$ex" "$rule")"
            rule="$(echo "$line" | cut -f$n -d",")"
            if [[ "$x" ]]; then
                packs="$x"
            else
                packs=""
            fi
        done

	if [[ s -eq 0 ]]; then
            out="$packs"
        else
            out="$out n $packs"
        fi
        s=1
    fi
done < $1

out="$(sed 's/n/\n/g' <(echo "$out"))"
grep -v '^$' <(echo "$out" | sort | tr -d ' \t')
