# PhotoQuick plugins

### Description
A few set of plugins for the viewer [photoquick](https://github.com/ksharindam/photoquick).  
Check [here](https://github.com/ImageProcessing-ElectronicPublications/photoquick-plugins) full set of plugins available.  


### Available Plugins
* grayscale-local  
* stretch-histogram  
* kuwahara  
* tone-mapping  
* photoframe  
* histogram-viewer  
* barcode-generator  
* pixart-scaler  

### Runtime Dependencies
* libqtcore4  
* libqtgui4  
* libgomp1  

### Build 

#### Linux
Install dependencies...  
**Build dependencies ...**  
 * libqt4-dev  

To build this program, extract the source code zip.  
Open terminal and change directory to src/  
Then run these commands to compile...  
```
qmake  
make -j4  
```

#### Windows
Download Qt 4.8.7 and minGW32  
Add Qt/4.8.7/bin directory and mingw32/bin directory in PATH environment variable.  
In src directory open Command Line.  
Run command...  
```sh
qmake
make -j4
```

### Install (Linux)
```sh
sudo make install
```

### Links

* https://github.com/ksharindam/photoquick
* https://github.com/ImageProcessing-ElectronicPublications/photoquick
*  https://github.com/ImageProcessing-ElectronicPublications/photoquick-plugins