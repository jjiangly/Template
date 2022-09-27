#!/usr/bin/env bash

DIR=$(dirname $0)

search_up ()
(
    while [[ $PWD != "/" ]]; do
        if [[ -e "$1" ]]; then
            pwd
            if [[ ! -e "$1/$2" ]]; then
                break
            fi
        fi
        cd ..
    done
)
TEMPLATE_DIR='.template'
PARENT_FILE='$PARENT'

IFS=$'\n'
TEMPLATE_DIRS=($(search_up "$TEMPLATE_DIR" "$PARENT_FILE" | tac))
unset IFS
TEMPLATE_DIRS=(${TEMPLATE_DIRS[@]/%/\/"$TEMPLATE_DIR"})

for filepath in "$@"; do
    PROBLEM_NAME=$(basename "$filepath")

    if [[ -e "$filepath" ]]; then
        echo "$filepath already exists. Remove it and retry."
        continue
    fi

    # Create folder
    mkdir "$PROBLEM_NAME"

    # Copy files in
    cp ~/programming/.template/main.cpp "$filepath"/

    # Rename PROBLEM_NAME in file names
    cd "$PROBLEM_NAME"
    mv main.cpp "$PROBLEM_NAME".cpp
    subl "$PROBLEM_NAME".cpp
    cd ..
    
done