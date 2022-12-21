cd ~/Projects/RAPSN/github/qmk_firmware/keyboards/sofle_choc/keymaps/rap-eu
mv ~/Downloads/sofle_rev1_layout_mine.json rapsn_neo-eu.json
qmk json2c -o keymap-rap.c rapsn_neo-eu.json
qmk flash -kb sofle_choc -km rap-eu