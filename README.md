# ORB-Application

Author:    Thomas Breuer
Date:    23.11.2023

## Introduction

This Project supports programming of the [OpenRoboticBoard (ORB)](https://www.github.com/ThBreuer/OpenRoboticBoard) as a local application. The local application is developed with an IDE (e.g. EmBitz, which must be installed separatly) in the programming language C/C++. Access to the hardware uses the ORB-Firmware API, which is also supported by more convenient middleware functions. 

Once the code has been generated, it can be downloaded to the ORB using the **ORB-Monitor**. The **ORB-Monitor** can also be used to:

- Start and stop the local application
- Send button events to the local application
- Display text messages from the local application 

## Preparation

### Download

1. Download [ORB-Application](https://www.github.com/ThBreuer/ORB-Application)

2. Unzip downloaded files into a suitable directory (e.g. D:\ORB)

3. Navigate to this directory and run _setEnv.bat. This batch sets the enviroment variable `ORB` to the current path, used by compiler and other tools.

4. Navigate to ORB\Middleware\Doc and unzip doc.zip

5. Navigate into directory `Example` and copy any one of the examples into a suitable directory (e.g. D:\Projekte)

### Install EmBitz

1. Download **EmBitz**  from  [[www.embitz.org](http://www.embitz.org)](https://www.embitz.org/)

2. Unzip and execute downloaded file
   
   - Use default settings if requested
   
   - *Install EBlink:* no 
     EBlink is not used within ORB-Application, but it could be useful somewhere else.

3. Start **EmBitz** from Windows Desktop or Start Menu
   
   - Dialog box *File associations*: Set "Yes, associate EmBitz with project and workspace files"
   
   - If this dialog box doesn't appear, set file associations in  **EmBitz** menu 
     `Settings`-`Enviroment settings`-`General settings`
     Set checkbox "check & set file associations"

4. Optional (for more comfort): Add tools in menu `Tools`-`Configure tools...`: 
   
   ```
   Name:              Clean
   Executable:        ..\..\_clean.bat
   Launching options: "Launch tool hidden with standard output redirect"
   ```
   
   ```
   Name:              Docu
   Executable:        ..\..\_Docu.bat
   Launching options: "Launch tool hidden with standard output redirect"
   ```
   
   ```
   Name:              ORB-Monitor
   Executable:        ..\..\_ORB-Monitor.bat
   Parameters:        ..\..\
   Launching options: "Launch tool hidden with standard output redirect"
   ```
   
   Optionally (for even more comfort), set keyboard shortcuts in **EmBitz** menu `Settings`-`Enviroment settings`-`Keyboard shortcuts`

5. Close **EmBitz**

### Start ORB-Project

1. Use windows file manager (e.g. explorer) to navigate to your ORB project.  (e.g. D:\Projekte\Template)

2. Run batch _EmBitz.bat to start **EmBitz**

3. Compile Project

4. Start **ORB-Monitor** from file manager by calling _ORB-Monitor.bat
   or from **EmBitz** menu `Tools`-`ORB-Monitor`

5. Use drop-down-list (located left top) to connect to the ORB

6. Once connected you can download your App to the ORB 
   from **ORB-Monitor** by pressing `Download Program` button
     or again calling **EmBitz** menu `Tools`-`ORB-Monitor`
   
   - Start the App with green or yellow button on ORB-Monitor
   
   - Alternatively press button on the ORB (short or long key press)
   
   - Press red button on ORB-Monitor or button on the ORB to stop the App

## Programming a Local Appication

There are some restrictions regarding the firmware:

- Global instances or variables are not allowed

- Stack and heap sizes are limited

- Dynamic memory allocation (`new`) is not supported

The Local Application  must be written in C++. 

- Create a class `Application`, which must be derived from the base class `ApplicationBase`

- Override the method  `void run( BYTE para )`
  
  - The parameter `BYTE para` indicates, if the application is startet with a short key press (0) or with a long key press

- Use file name `Application.h`. 

- Template:
  
  ```
  class Application : public ApplicationBase
  {
    public:
      Application() {
      }
  
    public:
      virtual void run( BYTE para )
      {
        while( 1 ) {
        }
      }
  };
  ```

- See directory `Example`, choose a suitable example and use it as a template for your own project. 

### Using Middleware

see [ORB-Middleware Documentation](https://github.com/ThBreuer/ORB-Application/tree/main/Doc)

### Using ORB-Firmware

see [ORB-Firmware Documentation](https://github.com/ThBreuer/ORB-Firmware/tree/main/Doc)

usepedefined object `ORB orb`

example ORB-Firmware-API
