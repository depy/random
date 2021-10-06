$8 != "HTTP/1.0" {
    if(codes[$8] != "") {
        time_per_10min = substr($3, 14, 4)
        http_resp_code = $8
        counts[time_per_10min][http_resp_code]++
    }
}

BEGIN {
    codes[400] = 1
    codes[403] = 1
    codes[404] = 1
    codes[429] = 1
    codes[499] = 1

    printf "time\t"
    for(c in codes) {
      printf c "\t"
    }
    printf "\n"
}

END {
    n = asorti(counts, time_sorted)
    for(i=1; i<=n; i++) {
        printf time_sorted[i] "0\t"
        for(c in codes) {
            codes_counts = counts[time_sorted[i]][c]

            if(codes_counts != "") {
                printf counts[time_sorted[i]][c] "\t"
            }

            if(codes[c] == 1 && codes_counts == "") {
                printf "0" "\t"
            }
        }
        printf "\n"
    }
}
