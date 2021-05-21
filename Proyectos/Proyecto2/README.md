# project 2

## requirements

### packages used

```
md5sum.exe Quartus-lite-19.1.0.670-windows.tar
baf31a0c1f9c9f000e388d277308a96f Quartus-lite-19.1.0.670-windows.tar
md5sum.exe eclipse-cpp-mars-2-win32-x86_64.zip
6c29aabb67bd8f5a52de85e2382fccbe eclipse-cpp-mars-2-win32-x86_64.zip
```

### setup

- Download [eclipse C++ mars 2](https://archive.eclipse.org/technology/epp/downloads/release/mars/2/eclipse-cpp-mars-2-win32-x86_64.zip)
Note: Try the mirror links if the main source link doesn't work.
- Extract the downloaded file into `<install dir>/nios2eds/bin`.  You should see the `<install dir>/nios2eds/bin/eclipse` folder after extraction is done.
- Rename the `<install dir>/nios2eds/bin/eclipse` folder to `<install dir>/nios2eds/bin/eclipse_nios2`
- Extract the `<install dir>/nios2eds/bin/eclipse_nios2_plugins.zip` (or tar.gz for Linux) to `<install dir>/nios2eds/bin`. The extraction will override files in `<install dir>/nios2eds/bin/eclipse_nios2`.
- Verify the extraction is done correctly by making sure you see the `<install dir>/nios2eds/bin/eclipse_nios2/plugin_customization.ini` file
- You can now launch Nios II SBT for Eclipse via eclipse-nios2.exe

The instructions should be included in the `<install dir>/nios2eds/bin/README`.

- install WSL 1, NOT WSL 2, and Ubuntu 18.04 in it, you might require a reboot or two

update and install required packages
```
sudo apt-get update && sudo apt-get install dos2unix build-essential
```

### steps to produce working project

- open `alarm_clock.qsys` in Platform Designer
- generate HDL
- open NIOS Software Build Tools for Eclipse in Platform Designer
- create new "hello world small" type "Nios II Application & BSP from Template" Project
- include `"../../alarm_clock.h"` and replace body of `main()` with call to `alarm_clock()`
