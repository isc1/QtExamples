# QtExamples/QtWorker2GUIThreadSync

![QtExamples/QtWorker2GUIThreadSync](/res/img/Girlie-blep.jpg)

A simple example of how to have a worker thread that performs the application logic, which is represented graphically in the GUI MainWindow.cpp thread, and how to do basic synchronization between these two threads so the whole thing doesn't crash, and the data doesn't get corrupted, and all that kind of stuff.  This is basically a two-way (or circular) producer-consumer arrangement.

The GUI MainWindow.cpp thread is the only thread that can change Qt GUI/Widget type display stuff.  Other threads are not permitted to do that.

The Application.cpp thread performs the application logic.  When the app logic causes a change that needs to be reflected in GUI objects, then the app logic data member that has GUI stuff associated with it gets it's new GUI info added to object.guiDatamember member variables (e.g. object.guiNewX = 100;), and the app object gets added to a GUIUpdateQueue.

The GUI MainWindow.cpp thread reads from this queue and updates the GUI stuff.  The GUI thread also receives user input and other events, and adds them to an ApplicationInput queue, for the app thread to process.

We also need a facility that allows the App thread to inform the GUI thread that new app objects have been created, and request that they be giving the correct GUI object.  When an App thread object is destroyed, we need to be able to inform the GUI thread, so that it can remove the associated GUI object(s).

We also need some sanity checking, for example, we will have a chaos monkey that randomly deletes GUI thread objects and App thread objects every so often.  Then our sanity checker will detect that these objects were deleted, and will remake them and issue the correct queue messages to ensure that they are remade properly in both the GUI thread and the App thread.  This would require a separate copy of all the GUI thread graphical objects, and all the App thread business logic objects, and a means of detecting whether objects were properly deleted.  This may be a bad or unnecessary idea, so we should think it through before we spend time trying to implement it.

On the other hand, it is definitely a good idea to try to address the issue of data synchronization between threads, and how to keep that orderly and healthy, and the sanity checking just discussed might be a good way to explore that.

#TODO

* go read about producer-consumer so I don't do anything obviously stupid


_This code is copyright 2019 inhabited.systems and is shared under the [MIT License](https://choosealicense.com/licenses/mit/) which means you can use it without asking me._

_This code was written on Desktop Qt 5.13.0 MinGW 64-bit (Windows), and might require modification to run properly on other versions of Qt or on other platforms such as Linux or MacOS._

THIS CODE IS UNSUPPORTED and no one is available to respond to questions or comments about it.

![Girlie Blep](/res/img/WhichIsNice.jpg) 