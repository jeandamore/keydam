**Keyboard Pressing Anonymisation**

*Installation*

```
brew tap homebrew/science 
brew install r
git clone https://github.com/jeandamore/keydam.git
```

*Run the keypress logger*

```
cd keydam
make clean
make
sudo ./main.exe
```

*Run the keypress visualiser*

```
cd keydam
./plot.sh
```

*Monitor the log (optional)*

```
cd keydam
tail -f keydam.csv
```
