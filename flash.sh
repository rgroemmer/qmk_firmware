set -e

gum() {
    nix run nixpkgs#gum -- "$@"
}
qmk() {
    nix run nixpkgs#qmk -- "$@"
}

gum style --foreground 82 --align left 'Flashing the Corne 🌩️'
KEYBOARD=$(echo -e "rapsn\nrapsn-led" | gum choose)

if gum confirm "flash from download json?"; then
    QMK_JSON=$(find ~/Downloads -name "*.json" | gum choose)
    mv rapsn.json rapsn.json.BAK
    mv "$QMK_JSON" rapsn.json
    qmk json2c rapsn.json -o ./keyboards/crkbd/keymaps/"$KEYBOARD"/keymap.c
fi

qmk clean
qmk flash -kb crkbd -km "$KEYBOARD"
qmk flash -kb crkbd -km "$KEYBOARD"
