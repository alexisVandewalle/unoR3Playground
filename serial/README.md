# Display messages from serial port
- install minicom application
- set default parameters of minicom:
    - edit file `~/.minirc.dfl`
    - paste:
```
pu addcarreturn Yes
pu linewrap     Yes
```
- launch minicom:
    - `minicom -b 9600 -D /dev/ttyACM0`
