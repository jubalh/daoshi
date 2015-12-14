# Creating Lessons

All lessons reside in `~/.local/share/daoshi/lessons`.
The name of the folder will determine the lessons name.
It is expected to contain a `content.xml` compatible with the XML schema which can be found in the resources subfolder of the source code, the audio and image files.

## Characters
The image files need to be GIF files which can be obtained from the [Stroke Order Project](https://commons.wikimedia.org/wiki/Commons:Stroke_Order_Project). It will display a character and show the stroke order.
Whenever there is a character missing it is encouraged not just to create the GIF for oneself but upload it and thus contribute to the Stroke Order Project.

A good resource which will find more use in later versions is the [CC-CEDICT](http://cc-cedict.org/wiki/). It can help you with creating new lessons. [MDBG](http://www.mdbg.net/chindict/chindict.php) makes use of the CC-CEDICT.

## Audio
You can get audio lessons licensed under the Creative Commons license from:

 * [stooka](http://shtooka.net)

Just search for the word in the bar, top right. Click on *Download* -> *Ogg Vorbis*
As an example I did this for the word *hao* and got this URL: http://packs.shtooka.net/cmn-balm-hsk1/ogg/cmn-0833556b.ogg
Now remoove the filename and last directory to get http://packs.shtooka.net/cmn-balm-hsk1/ in which you should a file called `readme.txt`. Check whether it uses a free license (which most of them do).

 * [tatoeba](http://tatoeba.org)

It is encouraged to use OGG vorbis.
If you create any new audio files please contribute to one of the above mentioned projects too and upload it there for others to use.

## Example
For an example lesson please take a look at [this](https://github.com/jubalh/daoshi-test-lesson).
