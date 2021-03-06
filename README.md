CBM DOS Wedge
==============
**Issuing arbitrary Commodore DOS commands to a disk drive directly from the BASIC command line**

Table of Contents
-----------------

- [Installation](#installation)
- [Command descriptions](#command-descriptions)
- [Wedge activation signs](#wedge-activation-signs)
- [Setting the default device](#setting-the-default-device)
- [Displaying the directory](#displaying-the-directory)
- [Reading the disk drive error channel](#reading-the-disk-drive-error-channel)
- [Loading a program](#loading-a-program)
- [Loading and running a program](#loading-and-running-a-program)
- [Sending DOS commands](#sending-dos-commands)
- [Downloads](#downloads)

Installation
------------

The wedge is compatible with Commodore BASIC 2 and BASIC 4 and consumes only 389 bytes RAM.

Load and start the wedge installer just like any other program:

   BASIC 2:

          LOAD"WEDGE",8
          RUN

   BASIC 4:

          dL"wedge
          run

The wedge installer is a "universal binary" containing a couple of resident wedge versions. The wedge installer tries to auto-detect your BASIC version first and installs the appropriate version of the resident wedge afterwards (if any).

BASIC 2 and BASIC 4 are fully supported. The installer can detect BASIC 1 (PET 2001), but this BASIC version is unsupported. The CBM-II series aren't supported at all, but you can use Michael Pleban's CBM-II DOS Wedge instead.

Command descriptions
--------------------

[ ] Square brackets are used to enclose information which is optional
to the command syntax. The brackets themselves are not part of the
command.

< > Angle brackets act as a placeholder that will be replaced by an
applicable value. The brackets themselves are not part of the command.

... Three dots indicate that the last parameter can given several
times. Usually this applies for filenames where the operation can
applied to a single file or multiple files.

Device - usually a floppy disk drive connected to your PET using the
IEEE bus. In this context, device means the unique device address that
is used to communicate with the device. If you load a program by
LOAD"PRG",8 your device has the address 8. A device may contain a
single drive like the 2031, or two drives like the 8050.

Drive - a dual floppy like the 8050 is a single device with two drives.

Wedge activation signs
----------------------

Wedge commands are only available in direct mode. You cannot use them in your programs. The wedge is a BASIC extension that is activated by one of the magic characters #@>/^ at the beginning of the line when you enter a command in direct mode. The greater than > has the same function as the at @, so e.g. @$ and >$ do the same. In the following text, only the @ is used to simplify things.

Leading spaces are omitted.

Here's an overview of each wedge activation sign's purpose that will be discussed later:

    @ and >
        Displaying the directory
        Reading the disk drive error channel
        Sending DOS commands

    #
        setting the default device

    /
        loading a program

    ^
        loading and running a program

Setting the default device
--------------------------

 `#<unit number>` sets the default drive,  `#` without unit number shows the current default drive.

The default device is initialized with 8.

 `#9` sets the default drive to 9.

 `#` will show you the default drive was really set to 9.

 `#8` sets the default drive back to 8.

Displaying the directory
------------------------

   @$[ [drive] : filename ] displays the disk's directory.

Typing @$ without filename displays the entire directory. @$ followed by a colon and a filename will display the specified file in the directory listing (if it exists). A selective listing can be displayed by using pattern patching or wild cards as part of the filename.

Press  Space Bar  to pause the listing and any other key to continue it.

Abort the listing with the STOP-key.

`@$` displays the entire directory.

`@$1:` displays the directory of default's device drive 1 only. Do not confuse drive and device.

`@$:N*` displays all files having a "N" as the first letter in their filename.

Reading the disk drive error channel
------------------------------------

`@` without any parameters reads and displays the disk drive error message channel. If everything is okay, you'll get your DOS version at startup and 00, OK, 00, 00 afterwards.

Loading a program
-----------------

`/filename` loads a program.

`/GARY` loads the program called GARY, but doesn't start it. So you can list and edit it afterwards.

Loading and running a program
-----------------------------

`^GAME` loads and runs a game. Probably. But it wouldn't be very clever to save it on disk using this name.

If you're using BASIC 2 and try to load a non-existent file, these load commands act just in the same way the normal BASIC-2-LOAD does: it hangs and tries to load forever. Use the STOP-key to get back to BASIC then.

Sending DOS commands
--------------------

@<DOS command string> sends your command to the device's command channel. This text is not interpreted by the wedge, so the result depends on what your drive understands.

These Commodore DOS commands are available (your device may support some others too):

     @C:newfile=existingfile

Copy a file on the same diskette


     @I

Initialize the disk drive. Rarely needed as the drive usually does this on its own if it has a door switch.


     @N:diskname

New a disk that was already formatted


     @N:diskname,id

Format (new) a diskette, giving it an index at your choice


     @R:newname=oldname

Rename a file


     @S:file1[,file2 ...]

Scratch a file (or files). Wild cards are allowed!
Read the status channel with @ to see how many files were scratched.


     @UJ

Reset the disk drive. Read the status channel with @ to get the DOS version string.


     @V

Validate a disk: reconcile the BAM with the disk directory, allocate all used blocks and free all blocks not being used by files, and delete all unclosed files from the directory.


     @D1=0

Duplicate an entire disk. Only available in dual drive units. The target(!) drive number comes first, then the source drive number.

Downloads
---------

http://petsd.net/wedge.php

