# Set Window Icon NDLL

Forked from the [Codename Engine NDLL Example](https://github.com/CodenameCrew/ndll-example)

It will use the 16x16 icon for the small window icon and the 256x256 icon for the large taskbar icon.

This NDLL will only work on Windows.

## Usage in Codename:

```hx
import funkin.backend.utils.NdllUtil;

// place ndll in mods/yourmodname/ndlls/

var setWindowIcon = NdllUtil.getFunction('set_window_icon', "set_window_icon", 2);
// setWindowIcon(path:String, modsFolder:String);
// if modsFolder is a string, it will prefix the path with "./mods/" + modsFolder + "/"

// setting icon to custom icon located in ./mods/yourmodname/icon.ico
#if windows
setWindowIcon('icon.ico', ModsFolder.currentModFolder);
#end

// setting icon to default icon.ico located in ./icon.ico
#if windows
setWindowIcon('icon.ico', null);
#end
```