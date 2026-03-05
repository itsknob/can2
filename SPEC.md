# CAN App

> [Basic Scenes Tutorial by Jamison Derek](https://github.com/jamisonderek/flipper-zero-tutorials/tree/main/ui/basic_scenes)

## Introduction
This app is used to read messages from and send messages to a CAN bus network. 

The user should be able to read data coming from the CAN. This data should be 
able to filter information coming in by the Device Identifier (DID). The user 
should be able to start recording data, filtered or not, and save that 
information to disk, upon stopping the recording. 

The user should be able to send messages to the CAN. They should be able to 
either load a file containing one or more messages and send those, or they 
should be able to manually create a payload to send. Either a single message 
or multiple messages in order. The user should be able to save the payloads 
they create to disk, to later load and send them.

There should be some configuration options that exist for the user within the 
application. These might be things like, baud rate, CAN FD support (or maybe 
specifying which hardware they have attached to the flipper), and, if using 
an MCP2515, the crystal speed.


## Terminology and Hierarchy

### Application
The application is the container for all other parts of the app. This is generally structured as the main method that runs and is responsible for managing the state of the application, initializing and freeing the GUI, and handling the user input.

#### Application State
The application state holds information specific to the logic of the application. The state also holds references to the GUI components (see below).

### GUI
The Graphical User Interface is the user facing portion of the application. For the flipper, this is done by utilizing Scenes and a Scene Manager. Scenes can utilize pre-existing Modules (found in gui/gui.h) such as TextInput, Menu, Loading, FileBrowser, and more. There is also a Module called Widget that allows you to create your own custom layout to be utilized in the same manner as a pre-existing Module.

#### Scene
A Scene uses a module to display the user interface. The Module for the Scene also handles the user input. [flipper-zero-tutorials#Scenes](https://github.com/jamisonderek/flipper-zero-tutorials/tree/main/ui/basic_scenes#scenes) 
#### Scene Manager
The Scene Manager will display the Scene and handle transitions between Scenes. This is done by calling the Scene's `on_enter` function when the Scene should be displayed, calling the `on_event` function when an event is invoked, and calling the `on_exit` function when the Scene should no longer be displayed.

#### Modules
A Module is a prebuilt View that can be displayed on the flipper. See [A Visual Guide to Flipper Zero GUI Components](https://brodan.biz/blog/a-visual-guide-to-flipper-zero-gui-components/)

#### View
A view is the actual layout displayed to the user on the flipper. 


## Graphical User Interface (GUI)

### Main Menu
The main menu should have to menu options: Read and Send. There should also be 
an option for navigating to the Configuration options.

### Read Menu 
The Read view should take some inspiration from other CAN reading tools like 
[CAN-X](https://github.com/karlyamashita/CAN-X), [CANLogger](https://github.com/olegel/CANLogger), [CAN Hacker's Car BUS Analyzer](https://canhacker.com/projects/carbus-analyzer/), [CAN Monitor QT](https://github.com/tixiv/CAN-Monitor-qt), and 
[CANalyzat0r](http://github.com/schutzwerk/CANalyzat0r). 

These provide a spreadsheet like columnar view of the data. In this case an 
extremely reduced amount of information will be able to be viewed at one time 
on the screen. In this case, only displaying the DID and the raw data (hex) in 
a scrollable table might be the best option. Scrolling down the rows in this 
"table" could allow for context options such as adding the current DID to a 
filter (Left Button), or viewing more columns for the specific DID in a 
different format on another page (Center Button). There should be an option to 
start recording (Hold Center Button), or, when already recording, to stop.

When stopping the recording, the user should be presented with a Save File 
screen, allowing them to enter a filename, but not necessarily a path.

#### Required Views
- Read Menu
  - Current filters applied
  - Column headers
  - Scrollable List of Streaming Data sorted by DID 
  - Tooltips (Needs Work)
    - Left -> Add Currently Selected Rows' DID to Filter
    - Center -> Drill Down to view more data (columns) of current rows' DID
    - Center (Hold) -> Start/Stop Recording
  - Save File / Enter Filename

### Send Menu
The send view should allow the user to construct a payload to be sent. This 
could either be done with a form for each part required for the CAN payload, 
or this could utilize the builtin Flipper Zero Hex Editor GUI. The user should 
be able to update multiple messages which should be able to be sent one at a 
time manually, or as a sequential batch (send all messages in order). The user 
should be able to load messages from a saved file.

The main screen will need to indicate that there are multiple areas for single 
messages to be entered. Selecting one of these message areas should navigate 
to the message entry view. 

#### Required Views
- Send Menu
  - Scrollable List of messages
    - Columns for ID, Data
    - "+ Add Another Message" option at bottom of list
  - Form (Option #1)
    - Device ID Input
      - Required
    - Raw Message Data Input
      - Required
    - Data Length Code (DLC)
      - Default Value?
    - ... ?
  - Raw Payload (Option #2)
    - Hex Editor GUI Component
  - Tooltips
    - Up/Down -> scroll between messages
    - Right -> Edit Message
      - Either Form or Hex Input Component
    - Center -> Send (Current Message)
    - Center (Hold) -> Send (All Messages)
    - Left (Hold?) -> Load Message from File
    - Left -> Config? 
      - Extended ID on/off 
      - Default Data Length Code

## Read - Save File Format
> Should this be the same file format as Load/Send Messages?

## Send - Load File Format
> Should this be the same file format as Read Messages?

## Configuration Menus
### Main Config Menu
### Read Config Menu
### Send Config Menu

___

## Specifics 
```yaml
Application Name: OBDTool
Scenes:
  - OBDToolScenesMainMenuScene: 
    Description: Main Menu
    Module: Menu
    Options:
      - Send Message
      - Read Data
      - Configuration
  - OBDToolScenesReadDataScene: 
    Description: Read Data from Connected CAN device 
    Module: TextBox # (First Pass) (Potentially Custom)
    Content: Stream of CAN Data
  - OBDToolScenesSendDataScene: 
    Description: Send Data to Connected CAN device 
    Module: Dialog
    Title: Send Message
    Content: <Payload to Send>
    Options:
      - OptionLeft: Edit Message
      - OptionRight: Send Message
  - OBDToolScenesEditDataSimpleScene: 
    Description: Simple Edit Message to Send on Send Screen
    Module: VariableItemList # (Maybe?) or Widget (Custom Form) 
    Options:
      - Label: Device ID Input (Required)
        Type: ByteInput
      - Label: Data Length Code (DLC) (Optional)
        Type: TextInput # Maybe Just a selection from a list. Maybe this is in the config menu?
      - Label: Raw Message Data Input (Required)
        Type: ByteInput
  - OBDToolScenesEditDataAdvancedScene: 
    Description: Advanced Edit Message to Send on Send Screen
    Module: ByteInput (Hex Input)
    Title: Raw CAN Data to Send
  - OBDToolScenesConfigMenuScene: 
    Description: Configure settings of OBDTool
    Module: SubMenu
    Title: Configuration Menu
    Options:
      - Label: Read Config
        Scene: OBDToolScenesConfigReadScene
      - Label: Send Config
        Scene: OBDToolScenesConfigSendScene
  - OBDToolScenesConfigReadScene:
    Module: VariableItemList
    Options:
      - Baud Rate:
        Values:
          - 8 Mbps (FD Max)
          - 1 Mbps (FD Min)
          - 500 kbps (Automotive) [Default]
          - 250 kbps (Agriculture)
          - 125 kbps (Industrial)
  - OBDToolScenesConfigSendScene:
    Module: VariableItemList
    Options:
      - EditMenuStyle:
        Values:
          - Simple [Default]
          - Advanced
Modules:
  - Menu
  - ByteInput
  - Submenu
  - TextInput
  - TextBox
  - VariableItemList
  - Dialog
  - Widget # For Custom UIs
Views:
  - OBDToolMenuView
  - OBDToolSubMenuView
  - OBDToolTextInputView
  - OBDToolByteInputView
  - OBDToolTextBoxView
  - OBDToolVariableItemListView
  - OBDToolDialogView
  - OBDToolWidgetView

```


## References
[CAN-X Wiki](https://github.com/karlyamashita/CAN-X/wiki) - CAN Sniffing Util

[ICSim](https://github.com/zombieCraig/ICSim) - Instrument Cluster Simulator (Virtual CAN Devices)

[ESP32 ESP-NOW Wireless Serial Communication Guide](https://www.engineersgarage.com/esp-now-esp32-communication-without-router-or-internet/)
[Flipper Local Dev Env](https://unlimitedhummus.com/blogposts/programming/nvim_lsp_flipper_zero)
