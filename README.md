**Keyboard Pressing Anynomisation**

*Installation*

```
brew tap homebrew/science 
brew install r
brew install watch
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
./visu.sh
open keydam.pdf
```

*Monitor the log (optional)*

```
cd keydam
tail -f keydam.csv
```
