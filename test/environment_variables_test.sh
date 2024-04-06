FILE_NAME="environment_variables"
GREEN="\e[32m"
RED="\e[31m"
RESET="\e[0m"
PASS=1

cc src/"$FILE_NAME".c test/"$FILE_NAME"_test.c \
    -I lib/libft/inc -Iinc -Isrc \
    -L lib/libft/lib \
    -lft \
    -o "$FILE_NAME"_test \
    -Wall -Wextra -g

# Normal output
./"$FILE_NAME"_test

# Run program and capture its output
output=$(./"$FILE_NAME"_test)

# Compare output    or USER
echo "$output" | grep -q "USER: >$USER<" \
    && echo -e "USER: ""$GREEN""OK"$RESET \
    || (echo -e "USER: "$RED" Failed" $RESET; PASS=0)

# Compare output for LANGUAGE
echo "$output" | grep -q "LANGUAGE: >$LANGUAGE<" \
    && echo -e "LANGUAGE: "$GREEN"OK" $RESET \
    || (echo -e "LANGUAGE: "$RED"Failed" $RESET; PASS=0)

# Compare output for HOME
echo "$output" | grep -q "HOME: >$HOME<" \
    && echo -e "HOME: "$GREEN"OK" $RESET \
    || (echo -e "HOME: ""$RED""Failed" $RESET; PASS=0)

# Add new variable to environment and compare output
echo "$output" | grep -q "MYVAR: >Hello World<" \
    && echo -e "Add to env: "$GREEN"OK" $RESET \
    || (echo -e "Add new var to env: ""$RED""Failed" $RESET; PASS=0)

# Remove new variable to environment and compare output
echo "$output" | grep -q "MYVAR: >(null)<" \
    && echo -e "Remove from env: "$GREEN"OK" $RESET \
    || (echo -e "Add new var to env: "$RED"Failed" $RESET; PASS=0)

if [ $PASS -eq 1 ]; then
    echo -e "$GREEN""All tests OK $RESET"
else
    echo -e ""$RED"""Some tests failed $RESET"
fi
